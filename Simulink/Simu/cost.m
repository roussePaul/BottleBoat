function [ c ] = cost( X )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    global m;
    global n;
    global N;
    global Xf;
    global h;
    
    % We select the time prop in X
    select = [repmat([zeros(m-1, 1); 1], N+1, 1); zeros(N*n,1)];
    newX = ceil(X.*select);
    
    distance = sqrt(abs(X(N*m+1)-Xf(1,1))^2 + abs(X(N*m+2)-Xf(2,1))^2);
    speed = sqrt(abs(X(N*m+5))^2+ abs(X(N*m+6))^2);
    
    if(speed < 0.1)
        speed=0.1;
    end
    
    c = h*sum(newX) + (distance)*ceil(X(N*m+9));

end

