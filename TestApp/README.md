# Test Apps

## imEnc.m

**Purpose** Use OpenSSL toolbox to encode and display an image

## test_AES.c

**Purpose** Short example to help learn and navigate OpenSSL land. It should go with out saying this code is not industrial strength and is really just a fun example to have fun with.

### Build Examples ###

This command line example shows the code building under widows with Visual C++ Express:

cl test_AES.c /IC:\openssl\include /linkC:\openssl\lib\libeay32.lib

This example moves on to building on UNIX - I'm using gcc with OS X:

gcc test_AES.c -L/usr/local/ssl/lib/ -lssl -lcrypto

With all of that said, what example could possible be complete without output:

### Output ###

No encrypt: Hello World? - this is a test of AES! of which I'm curious to see if it really is working.
Encrypted: ;|?|??`A ??)?????#?'??7E??/
Hv???G????b0&?/i???Y????????O??R?l?v?W??xT?ɡzp?????<?Y?aU
Decrypted: Hello World? - this is a test of AES! of which I'm curious to see if it really is working.


