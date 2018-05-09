#pragma once

/* MatlabIO.hpp
 */

#include "mex.h"
#include "types.h"
#include <string>
#include <limits>

using namespace std;

/*
 *  getNumeric:  Gets dnumeric data from a Matlab argument.
 *
 *  Inputs: 
 *      const mxArray **prhs: Right hand side argument with data
 *		Type &data: variable that matlab argument will map into.
 *
 *  Returns:
 *      (Type) the data
 */
template<class Type>
void getNumeric( const mxArray **prhs, Type &data )
{ 
    int         number_of_dimensions, total_elements;  
    const int   *ldims;
    
	if (mxIsNumeric(*prhs) == 0) 
		mexErrMsgTxt("Not numbers...\n");

	string cName = mxGetClassName(*prhs);
    
    total_elements = mxGetNumberOfElements(*prhs);
    number_of_dimensions = mxGetNumberOfDimensions(*prhs);
    ldims = mxGetDimensions(*prhs);

    if( number_of_dimensions != 2 || total_elements != 1)
		mexErrMsgTxt("getNumeric: Inproper input...\n");
   
    //Map incoming data to Type
	if( cName == "uint8" ){
		uint8 *pr = static_cast<uint8 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "uint16" ){
		uint16 *pr = static_cast<uint16 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "uint32" ){
		uint32 *pr = static_cast<uint32 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "uint64" ){
		uint64 *pr = static_cast<uint64 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "int8" ){
		int8 *pr = static_cast<int8 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "int16" ){
		int16 *pr = static_cast<int16 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "int32" ){
		int32 *pr = static_cast<int32 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "int64" ){
		int64 *pr = static_cast<int64 *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else if( cName == "double" ){
		double *pr = static_cast<double *>(mxGetData(*prhs));
		data = static_cast<Type>(*pr);
	}else{
		printf("Type Confusion: %s\n",cName.c_str());
	}

    return;
}

/*
 *  getData:  Gets a string from a Matlab argument.
 *
 *  Inputs: 
 *      mxArray **prhs: Right hand side argument to get string
 *      Type [] Data coming from matlab.
 *		size_t	size of the array
 */
template<class Type>
int getData( const mxArray **prhs, Type data[], size_t elem_len )
{ 
	Type		*pr;  
	size_t		total_elements; 
	const int   *ldims;
    
	total_elements = mxGetNumberOfElements(*prhs);
	int ndims = mxGetNumberOfDimensions(*prhs);

	ldims = mxGetDimensions(*prhs);
	    
	pr = static_cast<Type*>(mxGetData(*prhs));

	size_t	cpy_len = elem_len;
	if(total_elements < cpy_len)
		cpy_len = total_elements;

	memcpy(&data[0],pr,cpy_len);

	return 0;
}

/*
 *  getStr:  Gets a string from a Matlab argument.
 *
 *  Inputs: 
 *      mxArray **prhs: Right hand side argument to get string
 *      (char **) String coming from matlab.
 */
void getStr( const mxArray **prhs, string &str )
{ 
    char *temp_str;
	int	index = 0; 
	size_t tot_elem = 0; 
    
    if ( mxIsNumeric(*prhs) == 0 ) {  //User specifing numbers
		tot_elem = mxGetNumberOfElements(*prhs)+1;
        //Allocate memory using dynamic memory allocation routine mxCalloc 
        temp_str = (char *)mxCalloc( (tot_elem) ,sizeof(char));       
        mxGetString(*prhs, temp_str, tot_elem);
		str = temp_str;
	} else {
		mexErrMsgTxt("getStr: Inproper input...\n");
	}   

	return;
}

/*
 *  sendStr:  Sends a string back to Matlab.
 *
 *  Inputs: 
 *      mxArray **plhs: Left hand side argument to send string
 *      (char **) String going to matlab.
 *		or
 *		(char *) String coming from matlab.
 */

void sendStr( mxArray **plhs, string &str )
{ 
	*plhs = mxCreateString(str.c_str());
       
	return;
}

/*
 *  sendBool:  Sends a bool back to a Matlab argument. (True/False)
 *
 *  Inputs: 
 *      mxArray **plhs: Left hand side argument
 *      bool: true/false to go back to Matlab.
 */
void sendBool(mxArray **plhs, bool result)
{
    bool *start_of_pr;   
	const int ndims = 1;
	const mwSize dims[]={1,1};

    //Create a dims[0] by dims[1] array of logical bits. 
    *plhs = mxCreateNumericArray(ndims,dims,mxLOGICAL_CLASS,mxREAL); 
                                  
    //Populate the the created array.
    start_of_pr = static_cast<bool *>(mxGetData(*plhs));
	*start_of_pr = result;
	
    return;
}

/*
 *  sendDouble:  Sends a double back to a Matlab argument.
 *
 *  Inputs: 
 *      mxArray **plhs: Left hand side argument 
 *      Type: (double) to go back to Matlab.
 */
template<class Type>
void sendDouble(mxArray **plhs, Type &result)
{
    double *start_of_pr;  
	const int ndims = 1;
	const mwSize dims[]={1,1};

    //Create a dims[0] by dims[1] array of logical bits. 
    *plhs = mxCreateNumericArray(ndims,dims,mxDOUBLE_CLASS,mxREAL); 
                                  
    //Populate the the created array.
    start_of_pr = static_cast<double *>(mxGetData(*plhs));
	*start_of_pr = static_cast<double>(result);
	
    return;
}

/*
 *  sendType:  Sends a double back to a Matlab argument.
 *
 *  Inputs: 
 *      mxArray **plhs: Left hand side argument 
 *      Type: (double) to go back to Matlab.
 */
template<class Type>
void sendType(mxArray **plhs, Type result)
{
    Type *start_of_pr;   
	const int ndims = 1;
	const mwSize dims[]={1,1};
	mxClassID out_type;
	
	if(std::numeric_limits<Type>::max() == std::numeric_limits<uint8>::max())
		out_type = mxUINT8_CLASS; 
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint16>::max())
		out_type = mxUINT16_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint32>::max())
		out_type = mxUINT32_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint64>::max())
		out_type = mxUINT64_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int8>::max())
		out_type = mxINT8_CLASS; 
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int16>::max())
		out_type = mxINT16_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int32>::max())
		out_type = mxINT32_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int64>::max())
		out_type = mxINT64_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<double>::max())
		out_type = mxDOUBLE_CLASS;

    //Create a dims[0] by dims[1] array of logical bits. 
    *plhs = mxCreateNumericArray(ndims,dims,out_type,mxREAL); 
                                  
    //Populate the the created array.
    start_of_pr = static_cast<Type *>(mxGetData(*plhs));
	*start_of_pr = result;

    return;
}

template<class Type>
void sendType(mxArray **plhs, Type *result, int length = 1, int width = 1)
{
    Type *start_of_pr;   
	size_t bytes_to_copy;
	int ndims = 1;
	const mwSize dims[]={length,width};

	if(length>1 && width>1)
		ndims = 2;

	mxClassID out_type;
	
	if(std::numeric_limits<Type>::max() == std::numeric_limits<uint8>::max())
		out_type = mxUINT8_CLASS; 
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint16>::max())
		out_type = mxUINT16_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint32>::max())
		out_type = mxUINT32_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<uint64>::max())
		out_type = mxUINT64_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int8>::max())
		out_type = mxINT8_CLASS; 
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int16>::max())
		out_type = mxINT16_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int32>::max())
		out_type = mxINT32_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<int64>::max())
		out_type = mxINT64_CLASS;
	else if(std::numeric_limits<Type>::max() == std::numeric_limits<double>::max())
		out_type = mxDOUBLE_CLASS;

    //Create a dims[0] by dims[1] array of logical bits. 
    *plhs = mxCreateNumericArray(ndims,dims,out_type,mxREAL); 
                                  
    //Populate the the created array.
    start_of_pr = static_cast<Type *>(mxGetData(*plhs));	
	bytes_to_copy = length * width * mxGetElementSize(*plhs);
	memcpy((void *)start_of_pr, result, bytes_to_copy);// Populate the the created array.

    return;
}
