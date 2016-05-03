function g = dem2shaderel(I, sun_ang)

% degrees => radians
deg2radcoeff = pi / 180;

azim = sun_ang(1) * deg2radcoeff;
elev = sun_ang(2) * deg2radcoeff;

d2r = pi/180; theta = elev*d2r; psi = azim*d2r;
St = sin(theta); Ct = cos(theta); Sp = sin(psi); Cp = cos(psi);

[X, Y] = meshgrid(1:size(I, 1), 1:size(I, 2));
[Nx,Ny,Nz] = surfnorm(X,Y,I);

g1 = Nx*Ct*Sp;
g2 = Ny*Ct*Cp;
g3 = Nz*St;
g = g1 + g2 + g3;
