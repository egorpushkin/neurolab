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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "config.h"
#include "fann.h"
#include "fann_errno.h"

/* Prints all of the parameters and options of the ANN */
FANN_EXTERNAL void FANN_API fann_print_parameters(struct fann *ann)
{
	struct fann_layer *layer_it;
	
	printf("Input layer                : %2d neurons, 1 bias\n", ann->num_input);
	for(layer_it = ann->first_layer+1; layer_it != ann->last_layer-1; layer_it++){
		printf("  Hidden layer             : %2d neurons, 1 bias\n",
			layer_it->last_neuron - layer_it->first_neuron - 1);
	}
	printf("Output layer               : %2d neurons\n", ann->num_output);
	printf("Total neurons and biases   : %2d\n", fann_get_total_neurons(ann));
	printf("Total connections          : %2d\n", ann->total_connections);
	printf("Connection rate            : %5.2f\n", ann->connection_rate);
	printf("Shortcut connections        : %2d\n", ann->shortcut_connections);
	printf("Training algorithm         :  %s\n", FANN_TRAIN_NAMES[ann->training_algorithm]);	
	printf("Learning rate              : %5.2f\n", ann->learning_rate);
	printf("Activation function hidden :  %s\n", FANN_ACTIVATION_NAMES[ann->activation_function_hidden]);
	printf("Activation function output :  %s\n", FANN_ACTIVATION_NAMES[ann->activation_function_output]);
#ifndef FIXEDFANN
	printf("Activation steepness hidden: %5.2f\n", ann->activation_steepness_hidden);
	printf("Activation steepness output: %5.2f\n", ann->activation_steepness_output);
#else
	printf("Activation steepness hidden: %d\n", ann->activation_steepness_hidden);
	printf("Activation steepness output: %d\n", ann->activation_steepness_output);
	printf("Decimal point              : %2d\n", ann->decimal_point);
	printf("Multiplier                 : %2d\n", ann->multiplier);
#endif
	printf("Training error function    :  %s\n", FANN_ERRORFUNC_NAMES[ann->train_error_function]);
	printf("Quickprop decay            : %9.6f\n", ann->quickprop_decay);
	printf("Quickprop mu               : %5.2f\n", ann->quickprop_mu);
	printf("RPROP increase factor      : %5.2f\n", ann->rprop_increase_factor);
	printf("RPROP decrease factor      : %5.2f\n", ann->rprop_decrease_factor);
	printf("RPROP delta min            : %5.2f\n", ann->rprop_delta_min);
	printf("RPROP delta max            : %5.2f\n", ann->rprop_delta_max);
}

FANN_EXTERNAL unsigned int FANN_API fann_get_training_algorithm(struct fann *ann)
{
	return ann->training_algorithm;
}

FANN_EXTERNAL void FANN_API fann_set_training_algorithm(struct fann *ann, unsigned int training_algorithm)
{
	ann->training_algorithm = training_algorithm;
}

FANN_EXTERNAL void FANN_API fann_set_learning_rate(struct fann *ann, float learning_rate)
{
	ann->learning_rate = learning_rate;
}

FANN_EXTERNAL void FANN_API fann_set_activation_function_hidden(struct fann *ann, unsigned int activation_function)
{
	ann->activation_function_hidden = activation_function;
	fann_update_stepwise_hidden(ann);
}

FANN_EXTERNAL void FANN_API fann_set_activation_function_output(struct fann *ann, unsigned int activation_function)
{
	ann->activation_function_output = activation_function;
	fann_update_stepwise_output(ann);
}

FANN_EXTERNAL void FANN_API fann_set_activation_steepness_hidden(struct fann *ann, fann_type steepness)
{
	ann->activation_steepness_hidden = steepness;
	fann_update_stepwise_hidden(ann);
}

FANN_EXTERNAL void FANN_API fann_set_activation_steepness_output(struct fann *ann, fann_type steepness)
{
	ann->activation_steepness_output = steepness;
	fann_update_stepwise_output(ann);
}

FANN_EXTERNAL void FANN_API fann_set_activation_hidden_steepness(struct fann *ann, fann_type steepness)
{
	fann_set_activation_steepness_hidden(ann, steepness);
}

FANN_EXTERNAL void FANN_API fann_set_activation_output_steepness(struct fann *ann, fann_type steepness)
{
	fann_set_activation_steepness_output(ann, steepness);
}

FANN_EXTERNAL float FANN_API fann_get_learning_rate(struct fann *ann)
{
	return ann->learning_rate;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_num_input(struct fann *ann)
{
	return ann->num_input;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_num_output(struct fann *ann)
{
	return ann->num_output;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_activation_function_hidden(struct fann *ann)
{
	return ann->activation_function_hidden;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_activation_function_output(struct fann *ann)
{
	return ann->activation_function_output;
}

FANN_EXTERNAL fann_type FANN_API fann_get_activation_hidden_steepness(struct fann *ann)
{
	return ann->activation_steepness_hidden;
}

FANN_EXTERNAL fann_type FANN_API fann_get_activation_output_steepness(struct fann *ann)
{
	return ann->activation_steepness_output;
}

FANN_EXTERNAL fann_type FANN_API fann_get_activation_steepness_hidden(struct fann *ann)
{
	return ann->activation_steepness_hidden;
}

FANN_EXTERNAL fann_type FANN_API fann_get_activation_steepness_output(struct fann *ann)
{
	return ann->activation_steepness_output;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_total_neurons(struct fann *ann)
{
	/* -1, because there is always an unused bias neuron in the last layer */
	return ann->total_neurons - 1;
}

FANN_EXTERNAL unsigned int FANN_API fann_get_total_connections(struct fann *ann)
{
	return ann->total_connections;
}

fann_type * fann_get_weights(struct fann *ann)
{
	return (ann->first_layer+1)->first_neuron->weights;
}

struct fann_neuron** fann_get_connections(struct fann *ann)
{
	return (ann->first_layer+1)->first_neuron->connected_neurons;
}


/* When using this, training is usually faster. (default ).
   Makes the error used for calculating the slopes
   higher when the difference is higher.
 */
FANN_EXTERNAL void FANN_API fann_set_train_error_function(struct fann *ann, unsigned int train_error_function)
{
	ann->train_error_function = train_error_function;
}

/* Decay is used to make the weights do not go so high (default -0.0001). */
FANN_EXTERNAL void FANN_API fann_set_quickprop_decay(struct fann *ann, float quickprop_decay)
{
	ann->quickprop_decay = quickprop_decay;
}
	
/* Mu is a factor used to increase and decrease the stepsize (default 1.75). */
FANN_EXTERNAL void FANN_API fann_set_quickprop_mu(struct fann *ann, float quickprop_mu)
{
	ann->quickprop_mu = quickprop_mu;
}

/* Tells how much the stepsize should increase during learning (default 1.2). */
FANN_EXTERNAL void FANN_API fann_set_rprop_increase_factor(struct fann *ann, float rprop_increase_factor)
{
	ann->rprop_increase_factor = rprop_increase_factor;
}

/* Tells how much the stepsize should decrease during learning (default 0.5). */
FANN_EXTERNAL void FANN_API fann_set_rprop_decrease_factor(struct fann *ann, float rprop_decrease_factor)
{
	ann->rprop_decrease_factor = rprop_decrease_factor;
}

/* The minimum stepsize (default 0.0). */
FANN_EXTERNAL void FANN_API fann_set_rprop_delta_min(struct fann *ann, float rprop_delta_min)
{
	ann->rprop_delta_min = rprop_delta_min;
}

/* The maximum stepsize (default 50.0). */
FANN_EXTERNAL void FANN_API fann_set_rprop_delta_max(struct fann *ann, float rprop_delta_max)
{
	ann->rprop_delta_max = rprop_delta_max;
}

/* When using this, training is usually faster. (default ).
   Makes the error used for calculating the slopes
   higher when the difference is higher.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_train_error_function(struct fann *ann)
{
	return ann->train_error_function;
}

/* Decay is used to make the weights do not go so high (default -0.0001). */
FANN_EXTERNAL float FANN_API fann_get_quickprop_decay(struct fann *ann)
{
	return ann->quickprop_decay;
}
	
/* Mu is a factor used to increase and decrease the stepsize (default 1.75). */
FANN_EXTERNAL float FANN_API fann_get_quickprop_mu(struct fann *ann)
{
	return ann->quickprop_mu;
}

/* Tells how much the stepsize should increase during learning (default 1.2). */
FANN_EXTERNAL float FANN_API fann_get_rprop_increase_factor(struct fann *ann)
{
	return ann->rprop_increase_factor;
}

/* Tells how much the stepsize should decrease during learning (default 0.5). */
FANN_EXTERNAL float FANN_API fann_get_rprop_decrease_factor(struct fann *ann)
{
	return ann->rprop_decrease_factor;
}

/* The minimum stepsize (default 0.0). */
FANN_EXTERNAL float FANN_API fann_get_rprop_delta_min(struct fann *ann)
{
	return ann->rprop_delta_min;
}

/* The maximum stepsize (default 50.0). */
FANN_EXTERNAL float FANN_API fann_get_rprop_delta_max(struct fann *ann)
{
	return ann->rprop_delta_max;
}

#ifdef FIXEDFANN
/* returns the position of the fix point.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_decimal_point(struct fann *ann)
{
	return ann->decimal_point;
}

/* returns the multiplier that fix point data is multiplied with.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_multiplier(struct fann *ann)
{
	return ann->multiplier;
}

#endif

/* INTERNAL FUNCTION
   Adjust the steepwise functions (if used)
*/
void fann_update_stepwise_hidden(struct fann *ann)
{
	unsigned int i = 0;
#ifndef FIXEDFANN
	/* For use in stepwise linear activation function.
	   results 0.005, 0.05, 0.25, 0.75, 0.95, 0.995
	*/
	switch(ann->activation_function_hidden){
		case FANN_SIGMOID:
		case FANN_SIGMOID_STEPWISE:
			ann->activation_results_hidden[0] = (fann_type)0.005;
			ann->activation_results_hidden[1] = (fann_type)0.05;
			ann->activation_results_hidden[2] = (fann_type)0.25;
			ann->activation_results_hidden[3] = (fann_type)0.75;
			ann->activation_results_hidden[4] = (fann_type)0.95;
			ann->activation_results_hidden[5] = (fann_type)0.995;	
			break;
		case FANN_SIGMOID_SYMMETRIC:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:
			ann->activation_results_hidden[0] = (fann_type)-0.99;
			ann->activation_results_hidden[1] = (fann_type)-0.9;
			ann->activation_results_hidden[2] = (fann_type)-0.5;
			ann->activation_results_hidden[3] = (fann_type)0.5;
			ann->activation_results_hidden[4] = (fann_type)0.9;
			ann->activation_results_hidden[5] = (fann_type)0.99;
			break;
		default:
			/* the actiavation functions which do not have a stepwise function
			   should not have it calculated */
			return;
	}
#else
	/* Calculate the parameters for the stepwise linear
	   sigmoid function fixed point.
	   Using a rewritten sigmoid function.
	   results 0.005, 0.05, 0.25, 0.75, 0.95, 0.995
	*/
	switch(ann->activation_function_hidden){
		case FANN_SIGMOID:
		case FANN_SIGMOID_STEPWISE:
			ann->activation_results_hidden[0] = (fann_type)(ann->multiplier/200.0+0.5);
			ann->activation_results_hidden[1] = (fann_type)(ann->multiplier/20.0+0.5);
			ann->activation_results_hidden[2] = (fann_type)(ann->multiplier/4.0+0.5);
			ann->activation_results_hidden[3] = ann->multiplier - (fann_type)(ann->multiplier/4.0+0.5);
			ann->activation_results_hidden[4] = ann->multiplier - (fann_type)(ann->multiplier/20.0+0.5);
			ann->activation_results_hidden[5] = ann->multiplier - (fann_type)(ann->multiplier/200.0+0.5);
			break;
		case FANN_SIGMOID_SYMMETRIC:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:
			ann->activation_results_hidden[0] = (fann_type)((ann->multiplier/100.0) - ann->multiplier + 0.5);
			ann->activation_results_hidden[1] = (fann_type)((ann->multiplier/10.0) - ann->multiplier + 0.5);
			ann->activation_results_hidden[2] = (fann_type)((ann->multiplier/2.0) - ann->multiplier + 0.5);
			ann->activation_results_hidden[3] = ann->multiplier - (fann_type)(ann->multiplier/2.0+0.5);
			ann->activation_results_hidden[4] = ann->multiplier - (fann_type)(ann->multiplier/10.0+0.5);
			ann->activation_results_hidden[5] = ann->multiplier - (fann_type)(ann->multiplier/100.0+0.5);
			break;
		default:
			/* the actiavation functions which do not have a stepwise function
			   should not have it calculated */
			return;
	}			
#endif

	for(i = 0; i < 6; i++){
#ifndef FIXEDFANN
		switch(ann->activation_function_hidden){
			case FANN_SIGMOID:
				break;
			case FANN_SIGMOID_STEPWISE:
				ann->activation_values_hidden[i] = (fann_type)((log(1.0/ann->activation_results_hidden[i] -1.0) * 1.0/-2.0) * 1.0/ann->activation_steepness_hidden);
				break;
			case FANN_SIGMOID_SYMMETRIC:
			case FANN_SIGMOID_SYMMETRIC_STEPWISE:
				ann->activation_values_hidden[i] = (fann_type)((log((1.0-ann->activation_results_hidden[i]) / (ann->activation_results_hidden[i]+1.0)) * 1.0/-2.0) * 1.0/ann->activation_steepness_hidden);
				break;
		}
#else
		switch(ann->activation_function_hidden){
			case FANN_SIGMOID:
			case FANN_SIGMOID_STEPWISE:
				ann->activation_values_hidden[i] = (fann_type)((((log(ann->multiplier/(float)ann->activation_results_hidden[i] -1)*(float)ann->multiplier) / -2.0)*(float)ann->multiplier) / ann->activation_steepness_hidden);
				break;
			case FANN_SIGMOID_SYMMETRIC:
			case FANN_SIGMOID_SYMMETRIC_STEPWISE:
				ann->activation_values_hidden[i] = (fann_type)((((log((ann->multiplier - (float)ann->activation_results_hidden[i])/((float)ann->activation_results_hidden[i] + ann->multiplier))*(float)ann->multiplier) / -2.0)*(float)ann->multiplier) / ann->activation_steepness_hidden);
				break;
		}
#endif
	}
}

/* INTERNAL FUNCTION
   Adjust the steepwise functions (if used)
*/
void fann_update_stepwise_output(struct fann *ann)
{
	unsigned int i = 0;
#ifndef FIXEDFANN
	/* For use in stepwise linear activation function.
	   results 0.005, 0.05, 0.25, 0.75, 0.95, 0.995
	*/
	switch(ann->activation_function_output){
		case FANN_SIGMOID:
		case FANN_SIGMOID_STEPWISE:
			ann->activation_results_output[0] = (fann_type)0.005;
			ann->activation_results_output[1] = (fann_type)0.05;
			ann->activation_results_output[2] = (fann_type)0.25;
			ann->activation_results_output[3] = (fann_type)0.75;
			ann->activation_results_output[4] = (fann_type)0.95;
			ann->activation_results_output[5] = (fann_type)0.995;	
			break;
		case FANN_SIGMOID_SYMMETRIC:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:
			ann->activation_results_output[0] = (fann_type)-0.99;
			ann->activation_results_output[1] = (fann_type)-0.9;
			ann->activation_results_output[2] = (fann_type)-0.5;
			ann->activation_results_output[3] = (fann_type)0.5;
			ann->activation_results_output[4] = (fann_type)0.9;
			ann->activation_results_output[5] = (fann_type)0.99;
			break;
		default:
			/* the actiavation functions which do not have a stepwise function
			   should not have it calculated */
			return;
	}
#else
	/* Calculate the parameters for the stepwise linear
	   sigmoid function fixed point.
	   Using a rewritten sigmoid function.
	   results 0.005, 0.05, 0.25, 0.75, 0.95, 0.995
	*/
	switch(ann->activation_function_output){
		case FANN_SIGMOID:
		case FANN_SIGMOID_STEPWISE:
			ann->activation_results_output[0] = (fann_type)(ann->multiplier/200.0+0.5);
			ann->activation_results_output[1] = (fann_type)(ann->multiplier/20.0+0.5);
			ann->activation_results_output[2] = (fann_type)(ann->multiplier/4.0+0.5);
			ann->activation_results_output[3] = ann->multiplier - (fann_type)(ann->multiplier/4.0+0.5);
			ann->activation_results_output[4] = ann->multiplier - (fann_type)(ann->multiplier/20.0+0.5);
			ann->activation_results_output[5] = ann->multiplier - (fann_type)(ann->multiplier/200.0+0.5);
			break;
		case FANN_SIGMOID_SYMMETRIC:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:
			ann->activation_results_output[0] = (fann_type)((ann->multiplier/100.0) - ann->multiplier + 0.5);
			ann->activation_results_output[1] = (fann_type)((ann->multiplier/10.0) - ann->multiplier + 0.5);
			ann->activation_results_output[2] = (fann_type)((ann->multiplier/2.0) - ann->multiplier + 0.5);
			ann->activation_results_output[3] = ann->multiplier - (fann_type)(ann->multiplier/2.0+0.5);
			ann->activation_results_output[4] = ann->multiplier - (fann_type)(ann->multiplier/10.0+0.5);
			ann->activation_results_output[5] = ann->multiplier - (fann_type)(ann->multiplier/100.0+0.5);
			break;
		default:
			/* the actiavation functions which do not have a stepwise function
			   should not have it calculated */
			return;
	}			
#endif

	for(i = 0; i < 6; i++){
#ifndef FIXEDFANN
		switch(ann->activation_function_output){
			case FANN_SIGMOID:
				break;
			case FANN_SIGMOID_STEPWISE:
				ann->activation_values_output[i] = (fann_type)((log(1.0/ann->activation_results_output[i] -1.0) * 1.0/-2.0) * 1.0/ann->activation_steepness_output);
				break;
			case FANN_SIGMOID_SYMMETRIC:
			case FANN_SIGMOID_SYMMETRIC_STEPWISE:
				ann->activation_values_output[i] = (fann_type)((log((1.0-ann->activation_results_output[i]) / (ann->activation_results_output[i]+1.0)) * 1.0/-2.0) * 1.0/ann->activation_steepness_output);
				break;
		}
#else
		switch(ann->activation_function_output){
			case FANN_SIGMOID:
			case FANN_SIGMOID_STEPWISE:
				ann->activation_values_output[i] = (fann_type)((((log(ann->multiplier/(float)ann->activation_results_output[i] -1)*(float)ann->multiplier) / -2.0)*(float)ann->multiplier) / ann->activation_steepness_output);
				break;
			case FANN_SIGMOID_SYMMETRIC:
			case FANN_SIGMOID_SYMMETRIC_STEPWISE:
				ann->activation_values_output[i] = (fann_type)((((log((ann->multiplier - (float)ann->activation_results_output[i])/((float)ann->activation_results_output[i] + ann->multiplier))*(float)ann->multiplier) / -2.0)*(float)ann->multiplier) / ann->activation_steepness_output);
				break;
		}
#endif
	}
}
