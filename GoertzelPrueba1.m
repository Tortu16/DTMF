%Intento de Goertzel

%Cargamos un tono de Prueba: Fl = 770 y Fh = 1336
cd ~
[tono,Fs] = audioread ("Tono 5 slightly smaller.wav");

% Decimacion por un factor de 5 de Fs = 44100 a Fs = 8820 
tono2 = [0];
l=rows (tono)-1;
for i = [5:5:l];
tono2(i/5) = tono(i);
endfor 

y =[0];

for f = [200:5:1500];
y (f) = Goertzel (tono2,f,8820,256);
endfor

plot (y)