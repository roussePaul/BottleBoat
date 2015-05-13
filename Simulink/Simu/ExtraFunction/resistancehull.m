function F = resistancehull(alpha_a)

    xdata = linspace(0,6,13); % every 0.5m/s
    ydata = [0 0.15 0.35 0.5 0.675 0.825 1.175 1.4 2 4.85 9.85 18.46 27.5]*1000;

    % interpolation
    if alpha_a <= 6
        F = interp1(xdata,ydata,alpha_a,'pchip');
    else
        F = interp1(xdata,ydata,alpha_a,'pchip','extrap');
    end
end