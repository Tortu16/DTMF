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


% Frecuencia del tono
F=697;
% Frecuencia de muestreo recomendada por el enunciado;
Fs=8000;
% En la practica, esto depende del tiempo que el usuario presione el boton;
C=5;

%Pasos intermedios auxiliares.


%Calculamos el periodo de la señal analogica
T=1/F;
%Se asume que se cumple el criterio de Nyquist para todo

% Se construye una variable analogica para comparar efectividad
%Se construye el arreglo de la variable independiente analogica. Se elige arbitrariamente 100 puntos por periodo
t=[0:0.0001*T:C*T];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       
%
%      Calculo de los valores de la señal discreta
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Construye el arreglo de la variable independiente discreta a partir del numero de ciclos y la tasa de muestreo
n=[0:1/Fs:C*T];

% Coeficientes del polinomio
c1 = 26-15*sqrt(3)
c2 = 810000*(1657+930*sqrt(3))
c3 = 324000*(19+15*sqrt(3))
c4 = -1800*(1+15*sqrt(3))
c5 = -360

% Preprocesado

% Conversion de variable discreta a grados entre 0 y 180 (region de convergencia para la aproximacion polinomial)
o = mod(n*(2*F*180)+90,180);

% Calculo del cuadrante mediante la diferencia entre el modulo a 180 y a 360 grados.
o2 = mod(n*(2*F*180)+90,360);
quadrant = 2*sign (o-o2)+1;

% Calculo de la aproximacion cosenoidal en dos partes.
part1=c2+c3*o+c4*(realpow(o,2))+c5*(realpow(o,3))+(realpow(o,4));
sinn = quadrant.*( c1*o.*(180-o).*(part1) )/524880000000;


%Funciones de graficacion


%Grafica la señal analogica
labelF= strcat("-b;Fs = 8000 Hz", ";");
plot(t,cos(2*pi*F*t),labelF)
%Congela el grafico para agregar la señal discreta
hold on
%Grafica la señal alias
labelFa= strcat("-r;Fcos ="," ",num2str(Fa)," Hz", ";");
plot(t,cos(2*pi*Fa*t),labelFa)
% Grafica la señal discreta
labeln= strcat("ok;Fs ="," ",num2str(Fs), ";");
stem (n, sinn, labeln)

hold off
