function [sh_mask, I, resimg, geoloc] = shadowovertime(fn, time_p)

% time_p.hours = 16;
% get the index of a dot before the extension of the file
ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
fmt = lower(fn(ext_ind:end));
% read dem data & calculate shadow pixels
if ~isempty(license('inuse', 'map_toolbox')) && strfind('.tiff', fmt)
    [I, R] = geotiffread(fn);
    if size(I, 1) == 1201
        res = 90;
    else
        res = 30;
    end
%     I = imresize(I, 3);
%     I = I(2:end-1, 2:end-1);
%     res = res / 3;
    [geoloc.lon, geoloc.lat] = meshgrid(R.Lonlim(1):(R.Lonlim(2) - ...
        R.Lonlim(1)) / (size(I,2) - 1):R.Lonlim(2), R.Latlim(2): ...
        (R.Latlim(1) - R.Latlim(2)) / (size(I,1) - 1):R.Latlim(1));
    
    %     rs = zeros(size(I));
    %     for j = 1:50
    %         fprintf('layer %d ...\n', j);
    %         time_p.hours = ceil(j/5) + 3;
    %         time_p.minutes = 12 * mod(j-1,5);
    [azi, zen] = sunangles(time_p, geoloc);
    sh_mask = shadowdem(I, res, azi, zen);
    % tic
    % sh_mask1 = shaderelief(I, res, azi - 0.5 * pi, zen);
    % toc
    %         sh_mask = imclose(sh_mask, strel('disk', 1));
    %         M(j) = im2frame(double(sh_mask), 'gray');
    %         rs = rs + sh_mask;
    %     figure(); imshow(sh_mask); zoom on
    %     end
    
    %     resimg = rs / max(rs(:)) * 255;
    %     figure(); imshow(uint8(resimg)); axis equal; zoom on; colormap(gray)
    % name of the shadow mask file (remove the original file extension,
    % append _sh_mask mark and use extension .png
    %     fn_str = sprintf('%s_sumsh.png', fn(1:ext_ind(end) - 1));
    geotiffwrite([fn(1:ext_ind(end)-1) '_v1.tif'], sh_mask, R);
    
    %     if exist(fn_str, 'file')
    %         fprintf('Rewriting sum shadow mask into file %s ...\n', fn_str);
    %     else
    %         fprintf('Writing sum shadow mask into file %s ...\n', fn_str);
    %     end
    %     imwrite(uint8(resimg), fn_str, 'png');
    
    %     sh_mask = shadowdem(I, res, time_p, geoloc);
    %     sh_mask = imclose(sh_mask, strel('disk', 3));
    %     sh_mask = imclose(sh_mask, strel('disk', 3));
    %     r.rastersize = size(sh_mask);
    %     geotiffwrite([fn(1:ext_ind(end)-1) '_shmask_georef'], ...
    %         sh_mask, r);
else
    [I, res, geo_dem] = readdem(fn, fmt);
    %     i = imresize(i, 3);
    %     i = i(2:end-1, 2:end-1);
    %     res = res / 3;
    lat = geo_dem(1,:); lon = geo_dem(2,:);
    [geoloc.lon, geoloc.lat] = meshgrid(min(lon) : 1/(size(I,2)-1) : ...
        max(lon), max(lat) : -1/(size(I,1)-1) : min(lat));
    rs = zeros(size(I));
    for j = 1:20
        fprintf('layer %d ...\n', j);
        time_p.hours = round(j/2) + 3;
        time_p.minutes = 30 * mod(j+1,2);
        sh_mask = shadowdem(I, res, time_p, geoloc);
        sh_mask = imclose(sh_mask, strel('disk', 3));
        rs = rs + sh_mask;
        %     figure(); imshow(sh_mask); zoom on
    end
    
    resimg = uint8(rs / max(rs(:)) * 255);
    %     figure(); imshow(uint8(resimg)); axis equal; zoom on; colormap(gray)
    % name of the shadow mask file (remove the original file extension,
    % append _sh_mask mark and use extension .png
    fn_str = sprintf('%s_sumsh.png', fn(1:ext_ind(end) - 1));
    if exist(fn_str, 'file')
        fprintf('Rewriting sum shadow mask into file %s ...\n', fn_str);
    else
        fprintf('Writing sum shadow mask into file %s ...\n', fn_str);
    end
    imwrite(resimg, fn_str, 'png');
    
    %     sh_mask = imclose(sh_mask, strel('disk', 3));
    %     if (size(sh_mask, 1) ~= s1) || (size(sh_mask, 2) ~= s2)
    %         sh_mask = sh_mask(2:end-1, 2:end-1);
    %         sh_mask = imclose(sh_mask, strel('disk', 3));
    %     end
end
