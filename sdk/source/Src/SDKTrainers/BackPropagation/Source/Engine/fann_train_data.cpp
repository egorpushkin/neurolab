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

/* Reads training data from a file.
 */
FANN_EXTERNAL struct fann_train_data* FANN_API fann_read_train_from_file(char *configuration_file)
{
	struct fann_train_data* data;
	FILE *file = fopen(configuration_file, "r");

	if(!file){
		fann_error(NULL, FANN_E_CANT_OPEN_CONFIG_R, configuration_file);
		return NULL;
	}

	data = fann_read_train_from_fd(file, configuration_file);
	fclose(file);
	return data;
}

/* Save training data to a file
 */
FANN_EXTERNAL void FANN_API fann_save_train(struct fann_train_data* data, char *filename)
{
	fann_save_train_internal(data, filename, 0, 0);
}

/* Save training data to a file in fixed point algebra.
   (Good for testing a network in fixed point)
*/
FANN_EXTERNAL void FANN_API fann_save_train_to_fixed(struct fann_train_data* data, char *filename, unsigned int decimal_point)
{
	fann_save_train_internal(data, filename, 1, decimal_point);
}

/* deallocate the train data structure.
 */
FANN_EXTERNAL void FANN_API fann_destroy_train(struct fann_train_data *data)
{
	if(data == NULL) return;
	fann_safe_free(data->input[0]);
	fann_safe_free(data->output[0]);
	fann_safe_free(data->input);
	fann_safe_free(data->output);
	fann_safe_free(data);
}

#ifndef FIXEDFANN

/* Internal train function */
float fann_train_epoch_quickprop(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;

	if(ann->prev_train_slopes == NULL){
		fann_clear_train_arrays(ann);
	}
	
	fann_reset_MSE(ann);
	
	for(i = 0; i < data->num_data; i++){
		fann_run(ann, data->input[i]);
		fann_compute_MSE(ann, data->output[i]);
		fann_backpropagate_MSE(ann);
		fann_update_slopes_batch(ann);
	}
	fann_update_weights_quickprop(ann, data->num_data);

	return fann_get_MSE(ann);
}

/* Internal train function */
float fann_train_epoch_irpropm(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;

	if(ann->prev_train_slopes == NULL){
		fann_clear_train_arrays(ann);
	}
	
	fann_reset_MSE(ann);
	
	for(i = 0; i < data->num_data; i++){
		fann_run(ann, data->input[i]);
		fann_compute_MSE(ann, data->output[i]);
		fann_backpropagate_MSE(ann);
		fann_update_slopes_batch(ann);
	}
	fann_update_weights_irpropm(ann, data->num_data);

	return fann_get_MSE(ann);
}

/* Internal train function */
float fann_train_epoch_batch(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;
	fann_reset_MSE(ann);
	
	for(i = 0; i < data->num_data; i++){
		fann_run(ann, data->input[i]);
		fann_compute_MSE(ann, data->output[i]);
		fann_backpropagate_MSE(ann);
		fann_update_slopes_batch(ann);
	}
	fann_update_weights_batch(ann, data->num_data);

	return fann_get_MSE(ann);
}

/* Internal train function */
float fann_train_epoch_incremental(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;
	fann_reset_MSE(ann);
	
	for(i = 0; i != data->num_data; i++){
		fann_train(ann, data->input[i], data->output[i]);
	}

	return fann_get_MSE(ann);
}

/* Train for one epoch with the selected training algorithm
 */
FANN_EXTERNAL float FANN_API fann_train_epoch(struct fann *ann, struct fann_train_data *data)
{
	switch(ann->training_algorithm){
		case FANN_TRAIN_QUICKPROP:
			return fann_train_epoch_quickprop(ann, data);
			break;
		case FANN_TRAIN_RPROP:
			return fann_train_epoch_irpropm(ann, data);
			break;
		case FANN_TRAIN_BATCH:
			return fann_train_epoch_batch(ann, data);
			break;
		case FANN_TRAIN_INCREMENTAL:
			return fann_train_epoch_incremental(ann, data);
			break;
		default:
			return 0.0;
	}
}

/* Test a set of training data and calculate the MSE
 */
FANN_EXTERNAL float FANN_API fann_test_data(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;
	fann_reset_MSE(ann);
	
	for(i = 0; i != data->num_data; i++){
		fann_test(ann, data->input[i], data->output[i]);
	}

	return fann_get_MSE(ann);
}

/* Train directly on the training data.
 */
FANN_EXTERNAL void FANN_API fann_train_on_data_callback(struct fann *ann, struct fann_train_data *data, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error, int (FANN_API *callback)(unsigned int epochs, float error))
{
	float error;
	unsigned int i;

#ifdef DEBUG
	printf("Training with ");
	switch(ann->training_algorithm){
		case FANN_TRAIN_QUICKPROP:
			printf("FANN_TRAIN_QUICKPROP");
			break;
		case FANN_TRAIN_RPROP:
			printf("FANN_TRAIN_RPROP");
			break;
		case FANN_TRAIN_BATCH:
			printf("FANN_TRAIN_BATCH");
			break;
		case FANN_TRAIN_INCREMENTAL:
			printf("FANN_TRAIN_INCREMENTAL");
			break;
	}
	printf("\n");
#endif	
	
	if(epochs_between_reports && callback == NULL){
		printf("Max epochs %8d. Desired error: %.10f\n", max_epochs, desired_error);
	}

	/* some training algorithms need stuff to be cleared etc. before training starts.
	 */
	if(ann->training_algorithm == FANN_TRAIN_RPROP ||
		ann->training_algorithm == FANN_TRAIN_QUICKPROP){
		fann_clear_train_arrays(ann);
	}

	for(i = 1; i <= max_epochs; i++){
		/* train */
		error = fann_train_epoch(ann, data);
		
		/* print current output */
		if(epochs_between_reports &&
			(i % epochs_between_reports == 0
				|| i == max_epochs
				|| i == 1
				|| error < desired_error)){
			if (callback == NULL) {
				printf("Epochs     %8d. Current error: %.10f\n", i, error);
			} else if((*callback)(i, error) == -1){
				/* you can break the training by returning -1 */
				break;
			}
		}
		
		if(error < desired_error){
			break;
		}
	}
}

FANN_EXTERNAL void FANN_API fann_train_on_data(struct fann *ann, struct fann_train_data *data, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error)
{
	fann_train_on_data_callback(ann, data, max_epochs, epochs_between_reports, desired_error, NULL);
}


/* Wrapper to make it easy to train directly on a training data file.
 */
FANN_EXTERNAL void FANN_API fann_train_on_file_callback(struct fann *ann, char *filename, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error, int (FANN_API *callback)(unsigned int epochs, float error))
{
	struct fann_train_data *data = fann_read_train_from_file(filename);
	if(data == NULL){
		return;
	}
	fann_train_on_data_callback(ann, data, max_epochs, epochs_between_reports, desired_error, callback);
	fann_destroy_train(data);
}

FANN_EXTERNAL void FANN_API fann_train_on_file(struct fann *ann, char *filename, unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error)
{
	fann_train_on_file_callback(ann, filename, max_epochs, epochs_between_reports, desired_error, NULL);
}

#endif

/* shuffles training data, randomizing the order
 */
FANN_EXTERNAL void FANN_API fann_shuffle_train_data(struct fann_train_data *train_data) {
	unsigned int dat = 0, elem, swap;
	fann_type temp;

	for ( ; dat < train_data->num_data ; dat++ ) {
		swap = (unsigned int)(rand() % train_data->num_data);
		if ( swap != dat ) {
			for ( elem = 0 ; elem < train_data->num_input ; elem++ ) {
				temp = train_data->input[dat][elem];
				train_data->input[dat][elem] = train_data->input[swap][elem];
				train_data->input[swap][elem] = temp;
			}
			for ( elem = 0 ; elem < train_data->num_output ; elem++ ) {
				temp = train_data->output[dat][elem];
				train_data->output[dat][elem] = train_data->output[swap][elem];
				train_data->output[swap][elem] = temp;
			}
		}
	}
}

/* merges training data into a single struct.
 */
FANN_EXTERNAL struct fann_train_data * FANN_API fann_merge_train_data(struct fann_train_data *data1, struct fann_train_data *data2) {
	struct fann_train_data * train_data;
	unsigned int x;

	if ( (data1->num_input  != data2->num_input) ||
	     (data1->num_output != data2->num_output) ) {
		fann_error(NULL, FANN_E_TRAIN_DATA_MISMATCH);
		return NULL;
	}

	train_data = (struct fann_train_data *)malloc(sizeof(struct fann_train_data));

	fann_init_error_data((struct fann_error *)train_data);

	train_data->num_data = data1->num_data + data2->num_data;
	train_data->num_input = data1->num_input;
	train_data->num_output = data1->num_output;

	if ( ((train_data->input  = (fann_type **)calloc(train_data->num_data, sizeof(fann_type *))) == NULL) ||
	     ((train_data->output = (fann_type **)calloc(train_data->num_data, sizeof(fann_type *))) == NULL) ) {
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(train_data);
		return NULL;
	}
	for ( x = 0 ; x < train_data->num_data ; x++ ) {
		if ( ((train_data->input[x]  = (fann_type *)calloc(train_data->num_input,  sizeof(fann_type))) == NULL) ||
		     ((train_data->output[x] = (fann_type *)calloc(train_data->num_output, sizeof(fann_type))) == NULL) ) {
			fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
			fann_destroy_train(train_data);
			return NULL;
		}
		memcpy(train_data->input[x],
		       ( x < data1->num_data ) ? data1->input[x]  : data2->input[x - data1->num_data],
		       train_data->num_input  * sizeof(fann_type));
		memcpy(train_data->output[x],
		       ( x < data1->num_data ) ? data1->output[x] : data2->output[x - data1->num_data],
		       train_data->num_output * sizeof(fann_type));
	}

	return train_data;
}

/* return a copy of a fann_train_data struct
 */
FANN_EXTERNAL struct fann_train_data * FANN_API fann_duplicate_train_data(struct fann_train_data *data)
{
	unsigned int i;
	fann_type *data_input, *data_output;
	struct fann_train_data* dest = (struct fann_train_data *)malloc(sizeof(struct fann_train_data));

	if(dest == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		return NULL;
	}

	fann_init_error_data((struct fann_error *)dest);

	dest->num_data = data->num_data;
	dest->num_input = data->num_input;
	dest->num_output = data->num_output;
	dest->input = (fann_type **)calloc(dest->num_data, sizeof(fann_type *));
	if(dest->input == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(dest);
		return NULL;
	}
	
	dest->output = (fann_type **)calloc(dest->num_data, sizeof(fann_type *));
	if(dest->output == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(dest);
		return NULL;
	}
	
	data_input = (fann_type *)calloc(dest->num_input*dest->num_data, sizeof(fann_type));
	if(data_input == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(dest);
		return NULL;
	}
	memcpy(data_input, data->input[0], dest->num_input*dest->num_data*sizeof(fann_type));

	data_output = (fann_type *)calloc(dest->num_output*dest->num_data, sizeof(fann_type));
	if(data_output == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(dest);
		return NULL;
	}
	memcpy(data_output, data->output[0], dest->num_output*dest->num_data*sizeof(fann_type));

	for(i = 0; i != dest->num_data; i++){
		dest->input[i] = data_input;
		data_input += dest->num_input;
		dest->output[i] = data_output;
		data_output += dest->num_output;
	}
	return dest;
}

/* INTERNAL FUNCTION
   Reads training data from a file descriptor.
 */
struct fann_train_data* fann_read_train_from_fd(FILE *file, char *filename)
{
	unsigned int num_input, num_output, num_data, i, j;
	unsigned int line = 1;
	fann_type *data_input, *data_output;
	struct fann_train_data* data = (struct fann_train_data *)malloc(sizeof(struct fann_train_data));

	if(data == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		return NULL;
	}
	
	if(fscanf(file, "%u %u %u\n", &num_data, &num_input, &num_output) != 3){
		fann_error(NULL, FANN_E_CANT_READ_TD, filename, line);
		fann_destroy_train(data);
		return NULL;
	}
	line++;

	fann_init_error_data((struct fann_error *)data);

	data->num_data = num_data;
	data->num_input = num_input;
	data->num_output = num_output;
	data->input = (fann_type **)calloc(num_data, sizeof(fann_type *));
	if(data->input == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(data);
		return NULL;
	}
	
	data->output = (fann_type **)calloc(num_data, sizeof(fann_type *));
	if(data->output == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(data);
		return NULL;
	}
	
	data_input = (fann_type *)calloc(num_input*num_data, sizeof(fann_type));
	if(data_input == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(data);
		return NULL;
	}

	data_output = (fann_type *)calloc(num_output*num_data, sizeof(fann_type));
	if(data_output == NULL){
		fann_error(NULL, FANN_E_CANT_ALLOCATE_MEM);
		fann_destroy_train(data);
		return NULL;
	}
	
	for(i = 0; i != num_data; i++){
		data->input[i] = data_input;
		data_input += num_input;
		
		for(j = 0; j != num_input; j++){
			if(fscanf(file, FANNSCANF" ", &data->input[i][j]) != 1){
				fann_error(NULL, FANN_E_CANT_READ_TD, filename, line);
				fann_destroy_train(data);
				return NULL;
			}
		}
		line++;
		
		data->output[i] = data_output;
		data_output += num_output;
		
		for(j = 0; j != num_output; j++){
			if(fscanf(file, FANNSCANF" ", &data->output[i][j]) != 1){
				fann_error(NULL, FANN_E_CANT_READ_TD, filename, line);
				fann_destroy_train(data);
				return NULL;
			}
		}
		line++;
	}
	return data;
}
