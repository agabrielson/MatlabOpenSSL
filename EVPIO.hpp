#pragma once

#include "mex.h"
#include "types.h" 

typedef struct {
	int elem;
	uint8 *mem;
}data;

/*
 *  getData:  Gets data from a Matlab argument.
 *  Inputs: 
 *      const mxArray **prhs: Right hand side argument with data
 *      (data &) Pointer to the data structure.
 *	Notes:
 *		This function is written specifically for use with the data struct
 */
void getData( const mxArray **prhs, data &data2Enc )
{ 
    void	*pr;
    int		total_elements; 
    
	if (mxIsNumeric(*prhs) == 0) 
		mexErrMsgTxt("Not numbers...\n");
    
    total_elements = mxGetNumberOfElements(*prhs);
    data2Enc.elem = total_elements;
    pr = mxGetData(*prhs);
    
	data2Enc.mem = static_cast<uint8*>(pr);

    return;
}