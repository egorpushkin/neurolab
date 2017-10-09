#include "StdAfx.h"
#include "fft.h"

#include <math.h>
#include "general.h"
#include "Complex.h"

#define TRIG_VARS                 	\
	ulong TLen,TNdx;int TDir;	\
	Complex PRoot,Root;

#define INIT_TRIG(LENGTH,DIR)    		\
	TNdx=0;TLen=(LENGTH);TDir=(DIR);    	\
	PRoot.r=1.0;PRoot.i=0.0;          	\
	Root.r=sin(CONST_PI/((LENGTH)*2.0)); 	\
	Root.r=-2.0*Root.r*Root.r;         	\
	Root.i=sin(CONST_PI/(LENGTH))*(DIR);

#define NEXT_TRIG_POW               			\
	if (((++TNdx)&15)==0) {            		\
		real Angle=(CONST_PI*(TNdx))/TLen;      \
		PRoot.r=sin(Angle*0.5);         	\
		PRoot.r=1.0-2.0*PRoot.r*PRoot.r;	\
		PRoot.i=sin(Angle)*(TDir);      	\
	} else {             				\
		Complex Temp;                     	\
		Temp=PRoot;                     	\
		PRoot = PRoot*Root;     		\
		PRoot = PRoot+Temp;     		\
	}


inline ulong rev_next(ulong r, ulong n) { 
	do {
		n = n >> 1;
		r = r^n;
	} while ( (r&n) == 0);
	return r;
}


void FFTReOrder(Complex *Data, ulong Len) {
	Complex temp;
	if (Len <= 2) return;
	ulong r=0;
	for ( ulong x=1; x<Len; x++) {
		r = rev_next(r, Len);
		if (r>x) { temp=Data[x]; Data[x]=Data[r]; Data[r]=temp; } 
	}
}


void IFFT_T(Complex *Data, ulong Len, int Dir) {
	ulong Step, HalfStep;
	ulong b;
	TRIG_VARS;

	Step = 1;
	while (Step < Len) {
		HalfStep = Step;
		Step *= 2;

		INIT_TRIG(HalfStep,Dir);

		for (b = 0; b < HalfStep; b++) {
			ulong L,R;
			for (L=b; L<Len; L+=Step) {
				Complex TRight,TLeft;
				R=L+HalfStep;
				TLeft=Data[L];TRight=Data[R];
				TRight  = TRight * PRoot;
				Data[L] = TLeft + TRight;
				Data[R] = TLeft - TRight;
			}
			NEXT_TRIG_POW;
		}

	}
}


void FFT_T(Complex *Data, ulong Len, int Dir) {
	ulong k;

	TRIG_VARS;

	if (Len <= (CACHE_HALF/sizeof(Complex)) ) {
		IFFT_T(Data, Len,Dir);
		return;
	}

	Len /= 2;

	INIT_TRIG(Len, Dir);

	FFT_T(Data,    Len,Dir);
	FFT_T(Data+Len,Len,Dir);

	for (k=0; k<Len; k++) {
		Complex b,c;
		b=Data[k];
		c = Data[k+Len] * PRoot;
		Data[k] = b + c;
		Data[k+Len] = b - c;
		NEXT_TRIG_POW;
	}
}



void RealFFT(real *ddata, ulong Len, int Dir) {
	ulong i, j;
	Complex *Data=(Complex*)ddata;
	TRIG_VARS;

	Len /= 2;

	if (Dir > 0) {
		FFTReOrder(Data,Len);
		FFT_T(Data,Len,1);
	}

	INIT_TRIG(Len,Dir);
	NEXT_TRIG_POW;

	for (i = 1, j = Len - i; i < Len/2; i++, j--) {
    		Complex p1,p2,t;
		t = conj(Data[j]);
		p1 = Data[i] + t;
		p2 = Data[i] - t;
		p2 = p2 * PRoot;

		t = Complex(-Dir*p2.i,Dir*p2.r);

		Data[i] = p1 - t;
		Data[j] = p1 + t;
		Data[j] = conj(Data[j]);

		Data[i] = Data[i]/2;
		Data[j] = Data[j]/2;

		NEXT_TRIG_POW;
	}

	{	real r,i;
		r=Data[0].r;i=Data[0].i;
		Data[0] = Complex(r+i,r-i);
	}

	if (Dir < 0) {
		Data[0] = Data[0]/2.0;
		FFTReOrder(Data,Len);
		FFT_T(Data,Len,-1);
	}
}

