% Calcula el coeficiente de Goertzel

% xn = tono
%fk = 770; 
%fs=8820;
%N = 256


function GoertzelCoeff = Goertzel (xn, fk, fs , N)
GoertzelCoeff = 1;

if (nargin != 4)
usage ("Goertzel espera xn: el audio a analizar, fk: la frecuencia a calcular el coeficiente y fs: la frecuencia de muestreo, N:El tamaño de la muestra en el tiempo (resolucion en frecuencia)")
endif

w2 = 0; % wk(n-2)
w1 = 0; %wk(n-1)
wk = 0;

for i  = [1:N];
w2 = w1;
w1 = wk;
wk = xn(i) + 2*cos(2*pi*fk/fs)*w1-w2;
endfor

Xk = w1^2 - 2*cos(2*pi*fk/fs)*w1*w2 + w2^2;

GoertzelCoeff = Xk

endfunction