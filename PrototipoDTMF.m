% https://tty1.net/blog/2009/audio-with-gnu-octave_en.html

% For the FFT
%http://appliedelectronicsengineering.blogspot.com/2015/08/matlab-audioread-and-audiowrite-examples.html

Flc = [697,770,852,941];
Fhc = [1209,1336,1477,1633];
Fs = 44100;
nsec = input ("Duration of tone in seconds: ");
N = Fs*nsec;
n = linspace(0,nsec,N);
in = "g";
name="Fl Fh";
for Fl = Flc
  Fl
  for Fh = Fhc
    Fh
    xn = 0.5*(cos(2*pi*Fl*n) + cos(2*pi*Fh*n));
    player = audioplayer (xn, 44100, 8);
    play (player)
    %name = sprintf("Fl_%d-Fh_%d.wav",Fl,Fh);
    %audiowrite(name, xn, Fs);
    in=kbhit();
    endfor
  endfor 
%plot (xn);


