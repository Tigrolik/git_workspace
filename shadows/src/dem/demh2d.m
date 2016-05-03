function H = demh2d(I, latlon_dem)

[s1, s2] = size(I);

% define corner coordinates for pixels and latitude/longitude
frame_dem = [1, s2, s2, 1; 1, 1, s1, s1; ones(1, 4)];
lat_min = min(latlon_dem(1, :)); lat_max = max(latlon_dem(1, :));
lon_min = min(latlon_dem(2, :)); lon_max = max(latlon_dem(2, :));
latlon_dem_lim = [lat_max, lat_max, lat_min, lat_min;
    lon_min, lon_max, lon_max, lon_min; ones(1, 4)];

% compute the homography matrix
H = h2d_corresp(frame_dem, latlon_dem_lim);
