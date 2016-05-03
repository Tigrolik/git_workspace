% 
[s1, s2] = size(I_dem);

% define corner coordinates for pixels and latitude/longitude
frame_dem = [1, s2, s2, 1; 1, 1, s1, s1; ones(1, 4)];
lat_min = min(latlon_dem(1, :)); lat_max = max(latlon_dem(1, :));
lon_min = min(latlon_dem(2, :)); lon_max = max(latlon_dem(2, :));
latlon_dem_lim = [lat_max, lat_max, lat_min, lat_min;
    lon_min, lon_max, lon_max, lon_min; ones(1, 4)];
% latlon_dem(1, :) = latlon_dem(1, :);
% latlon_dem(2, :) = latlon_dem(2, :);
latlon_dem(1, :) = sort(latlon_dem(1, :), 'descend');
% compute the homography matrices

% H1 = h2d_corresp(latlon_landsat, frame_landsat);
% H1 = h2d_corresp(latlon_landsat, frame_landsat - 30/1000000, 'hType', ...
%     'projectivity', 'estMethod', 'dlt');
H1 = homography_svd(latlon_landsat, frame_landsat);
% tf = cp2tform(latlon_landsat(1:2, :)', frame_landsat(1:2, :)', 'projective');
% H1 = tf.tdata.T;
% H2 = h2d_corresp(frame_dem, latlon_dem_lim);
% H2 = h2d_corresp(frame_dem, latlon_dem_lim, 'hType', ...
%     'projectivity', 'estMethod', 'dlt');
H2 = homography_svd(frame_dem, latlon_dem_lim);
% tf = cp2tform(frame_dem(1:2, :)', latlon_dem_lim(1:2, :)', 'projective');
% H2 = tf.tdata.T;
% H1 = latlon_landsat' \ frame_landsat';
% H2 = frame_dem' \ latlon_dem_lim';

[x, y] = find(sh_mask > 0);
M = [y'; x'; ones(1, numel(x))];

% c = H2 * M;
c = [latlon_dem(1, x); latlon_dem(2, y); ones(1, numel(x))];

% c = H2_ * M;
% c(1, :) = c(1, :) ./ c(3, :); c(2, :) = c(2, :) ./ c(3, :);

xy = H1 * c;
% xy  = H1_ * c;
xy(1, :) = xy(1, :) ./ xy(3, :); xy(2, :) = xy(2, :) ./ xy(3, :);

% alpha = 0 * pi / 180;
% y = xy(1, :) * cos(alpha) + xy(2, :) * sin(alpha) + 0;
% x = (xy(2, :) * cos(alpha) - xy(1, :) * sin(alpha)) * 0.995 + 20;

y = xy(1, :);
x = xy(2, :);

figure(); imshow(uint16(img) * 20); hold on; zoom on; plot(y, x, 'r.')
 
% [s1, s2] = size(bands{1});
% l_mask = zeros(s1, s2);
% 
% for j = 1:numel(y)
%     x_t = round(x(j)); y_t = round(y(j));
%     if ((x_t > 0) && (y_t > 0) && (x_t <= s1) && (y_t <= s2) && ...
%             bands{1}(x_t, y_t) > -9999)
%         l_mask(x_t, y_t) = 1;
%     end
% end

% l_mask = imdilate(l_mask, strel('square', 3));
% [x, y] = find(l_mask > 0);
% %  
% xy_ = [y'; x'];
% 
% figure(); imshow(uint16(img) * 20); hold on; zoom on;
% plot(xy_(1, :), xy_(2, :), 'r.')
% % 
% imwrite(l_mask, regexprep(upper(file_MTL), '_MTL.TXT', '_SM.tiff'), 'tiff');

