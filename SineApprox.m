%% Sin approximation



c1 = 26-15*sqrt(3)
c2 = 810000*(1657+930*sqrt(3))
c3 = 324000*(19+15*sqrt(3))
c4 = -1800*(1+15*sqrt(3))
c5 = -360

o  = 35;
o2 = o*o;
o3 = o2*o;
o4 = o3*o;

ho = ( c1*o*(180-o)*(c2+c3*o+c4*o2+c5*o3+o4) )/524880000000
error = sin(pi*o/180) - ho


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       
%
%
%             Luis Diego Jimenez Mora
%
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



% Funciones relacionadas a la interfaz de usuario.


% Ejemplo de la tarea F=5/7;
F=697;
%Ejemplo de la tarea Fs=1;
Fs=8000;
%Ejemplo de la tarea C=5;
C=2;

%Pasos intermedios auxiliares.


%Calculamos el periodo de la señal analogica
T=1/F;
%Revisa el criterio de Nyquist
%Si la frecuencia de muestreo es menor a la frecuencia de Nyquist
if ( Fs < 2*F )
%La frecuencia del alias es la frecuencia de muestreo menos la frecuencia real.
  Fa=Fs-F
% En caso contrario
else
% La señal se puede recuperar y no hay aliasing.
  Fa=F
endif 

%Se construye el arreglo de la variable independiente analogica. Se elige arbitrariamente 100 puntos por periodo
t=[0:0.0001*T:C*T];
%Construye el arreglo de la variable independiente discreta a partir del numero de ciclos y la tasa de muestreo
n=[0:1/Fs:C*T];
%Calcula los valores de la señal discreta
%sinn=sin(2*pi*F*n);uahhñ

o = mod(n*(2*697*180)+90,180)
part1=c2+c3*o+c4*(realpow(o,2))+c5*(realpow(o,3))+(realpow(o,4));
sinn = ( c1*o.*(180-o).*(part1) )/524880000000;


%Funciones de graficacion


%Grafica la señal analogica
labelF= strcat("-b;F ="," ",num2str(F), ";");
plot(t,sin(2*pi*F*t),labelF)
%Congela el grafico para agregar la señal discreta
hold on
%Grafica la señal alias
labelFa= strcat("-r;Falias ="," ",num2str(Fa), ";");
plot(t,cos(2*pi*Fa*t),labelFa)
% Grafica la señal discreta
labeln= strcat("ok;Fs ="," ",num2str(Fs), ";");
stem (n, sinn, labeln)

hold off
