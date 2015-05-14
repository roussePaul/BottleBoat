%% Lookuptable

nbre_pts = 100;

% sail coeff
% lookup table
alphacoeff_xdata = linspace(-pi,pi,73); % every 5 degrees
alphacoeff_xdata = alphacoeff_xdata;

% lift curve
alphacoeff_yldata = [fliplr([0 0.15 0.32 ...
    0.48 0.7 0.94 1.15 1.3 1.28 1.15 1.1 1.05 1 0.9 0.82 0.72 0.68 0.56 0.48 0.32 0.21 0.08 ...
    -0.06 -0.18 -0.3 -0.4 -0.53 -0.64 -0.72 -0.84 -0.95 -1.04 -1.1 -1.14 -1.08 -0.76 0])*(-1) ...
    [0.15 0.32 ...
    0.48 0.7 0.94 1.15 1.3 1.28 1.15 1.1 1.05 1 0.9 0.82 0.72 0.68 0.56 0.48 0.32 0.21 0.08 ...
    -0.06 -0.18 -0.3 -0.4 -0.53 -0.64 -0.72 -0.84 -0.95 -1.04 -1.1 -1.14 -1.08 -0.76 0]];

% drag curve
alphacoeff_yddata = [fliplr([0.1 0.12 0.14 ...
    0.16 0.19 0.26 0.35 0.46 0.54 0.62 0.7 0.78 0.9 0.98 1.04 1.08 1.16 1.2 1.24 1.26 ...
    1.28 1.34 1.36 1.37 1.33 1.31 1.28 1.26 1.25 1.2 1.1 1.04 0.88 0.8 0.64 0.38 0.1])...
    [0.12 0.14 ...
    0.16 0.19 0.26 0.35 0.46 0.54 0.62 0.7 0.78 0.9 0.98 1.04 1.08 1.16 1.2 1.24 1.26 ...
    1.28 1.34 1.36 1.37 1.33 1.31 1.28 1.26 1.25 1.2 1.1 1.04 0.88 0.8 0.64 0.38 0.1]];

alphacoeff_xdata2 = linspace(-pi,pi,nbre_pts);
alphacoeff_xdata2 = alphacoeff_xdata2;
%alphacoeff_yldata = arrayfun(@(x)sailcoef_cls(x),alphacoeff_xdata2);
alphacoeff_yldata = interp1(alphacoeff_xdata,alphacoeff_yldata,alphacoeff_xdata2,'pchip');
alphacoeff_yddata = interp1(alphacoeff_xdata,alphacoeff_yddata,alphacoeff_xdata2,'pchip');
alphacoeff_xdata = alphacoeff_xdata2;

%%
% Rudder angle
% lookup table
ruddercoeff_xdata = linspace(-pi,pi,73); % every 5 degrees
ruddercoeff_xdata = ruddercoeff_xdata;

% lift curve
ruddercoeff_yl = fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185])*(-1);
ruddercoeff_yldata = [fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 ruddercoeff_yl])*(-1) ...
    [0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 ruddercoeff_yl]];

% drag curve
ruddercoeff_yd = fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05]);
ruddercoeff_yddata = [fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 ruddercoeff_yd])...
    [0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 ruddercoeff_yd]];

ruddercoeff_xdata2 = linspace(-pi,pi,nbre_pts);
ruddercoeff_xdata2 = ruddercoeff_xdata2;
ruddercoeff_yldata = interp1(ruddercoeff_xdata,ruddercoeff_yldata,ruddercoeff_xdata2,'pchip');
ruddercoeff_yddata = arrayfun(@(x)ruddercoef_cdr(x),ruddercoeff_xdata2);
%ruddercoeff_yddata = interp1(ruddercoeff_xdata,ruddercoeff_yddata,ruddercoeff_xdata2,'pchip');
ruddercoeff_xdata = ruddercoeff_xdata2;

%keelcoef

% lookup table
keelcoeff_xdata = linspace(-pi,pi,73); % every 5 degrees
keelcoeff_xdata = keelcoeff_xdata;

% lift curve
keelcoeff_yl = fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185])*(-1);
keelcoeff_yldata = [fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 keelcoeff_yl])*(-1) ...
    [0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 keelcoeff_yl]];

% drag curve
keelcoeff_yd = fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05]);
keelcoeff_yddata = [fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 keelcoeff_yd])...
    [0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 keelcoeff_yd]];

keelcoeff_xdata2 = linspace(-pi,pi,nbre_pts);
keelcoeff_xdata2 = keelcoeff_xdata2;
keelcoeff_yldata = interp1(keelcoeff_xdata,keelcoeff_yldata,keelcoeff_xdata2,'pchip');
keelcoeff_yddata = interp1(keelcoeff_xdata,keelcoeff_yddata,keelcoeff_xdata2,'pchip');
keelcoeff_xdata = keelcoeff_xdata2;

% resistance hull
hull_xdata2 = linspace(0,20,nbre_pts);
hull_ydata = arrayfun(@(x)resistancehull(x),hull_xdata2);
hull_xdata = hull_xdata2;
