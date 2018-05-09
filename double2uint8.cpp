/*  double2uint8.cpp
 *  Examples:
 *      uint8Data = double2uint8(4);
 *	Ref example.m for a more complete example
 *
 *  Notes:
 *	This code will convert data from a double to uint8 array
 *
 *  To Build:
 *      Reference buildMex
 *
 *  Author:
 *	Anthony Gabrielson
 *	agabrielson@me.com
 *      3/26/2010
 *
 *  Modifications:
 *	3/29/2010	Added a bit more documentation and cleaned up the code presentation
 *
 */

#include "mex.h"
#include "matlabIO.hpp"

void help(void);

typedef union {
    uint8 uData[8];
    double dData;
} convData;

/*
 *  mexFunction:  Matlab entry function into this C code
 *  Inputs: 
 *      int nlhs:   Number of left hand arguments (output)
 *      mxArray *plhs[]:   The left hand arguments (output)
 *      int nrhs:   Number of right hand arguments (inputs)
 *      const mxArray *prhs[]:   The right hand arguments (inputs)
 *
 * Notes:
 *      (Left)  goes_out = foo(goes_in);    (Right)
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{	
    if( nrhs != nlhs || nrhs == 0){
        mexPrintf("improper input...\n");
        help();
        return;
    }

    convData data;

    getNumeric( &prhs[0], data.dData );

    sendType(&plhs[0], &data.uData[0], 8, 1);

    return;
}

void help(void)
{
    mexPrintf("double2uint8 help: convert a uint8 array to double\n");
    mexPrintf("\tuint8Data = double2uint8(double(4))\n");
}
