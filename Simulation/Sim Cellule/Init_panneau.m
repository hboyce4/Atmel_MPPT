load VI.txt

current = VI(:,2);
voltage = VI(:,1);

rev_current = flipud(current);
rev_voltage = flipud(voltage);

plot(VI(:,2),VI(:,1));