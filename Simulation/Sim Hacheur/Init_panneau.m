clock = 16e6;
resolution = 7; %résolution en bits
V_Batt = 6;
RDS_on = 0.1;


steps = 2^resolution;
freq = clock/steps;

load VI.txt

current = VI(:,2);
voltage = VI(:,1);

rev_current = flipud(current);
rev_voltage = flipud(voltage);

