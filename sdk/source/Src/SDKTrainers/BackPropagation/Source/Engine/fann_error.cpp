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
#include "fann_internal.h"
#include "fann_errno.h"

#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#define snprintf _snprintf
#endif

/* resets the last error number
 */
FANN_EXTERNAL void FANN_API fann_reset_errno(struct fann_error *errdat)
{
	errdat->errno_f = 0;
}

/* resets the last errstr
 */
FANN_EXTERNAL void FANN_API fann_reset_errstr(struct fann_error *errdat)
{
	if ( errdat->errstr != NULL )
		free(errdat->errstr);
	errdat->errstr = NULL;
}

/* returns the last error number
 */
FANN_EXTERNAL unsigned int FANN_API fann_get_errno(struct fann_error *errdat)
{
	return errdat->errno_f;
}

/* returns the last errstr
 */
FANN_EXTERNAL char * FANN_API fann_get_errstr(struct fann_error *errdat)
{
	char *errstr = errdat->errstr;

	fann_reset_errno(errdat);
	fann_reset_errstr(errdat);

	return errstr;
}

/* change where errors are logged to
 */
FANN_EXTERNAL void FANN_API fann_set_error_log(struct fann_error *errdat, FILE *log_file)
{
	errdat->error_log = log_file;
}

/* prints the last error to the error log (default stderr)
 */
FANN_EXTERNAL void FANN_API fann_print_error(struct fann_error *errdat) {
	if ( (errdat->errno_f != FANN_E_NO_ERROR) && (errdat->error_log != NULL) ){
		fputs(errdat->errstr, errdat->error_log);
	}
}

/* INTERNAL FUNCTION
   Populate the error information
 */
void fann_error(struct fann_error *errdat, const unsigned int errno_f, ...)
{
	va_list ap;
	char * errstr;

	if (errdat != NULL) errdat->errno_f = errno_f;
	
	if(errdat != NULL && errdat->errstr != NULL){
		errstr = errdat->errstr;
	}else{
		errstr = (char *)malloc(FANN_ERRSTR_MAX);
		if(errstr == NULL){
			fprintf(stderr, "Unable to allocate memory.\n");
			return;
		}
	}

	va_start(ap, errno_f);
	switch ( errno_f ) {
	case FANN_E_NO_ERROR:
		break;
	case FANN_E_CANT_OPEN_CONFIG_R:
		vsprintf(errstr, "Unable to open configuration file \"%s\" for reading.\n", ap);
		break;
	case FANN_E_CANT_OPEN_CONFIG_W:
		vsprintf(errstr, "Unable to open configuration file \"%s\" for writing.\n", ap);
		break;
	case FANN_E_WRONG_CONFIG_VERSION:
		vsprintf(errstr, "Wrong version of configuration file, aborting read of configuration file \"%s\".\n", ap);
		break;
	case FANN_E_CANT_READ_CONFIG:
		vsprintf(errstr, "Error reading info from configuration file \"%s\".\n", ap);
		break;
	case FANN_E_CANT_READ_NEURON:
		vsprintf(errstr, "Error reading neuron info from configuration file \"%s\".\n", ap);
		break;
	case FANN_E_CANT_READ_CONNECTIONS:
		vsprintf(errstr, "Error reading connections from configuration file \"%s\".\n", ap);
		break;
	case FANN_E_WRONG_NUM_CONNECTIONS:
		vsprintf(errstr, "ERROR connections_so_far=%d, total_connections=%d\n", ap);
		break;
	case FANN_E_CANT_OPEN_TD_W:
		vsprintf(errstr, "Unable to open train data file \"%s\" for writing.\n", ap);
		break;
	case FANN_E_CANT_OPEN_TD_R:
		vsprintf(errstr, "Unable to open train data file \"%s\" for writing.\n", ap);
		break;
	case FANN_E_CANT_READ_TD:
		vsprintf(errstr, "Error reading info from train data file \"%s\", line: %d.\n", ap);
		break;
	case FANN_E_CANT_ALLOCATE_MEM:
		sprintf(errstr, "Unable to allocate memory.\n");
		break;
	case FANN_E_CANT_TRAIN_ACTIVATION:
		sprintf(errstr, "Unable to train with the selected activation function.\n");
		break;
	case FANN_E_CANT_USE_ACTIVATION:
		sprintf(errstr, "Unable to use the selected activation function.\n");
		break;
	case FANN_E_TRAIN_DATA_MISMATCH:
		sprintf(errstr, "Training data must be of equivalent structure.");
		break;
	default:
		vsprintf(errstr, "Unknown error.\n", ap);
		break;
	}
	va_end(ap);

	if ( errdat == NULL ) {
		fprintf(stderr, "FANN Error %d: %s", errno_f, errstr);
	} else {
		errdat->errstr = errstr;
		if ( errdat->error_log != NULL ) {
			fprintf(errdat->error_log, "FANN Error %d: %s", errno_f, errstr);
		}
	}
}

/* INTERNAL FUNCTION
   Initialize an error data strcuture
 */
void fann_init_error_data(struct fann_error *errdat)
{
	errdat->errstr = NULL;
	errdat->errno_f = 0;
	errdat->error_log = stderr;
}
