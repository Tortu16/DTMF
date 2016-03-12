

N1 = 1;%no hay elemento 0 en vectores!
N2 = 44100;
N = N2-N1;
[x, fs] = audioread('Fl_697-Fh_1209.wav',[N1 N2]);

soundsc(x,fs)

X = fft(x);   % complex signal

Xmag = abs(X);   % magnitude
Xph = angle(X);   % phase

f = (0:N)*fs/N;  % frequency points
FFTmag = Xmag(1:end/10);

plot(FFTmag)

