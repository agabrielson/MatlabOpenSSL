function buildMex(enblDbg)
%   Examples:
%       buildMex    Defaults to false
%       buildMex(true) or buildMex(false)
%
%   Takes:
%       enblDbg:   Enable Debug mode (defaults false)
%
%   Notes:
%       false has no debugging symbols (DEFAULT)
%       true has debugging symbols
%
%   Author:
%       Anthony Gabrielson

% OS X Edits: Added new dirs to check at bottom
%   edit /Applications/MATLAB_R2015a.app/bin/maci64/mexopts/clang++_maci64.xml
%   edit /Applications/MATLAB_R2015a.app/bin/maci64/mexopts/clang_maci64.xml

if ~exist('enblDbg','var') || isempty(enblDbg),enblDbg=false; end

filenames = dir('*.c*');

options = ' -v ';
if(enblDbg)
   options = [options ' -g ']; 
end

if(ispc()) 
    fprintf(1,'Building PC...\n');
    options = [' C:\openssl\lib\libeay32.lib -IC:\openssl\include ' options];
elseif(ismac())
    fprintf(1,'Building Mac...\n');
    options = [options ' -I/usr/local/ssl/include -lssl -lcrypto '];
elseif(isunix())
    fprintf(1,'Building UNIX...\n');
    options = [options ' -I/usr/local/ssl/lib -lssl -lcrypto '];
end

for J=1:length(filenames)
    cmd = ['mex ' filenames(J).name options];
    eval(cmd);
end

% if(ispc())
%     switch enblDbg
%         case false  % 0
%             mex -IC:\openssl\include -v mexEVP_Encrypt.cpp C:\openssl\lib\libeay32.lib
%             mex -IC:\openssl\include -v mexEVP_Decrypt.cpp C:\openssl\lib\libeay32.lib
%             mex -IC:\openssl\include -v mexRandom.cpp C:\openssl\lib\libeay32.lib
%             mex -v double2uint8.cpp
%             mex -v uint82double.cpp
%         case true   % 1 Debug Symbols
%             mex -IC:\openssl\include -g -v mexEVP_Encrypt.cpp C:\openssl\lib\libeay32.lib
%             mex -IC:\openssl\include -g -v mexEVP_Decrypt.cpp C:\openssl\lib\libeay32.lib
%             mex -IC:\openssl\include -g -v mexRandom.cpp C:\openssl\lib\libeay32.lib
%             mex -g -v double2uint8.cpp
%             mex -g -v uint82double.cpp
%         otherwise
%             fprintf('Debug Mode Invalid (not true or false)\n');
%     end
% elseif(isunix())
%     switch enblDbg
%         case false  % 0
%             mex -I/usr/local/ssl/lib -v mexEVP_Encrypt.cpp -lssl -lcrypto
%             mex -I/usr/local/ssl/lib -v mexEVP_Decrypt.cpp -lssl -lcrypto
%             mex -I/usr/local/ssl/lib -v mexRandom.cpp -lssl -lcrypto
%             mex -v double2uint8.cpp
%             mex -v uint82double.cpp
%         case true   % 1 Debug Symbols
%             mex -I/usr/local/ssl/lib -g -v mexEVP_Encrypt.cpp -lssl -lcrypto
%             mex -I/usr/local/ssl/lib -g -v mexEVP_Decrypt.cpp -lssl -lcrypto
%             mex -I/usr/local/ssl/lib -g -v mexRandom.cpp -lssl -lcrypto
%             mex -g -v double2uint8.cpp
%             mex -g -v uint82double.cpp
%         otherwise
%             fprintf('Debug Mode Invalid (not true or false)\n');
%     end
% end