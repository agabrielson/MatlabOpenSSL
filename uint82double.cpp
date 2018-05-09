/*  uint82double.cpp
 *  Examples:
 *      doubleData = uint82double(uin8Data(1:7));
 *	Ref example.m for a more complete example
 *
 *  Notes:
 *	This code will convert data from a uint8 array to double
 *	uint8s should be in blocks that are the same size as a double...
 *
 *  To Build:
 *	Reference buildMex
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

    getData( &prhs[0], data.uData, sizeof(double) );

    sendType(&plhs[0], data.dData);

    return;
}

void help(void)
{
    mexPrintf("uint82double help: Convert a uint8 array to a double\n");
    mexPrintf("\tdoubleData = uint82double(uint8([0; 0; 0; 0; 0; 0; 16; 64])) %equals 4\n");
}
