/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __fann_activation_h__
#define __fann_activation_h__
/* internal include file, not to be included directly
 */

/* The possible activation functions.
   They are described with functions,
   where x is the input to the activation function,
   y is the output,
   s is the steepness and
   d is the derivation.
 */

enum {
	/* Linear activation function.
	   span: -inf < y < inf
	   y = x*s, d = 1*s
	   Can NOT be used in fixed point.
	*/
	FANN_LINEAR = 0,

	/* Threshold activation function.
	   x < 0 -> y = 0, x >= 0 -> y = 1
	   Can NOT be used during training.
	*/
	FANN_THRESHOLD,

	/* Threshold activation function.
	   x < 0 -> y = 0, x >= 0 -> y = 1
	   Can NOT be used during training.
	*/
	FANN_THRESHOLD_SYMMETRIC,

	/* Sigmoid activation function.
	   One of the most used activation functions.
	   span: 0 < y < 1
	   y = 1/(1 + exp(-2*s*x)), d = 2*s*y*(1 - y)
	*/
	FANN_SIGMOID,

	/* Stepwise linear approximation to sigmoid.
	   Faster than sigmoid but a bit less precise.
	*/
	FANN_SIGMOID_STEPWISE, /* (default) */


	/* Symmetric sigmoid activation function, aka. tanh.
	   One of the most used activation functions.
	   span: -1 < y < 1
	   y = tanh(s*x) = 2/(1 + exp(-2*s*x)) - 1, d = s*(1-(y*y))
	*/
	FANN_SIGMOID_SYMMETRIC,
	
	/* Stepwise linear approximation to symmetric sigmoid.
	   Faster than symmetric sigmoid but a bit less precise.
	*/
	FANN_SIGMOID_SYMMETRIC_STEPWISE,

	/* Gausian activation function.
	   0 when x = -inf, 1 when x = 0 and 0 when x = inf
	   span: 0 < y < 1
	   y = exp(-x*s*x*s), d = -2*x*y*s
	*/
	FANN_GAUSSIAN,

	/* Stepwise linear approximation to gaussian.
	   Faster than gaussian but a bit less precise.
	   NOT implemented yet.
	*/
	FANN_GAUSSIAN_STEPWISE,

	/* Fast (sigmoid like) activation function defined by David Elliott
	   span: 0 < y < 1
	   y = ((x*s) / 2) / (1 + |x*s|) + 0.5, d = s*1/(2*(1+|x|)*(1+|x|))
	   NOT implemented yet.
	*/
	FANN_ELLIOT,

	/* Fast (symmetric sigmoid like) activation function defined by David Elliott
	   span: -1 < y < 1   
	   y = (x*s) / (1 + |x*s|), d = s*1/((1+|x|)*(1+|x|))
	   NOT implemented yet.
	*/
	FANN_ELLIOT_SYMMETRIC
};

static char const * const FANN_ACTIVATION_NAMES[] = {
	"FANN_LINEAR",
	"FANN_THRESHOLD",
	"FANN_THRESHOLD_SYMMETRIC",
	"FANN_SIGMOID",
	"FANN_SIGMOID_STEPWISE",
	"FANN_SIGMOID_SYMMETRIC",
	"FANN_SIGMOID_SYMMETRIC_STEPWISE",
	"FANN_GAUSSIAN",
	"FANN_GAUSSIAN_STEPWISE",
	"FANN_ELLIOT",
	"FANN_ELLIOT_SYMMETRIC"
};

/* Implementation of the activation functions
 */

/* stepwise linear functions used for some of the activation functions */

/* defines used for the stepwise linear functions */

#define fann_linear_func(v1, r1, v2, r2, value) ((((r2-r1) * (value-v1))/(v2-v1)) + r1)
#define fann_stepwise(v1, v2, v3, v4, v5, v6, r1, r2, r3, r4, r5, r6, min, max, value) (value < v5 ? (value < v3 ? (value < v2 ? (value < v1 ? min : fann_linear_func(v1, r1, v2, r2, value)) : fann_linear_func(v2, r2, v3, r3, value)) : (value < v4 ? fann_linear_func(v3, r3, v4, r4, value) : fann_linear_func(v4, r4, v5, r5, value))) : (value < v6 ? fann_linear_func(v5, r5, v6, r6, value) : max))

/* FANN_LINEAR */
#define fann_linear(steepness, value) fann_mult(steepness, value)
#define fann_linear_derive(steepness, value) (steepness)

/* FANN_SIGMOID */
#define fann_sigmoid(steepness, value) (1.0f/(1.0f + exp(-2.0f * steepness * value)))
#define fann_sigmoid_derive(steepness, value) (2.0f * steepness * value * (1.0f - value)) /* the plus is a trick to the derived function, to avoid getting stuck on flat spots */

/* FANN_SIGMOID_SYMMETRIC */
#define fann_sigmoid_symmetric(steepness, value) (2.0f/(1.0f + exp(-2.0f * steepness * value)) - 1.0f)
#define fann_sigmoid_symmetric_derive(steepness, value) steepness * (1.0f - (value*value))

/* FANN_GAUSSIAN */
#define fann_gaussian(steepness, value) (exp(-value * steepness * value * steepness))

#endif
