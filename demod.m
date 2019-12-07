% demodulatedulation Code
 clc;
 clear all;
 close all; 
 
fileID = fopen('output.txt','r');
formatSpec = '%f';
Modulated = fscanf(fileID,formatSpec);

mes1 = max(Modulated(40:80));
mes2 = max(Modulated(160:200));
mes3 = max(Modulated(280:320));
mes4 = max(Modulated(400:440));

demodulated(1:120) = mes1/2666;
demodulated(120:240) = mes2/2666;
demodulated(240:360) = mes3/2666;
demodulated(360:480) = mes4/2666;

figure;
subplot(2, 1, 1); title('Modulated Signal'); plot(Modulated);
subplot(2, 1, 2); title('demodulatede Modulated'); plot(demodulated);