%------------------------------------------------------------------------------------------------------------------------------
function [y,Clk,Cdk] = keelcoef(attack)
% generate a lookup table for the lift/drag coefficients for the sail
% and compute Cls/Cds from the lookup table using interpolation.

% lookup table
xdata = linspace(-pi,pi,73); % every 5 degrees
xdata = xdata/pi*180;

% lift curve
yl = fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185])*(-1);
yldata = [fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 yl])*(-1) ...
    [0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 yl]];

% drag curve
yd = fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05]);
yddata = [fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 yd])...
    [0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 yd]];

% fit the input angle of attack into the interval [-pi,pi]
if attack > pi
    attack = mod(attack+pi,2*pi) - pi;
else
    if attack < -pi
        attack = mod(attack-pi,-2*pi) + pi;
    end
end

% interpolation
attack = attack/pi*180;
Clk = interp1(xdata,yldata,attack,'pchip');
Cdk = interp1(xdata,yddata,attack,'pchip');
