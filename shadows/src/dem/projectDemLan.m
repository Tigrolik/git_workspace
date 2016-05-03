function projectDemLan(geo_dem, I_lan, geo_lan, sh_mask)

% [s1, s2] = size(I_dem);

% define corner coordinates for pixels and latitude/longitude
% frame_dem = [1, s2, s2, 1; 1, 1, s1, s1; ones(1, 4)];
% lat_min = min(geo_dem(1, :)); lat_max = max(geo_dem(1, :));
% lon_min = min(geo_dem(2, :)); lon_max = max(geo_dem(2, :));
% geo_dem_lim = [lat_max, lat_max, lat_min, lat_min;
%     lon_min, lon_max, lon_max, lon_min; ones(1, 4)];
geo_dem(1, :) = sort(geo_dem(1, :), 'descend');

if ndims(I_lan) == 3
    [s1, s2] = size(I_lan(:, :, 1));
else
    [s1, s2] = size(I_lan);
end
% frame_lan = [1, s2, s2, 1; 1, 1, s1, s1; ones(1, 4)];
frame_lan = [x'; y'; ones(1, 4)];

H1 = homography_svd(geo_lan, frame_lan);
% H2 = homography_svd(frame_dem, geo_dem_lim);

[x, y] = find(sh_mask > 0);
% M = [y'; x'; ones(1, numel(x))];

% c = H2 * M;
c = [geo_dem(1, x); geo_dem(2, y); ones(1, numel(x))];

% c = H2_ * M;
% c(1, :) = c(1, :) ./ c(3, :); c(2, :) = c(2, :) ./ c(3, :);
% H = geo_lan' \ frame_lan';

xy = H1 * c;
xy(1, :) = xy(1, :) ./ xy(3, :); xy(2, :) = xy(2, :) ./ xy(3, :);

% alpha = 0 * pi / 180;
% y = xy(1, :) * cos(alpha) + xy(2, :) * sin(alpha) + 0;
% x = (xy(2, :) * cos(alpha) - xy(1, :) * sin(alpha)) * 0.995 + 20;

y = xy(1, :);
x = xy(2, :);

figure(); imshow(uint16(img) * 20); hold on; zoom on;
plot(y, x, 'r.')
