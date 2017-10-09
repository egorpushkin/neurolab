#pragma once

#include "Complex.h"

// Transformation routines
void IFFT_T(Complex *Data, ulong Len, int Dir);
void FFT_T(Complex *Data, ulong Len, int Dir);

// Real FFT transform
void RealFFT(real *ddata, ulong Len, int Dir);

// Engine tools
void FFTReOrder(Complex *Data, ulong Len);
