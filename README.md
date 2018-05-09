# MatlabOpenSSL

**Purpose** MatlabOpenSSL was written to bridge Matlab and OpenSSL with a toolbox like capability

## Background ##

**tutorial** https://agabrielson.wordpress.com/

The basic data type this code works with is a uint8.  Everything passed in and out of the encrypt and decrypt functions should a uint8 type (the example shows you how).  If your data type is not a uint8 you should convert it to a uint8 first.  The conversion methods provided by Mathworks cause data loss, so I have included my own methods to break the memory up into uint8 arrays rather lose data. To help with the process - 1 double = 8 bytes; 1 uint8 = 1 byte).

## Build Instructions ##

The buildMex script was provided to help build source if needed. Please verify your paths match the ones in buildMex, if they do not - change buildMex.

This code was originally built with OpenSSL 0.9.8l for windows (http://www.slproweb.com/products/Win32OpenSSL.html) & UNIX.  If you modify your installation path you will need to modify buildMex so this project will build on your platform.  With that said, this is dependent on OpenSSL, and you must install it if you want to use it.

This code was most recently tested with OpenSSL 1.0.2o for Mac OS. Matlab version R2015a. OS X version 10.13.4. The code was written awhile ago and may no longer work with all the originally tested compilers. I have heard the Microsoft compiler may throw a typedef warning or error. I do not currently have the Windows & Linux resources required test and fix if the issue actually exists.

## Running Instructions ##

When running mexEVP_Encrypt & mexEVP_Decrypt I would suggest doing your due diligence in terms of picking out a key, iv, and a cipher.  The choices I have made for defaults are not ideal.  If you look at the encrypt & decrypt functions they should support any cipher that is supported by OpenSSL and can be looked up by name, I have included a partial list but if you want to run another one I would suggest you look through the documentation.  I have found OpenSSL book helpful, it would probably be a worthwhile read if this code interests you.  If you need help determining what mode to run a cipher in I would suggest looking at the Wikipedia page as a good start: http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation

## Inventory ##

Function & Code Included

	example.m	Provides a few examples of how this code works
	buildMex.m	Builds the code needed to run this toolbox
	mexRandom	Generate a Random key and or IV
	mexEVP_Encrypt	Encrypt Data
	mexEVP_Decrypt	Decrypt Data
	double2uint8	convert a double to a uint8
	uint82double	convert a uint8 back to a double

## Notes ##
* More conversions may be needed, but one is provided as a start.  Others should be trivial to add with a basic programming understanding combined with the provided example.
* This basis of this code was put together quickly. I won't be shocked if a bug or two exists - please let me know.

