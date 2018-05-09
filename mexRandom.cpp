/*  mexEVP_Decrypt.cpp
 *  Examples:
 *	reference readme.txt
 *
 *  Notes:
 *	Lots - reference readme.txt
 *
 *  To Build:
 *	Reference buildMex
 *
 *  Author:
 *	Anthony Gabrielson
 *	agabrielson@me.com
 *      3/30/2010
 *
 *  Modifications:
 *
 */

#include "mex.h"
#include "matlabIO.hpp"
#include <openssl/rand.h>
#include <openssl/evp.h> 
#include <string> 

using namespace std;

void select_random_key(char *key, int b);
void select_random_iv(char *iv, int b);
int  seed_prng(void);
void help();

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
    bool keySet = false, ivSet = false;
    char key[EVP_MAX_KEY_LENGTH] = "this's my key";
    char iv[EVP_MAX_IV_LENGTH] = "my iv";
    string cmd;

    for (int inputProc = 0; inputProc < nrhs; ) {
        getStr( &prhs[inputProc++], cmd );
        if (cmd == "key") {
            keySet = true;
        } else if(cmd == "iv") {
            ivSet = true;
        }else{
            printf("Input Confusion: %s\n",cmd.c_str());
            mexErrMsgTxt( cmd.c_str() );
        }
    }

    if( keySet == false && ivSet == false ){
        help();
        return;
    }

    //OpenSSL automatically manages PRNG entropy (see function notes)
    //if (!seed_prng()){
    //	mexPrintf("seed_prng()...\n");
    //	return;
    //}

    select_random_key(key, EVP_MAX_KEY_LENGTH);
    select_random_iv(iv, EVP_MAX_IV_LENGTH);

    //Send the data back to Matlab.
    int output = 0;
    if( keySet == true )
        sendType(&plhs[output++], key, EVP_MAX_KEY_LENGTH, 1);
    if( ivSet == true )
        sendType(&plhs[output++], iv, EVP_MAX_IV_LENGTH, 1);
}

/*
 *  select_random_key:  Computes a Psuedo Random Key
 *  Inputs: 
 *      char *:	The key to be computed
 *		int:	The length of the key to be computed		
 *
 * Notes:
 *      This function is from the OpenSSL book
 */
void select_random_key(char *key, int b)
{
    RAND_bytes((unsigned char *) key, b);
    //for (int i = 0; i < b - 1; i++)
    //	printf("%02X:", key[i]);

    //printf("%02X\n", key[b - 1]);
}

/*
 *  select_random_iv:  Computes a Psuedo Random IV
 *  Inputs: 
 *      char *:	The key to be computed
 *		int:	The length of the key to be computed		
 *
 * Notes:
 *      This function is from the OpenSSL book
 */
void select_random_iv(char *iv, int b)
{
    RAND_pseudo_bytes((unsigned char *) iv, b);
}

/*
 *  seed_prng:  Seed the random number generator
 *  Inputs: 	
 *
 * Notes:
 *		The OpenSSL code already uses /dev/urandom if 
 *			available as well as other sources. On Windows 
 *			it uses CryptGenRandom() among other things.
 */
int seed_prng(void)
{	    
#ifdef _WIN32
    RAND_screen();
    return 1;
#else
    return RAND_load_file("/dev/urandom", 1024);
#endif
}

void help()
{
    mexPrintf("mexRandom:\n");
    mexPrintf("\tkey: Generate a key\n");
    mexPrintf("\tiv: Generate a iv\n");
    mexPrintf("If generating both a key and an iv the first return\n\tvalue will be the key and the second will be the iv.\n");
}
