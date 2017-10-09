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

/* Create a network from a configuration file.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_from_file(const char *configuration_file)
{
	struct fann *ann;
	FILE *conf = fopen(configuration_file, "r");
	if(!conf){
		fann_error(NULL, FANN_E_CANT_OPEN_CONFIG_R, configuration_file);
		return NULL;
	}
	ann = fann_create_from_fd(conf, configuration_file);
	fclose(conf);
	return ann;
}

/* Save the network.
 */
FANN_EXTERNAL void FANN_API fann_save(struct fann *ann, const char *configuration_file)
{
	fann_save_internal(ann, configuration_file, 0);
}

/* Save the network as fixed point data.
 */
FANN_EXTERNAL int FANN_API fann_save_to_fixed(struct fann *ann, const char *configuration_file)
{
	return fann_save_internal(ann, configuration_file, 1);
}

/* INTERNAL FUNCTION
   Used to save the network to a file.
 */
int fann_save_internal(struct fann *ann, const char *configuration_file, unsigned int save_as_fixed)
{
	int retval;
	FILE *conf = fopen(configuration_file, "w+");
	if(!conf){
		fann_error((struct fann_error *)ann, FANN_E_CANT_OPEN_CONFIG_W, configuration_file);
		return -1;
	}
	retval = fann_save_internal_fd(ann, conf, configuration_file, save_as_fixed);
	fclose(conf);
	return retval;
}

/* INTERNAL FUNCTION
   Used to save the network to a file descriptor.
 */
int fann_save_internal_fd(struct fann *ann, FILE *conf, const char * /* configuration_file*/, unsigned int save_as_fixed)
{
	struct fann_layer *layer_it;
	int calculated_decimal_point = 0;
	struct fann_neuron *neuron_it, *first_neuron;
	fann_type *weights;
	struct fann_neuron **connected_neurons;
	unsigned int i = 0;
#ifndef FIXEDFANN
	/* variabels for use when saving floats as fixed point variabels */
	unsigned int decimal_point = 0;
	unsigned int fixed_multiplier = 0;
	fann_type max_possible_value = 0;
	unsigned int bits_used_for_max = 0;
	fann_type current_max_value = 0;
#endif

#ifndef FIXEDFANN
	if(save_as_fixed){
		/* save the version information */
		fprintf(conf, FANN_FIX_VERSION"\n");
	}else{
		/* save the version information */
		fprintf(conf, FANN_FLO_VERSION"\n");
	}
#else
	/* save the version information */
	fprintf(conf, FANN_FIX_VERSION"\n");
#endif
	
#ifndef FIXEDFANN
	if(save_as_fixed){
		/* calculate the maximal possible shift value */

		for(layer_it = ann->first_layer+1; layer_it != ann->last_layer; layer_it++){
			for(neuron_it = layer_it->first_neuron; neuron_it != layer_it->last_neuron; neuron_it++){
				/* look at all connections to each neurons, and see how high a value we can get */
				current_max_value = 0;
				for(i = 0; i != neuron_it->num_connections; i++){
					current_max_value += fann_abs(neuron_it->weights[i]);
				}

				if(current_max_value > max_possible_value){
					max_possible_value = current_max_value;
				}
			}
		}

		for(bits_used_for_max = 0; max_possible_value >= 1; bits_used_for_max++){
			max_possible_value /= 2.0;
		}

		/* The maximum number of bits we shift the fix point, is the number
		   of bits in a integer, minus one for the sign, one for the minus
		   in stepwise, and minus the bits used for the maximum.
		   This is devided by two, to allow multiplication of two fixed
		   point numbers.
		*/
		calculated_decimal_point = (sizeof(int)*8-2-bits_used_for_max)/2;

		if(calculated_decimal_point < 0){
			decimal_point = 0;
		}else{
			decimal_point = calculated_decimal_point;
		}
		
		fixed_multiplier = 1 << decimal_point;

#ifdef DEBUG
		printf("calculated_decimal_point=%d, decimal_point=%u, bits_used_for_max=%u\n", calculated_decimal_point, decimal_point, bits_used_for_max);
#endif
		
		/* save the decimal_point on a seperate line */
		fprintf(conf, "%u\n", decimal_point);
		
		/* save the number layers "num_layers learning_rate connection_rate shortcut_connections activation_function_hidden activation_function_output activation_steepness_hidden activation_steepness_output" */	
		fprintf(conf, "%u %f %f %u %u %u %d %d\n", ann->last_layer - ann->first_layer, ann->learning_rate, ann->connection_rate, ann->shortcut_connections, ann->activation_function_hidden, ann->activation_function_output, (int)(ann->activation_steepness_hidden * fixed_multiplier), (int)(ann->activation_steepness_output * fixed_multiplier));
	}else{
		/* save the number layers "num_layers learning_rate connection_rate shortcut_connections activation_function_hidden activation_function_output activation_steepness_hidden activation_steepness_output" */	
		fprintf(conf, "%u %f %f %u %u %u "FANNPRINTF" "FANNPRINTF"\n", ann->last_layer - ann->first_layer, ann->learning_rate, ann->connection_rate, ann->shortcut_connections, ann->activation_function_hidden, ann->activation_function_output, ann->activation_steepness_hidden, ann->activation_steepness_output);
	}
#else
	/* save the decimal_point on a seperate line */
	fprintf(conf, "%u\n", ann->decimal_point);
	
	/* save the number layers "num_layers learning_rate connection_rate shortcut_connections activation_function_hidden activation_function_output activation_steepness_hidden activation_steepness_output" */	
	fprintf(conf, "%u %f %f %u %u %u "FANNPRINTF" "FANNPRINTF"\n", ann->last_layer - ann->first_layer, ann->learning_rate, ann->connection_rate, ann->shortcut_connections, ann->activation_function_hidden, ann->activation_function_output, ann->activation_steepness_hidden, ann->activation_steepness_output);	
#endif

	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		/* the number of neurons in the layers (in the last layer, there is always one too many neurons, because of an unused bias) */
		fprintf(conf, "%u ", layer_it->last_neuron - layer_it->first_neuron);
	}
	fprintf(conf, "\n");

	
	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		/* the number of connections to each neuron */
		for(neuron_it = layer_it->first_neuron; neuron_it != layer_it->last_neuron; neuron_it++){
			fprintf(conf, "%u ", neuron_it->num_connections);
		}
		fprintf(conf, "\n");
	}

	connected_neurons = (ann->first_layer+1)->first_neuron->connected_neurons;
	weights = (ann->first_layer+1)->first_neuron->weights;
	first_neuron = ann->first_layer->first_neuron;
	
	/* Now save all the connections.
	   We only need to save the source and the weight,
	   since the destination is given by the order.

	   The weight is not saved binary due to differences
	   in binary definition of floating point numbers.
	   Especially an iPAQ does not use the same binary
	   representation as an i386 machine.
	 */
	for(i = 0; i < ann->total_connections; i++){
#ifndef FIXEDFANN
		if(save_as_fixed){
			/* save the connection "(source weight) "*/
			fprintf(conf, "(%u %d) ",
				connected_neurons[i] - first_neuron,
				(int)floor((weights[i]*fixed_multiplier) + 0.5));
		}else{
			/* save the connection "(source weight) "*/
			fprintf(conf, "(%u "FANNPRINTF") ",
				connected_neurons[i] - first_neuron, weights[i]);
		}
#else
		/* save the connection "(source weight) "*/
		fprintf(conf, "(%u "FANNPRINTF") ",
			connected_neurons[i] - first_neuron, weights[i]);
#endif
		
	}
	fprintf(conf, "\n");

	return calculated_decimal_point;
}

/* INTERNAL FUNCTION
   Save the train data structure.
 */
void fann_save_train_internal(struct fann_train_data* data, char *filename, unsigned int save_as_fixed, unsigned int decimal_point)
{	
	FILE *file = fopen(filename, "w");
	if(!file){
		fann_error((struct fann_error*)data, FANN_E_CANT_OPEN_TD_W, filename);
		return;
	}
	fann_save_train_internal_fd(data, file, filename, save_as_fixed, decimal_point);
	fclose(file);
}

/* INTERNAL FUNCTION
   Save the train data structure.
 */
void fann_save_train_internal_fd(struct fann_train_data* data, FILE *file, char * /*filename */, unsigned int save_as_fixed, unsigned int decimal_point)
{
	unsigned int num_data = data->num_data;
	unsigned int num_input = data->num_input;
	unsigned int num_output = data->num_output;
	unsigned int i, j;
#ifndef FIXEDFANN
	unsigned int multiplier = 1 << decimal_point;
#endif
	
	fprintf(file, "%u %u %u\n", data->num_data, data->num_input, data->num_output);

	for(i = 0; i < num_data; i++){
		for(j = 0; j < num_input; j++){
#ifndef FIXEDFANN
			if(save_as_fixed){
				fprintf(file, "%d ", (int)(data->input[i][j]*multiplier));
			}else{
				if(((int)floor(data->input[i][j]+0.5)*1000000) ==
					((int)floor(data->input[i][j]*1000000.0+0.5))){
					fprintf(file, "%d ", (int)data->input[i][j]);
				}else{
					fprintf(file, "%f ", data->input[i][j]);
				}
			}
#else
			fprintf(file, FANNPRINTF" ", data->input[i][j]);
#endif
		}
		fprintf(file, "\n");

		for(j = 0; j < num_output; j++){
#ifndef FIXEDFANN
			if(save_as_fixed){
				fprintf(file, "%d ", (int)(data->output[i][j]*multiplier));
			}else{
				if(((int)floor(data->output[i][j]+0.5)*1000000) ==
					((int)floor(data->output[i][j]*1000000.0+0.5))){
					fprintf(file, "%d ", (int)data->output[i][j]);
				}else{
					fprintf(file, "%f ", data->output[i][j]);
				}
			}
#else
			fprintf(file, FANNPRINTF" ", data->output[i][j]);
#endif
		}
		fprintf(file, "\n");
	}
}

/* INTERNAL FUNCTION
   Create a network from a configuration file descriptor.
 */
struct fann * fann_create_from_fd(FILE *conf, const char *configuration_file)
{
	unsigned int num_layers, layer_size, activation_function_hidden, activation_function_output, input_neuron, i, shortcut_connections;
#ifdef FIXEDFANN
	unsigned int decimal_point, multiplier;
#endif
	fann_type activation_steepness_hidden, activation_steepness_output;
	float learning_rate, connection_rate;
	struct fann_neuron *first_neuron, *neuron_it, *last_neuron, **connected_neurons;
	fann_type *weights;
	struct fann_layer *layer_it;
	struct fann *ann;
	
	char *read_version;
	
	read_version = (char *)calloc(strlen(FANN_CONF_VERSION"\n"), 1);
	if(read_version == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		return NULL;
	}
	
	fread(read_version, 1, strlen(FANN_CONF_VERSION"\n"), conf); /* reads version */
	
	/* compares the version information */
	if(strncmp(read_version, FANN_CONF_VERSION"\n", strlen(FANN_CONF_VERSION"\n")) != 0){
		fann_error(NULL, FANN_E_WRONG_CONFIG_VERSION, configuration_file);
		free(read_version);
		return NULL;
	}

	free(read_version);
	
#ifdef FIXEDFANN
	if(fscanf(conf, "%u\n", &decimal_point) != 1){
		fann_error(NULL, FANN_E_CANT_READ_CONFIG, configuration_file);
		return NULL;
	}
	multiplier = 1 << decimal_point;
#endif
	
	if(fscanf(conf, "%u %f %f %u %u %u "FANNSCANF" "FANNSCANF"\n", &num_layers, &learning_rate, &connection_rate, &shortcut_connections, &activation_function_hidden, &activation_function_output, &activation_steepness_hidden, &activation_steepness_output) != 8){
		fann_error(NULL, FANN_E_CANT_READ_CONFIG, configuration_file);
		return NULL;
	}
	
	ann = fann_allocate_structure(learning_rate, num_layers);
	if(ann == NULL){
		return NULL;
	}
	ann->connection_rate = connection_rate;
	ann->shortcut_connections = shortcut_connections;

#ifdef FIXEDFANN
	ann->decimal_point = decimal_point;
	ann->multiplier = multiplier;
#endif

	ann->activation_steepness_hidden = activation_steepness_hidden;
	ann->activation_steepness_output = activation_steepness_output;
	ann->activation_function_hidden = activation_function_hidden;
	ann->activation_function_output = activation_function_output;
	fann_update_stepwise_hidden(ann);
	fann_update_stepwise_output(ann);
	
#ifdef DEBUG
	printf("creating network with learning rate %f\n", learning_rate);
	printf("input\n");
#endif
	
	/* determine how many neurons there should be in each layer */
	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		if(fscanf(conf, "%u ", &layer_size) != 1){
			fann_error((struct fann_error *)ann, FANN_E_CANT_READ_NEURON, configuration_file);
			fann_destroy(ann);
			return NULL;
		}
		/* we do not allocate room here, but we make sure that
		   last_neuron - first_neuron is the number of neurons */
		layer_it->first_neuron = NULL;
		layer_it->last_neuron = layer_it->first_neuron + layer_size;
		ann->total_neurons += layer_size;
#ifdef DEBUG
		printf("  layer       : %d neurons, 1 bias\n", layer_size);
#endif
	}
	
	ann->num_input = (unsigned int)(ann->first_layer->last_neuron - ann->first_layer->first_neuron - 1);
	ann->num_output = (unsigned int)(((ann->last_layer-1)->last_neuron - (ann->last_layer-1)->first_neuron) - 1);
	
	/* allocate room for the actual neurons */
	fann_allocate_neurons(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}
	
	last_neuron = (ann->last_layer-1)->last_neuron;
	for(neuron_it = ann->first_layer->first_neuron;
		neuron_it != last_neuron; neuron_it++){
		if(fscanf(conf, "%u ", &neuron_it->num_connections) != 1){
			fann_error((struct fann_error *)ann, FANN_E_CANT_READ_NEURON, configuration_file);
			fann_destroy(ann);
			return NULL;
		}
		ann->total_connections += neuron_it->num_connections;
	}
	
	fann_allocate_connections(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}
	
	connected_neurons = (ann->first_layer+1)->first_neuron->connected_neurons;
	weights = (ann->first_layer+1)->first_neuron->weights;
	first_neuron = ann->first_layer->first_neuron;
	
	for(i = 0; i < ann->total_connections; i++){
		if(fscanf(conf, "(%u "FANNSCANF") ", &input_neuron, &weights[i]) != 2){
			fann_error((struct fann_error *)ann, FANN_E_CANT_READ_CONNECTIONS, configuration_file);
			fann_destroy(ann);
			return NULL;
		}
		connected_neurons[i] = first_neuron+input_neuron;
	}	
	
#ifdef DEBUG
	printf("output\n");
#endif
	return ann;
}

