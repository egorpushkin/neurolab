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

/* This file defines the user interface to the fann library.
   It is included from fixedfann.h, floatfann.h and doublefann.h and should
   NOT be included directly. If included directly it will react as if
   floatfann.h was included.
*/

#ifndef FANN_INCLUDE
/* just to allow for inclusion of fann.h in normal stuations where only floats are needed */
#ifdef FIXEDFANN
#include "fixedfann.h"
#else
#include "floatfann.h"
#endif /* FIXEDFANN  */

#else

#include "compat_time.h"
#include "fann_data.h"
#include "fann_internal.h"
#include "fann_activation.h"

#ifndef __fann_h__
#define __fann_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
#ifndef NULL
#define NULL 0
#endif /* NULL */

/* ----- Macros used to define DLL external entrypoints ----- */
/*
 DLL Export, import and calling convention for Windows.
 Only defined for Microsoft VC++ FANN_EXTERNAL indicates
 that a function will be exported/imported from a dll
 FANN_API ensures that the DLL calling convention
 will be used for  a function regardless of the calling convention
 used when compiling.

 For a function to be exported from a DLL its prototype and
 declaration must be like this:
    FANN_EXTERNAL void FANN_API function(char *argument)

 The following ifdef block is a way of creating macros which
 make exporting from a DLL simple. All files within a DLL are
 compiled with the FANN_DLL_EXPORTS symbol defined on the
 command line. This symbol should not be defined on any project
 that uses this DLL. This way any other project whose source
 files include this file see FANN_EXTERNAL functions as being imported
 from a DLL, whereas a DLL sees symbols defined with this
 macro as being exported which makes calls more efficient.
 The __stdcall calling convention is used for functions in a
 windows DLL.

 The callback functions for fann_train_on_data_callback and
 fann_train_on_file_callback must be declared as FANN_API
 so the DLL and the application program both use the same
 calling convention. The callback functions must of this form:
     int FANN_API user_callback(unsigned int epochs, float error)
*/

/*
 The following sets the default for MSVC++ 2003 or later to use
 the fann dll's. To use a lib or fixedfann.c, floatfann.c or doublefann.c
 with those compilers FANN_NO_DLL has to be defined before
 including the fann headers.
 The default for previous MSVC compilers such as VC++ 6 is not
 to use dll's. To use dll's FANN_USE_DLL has to be defined before
 including the fann headers.
*/
#if (_MSC_VER > 1300)
#ifndef FANN_NO_DLL
#define FANN_USE_DLL
#endif /* FANN_USE_LIB */
#endif /* _MSC_VER */
#if defined(_MSC_VER) && (defined(FANN_USE_DLL) || defined(FANN_DLL_EXPORTS))
#ifdef FANN_DLL_EXPORTS
#define FANN_EXTERNAL __declspec(dllexport)
#else
#define FANN_EXTERNAL // __declspec(dllimport)
#endif /* FANN_DLL_EXPORTS*/
#define FANN_API // __stdcall
#else
#define FANN_EXTERNAL
#define FANN_API
#endif /* _MSC_VER */
/* ----- End of macros used to define DLL external entrypoints ----- */


/* ----- Implemented in fann.c Creation, running and destruction of ANNs ----- */
	
/* Constructs a backpropagation neural network, from an connection rate,
   a learning rate, the number of layers and the number of neurons in each
   of the layers.

   The connection rate controls how many connections there will be in the
   network. If the connection rate is set to 1, the network will be fully
   connected, but if it is set to 0.5 only half of the connections will be set.

   There will be a bias neuron in each layer (except the output layer),
   and this bias neuron will be connected to all neurons in the next layer.
   When running the network, the bias nodes always emits 1
*/
FANN_EXTERNAL struct fann * FANN_API fann_create(float connection_rate, float learning_rate,
	/* the number of layers, including the input and output layer */
	unsigned int num_layers,
	/* the number of neurons in each of the layers, starting with
	   the input layer and ending with the output layer */
	...);

/* Just like fann_create, but with an array of layer sizes
   instead of individual parameters.
*/
FANN_EXTERNAL struct fann * FANN_API fann_create_array(float connection_rate, float learning_rate,
	unsigned int num_layers, unsigned int * layers);

/* create a fully connected neural network with shortcut connections.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_shortcut(float learning_rate,
	unsigned int num_layers, /* the number of layers, including the input and output layer */
	...); /* the number of neurons in each of the layers, starting with the input layer and ending with the output layer */

/* create a neural network with shortcut connections.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_shortcut_array(float learning_rate, unsigned int num_layers, unsigned int * layers);	
	
/* Runs a input through the network, and returns the output.
 */
FANN_EXTERNAL fann_type* FANN_API fann_run(struct fann *ann, fann_type *input);

/* Destructs the entire network.
   Be sure to call this function after finished using the network.
 */
FANN_EXTERNAL void FANN_API fann_destroy(struct fann *ann);
	
/* Randomize weights (from the beginning the weights are random between -0.1 and 0.1)
 */
FANN_EXTERNAL void FANN_API fann_randomize_weights(struct fann *ann, fann_type min_weight, fann_type max_weight);

/* Initialize the weights using Widrow + Nguyen's algorithm.
*/
FANN_EXTERNAL void FANN_API fann_init_weights(struct fann *ann, struct fann_train_data * train_data);

/* print out which connections there are in the ann */
FANN_EXTERNAL void FANN_API fann_print_connections(struct fann *ann);	
	
/* ----- Implemented in fann_io.c Saving and loading of ANNs ----- */

/* Constructs a backpropagation neural network from a configuration file.
 */
FANN_EXTERNAL struct fann * FANN_API fann_create_from_file(const char *configuration_file);

/* Save the entire network to a configuration file.
 */
FANN_EXTERNAL void FANN_API fann_save(struct fann *ann, const char *configuration_file);

/* Saves the entire network to a configuration file.
   But it is saved in fixed point format no matter which
   format it is currently in.

   This is usefull for training a network in floating points,
   and then later executing it in fixed point.

   The function returns the bit position of the fix point, which
   can be used to find out how accurate the fixed point network will be.
   A high value indicates high precision, and a low value indicates low
   precision.

   A negative value indicates very low precision, and a very
   strong possibility for overflow.
   (the actual fix point will be set to 0, since a negative
   fix point does not make sence).

   Generally, a fix point lower than 6 is bad, and should be avoided.
   The best way to avoid this, is to have less connections to each neuron,
   or just less neurons in each layer.

   The fixed point use of this network is only intended for use on machines that
   have no floating point processor, like an iPAQ. On normal computers the floating
   point version is actually faster.
*/
FANN_EXTERNAL int FANN_API fann_save_to_fixed(struct fann *ann, const char *configuration_file);


/* ----- Implemented in fann_train.c Training and testing of ANNs ----- */

#ifndef FIXEDFANN
/* Train one iteration with a set of inputs, and a set of desired outputs.
 */
FANN_EXTERNAL void FANN_API fann_train(struct fann *ann, fann_type *input, fann_type *desired_output);

#endif /* NOT FIXEDFANN */

/* Test with a set of inputs, and a set of desired outputs.
   This operation updates the mean square error, but does not
   change the network in any way.
*/
FANN_EXTERNAL fann_type * FANN_API fann_test(struct fann *ann, fann_type *input, fann_type *desired_output);

/* Reads the mean square error from the network.
   (obsolete will be removed at some point, use fann_get_MSE)
 */
FANN_EXTERNAL float FANN_API fann_get_error(struct fann *ann);

/* Reads the mean square error from the network.
 */
FANN_EXTERNAL float FANN_API fann_get_MSE(struct fann *ann);

/* Resets the mean square error from the network.
   (obsolete will be removed at some point, use fann_reset_MSE)
 */
FANN_EXTERNAL void FANN_API fann_reset_error(struct fann *ann);

/* Resets the mean square error from the network.
 */
FANN_EXTERNAL void FANN_API fann_reset_MSE(struct fann *ann);

/* ----- Implemented in fann_train_data.c Data for training of ANNs ----- */

/* Reads a file that stores training data, in the format:
   num_train_data num_input num_output\n
   inputdata seperated by space\n
   outputdata seperated by space\n

   .
   .
   .
   
   inputdata seperated by space\n
   outputdata seperated by space\n
*/
FANN_EXTERNAL struct fann_train_data* FANN_API fann_read_train_from_file(char *filename);

/* Destructs the training data
   Be sure to call this function after finished using the training data.
 */
FANN_EXTERNAL void FANN_API fann_destroy_train(struct fann_train_data* train_data);

#ifndef FIXEDFANN

/* Train one epoch with a set of training data.
 */
FANN_EXTERNAL float FANN_API fann_train_epoch(struct fann *ann, struct fann_train_data *data);

/* Test a set of training data and calculate the MSE
 */
FANN_EXTERNAL float FANN_API fann_test_data(struct fann *ann, struct fann_train_data *data);
	
/* Trains on an entire dataset, for a maximum of max_epochs
   epochs or until mean square error is lower than desired_error.
   Reports about the progress is given every
   epochs_between_reports epochs.
   If epochs_between_reports is zero, no reports are given.
*/
FANN_EXTERNAL void FANN_API fann_train_on_data(struct fann *ann, struct fann_train_data *data, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error);

/* Same as fann_train_on_data, but a callback function is given,
   which can be used to print out reports. (effective for gui programming).
   If the callback returns -1, then the training is terminated, otherwise
   it continues until the normal stop criteria.
*/
FANN_EXTERNAL void FANN_API fann_train_on_data_callback(struct fann *ann, struct fann_train_data *data, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error, int (FANN_API *callback)(unsigned int epochs, float error));

/* Does the same as train_on_data, but reads the data directly from a file.
 */
FANN_EXTERNAL void FANN_API fann_train_on_file(struct fann *ann, char *filename, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error);

/* Does the same as train_on_data_callback, but
   reads the data directly from a file.
 */
FANN_EXTERNAL void FANN_API fann_train_on_file_callback(struct fann *ann, char *filename, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error, int (FANN_API *callback)(unsigned int epochs, float error));

/* shuffles training data, randomizing the order
 */
FANN_EXTERNAL void FANN_API fann_shuffle_train_data(struct fann_train_data *train_data);

/* merges training data into a single struct.
 */
FANN_EXTERNAL struct fann_train_data * FANN_API fann_merge_train_data(struct fann_train_data *data1, struct fann_train_data *data2);

/* return a copy of a fann_train_data struct
 */
FANN_EXTERNAL struct fann_train_data * FANN_API fann_duplicate_train_data(struct fann_train_data *data);
	
#endif /* NOT FIXEDFANN */

/* Save the training structure to a file.
 */
FANN_EXTERNAL void FANN_API fann_save_train(struct fann_train_data* data, char *filename);

/* Saves the training structure to a fixed point data file.
 *  (Very usefull for testing the quality of a fixed point network).
 */
FANN_EXTERNAL void FANN_API fann_save_train_to_fixed(struct fann_train_data* data, char *filename, unsigned int decimal_point);

/* ----- Implemented in fann_options.c Get and set options for the ANNs ----- */

/* Prints all of the parameters and options of the ANN */
FANN_EXTERNAL void FANN_API fann_print_parameters(struct fann *ann);
	
/* Get the training algorithm.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_training_algorithm(struct fann *ann);

/* Set the training algorithm.
 */
FANN_EXTERNAL void FANN_API fann_set_training_algorithm(struct fann *ann, unsigned int training_algorithm);

/* Get the learning rate.
 */
FANN_EXTERNAL float FANN_API fann_get_learning_rate(struct fann *ann);

/* Set the learning rate.
 */
FANN_EXTERNAL void FANN_API fann_set_learning_rate(struct fann *ann, float learning_rate);

/* Get the activation function used in the hidden layers.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_activation_function_hidden(struct fann *ann);

/* Set the activation function for the hidden layers.
 */
FANN_EXTERNAL void FANN_API fann_set_activation_function_hidden(struct fann *ann, unsigned int activation_function);

/* Get the activation function used in the output layer.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_activation_function_output(struct fann *ann);

/* Set the activation function for the output layer.
 */
FANN_EXTERNAL void FANN_API fann_set_activation_function_output(struct fann *ann, unsigned int activation_function);

/* Get the steepness parameter for the sigmoid function used in the hidden layers.
 */
FANN_EXTERNAL fann_type FANN_API fann_get_activation_steepness_hidden(struct fann *ann);
	
/* Set the steepness of the sigmoid function used in the hidden layers.
   Only usefull if sigmoid function is used in the hidden layers (default 0.5).
 */
FANN_EXTERNAL void FANN_API fann_set_activation_steepness_hidden(struct fann *ann, fann_type steepness);

/* Get the steepness parameter for the sigmoid function used in the output layer.
 */
FANN_EXTERNAL fann_type FANN_API fann_get_activation_steepness_output(struct fann *ann);
	
/* Set the steepness of the sigmoid function used in the output layer.
   Only usefull if sigmoid function is used in the output layer (default 0.5).
 */
FANN_EXTERNAL void FANN_API fann_set_activation_steepness_output(struct fann *ann, fann_type steepness);

/* OBSOLETE use fann_get_activation_steepness_hidden
   Get the steepness parameter for the sigmoid function used in the hidden layers.
 */
FANN_EXTERNAL fann_type FANN_API fann_get_activation_hidden_steepness(struct fann *ann);
	
/* OBSOLETE use fann_set_activation_steepness_hidden
   Set the steepness of the sigmoid function used in the hidden layers.
   Only usefull if sigmoid function is used in the hidden layers (default 0.5).
 */
FANN_EXTERNAL void FANN_API fann_set_activation_hidden_steepness(struct fann *ann, fann_type steepness);

/* OBSOLETE use fann_get_activation_steepness_output
  Get the steepness parameter for the sigmoid function used in the output layer.
 */
FANN_EXTERNAL fann_type FANN_API fann_get_activation_output_steepness(struct fann *ann);
	
/* OBSOLETE use fann_set_activation_steepness_output
  Set the steepness of the sigmoid function used in the output layer.
   Only usefull if sigmoid function is used in the output layer (default 0.5).
 */
FANN_EXTERNAL void FANN_API fann_set_activation_output_steepness(struct fann *ann, fann_type steepness);

/* Get the error function used during training. (default FANN_ERRORFUNC_TANH)
 */
FANN_EXTERNAL void FANN_API fann_set_train_error_function(struct fann *ann, unsigned int train_error_function);

/* Get the error function used during training.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_train_error_function(struct fann *ann);

/* Decay is used to make the weights do not go so high (default -0.0001). */
FANN_EXTERNAL float FANN_API fann_get_quickprop_decay(struct fann *ann);
	
/* Decay is used to make the weights do not go so high (default -0.0001). */
FANN_EXTERNAL void FANN_API fann_set_quickprop_decay(struct fann *ann, float quickprop_decay);
	
/* Mu is a factor used to increase and decrease the stepsize (default 1.75). */
FANN_EXTERNAL float FANN_API fann_get_quickprop_mu(struct fann *ann);

/* Mu is a factor used to increase and decrease the stepsize (default 1.75). */
FANN_EXTERNAL void FANN_API fann_set_quickprop_mu(struct fann *ann, float quickprop_mu);

/* Tells how much the stepsize should increase during learning (default 1.2). */
FANN_EXTERNAL float FANN_API fann_get_rprop_increase_factor(struct fann *ann);

/* Tells how much the stepsize should increase during learning (default 1.2). */
FANN_EXTERNAL void FANN_API fann_set_rprop_increase_factor(struct fann *ann, float rprop_increase_factor);

/* Tells how much the stepsize should decrease during learning (default 0.5). */
FANN_EXTERNAL float FANN_API fann_get_rprop_decrease_factor(struct fann *ann);

/* Tells how much the stepsize should decrease during learning (default 0.5). */
FANN_EXTERNAL void FANN_API fann_set_rprop_decrease_factor(struct fann *ann, float rprop_decrease_factor);

/* The minimum stepsize (default 0.0). */
FANN_EXTERNAL float FANN_API fann_get_rprop_delta_min(struct fann *ann);

/* The minimum stepsize (default 0.0). */
FANN_EXTERNAL void FANN_API fann_set_rprop_delta_min(struct fann *ann, float rprop_delta_min);

/* The maximum stepsize (default 50.0). */
FANN_EXTERNAL float FANN_API fann_get_rprop_delta_max(struct fann *ann);

/* The maximum stepsize (default 50.0). */
FANN_EXTERNAL void FANN_API fann_set_rprop_delta_max(struct fann *ann, float rprop_delta_max);	
	
/* Get the number of input neurons.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_num_input(struct fann *ann);

/* Get the number of output neurons.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_num_output(struct fann *ann);

/* Get the total number of neurons in the entire network.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_total_neurons(struct fann *ann);

/* Get the total number of connections in the entire network.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_total_connections(struct fann *ann);

#ifdef FIXEDFANN

/* returns the position of the decimal point.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_decimal_point(struct fann *ann);

/* returns the multiplier that fix point data is multiplied with.
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_multiplier(struct fann *ann);
#endif /* FIXEDFANN */
	
/* ----- Implemented in fann_error.c Access error information about the ANN ----- */
	
/* change where errors are logged to
 */
FANN_EXTERNAL void FANN_API fann_set_error_log(struct fann_error *errdat, FILE *log_file);

/* returns the last error number
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_errno(struct fann_error *errdat);

/* resets the last error number
 */
FANN_EXTERNAL void FANN_API fann_reset_errno(struct fann_error *errdat);

/* resets the last error string
 */
FANN_EXTERNAL void FANN_API fann_reset_errstr(struct fann_error *errdat);

/* returns the last errstr.
 * This function calls fann_reset_errno and fann_reset_errstr
 */
FANN_EXTERNAL char * FANN_API fann_get_errstr(struct fann_error *errdat);

/* prints the last error to stderr
 */
FANN_EXTERNAL void FANN_API fann_print_error(struct fann_error *errdat);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __fann_h__ */

#endif /* NOT FANN_INCLUDE */
