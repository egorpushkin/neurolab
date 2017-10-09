/*--------------------------------------------------------------------*
 *    SRFFT.C  -  Split-Radix Fast Fourier Transform                  *
 *                                                                    *
 *    This is a decimation-in-frequency version, using the steps      *
 *    of the algorithm as described in Section 2.5.                   *
 *                                                                    *
 *    Author:  Henrique S. Malvar.                                    *
 *    Date:    October 8, 1991.                                       *
 *                                                                    *
 *    Usage:   srfft(xr, xi, logm);   --  for direct DFT              *
 *             srifft(xr, xi, logm);  --  for inverse DFT             *
 *                                                                    *
 *    Arguments:  xr (float)  - input and output vector, length M,    *
 *                              real part.                            *
 *                xi (float)  - imaginary part.                       *
 *                logm (int)  - log (base 2) of vector length M,      *
 *                              e.g., for M = 256 -> logm = 8.        *
 *--------------------------------------------------------------------*/

#include "StdAfx.h"
#include "SRFFT.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define  MAXLOGM     11    /* max FFT length = 2^MAXLOGM */
#define  TWOPI       6.28318530717958647692
#define  SQHALF      0.707106781186547524401
 
/*--------------------------------------------------------------------*
 *    Data unshuffling according to bit-reversed indexing.            *
 *                                                                    *
 *    Bit reversal is done using Evan's algorithm (Ref: D. M. W.      *
 *    Evans, "An improved digit-reversal permutation algorithm ...",  *
 *    IEEE Trans. ASSP, Aug. 1987, pp. 1120-1125).                    *
 *--------------------------------------------------------------------*/
 
static   int   brseed[256];   /* Evans' seed table */
static   int   brsflg;        /* flag for table building */
 
void BR_permute(float *x, int logm)
{
   int      i, j, imax, lg2, n;
   int      off, fj, gno, *brp;
   float    tmp, *xp, *xq;
 
   lg2 = logm >> 1;
   n = 1 << lg2;
   if (logm & 1) lg2++;
 
   /* Create seed table if not yet built */
   if (brsflg != logm) {
      brsflg = logm;
      brseed[0] = 0;
      brseed[1] = 1;
      for (j = 2; j <= lg2; j++) {
         imax = 1 << (j - 1);
         for (i = 0; i < imax; i++) {
            brseed[i] <<= 1;
            brseed[i + imax] = brseed[i] + 1;
         }
      }
   }
 
   /* Unshuffling loop */
   for (off = 1; off < n; off++) {
      fj = n * brseed[off]; i = off; j = fj;
      tmp = x[i]; x[i] = x[j]; x[j] = tmp;
      xp = &x[i];
      brp = &brseed[1];
      for (gno = 1; gno < brseed[off]; gno++) {
         xp += n;
         j = fj + *brp++;
         xq = x + j;
         tmp = *xp; *xp = *xq; *xq = tmp;
      }
   }
}
 
/*--------------------------------------------------------------------*
 *    Recursive part of the SRFFT algorithm.                          *
 *--------------------------------------------------------------------*/
 
void srrec(float *xr, float *xi, int logm)
{
   static   int      m, m2, m4, m8, nel, n;
   static   float    *xr1, *xr2, *xi1, *xi2;
   static   float    *cn, *spcn, *smcn, *c3n, *spc3n, *smc3n;
   static   float    tmp1, tmp2, ang, c, s;
   static   float    *tab[MAXLOGM];
 
   /* Check range of logm */
   if ((logm < 0) || (logm > MAXLOGM)) {
	   return;
   }
 
   /* Compute trivial cases */
   if (logm < 3) {
      if (logm == 2) {  /* length m = 4 */
         xr2  = xr + 2;
         xi2  = xi + 2;
         tmp1 = *xr + *xr2;
         *xr2 = *xr - *xr2;
         *xr  = tmp1;
         tmp1 = *xi + *xi2;
         *xi2 = *xi - *xi2;
         *xi  = tmp1;
         xr1  = xr + 1;
         xi1  = xi + 1;
         xr2++;
         xi2++;
         tmp1 = *xr1 + *xr2;
         *xr2 = *xr1 - *xr2;
         *xr1 = tmp1;
         tmp1 = *xi1 + *xi2;
         *xi2 = *xi1 - *xi2;
         *xi1 = tmp1;
         xr2  = xr + 1;
         xi2  = xi + 1;
         tmp1 = *xr + *xr2;
         *xr2 = *xr - *xr2;
         *xr  = tmp1;
         tmp1 = *xi + *xi2;
         *xi2 = *xi - *xi2;
         *xi  = tmp1;
         xr1  = xr + 2;
         xi1  = xi + 2;
         xr2  = xr + 3;
         xi2  = xi + 3;
         tmp1 = *xr1 + *xi2;
         tmp2 = *xi1 + *xr2;
         *xi1 = *xi1 - *xr2;
         *xr2 = *xr1 - *xi2;
         *xr1 = tmp1;
         *xi2 = tmp2;
         return;
      }
      else if (logm == 1) {   /* length m = 2 */
         xr2  = xr + 1;
         xi2  = xi + 1;
         tmp1 = *xr + *xr2;
         *xr2 = *xr - *xr2;
         *xr  = tmp1;
         tmp1 = *xi + *xi2;
         *xi2 = *xi - *xi2;
         *xi  = tmp1;
         return;
      }
      else if (logm == 0) return;   /* length m = 1 */
   }
 
   /* Compute a few constants */
   m = 1 << logm; m2 = m / 2; m4 = m2 / 2; m8 = m4 /2;
 
   /* Build tables of butterfly coefficients, if necessary */
   if ((logm >= 4) && (tab[logm-4] == NULL)) {
 
      /* Allocate memory for tables */
      nel = m4 - 2;
      if ((tab[logm-4] = (float *) calloc(6 * nel, sizeof(float))) == NULL) {
         return;
      }
 
      /* Initialize pointers */
      cn  = tab[logm-4]; spcn  = cn + nel;  smcn  = spcn + nel;
      c3n = smcn + nel;  spc3n = c3n + nel; smc3n = spc3n + nel;
 
      /* Compute tables */
      for (n = 1; n < m4; n++) {
         if (n == m8) continue;
         ang = n * TWOPI / m;
         c = cos(ang); s = sin(ang);
         *cn++ = c; *spcn++ = - (s + c); *smcn++ = s - c;
         ang = 3 * n * TWOPI / m;
         c = cos(ang); s = sin(ang);
         *c3n++ = c; *spc3n++ = - (s + c); *smc3n++ = s - c;
      }
   }
 
   /* Step 1 */
   xr1 = xr; xr2 = xr1 + m2;
   xi1 = xi; xi2 = xi1 + m2;
   for (n = 0; n < m2; n++) {
      tmp1 = *xr1 + *xr2;
      *xr2 = *xr1 - *xr2;
      *xr1 = tmp1;
      tmp2 = *xi1 + *xi2;
      *xi2 = *xi1 - *xi2;
      *xi1 = tmp2;
      xr1++; xr2++; xi1++; xi2++;
   }
 
   /* Step 2 */
   xr1 = xr + m2; xr2 = xr1 + m4;
   xi1 = xi + m2; xi2 = xi1 + m4;
   for (n = 0; n < m4; n++) {
      tmp1 = *xr1 + *xi2;
      tmp2 = *xi1 + *xr2;
      *xi1 = *xi1 - *xr2;
      *xr2 = *xr1 - *xi2;
      *xr1 = tmp1;
      *xi2 = tmp2;
      xr1++; xr2++; xi1++; xi2++;
   }
 
   /* Steps 3 & 4 */
   xr1 = xr + m2; xr2 = xr1 + m4;
   xi1 = xi + m2; xi2 = xi1 + m4;
   if (logm >= 4) {
      nel = m4 - 2;
      cn  = tab[logm-4]; spcn  = cn + nel;  smcn  = spcn + nel;
      c3n = smcn + nel;  spc3n = c3n + nel; smc3n = spc3n + nel;
   }
   xr1++; xr2++; xi1++; xi2++;
   for (n = 1; n < m4; n++) {
      if (n == m8) {
         tmp1 =  SQHALF * (*xr1 + *xi1);
         *xi1 =  SQHALF * (*xi1 - *xr1);
         *xr1 =  tmp1;
         tmp2 =  SQHALF * (*xi2 - *xr2);
         *xi2 = -SQHALF * (*xr2 + *xi2);
         *xr2 =  tmp2;
      } else {
         tmp2 = *cn++ * (*xr1 + *xi1);
         tmp1 = *spcn++ * *xr1 + tmp2;
         *xr1 = *smcn++ * *xi1 + tmp2;
         *xi1 = tmp1;
         tmp2 = *c3n++ * (*xr2 + *xi2);
         tmp1 = *spc3n++ * *xr2 + tmp2;
         *xr2 = *smc3n++ * *xi2 + tmp2;
         *xi2 = tmp1;
      }
      xr1++; xr2++; xi1++; xi2++;
   }
 
   /* Call ssrec again with half DFT length */
   srrec(xr, xi, logm-1);
 
   /* Call ssrec again twice with one quarter DFT length.
      Constants have to be recomputed, because they are static! */
   m = 1 << logm; m2 = m / 2;
   srrec(xr + m2, xi + m2, logm-2);
   m = 1 << logm; m4 = 3 * (m / 4);
   srrec(xr + m4, xi + m4, logm-2);
}
 
/*--------------------------------------------------------------------*
 *    Direct transform                                                *
 *--------------------------------------------------------------------*/
 
void  srfft(float *xr, float *xi, int logm)
{
   /* Call recursive routine */
   srrec(xr, xi, logm);
 
   /* Output array unshuffling using bit-reversed indices */
   if (logm > 1) {
      BR_permute(xr, logm);
      BR_permute(xi, logm);
   }
}
 
/*--------------------------------------------------------------------*
 *    Inverse transform.  Uses Duhamel's trick (Ref: P. Duhamel       *
 *    et. al., "On computing the inverse DFT", IEEE Trans. ASSP,      *
 *    Feb. 1988, pp. 285-286).                                        *
 *--------------------------------------------------------------------*/
 
void  srifft(float *xr, float *xi, int logm)
{
   int      i, m;
   float    fac, *xrp, *xip;
 
   /* Call direct FFT, swapping real & imaginary addresses */
   srfft(xi, xr, logm);
 
   /* Normalization */
   m = 1 << logm;
   fac = 1.0 / m;
   xrp = xr; xip = xi;
   for (i = 0; i < m; i++) {
      *xrp++ *= fac;
      *xip++ *= fac;
   }
}
