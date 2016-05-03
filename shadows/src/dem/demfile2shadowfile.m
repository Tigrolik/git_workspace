function [sh_mask, I, geo_dem] = demfile2shadowfile(fn, sun_ang)

% get the index of a dot before the extension of the file
ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
fmt = lower(fn(ext_ind:end));
azi = sun_ang(1);
zen = sun_ang(2);
% read DEM data & calculate shadow pixels
if ~isempty(license('inuse', 'map_toolbox')) && strfind('.tiff', fmt)
    [I, R] = geotiffread(fn);
    geo_dem.lon = linspace(R.Lonlim(1), R.Lonlim(2), R.RasterSize(1));
    geo_dem.lat = linspace(R.Latlim(1), R.Latlim(2), R.RasterSize(2));
%     [X, Y] = meshgrid(R.Lonlim(1):R.DeltaLon:R.Lonlim(2), ...
%         R.Latlim(2):R.DeltaLat:R.Latlim(1));
    res = 90;
    sh_mask = shadowdem(I, res, azi, zen);
    sh_mask = imclose(sh_mask, strel('disk', 3));
    R.RasterSize = size(sh_mask);
    geotiffwrite([fn(1:ext_ind(end)-1) '_shmask_georef'], ...
        sh_mask, R);
else
    [I, res, geo_dem] = readdem(fn, fmt);
    [s1, s2] = size(I);
    sh_mask = shadowdem(I, res, azi, zen);
    if (size(sh_mask, 1) ~= s1) || (size(sh_mask, 2) ~= s2)
        sh_mask = sh_mask(2:end-1, 2:end-1);
        sh_mask = imclose(sh_mask, strel('disk', 3));
    end
end

% geo_dem = [linspace(max(ltln_dem(1, :)), ...
%     min(ltln_dem(1, :)), length(ltln_dem(1, :)) * 3); ...
%     linspace(min(ltln_dem(2, :)), max(ltln_dem(2, :)), ...
%     length(ltln_dem(2, :)) * 3)];
% I = imresize(I, 3);
% res = res / 3;
% [sh_mask, I] = dem2shadow2(I, res/3, sun_ang);
% [lat, lon] = readdemlatlon(fn, ext_ind);
% %     latlon = [linspace(lat + 1, lat, sz1(1)); ...
% %             linspace(lon, lon + 1, sz1(2))];
% sz3 = size(I);
% sz_t1 = sz3(1) - 1; sz_t2 = sz3(2) - 1;
% latlon = [lat + (1 / sz_t1 ) * (0:sz_t1); ...
%     lon + (1 / sz_t2 ) * (0:sz_t2)];
% sh_mask = dem_shaderel(I, sun_ang);
% pix_num_lim = 50;
% sh_mask = bwareaopen(sh_mask, pix_num_lim, 4);
% sh_mask = dem2shadow(I, res, sun_ang);
% sh_mask = imresize(sh_mask, 3);

% sh_mask = dem2shadow3(I, res, sun_ang);
% ltln_dem = geo_dem;
% [x, y] = find(sh_mask > 0);
% geo_dem(1, :) = sort(geo_dem(1, :), 'descend');
% x = geo_dem(1, x);
% y = geo_dem(2, y);
% 
% n_str = num2str(numel(num2str(max(ceil(abs(x))))) + 3);
% fid = fopen('test.txt', 'w');
% fprintf(fid, ['%' n_str '.2f' ' %' n_str '.2f\n'], [x; y]);
% fclose(fid);

% H = demh2d(I, geo_dem);

% % compute shaded relief
% shad_indx = uint16(dem_shaderel(I, sun_ang)) * 20;
%
% % name of the shadow mask file (remove the original file extension,
% % append _sh_mask mark and use extension .png
% fn_str = sprintf('%s_SM_%.2f_%.2f.png', fn(1:ext_ind(end) - 1), ...
%     sun_ang(1), sun_ang(2));
% if exist(fn_str, 'file')
%     fprintf('Rewriting shadow mask into file %s ...\n', fn_str);
% else
%     fprintf('Writing shadow mask into file %s ...\n', fn_str);
% end
% imwrite(sh_mask, fn_str, 'png');
%
% fn_str = sprintf('%s_SR.png', fn(1:ext_ind(end) - 1));
% if exist(fn_str, 'file')
%     fprintf('Rewriting shaded relief into file %s ...\n', fn_str);
% else
%     fprintf('Writing shaded relief into file %s ...\n', fn_str);
% end
% imwrite(shad_indx, fn_str, 'png');
%
% fprintf('done\n');
% % make a lot of star symbols (length of the filename + number of
% % symbols for 'Rewriting... done' + more)
% fprintf([repmat('*', 1, max(numel(fn_str) + 42, 100)) '\n\n']);
