/*  mexEVP_Decrypt.cpp
 *  Examples:
 *      reference readme.txt
 *
 *  Notes:
 *	reference readme.txt
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
 *	3/29/2010	Added a bit more documentation
 *
 */

#include "mex.h"
#include "EVPIO.hpp"
#include "matlabIO.hpp"
#include <openssl/evp.h>
#include <string> 
#include <stdlib.h> 

void decrypt(data &encData, data &plainData, char key[], char iv[], string cipher);
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
    char key[EVP_MAX_KEY_LENGTH] = "this's my key";
    char iv[EVP_MAX_IV_LENGTH] = "my iv";
    string cmd, keyStr, ivStr, cipher;
    data plainData, encData;
    plainData.elem = 0;
    encData.elem = 0;

    for (int inputProc = 0; inputProc < nrhs; ) {
        getStr( &prhs[inputProc++], cmd );
        if (cmd == "data") {
            getData( &prhs[inputProc++], encData );
        } else if(cmd == "key") {
            memset(key,0,EVP_MAX_KEY_LENGTH);
            getData( &prhs[inputProc++], key, EVP_MAX_KEY_LENGTH );
        } else if(cmd == "iv") {
            memset(iv,0,EVP_MAX_IV_LENGTH);
            getData( &prhs[inputProc++], iv, EVP_MAX_IV_LENGTH );
        } else if(cmd == "cipher") {
            getStr( &prhs[inputProc++], cipher );
        } else {
            mexPrintf("Input Confusion: %s\n",cmd.c_str());
            mexErrMsgTxt( cmd.c_str() );
        }
    }

    if(encData.elem == 0){
        help();
        mexPrintf("Data not set...\n");
        return;
    }

    //Decrypt the data
    decrypt(encData, plainData, key, iv, cipher);

    //Send the decrypted data back to Matlab.
    sendType(&plhs[0], plainData.mem, plainData.elem, 1);
}

void decrypt(data &encData, data &plainData, char key[], char iv[], string cipher)
{ 
    OpenSSL_add_all_algorithms();	//EVP_get_cipherbyname will not work with out this

    const EVP_CIPHER *cipher_type;	//For cipher choice

    cipher_type = EVP_get_cipherbyname(cipher.c_str());

    if( cipher_type == NULL ){
        if(cipher.length() != 0)
            mexPrintf("Defaulting to: EVP_aes_128_cbc()\n");
        cipher_type = EVP_aes_128_cbc();	//Default to AES is there is a problem
    }

    EVP_CIPHER_CTX ctx;
    EVP_DecryptInit(&ctx, cipher_type, (const unsigned char *) key, (const unsigned char *) iv);

    //Need to allocate the encrypted memory
    int in_len = encData.elem;
    int malloc_len = in_len;
    plainData.mem = static_cast<uint8*>(mxCalloc(malloc_len, sizeof(char)));

    int out_len = 0, update, final;
    EVP_DecryptUpdate(&ctx, (unsigned char *) plainData.mem, &update, encData.mem, in_len);
    EVP_DecryptFinal(&ctx, (unsigned char *) &plainData.mem[update], &final);	

    out_len = update + final;
    plainData.elem = out_len;

    return;
} 

void help()
{
    mexPrintf("mexEVP_Decrypt:\n");
    mexPrintf("data: What data would you like to encrypt?  This is the only required option...\n");
    mexPrintf("key: what key would you like the data it be encrypted with?\n");
    mexPrintf("IV: The intialization vector used to speed some algorithms up\n");
    mexPrintf("Supported Ciphers: (Reference OpenSSL documentation for current & complete list)\n");
    mexPrintf("\tCurrently Defaults to: aes-128-cbc\n");
    mexPrintf("\tAES: aes-128-ecb, aes-128-cbc, aes-192-ecb, aes-192-cbc, aes-256-ecb, aes-256-cbc\n");
    mexPrintf("\tBlowfish: bf-ecb, bf-cbc, bf-cfb, bf-ofb\n");
    mexPrintf("\tCast: cast-ecb, cast-cbc, cast-cfb, cast-ofb\n");
    mexPrintf("\tDES: des-ecb, des-cbc, des-cfb, des-ofb\n");
    mexPrintf("\tDESX: desx\n");
    mexPrintf("\t3DES: des-ede3, des-ede3-cbc, des-ede3-cfb, des-ede3-ofb, des-ede, des-ede-cbc, des-ede-cfb, des-ede-ofb\n");
    mexPrintf("\tIDEA: idea-ecb, idea-cbc, idea-cfb, idea-ofb\n");
}
