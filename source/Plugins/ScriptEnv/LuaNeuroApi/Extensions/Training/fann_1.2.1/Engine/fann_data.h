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

#ifndef __fann_data_h__
#define __fann_data_h__

#include <stdio.h>

/* ----- Data structures -----
 * No data within these structures should be altered directly by the user.
 */

struct fann_neuron
{
	fann_type *weights;
	struct fann_neuron **connected_neurons;
	unsigned int num_connections;
	fann_type value;
#ifdef __GNUC__
}__attribute__((packed));
#else
};
#endif

/* A single layer in the neural network.
 */
struct fann_layer
{
	/* A pointer to the first neuron in the layer 
	 * When allocated, all the neurons in all the layers are actually
	 * in one long array, this is because we wan't to easily clear all
	 * the neurons at once.
	 */
	struct fann_neuron *first_neuron;

	/* A pointer to the neuron past the last neuron in the layer */
	/* the number of neurons is last_neuron - first_neuron */
	struct fann_neuron *last_neuron;
};

/* The fast artificial neural network(fann) structure
 */
struct fann
{
	/* The type of error that last occured. */
	unsigned int errno_f;

	/* Where to log error messages. */
	FILE *error_log;

	/* A string representation of the last error. */
	char * errstr;

	/* the learning rate of the network */
	float learning_rate;

	/* the connection rate of the network
	 * between 0 and 1, 1 meaning fully connected
	 */
	float connection_rate;

	/* is 1 if shortcut connections are used in the ann otherwise 0
	 * Shortcut connections are connections that skip layers.
	 * A fully connected ann with shortcut connections are a ann where
	 * neurons have connections to all neurons in all later layers.
	 */
	unsigned int shortcut_connections;

	/* pointer to the first layer (input layer) in an array af all the layers,
	 * including the input and outputlayers 
	 */
	struct fann_layer *first_layer;

	/* pointer to the layer past the last layer in an array af all the layers,
	 * including the input and outputlayers 
	 */
	struct fann_layer *last_layer;

	/* Total number of neurons.
	 * very usefull, because the actual neurons are allocated in one long array
	 */
	unsigned int total_neurons;

	/* Number of input neurons (not calculating bias) */
	unsigned int num_input;

	/* Number of output neurons (not calculating bias) */
	unsigned int num_output;

	/* Used to contain the errors used during training
	 * Is allocated during first training session,
	 * which means that if we do not train, it is never allocated.
	 */
	fann_type *train_errors;

	/* Used to choose which activation function to use
	   
	   Sometimes it can be smart, to set the activation function for the hidden neurons
	   to FANN_THRESHOLD and the activation function for the output neurons to FANN_SIGMOID,
	   in this way you get a very fast network, that is still cabable of
	   producing real valued output.
	 */
	unsigned int activation_function_hidden, activation_function_output;

	/* Parameters for the activation function */
	fann_type activation_steepness_hidden;
	fann_type activation_steepness_output;

	/* Training algorithm used when calling fann_train_on_..
	 */
	unsigned int training_algorithm;

#ifdef FIXEDFANN
	/* the decimal_point, used for shifting the fix point
	   in fixed point integer operatons.
	*/
	unsigned int decimal_point;
	
	/* the multiplier, used for multiplying the fix point
	   in fixed point integer operatons.
	   Only used in special cases, since the decimal_point is much faster.
	*/
	unsigned int multiplier;
#endif

	/* When in choosen (or in fixed point), the sigmoid function is
	   calculated as a stepwise linear function. In the
	   activation_results array, the result is saved, and in the
	   two values arrays, the values that gives the results are saved.
	 */
	fann_type activation_results_hidden[6];
	fann_type activation_values_hidden[6];
	fann_type activation_results_output[6];
	fann_type activation_values_output[6];

	/* Total number of connections.
	 * very usefull, because the actual connections
	 * are allocated in one long array
	 */
	unsigned int total_connections;

	/* used to store outputs in */
	fann_type *output;

	/* the number of data used to calculate the mean square error.
	 */
	unsigned int num_MSE;

	/* the total error value.
	   the real mean square error is MSE_value/num_MSE
	 */
	float MSE_value;

	/* The error function used during training. (default FANN_ERRORFUNC_TANH)
	 */
	unsigned int train_error_function;
	
	/* Variables for use with Cascade Correlation */

	/* The error must change by at least this
	   fraction of its old value to count as a
	   significant change. NOT IMPLEMENTED YET
	*/
	/* float change_fraction; */

	/* No change in this number of epochs will cause
	   stagnation. NOT IMPLEMENTED YET
	*/
	/* unsigned int stagnation_epochs; */

	/* Variables for use with Quickprop training */

	/* Decay is used to make the weights not go so high */
	float quickprop_decay;

	/* Mu is a factor used to increase and decrease the stepsize */
	float quickprop_mu;

	/* Variables for use with with RPROP training */

	/* Tells how much the stepsize should increase during learning */
	float rprop_increase_factor;

	/* Tells how much the stepsize should decrease during learning */
	float rprop_decrease_factor;

	/* The minimum stepsize */
	float rprop_delta_min;

	/* The maximum stepsize */
	float rprop_delta_max;
	
	/* Used to contain the slope errors used during batch training
	 * Is allocated during first training session,
	 * which means that if we do not train, it is never allocated.
	 */
	fann_type *train_slopes;

	/* The previous step taken by the quickprop/rprop procedures.
	   Not allocated if not used.
	 */
	fann_type *prev_steps;

	/* The slope values used by the quickprop/rprop procedures.
	   Not allocated if not used.
	 */
	fann_type *prev_train_slopes;
};

/* Structure used to store data, for use with training. */
struct fann_train_data
{
	unsigned int errno_f;
	FILE *error_log;
	char *errstr;

	unsigned int num_data;
	unsigned int num_input;
	unsigned int num_output;
	fann_type **input;
	fann_type **output;
};

/* Structure used to store error-related information */
struct fann_error
{
	unsigned int errno_f;
	FILE *error_log;
	char * errstr;
};

enum {
	/* Standard backpropagation incremental or online training */
	FANN_TRAIN_INCREMENTAL = 0,
	/* Standard backpropagation batch training */
	FANN_TRAIN_BATCH,
	/* The iRprop- training algorithm */
	FANN_TRAIN_RPROP,
	/* The quickprop training algorithm */
	FANN_TRAIN_QUICKPROP
};

static char const * const FANN_TRAIN_NAMES[] = {
	"FANN_TRAIN_INCREMENTAL",
	"FANN_TRAIN_BATCH",
	"FANN_TRAIN_RPROP",
	"FANN_TRAIN_QUICKPROP"
};

enum {
	/* Standard linear error function */
	FANN_ERRORFUNC_LINEAR = 0,
	/* Tanh error function, usually better but can require
	   a lower learning rate */
	FANN_ERRORFUNC_TANH
};

static char const * const FANN_ERRORFUNC_NAMES[] = {
	"FANN_ERRORFUNC_LINEAR",
	"FANN_ERRORFUNC_TANH"
};

#endif
