function I = Landsat_imcrop2lanlot(meta, img)

% add ones to incorporate the values into a matrix math
if meta.ISNEWMTL
    lat_landsat = [meta.CORNER_UL_LAT_PRODUCT, ...
        meta.CORNER_UR_LAT_PRODUCT, meta.CORNER_LR_LAT_PRODUCT, ...
        meta.CORNER_LL_LAT_PRODUCT];
    lon_landsat = [meta.CORNER_UL_LON_PRODUCT, ...
        meta.CORNER_UR_LON_PRODUCT, meta.CORNER_LR_LON_PRODUCT, ...
        meta.CORNER_LL_LON_PRODUCT];
else
    lat_landsat = [meta.PRODUCT_UL_CORNER_LAT, ...
        meta.PRODUCT_UR_CORNER_LAT, meta.PRODUCT_LR_CORNER_LAT, ...
        meta.PRODUCT_LL_CORNER_LAT];
    lon_landsat = [meta.PRODUCT_UL_CORNER_LON, ...
        meta.PRODUCT_UR_CORNER_LON, meta.PRODUCT_LR_CORNER_LON, ...
        meta.PRODUCT_LL_CORNER_LON];
end

latlon_landsat = [lat_landsat; lon_landsat; ones(1, 4)];

roi_ = [floor(latlon_landsat(1, 1:2)) ceil(latlon_landsat(1, 3:4));
    ceil(latlon_landsat(2, 1)), floor(latlon_landsat(2, 2:3)), ...
    ceil(latlon_landsat(2, 4)); ones(1, 4)];

% read a single image and extract the boundaries
I = img;
nodata_val = min(I(:));
isrgb_img = ndims(I) > 2; % rgb image
if isrgb_img
    img_frame = I(:, :, 1) > nodata_val;
else % grayscale image
    img_frame = I > nodata_val;
end

% find corners coordinates
[rows, cols] = find(img_frame);
y_ul = min(rows); x_ul = max(cols(rows == y_ul));
y_lr = max(rows); x_lr = min(cols(rows == y_lr));
x_ll = min(cols); y_ll = max(rows(cols == x_ll));
x_ur = max(cols); y_ur = min(rows(cols == x_ur));
frame_landsat = [x_ul, x_ur, x_lr, x_ll; y_ul, y_ur, y_lr, y_ll; ...
    ones(1, 4)];

[s1, s2] = size(bands{1});
frame_landsat = [1, s2, s2, 1, s2/2; 1, 1, s1, s1, s1/2; ones(1, 5)];
% get the tranformation matrix and new coordinates
% A = X1 \ X2;
% xy = round([frame_coord; ones(1, 4)] * (latlon \ roi_));
if exist('h2d_corresp', 'file')
    H_new = h2d_corresp(latlon_landsat, frame_landsat);
%     H_new = h2d_corresp(latlon_landsat, frame_landsat, 'hType', ...
%         'similarity', 'estMethod', 'ransam_similarity');
    xy = H_new * roi_;
    xy(1, :) = xy(1, :) ./ xy(3, :);
    xy(2, :) = xy(2, :) ./ xy(3, :);
else
    xy = round([frame_landsat; ones(1, 4)] * (latlon_landsat \ roi_));
end
xy = xy(1:2, :);

xmin = min(xy(1,:)); ymin = min(xy(2,:));
% assign the pixels values outside the target area to no data value and
% crop the image accordingly
if isrgb_img
    BW_roi = roipoly(img_frame, xy(1, :), xy(2, :));
    for j = 1:3
        img_temp = I(:, :, j);
        img_temp(~BW_roi) = nodata_val;
        I(:, :, j) = img_temp;
    end
else
    I(~roipoly(img_frame, xy(1, :), xy(2, :))) = nodata_val;
end
I = imcrop(I, [xmin, ymin, max(xy(1,:)) - xmin, max(xy(2,:)) - ymin]);
