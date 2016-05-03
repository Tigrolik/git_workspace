function sh_mask = dem_shaderel(I, sun_ang)

% degrees => radians
deg2radcoeff = pi / 180;
azi = sun_ang(1) * deg2radcoeff;
zen = sun_ang(2) * deg2radcoeff;

[Nx, Ny, Nz] = surfnorm(I);

Ct = cos(zen);
%{
Sp = sin(azi); Cp = cos(azi); St = sin(zen);
g1 = Nx * Ct * Sp;
g2 = Ny * Ct * Cp;
g3 = Nz * St;
g = g1 + g2 + g3;
%}
g = Nx * Ct * sin(azi) + Ny * Ct * cos(azi) + Nz * sin(zen);

cmap = hsv(16);
cmaplen = 256;
num_clr_chnl = max(2, floor(cmaplen / length(cmap(:,1))));

clr_shd_num = 256;
clr_chnl_num = num_clr_chnl;

gmin = min(g(:));
gindx = floor(1 + (g - gmin) * clr_chnl_num / (max(g(:)) - gmin));
gindx(gindx > clr_chnl_num) = clr_shd_num;

cmin = min(I(:));
Iindx = floor(1 + (I - cmin) * clr_shd_num / (max(I(:)) - cmin));
Iindx(Iindx > clr_shd_num) = clr_shd_num;

shad_indx = clr_shd_num * (gindx - 1) + double(Iindx);

sh_mask = false(size(g));
sh_mask(g < 0) = true;

% v_x = cos(zen) * sin(azi);
% v_y = cos(zen) * cos(azi);
% v_z = sin(zen);
% v = [v_x, v_y, v_z];

% sh_m = zeros(size(I));
% 
% for j = 1:size(Nx, 1)
%     for k = 1:size(Nx, 2)
%         u = [Nx(j, k), Ny(j, k), Nz(j, k)];
%         angle = atan2(norm(cross(v, u)), dot(v, u));
%         if (angle / deg2radcoeff) > 90
%             sh_m(j, k) = true;
%         end
%     end
% end


