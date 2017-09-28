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

#ifndef __fann_errno_h__
#define __fann_errno_h__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Maximum length (in bytes) of an error message */
#define FANN_ERRSTR_MAX 128

enum {
	/* No error */
	FANN_E_NO_ERROR = 0,

	/* Unable to open configuration file for reading */
	FANN_E_CANT_OPEN_CONFIG_R,

	/* Unable to open configuration file for writing */
	FANN_E_CANT_OPEN_CONFIG_W,

	/* Wrong version of configuration file */
	FANN_E_WRONG_CONFIG_VERSION,

	/* Error reading info from configuration file */
	FANN_E_CANT_READ_CONFIG,

	/* Error reading neuron info from configuration file */
	FANN_E_CANT_READ_NEURON,

	/* Error reading connections from configuration file */
	FANN_E_CANT_READ_CONNECTIONS,

	/* Number of connections not equal to the number expected. */
	FANN_E_WRONG_NUM_CONNECTIONS,

	/* Unable to open train data file for writing */
	FANN_E_CANT_OPEN_TD_W,

	/* Unable to open train data file for reading. */
	FANN_E_CANT_OPEN_TD_R,

	/* Error reading training data from file. */
	FANN_E_CANT_READ_TD,

	/* Unable to allocate memory. */
	FANN_E_CANT_ALLOCATE_MEM,

	/* Unable to train with the selected activation function */
	FANN_E_CANT_TRAIN_ACTIVATION,

	/* Unable to use the selected activation function */
	FANN_E_CANT_USE_ACTIVATION,

	/* Irreconcilable differences between two fann_train_data structures */
	FANN_E_TRAIN_DATA_MISMATCH
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __fann_errno_h__ */
