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

#include "stdafx.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "config.h"
#include "fann.h"
#include "fann_errno.h"

/* create a neural network.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create(float connection_rate, float learning_rate,
	unsigned int num_layers, /* the number of layers, including the input and output layer */


	...) /* the number of neurons in each of the layers, starting with the input layer and ending with the output layer */
{
	struct fann *ann;
	va_list layer_sizes;
	unsigned int *layers = (unsigned int *)calloc(num_layers, sizeof(unsigned int));
	int i = 0;

	va_start(layer_sizes, num_layers);
	for ( i=0 ; i<(int)num_layers ; i++ ) {
		layers[i] = va_arg(layer_sizes, unsigned int);
	}
	va_end(layer_sizes);

	ann = fann_create_array(connection_rate, learning_rate, num_layers, layers);

	free(layers);

	return ann;
}

/* create a neural network.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_array(float connection_rate, float learning_rate, unsigned int num_layers, unsigned int * layers)
{
	struct fann_layer *layer_it, *last_layer, *prev_layer;
	struct fann *ann;
	struct fann_neuron *neuron_it, *last_neuron, *random_neuron, *bias_neuron;
	unsigned int prev_layer_size, i, j;
	unsigned int num_neurons_in, num_neurons_out;
	unsigned int min_connections, max_connections, num_connections;
	unsigned int connections_per_neuron, allocated_connections;
	unsigned int random_number, found_connection;
	
#ifdef FIXEDFANN
	unsigned int decimal_point;
	unsigned int multiplier;
#endif
	if(connection_rate > 1){
		connection_rate = 1;
	}
	
	/* seed random */
	fann_seed_rand();
	
	/* allocate the general structure */
	ann = fann_allocate_structure(learning_rate, num_layers);
	if(ann == NULL){
		return NULL;
	}

	ann->connection_rate = connection_rate;
#ifdef FIXEDFANN
	decimal_point = ann->decimal_point;
	multiplier = ann->multiplier;
#endif
	fann_update_stepwise_hidden(ann);
	fann_update_stepwise_output(ann);

	/* determine how many neurons there should be in each layer */
	i = 0;
	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		/* we do not allocate room here, but we make sure that
		   last_neuron - first_neuron is the number of neurons */
		layer_it->first_neuron = NULL;
		layer_it->last_neuron = layer_it->first_neuron + layers[i++] +1; /* +1 for bias */
		ann->total_neurons += layer_it->last_neuron - layer_it->first_neuron;
	}
	
	ann->num_output = (ann->last_layer-1)->last_neuron - (ann->last_layer-1)->first_neuron -1;
	ann->num_input = ann->first_layer->last_neuron - ann->first_layer->first_neuron -1;
	
	/* allocate room for the actual neurons */
	fann_allocate_neurons(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}
	
#ifdef DEBUG
	printf("creating network with learning rate %f and connection rate %f\n", learning_rate, connection_rate);
	printf("input\n");
	printf("  layer       : %d neurons, 1 bias\n", ann->first_layer->last_neuron - ann->first_layer->first_neuron - 1);
#endif
	
	num_neurons_in = ann->num_input;
	for(layer_it = ann->first_layer+1; layer_it != ann->last_layer; layer_it++){
		num_neurons_out = layer_it->last_neuron - layer_it->first_neuron - 1;
		/* if all neurons in each layer should be connected to at least one neuron
		  in the previous layer, and one neuron in the next layer.
		  and the bias node should be connected to the all neurons in the next layer.
		  Then this is the minimum amount of neurons */
		min_connections = fann_max(num_neurons_in, num_neurons_out) + num_neurons_out;
		max_connections = num_neurons_in * num_neurons_out; /* not calculating bias */
		num_connections = fann_max(min_connections,
			(unsigned int)(0.5+(connection_rate * max_connections)) + num_neurons_out);
		
		ann->total_connections += num_connections;
		
		connections_per_neuron = num_connections/num_neurons_out;
		allocated_connections = 0;
		/* Now split out the connections on the different neurons */
		for(i = 0; i != num_neurons_out; i++){
			layer_it->first_neuron[i].num_connections = connections_per_neuron;
			allocated_connections += connections_per_neuron;
			
			if(allocated_connections < (num_connections*(i+1))/num_neurons_out){
				layer_it->first_neuron[i].num_connections++;
				allocated_connections++;
			}
		}
		
		/* used in the next run of the loop */
		num_neurons_in = num_neurons_out;
	}
	
	fann_allocate_connections(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}
	
	if(connection_rate >= 1){
		prev_layer_size = ann->num_input+1;
		prev_layer = ann->first_layer;
		last_layer = ann->last_layer;
		for(layer_it = ann->first_layer+1; layer_it != last_layer; layer_it++){
			last_neuron = layer_it->last_neuron-1;
			for(neuron_it = layer_it->first_neuron; neuron_it != last_neuron; neuron_it++){
				for(i = 0; i != prev_layer_size; i++){
					neuron_it->weights[i] = (fann_type)fann_random_weight();
					/* these connections are still initialized for fully connected networks, to allow
					   operations to work, that are not optimized for fully connected networks.
					*/
					neuron_it->connected_neurons[i] = prev_layer->first_neuron+i;
				}
				
			}
			prev_layer_size = layer_it->last_neuron - layer_it->first_neuron;
			prev_layer = layer_it;
#ifdef DEBUG
			printf("  layer       : %d neurons, 1 bias\n", prev_layer_size-1);
#endif
		}
	} else {
		/* make connections for a network, that are not fully connected */
		
		/* generally, what we do is first to connect all the input
		   neurons to a output neuron, respecting the number of
		   available input neurons for each output neuron. Then
		   we go through all the output neurons, and connect the
		   rest of the connections to input neurons, that they are
		   not allready connected to.
		*/
		
		/* first clear all the connections, because we want to
		   be able to see which connections are allready connected */
		memset((ann->first_layer+1)->first_neuron->connected_neurons, 0, ann->total_connections * sizeof(struct fann_neuron*));
		
		for(layer_it = ann->first_layer+1;
			layer_it != ann->last_layer; layer_it++){
			
			num_neurons_out = layer_it->last_neuron - layer_it->first_neuron - 1;
			num_neurons_in = (layer_it-1)->last_neuron - (layer_it-1)->first_neuron - 1;
			
			/* first connect the bias neuron */
			bias_neuron = (layer_it-1)->last_neuron-1;
			last_neuron = layer_it->last_neuron-1;
			for(neuron_it = layer_it->first_neuron;
				neuron_it != last_neuron; neuron_it++){
				
				neuron_it->connected_neurons[0] = bias_neuron;
				neuron_it->weights[0] = (fann_type)fann_random_weight();
			}
			
			/* then connect all neurons in the input layer */
			last_neuron = (layer_it-1)->last_neuron - 1;
			for(neuron_it = (layer_it-1)->first_neuron;
				neuron_it != last_neuron; neuron_it++){
				
				/* random neuron in the output layer that has space
				   for more connections */
				do {
					random_number = (int) (0.5+fann_rand(0, num_neurons_out-1));
					random_neuron = layer_it->first_neuron + random_number;
					/* checks the last space in the connections array for room */
				}while(random_neuron->connected_neurons[random_neuron->num_connections-1]);
				
				/* find an empty space in the connection array and connect */
				for(i = 0; i < random_neuron->num_connections; i++){
					if(random_neuron->connected_neurons[i] == NULL){
						random_neuron->connected_neurons[i] = neuron_it;
						random_neuron->weights[i] = (fann_type)fann_random_weight();
						break;
					}
				}
			}
			
			/* then connect the rest of the unconnected neurons */
			last_neuron = layer_it->last_neuron - 1;
			for(neuron_it = layer_it->first_neuron;
				neuron_it != last_neuron; neuron_it++){
				/* find empty space in the connection array and connect */
				for(i = 0; i < neuron_it->num_connections; i++){
					/* continue if allready connected */
					if(neuron_it->connected_neurons[i] != NULL) continue;
					
					do {
						found_connection = 0;
						random_number = (int) (0.5+fann_rand(0, num_neurons_in-1));
						random_neuron = (layer_it-1)->first_neuron + random_number;
						
						/* check to see if this connection is allready there */
						for(j = 0; j < i; j++){
							if(random_neuron == neuron_it->connected_neurons[j]){
								found_connection = 1;
								break;
							}
						}
						
					}while(found_connection);
					
					/* we have found a neuron that is not allready
					   connected to us, connect it */
					neuron_it->connected_neurons[i] = random_neuron;
					neuron_it->weights[i] = (fann_type)fann_random_weight();
				}
			}
			
#ifdef DEBUG
			printf("  layer       : %d neurons, 1 bias\n", num_neurons_out);
#endif
		}
		
		/* TODO it would be nice to have the randomly created
		   connections sorted for smoother memory access.
		*/
	}
	
#ifdef DEBUG
	printf("output\n");
#endif
	
	return ann;
}

 
/* create a neural network with shortcut connections.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_shortcut(float learning_rate,
	unsigned int num_layers, /* the number of layers, including the input and output layer */


	...) /* the number of neurons in each of the layers, starting with the input layer and ending with the output layer */
{
	struct fann *ann;
	va_list layer_sizes;
	unsigned int *layers = (unsigned int *)calloc(num_layers, sizeof(unsigned int));
	int i = 0;

	va_start(layer_sizes, num_layers);
	for ( i=0 ; i<(int)num_layers ; i++ ) {
		layers[i] = va_arg(layer_sizes, unsigned int);
	}
	va_end(layer_sizes);

	ann = fann_create_shortcut_array(learning_rate, num_layers, layers);

	free(layers);

	return ann;
}

/* create a neural network with shortcut connections.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_shortcut_array(float learning_rate, unsigned int num_layers, unsigned int * layers)
{
	struct fann_layer *layer_it, *layer_it2, *last_layer;
	struct fann *ann;
	struct fann_neuron *neuron_it, *neuron_it2 = 0;
	unsigned int i;
	unsigned int num_neurons_in, num_neurons_out;
	unsigned int num_connections;
	
#ifdef FIXEDFANN
	unsigned int decimal_point;
	unsigned int multiplier;
#endif
	/* seed random */
	fann_seed_rand();
	
	/* allocate the general structure */
	ann = fann_allocate_structure(learning_rate, num_layers);
	if(ann == NULL){
		return NULL;
	}

	ann->connection_rate = 1;
	ann->shortcut_connections = 1;
#ifdef FIXEDFANN
	decimal_point = ann->decimal_point;
	multiplier = ann->multiplier;
#endif
	fann_update_stepwise_hidden(ann);
	fann_update_stepwise_output(ann);

	/* determine how many neurons there should be in each layer */
	i = 0;
	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		/* we do not allocate room here, but we make sure that
		   last_neuron - first_neuron is the number of neurons */
		layer_it->first_neuron = NULL;
		layer_it->last_neuron = layer_it->first_neuron + layers[i++] +1; /* +1 for bias */
		ann->total_neurons += layer_it->last_neuron - layer_it->first_neuron;
	}
	
	ann->num_output = (ann->last_layer-1)->last_neuron - (ann->last_layer-1)->first_neuron -1;
	ann->num_input = ann->first_layer->last_neuron - ann->first_layer->first_neuron -1;
	
	/* allocate room for the actual neurons */
	fann_allocate_neurons(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}
	
#ifdef DEBUG
	printf("creating fully shortcut connected network with learning rate %f.\n", learning_rate);
	printf("input\n");
	printf("  layer       : %d neurons, 1 bias\n", ann->first_layer->last_neuron - ann->first_layer->first_neuron - 1);
#endif
	
	num_neurons_in = ann->num_input;
	last_layer = ann->last_layer;
	for(layer_it = ann->first_layer+1; layer_it != last_layer; layer_it++){
		num_neurons_out = layer_it->last_neuron - layer_it->first_neuron - 1;
		num_connections = num_neurons_in * num_neurons_out + num_neurons_out;
		ann->total_connections += num_connections;
		
		/* Now split out the connections on the different neurons */
		for(i = 0; i != num_neurons_out; i++){
			layer_it->first_neuron[i].num_connections = num_neurons_in+1;
		}
		
#ifdef DEBUG
		printf("  layer       : %d neurons, 1 bias\n", num_neurons_out);
#endif
		/* used in the next run of the loop */
		num_neurons_in += num_neurons_out;
	}
	
	fann_allocate_connections(ann);
	if(ann->errno_f == FANN_E_CANT_ALLOCATE_MEM){
		fann_destroy(ann);
		return NULL;
	}

	/* Connections are created from all neurons to all neurons in later layers
	 */
	num_neurons_in = ann->num_input+1;
	for(layer_it = ann->first_layer+1; layer_it != last_layer; layer_it++){
		for(neuron_it = layer_it->first_neuron; neuron_it != layer_it->last_neuron-1; neuron_it++){

			i = 0;
			for(layer_it2 = ann->first_layer; layer_it2 != layer_it; layer_it2++){
				for(neuron_it2 = layer_it2->first_neuron; neuron_it2 != layer_it2->last_neuron-1; neuron_it2++){
					
					neuron_it->weights[i] = (fann_type)fann_random_weight();
					/* these connections are still initialized for fully connected networks, to allow
					   operations to work, that are not optimized for fully connected networks.
					*/
					neuron_it->connected_neurons[i] = neuron_it2;
					i++;
				}
			}

			/* The connection to the bias neuron */
			neuron_it->weights[i] = (fann_type)fann_random_weight();
			neuron_it->connected_neurons[i] = neuron_it2;
		}
		num_neurons_in += layer_it->last_neuron - layer_it->first_neuron;
	}

#ifdef DEBUG
	printf("output\n");
#endif
	
	return ann;
}

/* runs the network.
 */
FANN_EXTERNAL fann_type * FANN_API fann_run(struct fann *ann, fann_type *input)
{
	struct fann_neuron *neuron_it, *last_neuron, *neurons, **neuron_pointers;
	unsigned int activation_function, i, num_connections, num_neurons, num_input, num_output;
	fann_type neuron_value, *output;
	fann_type *weights;
	struct fann_layer *layer_it, *layer_it2, *last_layer;
	
	
	/* store some variabels local for fast access */
#ifndef FIXEDFANN
	fann_type steepness;
	const fann_type activation_steepness_output = ann->activation_steepness_output;
	const fann_type activation_steepness_hidden = ann->activation_steepness_hidden;
#endif
	
	unsigned int activation_function_output = ann->activation_function_output;
	unsigned int activation_function_hidden = ann->activation_function_hidden;
	struct fann_neuron *first_neuron = ann->first_layer->first_neuron;
#ifdef FIXEDFANN
	int multiplier = ann->multiplier;
	unsigned int decimal_point = ann->decimal_point;
#endif
	
	/* values used for the stepwise linear sigmoid function */
	fann_type rh1 = 0, rh2 = 0, rh3 = 0, rh4 = 0, rh5 = 0, rh6 = 0;
	fann_type ro1 = 0, ro2 = 0, ro3 = 0, ro4 = 0, ro5 = 0, ro6 = 0;
	fann_type h1 = 0, h2 = 0, h3 = 0, h4 = 0, h5 = 0, h6 = 0;
	fann_type o1 = 0, o2 = 0, o3 = 0, o4 = 0, o5 = 0, o6 = 0;

	switch(ann->activation_function_hidden){
#ifdef FIXEDFANN
		case FANN_SIGMOID:
		case FANN_SIGMOID_SYMMETRIC:
#endif
		case FANN_SIGMOID_STEPWISE:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:			
			/* the hidden results */
			rh1 = ann->activation_results_hidden[0];
			rh2 = ann->activation_results_hidden[1];
			rh3 = ann->activation_results_hidden[2];
			rh4 = ann->activation_results_hidden[3];
			rh5 = ann->activation_results_hidden[4];
			rh6 = ann->activation_results_hidden[5];
			
			/* the hidden parameters */
			h1 = ann->activation_values_hidden[0];
			h2 = ann->activation_values_hidden[1];
			h3 = ann->activation_values_hidden[2];
			h4 = ann->activation_values_hidden[3];
			h5 = ann->activation_values_hidden[4];
			h6 = ann->activation_values_hidden[5];
			break;
		default:
			break;
	}
			
	switch(ann->activation_function_output){
#ifdef FIXEDFANN
		case FANN_SIGMOID:
		case FANN_SIGMOID_SYMMETRIC:
#endif
		case FANN_SIGMOID_STEPWISE:
		case FANN_SIGMOID_SYMMETRIC_STEPWISE:			
			/* the output results */
			ro1 = ann->activation_results_output[0];
			ro2 = ann->activation_results_output[1];
			ro3 = ann->activation_results_output[2];
			ro4 = ann->activation_results_output[3];
			ro5 = ann->activation_results_output[4];
			ro6 = ann->activation_results_output[5];
			
			/* the output parameters */
			o1 = ann->activation_values_output[0];
			o2 = ann->activation_values_output[1];
			o3 = ann->activation_values_output[2];
			o4 = ann->activation_values_output[3];
			o5 = ann->activation_values_output[4];
			o6 = ann->activation_values_output[5];
			break;
		default:
			break;
	}
	
	/* first set the input */
	num_input = ann->num_input;
	for(i = 0; i != num_input; i++){
#ifdef FIXEDFANN
		if(fann_abs(input[i]) > multiplier){
			printf("Warning input number %d is out of range -%d - %d with value %d, integer overflow may occur.\n", i, multiplier, multiplier, input[i]);
		}
#endif
		first_neuron[i].value = input[i];
	}
	
	last_layer = ann->last_layer;
	for(layer_it = ann->first_layer+1; layer_it != last_layer; layer_it++){
		
#ifdef FIXEDFANN
		((layer_it-1)->last_neuron-1)->value = multiplier;
#else
		/* set the bias neuron */
		((layer_it-1)->last_neuron-1)->value = 1;
		
		steepness = (layer_it == last_layer-1) ? 
			activation_steepness_output : activation_steepness_hidden;
#endif
		
		activation_function = (layer_it == last_layer-1) ?
			activation_function_output : activation_function_hidden;
		
		last_neuron = layer_it->last_neuron-1;
		for(neuron_it = layer_it->first_neuron; neuron_it != last_neuron; neuron_it++){
			neuron_value = 0;
			num_connections = neuron_it->num_connections;
			weights = neuron_it->weights;
			
			if(ann->connection_rate >= 1){
				if(ann->shortcut_connections){
					/* first go through the connections to the previous layers,
					   then let the normal operation go through the rest.
					*/

					for(layer_it2 = ann->first_layer;
						layer_it2 != layer_it-1; layer_it2++){

						neurons = layer_it2->first_neuron;
						num_neurons = layer_it2->last_neuron - neurons - 1; /* don't use bias from previous layers */
						i = num_neurons & 3; /* same as modulo 4 */
						switch(i) {
							case 3:
								neuron_value += fann_mult(weights[2], neurons[2].value);
							case 2:
								neuron_value += fann_mult(weights[1], neurons[1].value);
							case 1:
								neuron_value += fann_mult(weights[0], neurons[0].value);
							case 0:
								break;
						}
							
						for(;i != num_neurons; i += 4){
							neuron_value +=
								fann_mult(weights[i], neurons[i].value) +
								fann_mult(weights[i+1], neurons[i+1].value) +
								fann_mult(weights[i+2], neurons[i+2].value) +
								fann_mult(weights[i+3], neurons[i+3].value);
						}
							
						num_connections -= num_neurons;
						weights += num_neurons;
					}
				}
				
				neurons = (layer_it-1)->first_neuron;
				
				i = num_connections & 3; /* same as modulo 4 */
				switch(i) {
					case 3:
						neuron_value += fann_mult(weights[2], neurons[2].value);
					case 2:
						neuron_value += fann_mult(weights[1], neurons[1].value);
					case 1:
						neuron_value += fann_mult(weights[0], neurons[0].value);
					case 0:
						break;
				}
				
				for(;i != num_connections; i += 4){
					neuron_value +=
						fann_mult(weights[i], neurons[i].value) +
						fann_mult(weights[i+1], neurons[i+1].value) +
						fann_mult(weights[i+2], neurons[i+2].value) +
						fann_mult(weights[i+3], neurons[i+3].value);
				}
			}else{
				neuron_pointers = neuron_it->connected_neurons;
				
				i = num_connections & 3; /* same as modulo 4 */
				switch(i) {
					case 3:
						neuron_value += fann_mult(weights[2], neuron_pointers[2]->value);
					case 2:
						neuron_value += fann_mult(weights[1], neuron_pointers[1]->value);
					case 1:
						neuron_value += fann_mult(weights[0], neuron_pointers[0]->value);
					case 0:
						break;
				}
				
				for(;i != num_connections; i += 4){
					neuron_value +=
						fann_mult(weights[i], neuron_pointers[i]->value) +
						fann_mult(weights[i+1], neuron_pointers[i+1]->value) +
						fann_mult(weights[i+2], neuron_pointers[i+2]->value) +
						fann_mult(weights[i+3], neuron_pointers[i+3]->value);
				}
			}
			
			switch(activation_function){
#ifdef FIXEDFANN
				case FANN_SIGMOID:
				case FANN_SIGMOID_STEPWISE:
					if(layer_it == last_layer-1){
						neuron_it->value = (fann_type)fann_stepwise(o1, o2, o3, o4, o5, o6, ro1, ro2, ro3, ro4, ro5, ro6, 0, multiplier, neuron_value);
					}else{
						neuron_it->value = (fann_type)fann_stepwise(h1, h2, h3, h4, h5, h6, rh1, rh2, rh3, rh4, rh5, rh6, 0, multiplier, neuron_value);
					}
					break;
				case FANN_SIGMOID_SYMMETRIC:
				case FANN_SIGMOID_SYMMETRIC_STEPWISE:
					if(layer_it == last_layer-1){
						neuron_it->value = (fann_type)fann_stepwise(o1, o2, o3, o4, o5, o6, ro1, ro2, ro3, ro4, ro5, ro6, -multiplier, multiplier, neuron_value);
					}else{
						neuron_it->value = (fann_type)fann_stepwise(h1, h2, h3, h4, h5, h6, rh1, rh2, rh3, rh4, rh5, rh6, -multiplier, multiplier, neuron_value);
					}
					break;
#else
				case FANN_LINEAR:
					neuron_it->value = (fann_type)fann_linear(steepness, neuron_value);
					break;
					
				case FANN_SIGMOID:
					neuron_it->value = (fann_type)fann_sigmoid(steepness, neuron_value);
					break;
					
				case FANN_SIGMOID_SYMMETRIC:
					neuron_it->value = (fann_type)fann_sigmoid_symmetric(steepness, neuron_value);
					break;
					
				case FANN_SIGMOID_STEPWISE:
					if(layer_it == last_layer-1){
						neuron_it->value = (fann_type)fann_stepwise(o1, o2, o3, o4, o5, o6, ro1, ro2, ro3, ro4, ro5, ro6, 0, 1, neuron_value);
					}else{
						neuron_it->value = (fann_type)fann_stepwise(h1, h2, h3, h4, h5, h6, rh1, rh2, rh3, rh4, rh5, rh6, 0, 1, neuron_value);
					}
					break;
				case FANN_SIGMOID_SYMMETRIC_STEPWISE:
					if(layer_it == last_layer-1){
						neuron_it->value = (fann_type)fann_stepwise(o1, o2, o3, o4, o5, o6, ro1, ro2, ro3, ro4, ro5, ro6, -1, 1, neuron_value);
					}else{
						neuron_it->value = (fann_type)fann_stepwise(h1, h2, h3, h4, h5, h6, rh1, rh2, rh3, rh4, rh5, rh6, -1, 1, neuron_value);
					}
					break;
#endif
				case FANN_THRESHOLD:
					neuron_it->value = (fann_type)((neuron_value < 0) ? 0 : 1);
					break;
				case FANN_THRESHOLD_SYMMETRIC:
					neuron_it->value = (fann_type)((neuron_value < 0) ? -1 : 1);
					break;
				default:
					fann_error((struct fann_error *)ann, FANN_E_CANT_USE_ACTIVATION);
			}
		}
	}
	
	/* set the output */
	output = ann->output;
	num_output = ann->num_output;
	neurons = (ann->last_layer-1)->first_neuron;
	for(i = 0; i != num_output; i++){
		output[i] = neurons[i].value;
	}
	return ann->output;
}

/* deallocate the network.
 */
FANN_EXTERNAL void FANN_API fann_destroy(struct fann *ann)
{
	if(ann == NULL) return;
	fann_safe_free(fann_get_weights(ann));
	fann_safe_free(fann_get_connections(ann));
	fann_safe_free(ann->first_layer->first_neuron);
	fann_safe_free(ann->first_layer);
	fann_safe_free(ann->output);
	fann_safe_free(ann->train_errors);
	fann_safe_free(ann->train_slopes);
	fann_safe_free(ann->prev_train_slopes);
	fann_safe_free(ann->prev_steps);
	fann_safe_free(ann->errstr);
	fann_safe_free(ann);
}

FANN_EXTERNAL void FANN_API fann_randomize_weights(struct fann *ann, fann_type min_weight, fann_type max_weight)
{
	fann_type *last_weight;
	fann_type *weights = (ann->first_layer+1)->first_neuron->weights;
	last_weight = weights + ann->total_connections;
	for(;weights != last_weight; weights++){
		*weights = (fann_type)(fann_rand(min_weight, max_weight));
	}
}

FANN_EXTERNAL void FANN_API fann_print_connections(struct fann *ann)
{
	struct fann_layer *layer_it;
	struct fann_neuron *neuron_it;
	unsigned int i, value;
	char *neurons;
	unsigned int num_neurons = fann_get_total_neurons(ann) - fann_get_num_output(ann);
	neurons = (char *)malloc(num_neurons+1);
	neurons[num_neurons] = 0;

	printf("Layer / Neuron ");
	for(i = 0; i < num_neurons; i++){
		printf("%d", i%10);
	}
	printf("\n");
	
	for(layer_it = ann->first_layer+1; layer_it != ann->last_layer; layer_it++){
		for(neuron_it = layer_it->first_neuron;
			neuron_it != layer_it->last_neuron-1; neuron_it++){
			
			memset(neurons, (int)'.', num_neurons);
			for(i = 0; i < neuron_it->num_connections; i++){
				value = (unsigned int)(fann_abs(neuron_it->weights[i])+0.5);
				if(value > 25) value = 25;
				neurons[neuron_it->connected_neurons[i] - ann->first_layer->first_neuron] = 'a' + value;
			}
			printf("L %3d / N %4d %s\n", layer_it - ann->first_layer,
				neuron_it - ann->first_layer->first_neuron, neurons);
		}
	}

	free(neurons);
}

/* Initialize the weights using Widrow + Nguyen's algorithm.
*/
FANN_EXTERNAL void FANN_API fann_init_weights(struct fann *ann, struct fann_train_data *train_data)
{
	fann_type smallest_inp, largest_inp;
	unsigned int dat = 0, elem, num_neurons_in, num_neurons_out, num_connect, num_hidden_neurons;
	struct fann_layer *layer_it;
	struct fann_neuron *neuron_it, *last_neuron, *bias_neuron;
#ifdef FIXEDFANN
	unsigned int multiplier = ann->multiplier;
#endif
	float scale_factor;

	for ( smallest_inp = largest_inp = train_data->input[0][0] ; dat < train_data->num_data ; dat++ ) {
		for ( elem = 0 ; elem < train_data->num_input ; elem++ ) {
			if ( train_data->input[dat][elem] < smallest_inp )
				smallest_inp = train_data->input[dat][elem];
			if ( train_data->input[dat][elem] > largest_inp )
				largest_inp = train_data->input[dat][elem];
		}
	}

	num_hidden_neurons = ann->total_neurons - (ann->num_input + ann->num_output + (ann->last_layer - ann->first_layer));
	scale_factor = (float)(pow((double)(0.7f * (double)num_hidden_neurons),
				  (double)(1.0f / (double)ann->num_input)) / (double)(largest_inp - smallest_inp));

#ifdef DEBUG
	printf("Initializing weights with scale factor %f\n", scale_factor);
#endif
	for ( layer_it = ann->first_layer+1; layer_it != ann->last_layer ; layer_it++) {
#ifdef DEBUG
		printf(" Layer: %x/%x (%d neurons)\n", layer_it-ann->first_layer, ann->last_layer-ann->first_layer, layer_it->last_neuron - layer_it->first_neuron);
#endif
		num_neurons_out = layer_it->last_neuron - layer_it->first_neuron - 1;
		num_neurons_in = (layer_it-1)->last_neuron - (layer_it-1)->first_neuron - 1;

		last_neuron = layer_it->last_neuron-1;
		bias_neuron = (layer_it-1)->last_neuron-1;

		for(neuron_it = layer_it->first_neuron; neuron_it != last_neuron; neuron_it++) {
#ifdef DEBUG
			printf("  Neuron %x/%x (%d connections)\n", neuron_it-layer_it->first_neuron, last_neuron-layer_it->first_neuron, neuron_it->num_connections);
#endif
			for ( num_connect = 0 ; num_connect < neuron_it->num_connections ; num_connect++ ) {
#ifdef DEBUG
				printf("   Connection %d/%d (%x)\n", num_connect, neuron_it->num_connections, neuron_it->connected_neurons[num_connect] - ann->first_layer->first_neuron);
#endif
				if ( bias_neuron == neuron_it->connected_neurons[num_connect] ) {
#ifdef FIXEDFANN
					neuron_it->weights[num_connect] = (fann_type)fann_rand(-scale_factor, scale_factor * multiplier);
#else
					neuron_it->weights[num_connect] = (fann_type)fann_rand(-scale_factor, scale_factor);
#endif
				} else {
#ifdef FIXEDFANN
					neuron_it->weights[num_connect] = (fann_type)fann_rand(0, scale_factor * multiplier);
#else
					neuron_it->weights[num_connect] = (fann_type)fann_rand(0, scale_factor);
#endif
				}
			}
		}
	}
}

/* INTERNAL FUNCTION
   Allocates the main structure and sets some default values.
 */
struct fann * fann_allocate_structure(float learning_rate, unsigned int num_layers)
{
	struct fann *ann;
	
	if(num_layers < 2){
#ifdef DEBUG
		printf("less than 2 layers - ABORTING.\n");
#endif
		return NULL;
	}

	/* allocate and initialize the main network structure */
	ann = (struct fann *)malloc(sizeof(struct fann));
	if(ann == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		return NULL;
	}

	ann->errno_f = 0;
	ann->error_log = NULL;
	ann->errstr = NULL;
	ann->learning_rate = learning_rate;
	ann->total_neurons = 0;
	ann->total_connections = 0;
	ann->num_input = 0;
	ann->num_output = 0;
	ann->train_errors = NULL;
	ann->train_slopes = NULL;
	ann->prev_steps = NULL;
	ann->prev_train_slopes = NULL;
	ann->training_algorithm = FANN_TRAIN_RPROP;
	ann->num_MSE = 0;
	ann->MSE_value = 0;
	ann->shortcut_connections = 0;
	ann->train_error_function = FANN_ERRORFUNC_TANH;

	/* variables used for cascade correlation (reasonable defaults) */
	/*ann->change_fraction = 0.01;
	  ann->stagnation_epochs = 12;*/

	/* Variables for use with with Quickprop training (reasonable defaults) */
	ann->quickprop_decay = (float)-0.0001;
	ann->quickprop_mu = 1.75;

	/* Variables for use with with RPROP training (reasonable defaults) */
	ann->rprop_increase_factor = (float)1.2;
	ann->rprop_decrease_factor = 0.5;
	ann->rprop_delta_min = 0.0;
	ann->rprop_delta_max = 50.0;

	fann_init_error_data((struct fann_error *)ann);

#ifdef FIXEDFANN
	/* these values are only boring defaults, and should really
	   never be used, since the real values are always loaded from a file. */
	ann->decimal_point = 8;
	ann->multiplier = 256;
#endif
	
	ann->activation_function_hidden = FANN_SIGMOID_STEPWISE;
	ann->activation_function_output = FANN_SIGMOID_STEPWISE;
#ifdef FIXEDFANN
	ann->activation_steepness_hidden = ann->multiplier/2;
	ann->activation_steepness_output = ann->multiplier/2;
#else
	ann->activation_steepness_hidden = 0.5;
	ann->activation_steepness_output = 0.5;
#endif

	/* allocate room for the layers */
	ann->first_layer = (struct fann_layer *)calloc(num_layers, sizeof(struct fann_layer));
	if(ann->first_layer == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		free(ann);
		return NULL;
	}
	
	ann->last_layer = ann->first_layer + num_layers;

	return ann;
}

/* INTERNAL FUNCTION
   Allocates room for the neurons.
 */
void fann_allocate_neurons(struct fann *ann)
{
	struct fann_layer *layer_it;
	struct fann_neuron *neurons;
	unsigned int num_neurons_so_far = 0;
	unsigned int num_neurons = 0;

	/* all the neurons is allocated in one long array */
	neurons = (struct fann_neuron *)calloc(ann->total_neurons, sizeof(struct fann_neuron));
	if(neurons == NULL){
		fann_error((struct fann_error *)ann, FANN_E_CANT_ALLOCATE_MEM);
		return;
	}
	
	/* clear data, primarily to make the input neurons cleared */
	memset(neurons, 0, ann->total_neurons * sizeof(struct fann_neuron));
	
	for(layer_it = ann->first_layer; layer_it != ann->last_layer; layer_it++){
		num_neurons = layer_it->last_neuron - layer_it->first_neuron;
		layer_it->first_neuron = neurons+num_neurons_so_far;
		layer_it->last_neuron = layer_it->first_neuron+num_neurons;
		num_neurons_so_far += num_neurons;
	}

	ann->output = (fann_type *)calloc(num_neurons, sizeof(fann_type));
	if(ann->output == NULL){
		fann_error((struct fann_error *)ann, FANN_E_CANT_ALLOCATE_MEM);
		return;
	}
}

/* INTERNAL FUNCTION
   Allocate room for the connections.
 */
void fann_allocate_connections(struct fann *ann)
{
	struct fann_layer *layer_it, *last_layer;
	struct fann_neuron *neuron_it, *last_neuron;
	fann_type *weights;
	struct fann_neuron **connected_neurons = NULL;
	unsigned int connections_so_far = 0;
	
	weights = (fann_type *)calloc(ann->total_connections, sizeof(fann_type));
	if(weights == NULL){
		fann_error((struct fann_error *)ann, FANN_E_CANT_ALLOCATE_MEM);
		return;
	}
	
	/* TODO make special cases for all places where the connections
	   is used, so that it is not needed for fully connected networks.
	*/
	connected_neurons = (struct fann_neuron **) calloc(ann->total_connections, sizeof(struct fann_neuron*));
	if(connected_neurons == NULL){
		fann_error((struct fann_error *)ann, FANN_E_CANT_ALLOCATE_MEM);
		return;
	}
	

	last_layer = ann->last_layer;
	for(layer_it = ann->first_layer+1; layer_it != ann->last_layer; layer_it++){
		last_neuron = layer_it->last_neuron-1;
		for(neuron_it = layer_it->first_neuron; neuron_it != last_neuron; neuron_it++){
			neuron_it->weights = weights+connections_so_far;
			neuron_it->connected_neurons = connected_neurons+connections_so_far;
			connections_so_far += neuron_it->num_connections;
		}
	}

	if(connections_so_far != ann->total_connections){
		fann_error((struct fann_error *)ann, FANN_E_WRONG_NUM_CONNECTIONS, connections_so_far, ann->total_connections);
		return;
	}
}

/* INTERNAL FUNCTION
   Seed the random function.
 */
void fann_seed_rand()
{
	FILE *fp = fopen("/dev/urandom", "r");
	unsigned int foo;
	struct timeval t;
	if(!fp){
		gettimeofday(&t, NULL);
		foo = t.tv_usec;
#ifdef DEBUG
		printf("unable to open /dev/urandom\n");
#endif
	}else{
		fread(&foo, sizeof(foo), 1, fp);
		fclose(fp);
	}
	srand(foo);
}
