%   Examples:
%       example
%
%   Takes:
%       N/A
%
%   Gives:
%       N/A
%
%   Notes:
%       A few example of how to run the OpenSSL toolbox
%
%   Author:
%       Anthony Gabrielson
%		agabriel@home.tzo.org
%       3/26/2010
%
%   Modifications:
%       3/30/2010   Added example 1c & 1d

% Test 1a: Basic Encryption / Decryption
dataToEncrypt = uint8(1:255);
encryptedData = mexEVP_Encrypt('data',dataToEncrypt);
decrypted = mexEVP_Decrypt('data',encryptedData);

if( sum(dataToEncrypt' - decrypted) == 0 )
    fprintf(1,'Test 1a Passed\n');
else
    fprintf(1,'Test 1a Problem...\n');
end

clear 

% Test 1b: Basic Encryption / Decryption - different key & algorithm
dataToEncrypt = uint8(1:255);
encryptedData = mexEVP_Encrypt('data',dataToEncrypt,'key','another key!','cipher','bf-cbc');
decrypted = mexEVP_Decrypt('data',encryptedData,'key','another key!','cipher','bf-cbc');

if( sum(dataToEncrypt' - decrypted) == 0 )
    fprintf(1,'Test 1b Passed\n');
else
    fprintf(1,'Test 1b Problem...\n');
end

clear 

% Test 1c: Basic Encryption / Decryption - random key & algorithm
dataToEncrypt = uint8(1:255);
[key, iv] = mexRandom('key','iv');
encryptedData = mexEVP_Encrypt('data',dataToEncrypt,'key',key,'iv',iv,'cipher','bf-cbc');
decrypted = mexEVP_Decrypt('data',encryptedData,'key',key,'iv',iv,'cipher','bf-cbc');

if( sum(dataToEncrypt' - decrypted) == 0 )
    fprintf(1,'Test 1c Passed\n');
else
    fprintf(1,'Test 1c Problem...\n');
end

clear 

% Test 1d: Basic Encryption / Decryption with strings
dataToEncrypt = ['0':'9','a':'z','A':'Z'];
encryptedData = mexEVP_Encrypt('data',uint8(dataToEncrypt));
decrypted = mexEVP_Decrypt('data',encryptedData);

dataDecrypted = char(decrypted');
if( strcmp(dataToEncrypt,dataDecrypted) == 1 )
    fprintf(1,'Test 1d Passed\n');
else
    fprintf(1,'Test 1d Problem...\n');
end

clear 

%Test 2: Data Conversion
dataStart = 1:255;

toUint8 = [];
for J=1:length(dataStart)
     temp = double2uint8(dataStart(J));
     toUint8 = [toUint8; temp];
end

toDouble = [];
for J=1:8:length(toUint8)
     temp = uint82double(toUint8(J:J+7));
     toDouble = [toDouble; temp];
end

if( sum(dataStart' - toDouble) == 0 )
    fprintf(1,'Test 2 Passed\n');
else
    fprintf(1,'Test 2 Problem...\n');
end

clear

%Test 3: Data Conversion + Encryption
dataStart = 1:255;

toUint8 = [];
for J=1:length(dataStart)
     temp = double2uint8(dataStart(J));
     toUint8 = [toUint8; temp];
end

encryptedData = mexEVP_Encrypt('data',toUint8);
decrypted = mexEVP_Decrypt('data',encryptedData);

toDouble = [];
for J=1:8:length(decrypted)
     temp = uint82double(decrypted(J:J+7));
     toDouble = [toDouble; temp];
end

if( sum(dataStart' - toDouble) == 0 )
    fprintf(1,'Test 3 Passed\n');
else
    fprintf(1,'Test 3 Problem...\n');
end

clear