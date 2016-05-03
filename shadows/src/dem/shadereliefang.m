function sh_mask = shadereliefang(I, res, sun_ang)

if numel(res) < 2
    x_res = res; y_res = res;
else
    x_res = res(1); y_res = res(2);
end
% degrees => radians
rad = pi / 180;
azi = (sun_ang(1) - 90) * rad;
zen = sun_ang(2) * rad;
tan_zen = tan(zen);

% get normals to the surface
[Nx, Ny, Nz] = surfnorm(I);
Ct = cos(zen);
g = Nx * Ct * sin(azi) / (tan_zen * x_res) + ...
    Ny * Ct * cos(azi) / (tan_zen * y_res) + Nz * sin(zen);

sh_mask = false(size(g));
sh_mask(g < 0) = true;
