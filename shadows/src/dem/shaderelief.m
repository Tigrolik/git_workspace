function sh_mask = shaderelief(I, res, azi, zen)

if numel(res) < 2
    x_res = res; y_res = res;
else
    x_res = res(1); y_res = res(2);
end

tan_zen = tan(zen);

% get normals to the surface
[Nx, Ny, Nz] = surfnorm(I);
Ct = cos(zen);
g = Nx .* Ct .* sin(azi) ./ (tan_zen * x_res) + ...
    Ny .* Ct .* cos(azi) ./ (tan_zen * y_res) + Nz .* sin(zen);
clear tan_zen Ct Nx Ny Nz

sh_mask = g < 0;
