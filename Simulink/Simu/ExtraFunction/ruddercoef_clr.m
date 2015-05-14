
%------------------------------------------------------------------------------------------------------------------------------
function [Clr] = ruddercoef_clr(attack)
% generate a lookup table for the lift/drag coefficients for the sail
% and compute Cls/Cds from the lookup table using interpolation.

% lookup table
xdata = linspace(-pi,pi,73); % every 5 degrees
xdata = xdata/pi*180;

% lift curve
yl = fliplr([0 0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16])*(-1);
yldata = [fliplr([0 0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16 0 yl])*(-1) ...
    [0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16 0 yl]];

% drag curve
yd = fliplr([0 0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05]);
yddata = [fliplr([0 0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05 2.08 yd])...
    [0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05 2.08 yd]];

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
Clr = interp1(xdata,yldata,attack,'pchip');
