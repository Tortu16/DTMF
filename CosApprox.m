% https://www.gnu.org/software/octave/doc/interpreter/Defining-Functions.html#Defining-Functions

function retCos = CosApprox (F,Fs,t)
if (nargin != 3)
usage ("CosApprox (Tone Frequency (Hz), Sampling Frequency (S/s), Tone Duration(s))");
endif

T=1/F;

n=[0:1/Fs:t];

retCos = [0];
retCos(end+length(n)-1) = 0;

% Coeficientes del polinomio
c1 = 26-15*sqrt(3)
c2 = 810000*(1657+930*sqrt(3))
c3 = 324000*(19+15*sqrt(3))
c4 = -1800*(1+15*sqrt(3))
c5 = -360

% Preprocesado

o = mod(n*(2*F*180)+90,180);
o2 = mod(n*(2*F*180)+90,360);
quadrant = 2*sign (o-o2)+1;

% Calculo de la aproximacion cosenoidal en dos partes.
part1=c2+c3*o+c4*(realpow(o,2))+c5*(realpow(o,3))+(realpow(o,4));
sinn = quadrant.*( c1*o.*(180-o).*(part1) )/524880000000;

% Output return value

retCos = sinn;

endfunction