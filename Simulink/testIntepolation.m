x = attacks.Data;
D = [interSim.Data,x]
trueSim.Data

error = 2*((D-(trueSim.Data))./(D+trueSim.Data))




i=7;
j=1;
x1 = x(:,j);
x2 = trueSim.Data(:,7+j);
e = error(:,i)
s = trueSim.Data(:,i);
f = interSim.Data(:,i);
c = arrayfun(@(x)ruddercoef_cdr(x),x1)

l1 = s-f
l2 = s-c

[idx] = find(e>0.01)
r = [e(idx),x(idx),s(idx),f(idx),c(idx)]
%%

for i=1:size(attacks.Data,2)
    x = attacks.Data(:,i);
    e = error(:,i);
    [i,min(x), max(x)]
end
L = []
for i=1:size(error,2)
    e = error(:,i);
    L = [L;i,min(e), max(e)]
end
%%
sim('Test',2*pi)
figure(1)
clf
hold on
plot(ramp.Data,simout.Data(:,1),'.r')
plot(ramp.Data,simout.Data(:,2))

val = (2*abs(simout.Data(:,1)-simout.Data(:,2))./abs(simout.Data(:,1)+simout.Data(:,2)))

figure
plot(ramp.Data,val)