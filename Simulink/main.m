%% Control of a sailing boat with non linear MPC
clear all;
close all;
clc;

global m;
global n;
global N;
global Xf;
global h;

% Parameter
N = 20;% Number of step for MPC
h = 0.5; % Time step of the simulation
angleMaxRudder = pi/3;
angleMaxSail = pi/2;
posMaxYw = 0;

Xf = [-3 -4; -3 -4]; % 2x2 Matrix for final field (:,1) lb corner and (:,2) tr
Xb = [-5 5; -5 5]; % 2x2 Matrix size of the board same as before

X0 = [0; 0]; % Initial position
V0 = [1; 1]; % Initial velocity

%% Initialization
X = [X0; 0; 0; V0; 0; 0];
Xinit = X;
[a,b,c,d] = linmod('simple', X);
[a,b,c,d] = ssdata(c2d(ss(a,b,c,d), h));
[m,n] = size(b);
a = [a zeros(m,1); zeros(1, m+1)];
b = [b zeros(m,1); zeros(1, n) 1];
[m,n] = size(b);

%% Creation of matrix Aeq and Beq
Tinf = tril(ones(N+1)-tril(ones(N+1), -2), -1);
Btilde = [zeros(m, n*N); 
          kron(eye(N), -b)];
Aeq = [kron(Tinf, -a)+eye(m*(N+1)), Btilde];
Beq = [X; 1; zeros((N)*m, 1)];

%% Creation of constraints
% Constraints on the control and make a binary variable
constraints = [angleMaxRudder; angleMaxSail; posMaxYw; 1]; % On the command
lb = [repmat([-Inf*ones(m-1, 1); 0], N+1, 1); repmat(-constraints, N, 1)];
ub = [repmat([Inf*ones(m-1, 1); 1], N+1, 1);  repmat(constraints , N, 1)];

% Constraints on the binary variable
B = repmat(-Xf(:,1), N+1, 1);
Atilde = [-eye(2), zeros(2, 6), (Xb(:,1)-Xf(:,1))];
A = [kron(eye(N+1), Atilde), zeros(2*(N+1), n*N)];

B = [B; repmat(Xf(:,2), N+1, 1)];
Atilde = [eye(2), zeros(2, 6), (Xf(:,2)-Xb(:,2))];
A = [A; [kron(eye(N+1), Atilde), zeros(2*(N+1), n*N)]];

% Optimization
approx = [X; 1; zeros(N*m,1); zeros(n*N, 1)];
options = optimset('Display','iter');
[x, tps] = fmincon(@cost,approx,A,B,Aeq,Beq,lb,ub,[],options);

Xboat = [x((0:N)*m+1)'; x((0:N)*m+2)'];
Xbool = x((0:N)*m+9)';
XboolMax = (Xboat(1,:)-Xf(1,1))/(Xb(1,1)-Xf(1,1));
XboolMin = (Xboat(1,:)-Xf(1,2))/(Xb(1,2)-Xf(1,2));
XboolMax2 = (Xboat(2,:)-Xf(2,1))/(Xb(2,1)-Xf(2,1));
XboolMin2 = (Xboat(2,:)-Xf(2,2))/(Xb(2,2)-Xf(2,2));
control = [x((N+1)*m+(0:(N-1))*n+1)'; x((N+1)*m+(0:(N-1))*n+2)'; x((N+1)*m+(0:(N-1))*n+3)'];
deltaR = timeseries(control(1,:)', (0:(N-1))*h);
deltaS = timeseries(control(2,:)', (0:(N-1))*h);

% Plot of the trajectory
figure(1)
plot(Xboat(1,:), Xboat(2,:));
axis([Xb(1,1) Xb(1,2) Xb(2,1) Xb(2,2)]);
hold on;
plot([Xf(1,1) Xf(1,1) Xf(1, 2) Xf(1,2) Xf(1,1)], [Xf(2,1) Xf(2,2) Xf(2,2) Xf(2,1) Xf(2,1)], '--k')

% Plot of the boolean
figure(2)
hold on;
plot(Xbool);
plot(XboolMin', '--r');
plot(XboolMax', '--k');
plot(XboolMin2', '--r');
plot(XboolMax2', '--k');

% Plot of the control
figure(3)
hold on
plot(control(1,:), 'r');
plot(control(2,:), 'k');
plot(control(3,:), 'g');
legend('Radder', 'Sail', 'Gravity Center');