function imEnc(filename, cipher, randomKey, randomIV)

if ~exist('filename','var') || isempty(filename),filename='cameraman.tif'; end
if ~exist('cipher','var') || isempty(cipher),cipher='aes-128-cbc'; end
if ~exist('randomKey','var') ,randomKey = false; end
if ~exist('randomIV','var') ,randomIV = false; end

%'cast-cbc' 'bf-cfb', 'bf-ofb' interesting:  'idea-ecb' 'idea-ofb'


I = imread(filename);
if(size(I,3) ~= 1)
    I = rgb2gray(I);
end

Iw = size(I,1);
Ih = size(I,2);

[key, iv] = mexRandom('key','iv');

if(randomKey == false)
    key(:) = 0;
    keyStr = 'Key Zero';
else
    keyStr = 'Key Rand';
end

if(randomIV == false)
    iv(:) = 0;
    ivStr = 'IV Zero';
else
    ivStr = 'IV Rand';
end

Ienc = mexEVP_Encrypt('data',I(:),'key',key,'iv',iv,'cipher',cipher); 

subplot(2,2,1)
imagesc(I)
%colormap gray
title('Org Image')
axis off

subplot(2,2,3)
hist(double(I(:)),max(double(I(:))) - min(double(I(:))))

subplot(2,2,2)
imagesc(reshape(Ienc(1:Iw*Ih),Iw,Ih))
title([cipher ' Enc Image'])
axis off

subplot(2,2,4)
hist(double(Ienc(:)),max(double(I(:))) - min(double(I(:))))
title([keyStr ', ' ivStr])
fixfig
set(gcf,'color','white')