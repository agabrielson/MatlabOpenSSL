//cl test_AES.c /IC:\openssl\include /linkC:\openssl\lib\libeay32.lib
//gcc test_AES.c -L/usr/local/ssl/lib/ -lssl -lcrypto -Wall

#include <stdio.h>
#include <stdlib.h> 
#include <strings.h>
#include <openssl/evp.h> 

int main(void) { 

    char plaintext[1024] = "Hello World? - this is a test of AES! of which I'm curious to see if it really is working.\n";
    char ciphertext[1024]= {0,};
    char mykey[EVP_MAX_KEY_LENGTH] = "this's my key";
    char iv[EVP_MAX_IV_LENGTH] = "my iv";
    int tmp_len = 0, in_len, out_len=0;
    EVP_CIPHER_CTX ctx;

    //memset(mykey,0,sizeof(mykey));
    //memset(iv,0,sizeof(iv));

    in_len = strlen(plaintext);

    printf("No encrypt: %s\n", plaintext);

    //Encrypt
    EVP_EncryptInit(&ctx, EVP_aes_128_cbc(), (unsigned char *)mykey, (unsigned char *)iv);
    EVP_EncryptUpdate(&ctx, (unsigned char *)ciphertext, &out_len, (unsigned char *)plaintext, in_len);	//Block through the mem to be encrypted
    tmp_len += out_len;
    EVP_EncryptFinal(&ctx, (unsigned char *) &ciphertext[out_len], &out_len); //Finish any remaining encryption and throw a pad on
    tmp_len += out_len;
    printf("Encrypted: %s\n", ciphertext);

    //Reset memory for Decryption
    memset(plaintext,0,sizeof(plaintext));
    in_len = tmp_len;
    out_len = tmp_len = 0;

    //decrypt
    EVP_DecryptInit(&ctx, EVP_aes_128_cbc(), (unsigned char *)mykey, (unsigned char *)iv);
    EVP_DecryptUpdate(&ctx, (unsigned char *)plaintext, &out_len, (unsigned char *)ciphertext, in_len);
    tmp_len += out_len;
    EVP_DecryptFinal(&ctx, (unsigned char *)&plaintext[out_len], &out_len);
    tmp_len += out_len;

    //Zero out the pad
    memset(&plaintext[tmp_len],0,(int)(sizeof(plaintext)) - tmp_len);

    printf("Decrypted: %s\n", plaintext);

    printf("Block Size: %d\n",EVP_CIPHER_CTX_block_size(&ctx));

    return 0;
} 
