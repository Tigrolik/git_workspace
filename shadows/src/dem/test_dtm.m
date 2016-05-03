close all; clear all;

% dirpath = '../../images/DEM/';
%
% fn = [dirpath 'IC278.txt'];
%
% T = load(fn);
%
% % I = txt2img(T); azi = 128.39 * pi / 180; zen = 38.59 * pi / 180;
%
% normvec = [1 0 0] * [cos(azi) sin(azi) 0; -sin(azi) cos(azi) 0; 0 0 1]
% ...
%     * [cos(zen) 0 sin(zen); 0 1 0; -sin(zen) 0 cos(zen)];
%
% uv = T * null(normvec);
%
% hull = convhull(uv(:, 1), uv(:, 2));
%
% A = polyarea(uv(hull, 1), uv(hull, 2));
%
% [num txt raw] = xlsread('../../images/DEM/Icimod_coverage_points.xls');

% WellIndex = find(HeightArray < -10000);
%
% % Perform a close to get rid of the wells HeightClosed =
% imclose(HeightArray, strel('disk', DiskSize) );
%
% % Check that it got all the wells if (any(any(HeightClosed < -30000)))
%     error('Structuring Element not large enough to eliminate all wells');
% end
%
% % All the wells have been found, replace the wells HeightReplaced =
% HeightArray; HeightReplaced(WellIndex) = HeightClosed(WellIndex);
%
% % Perform smoothing with a Gaussian to help smooth over the wells Kernel
% = fspecial('gaussian', Sigma, (ceil(Sigma) * 3) + 1 ); HeightSmoothed =
% imfilter(HeightReplaced, Kernel, 'replicate', 'same');
%
% % Replace the output with the smoothed, interpolated well values OutArray
% = HeightArray; OutArray(WellIndex) = HeightSmoothed(WellIndex);


% [y_lim x_lim] = size(I); % value defining when there is no data below
% this value no_data_val = -32000; % amount of no data pixel in percent
% when no interpolation is applied no_data_lim = 0.1;
%
% I_nodata = false(y_lim, x_lim); I_nodata(I < no_data_val) = true;
%
% disk_size = 1; J = imclose(I, strel('disk', disk_size)); while any(J(:) <
% -32000)
%     disk_size = disk_size + 1; J = imclose(I, strel('disk', disk_size));
% end % J = imclose(I, strel('disk', 3)); % J = imfill(I, 'holes'); K = I;
%
% K(I_nodata) = J(I_nodata);
%
% % sz = [4 4]; % sig = 0.5; % ker = fspecial('gaussian', sz, sig); ker =
% fspecial('disk', 15); % JS = imfilter(K, ker, 'replicate', 'same'); JS =
% imfilter(K, ker, 'circular', 'same');
%
% I_new = I; I_new(I_nodata) = JS(I_nodata);
%
% % figure(); imshow(uint16(I(520:545, 645:675)) * 15); % figure();
% imshow(uint16(I_new(520:545, 645:675)) * 15);



x_num_cand = x_t - x0 + 1;
y_num_cand = y_t - y0 + 1;

if x0 > x_t
    x_c = x0:-1:x_t;
    x_d = -x_num_cand;
else
    x_c = x0:x_t;
    x_d = x_num_cand;
end

if y0 > y_t
    y_c = y0:-1:y_t;
    y_d = -y_num_cand;
else
    y_c = y0:y_t;
    y_d = y_num_cand;
end
cand = [];
if y_d > x_d
    for k = 1:y_num_cand - 1
        t1 = (y_c(k) - y0) / y_d;
        x1 = max(floor(y_d * t1 + y0), 1);
        t2 = (y_c(k + 1) - y0) / y_d;
        x2 = max(floor(y_d * t2 + y0), 1);
        if x1 == x2
            cand = [cand [x1; y_c(k); t1]];
        else
            cand = [cand [x1; y_c(k); t1] [x2; y_c(k); t2]];
        end
    end
else
    for k = 1:x_num_cand - 1
        t1 = (x_c(k) - x0) / x_d;
        y1 = max(floor(y_d * t1 + y0), 1);
        t2 = (x_c(k + 1) - x0) / x_d;
        y2 = max(floor(y_d * t2 + y0), 1);
        if y1 == y2
            cand = [cand [x_c(k); y1; t1]];
        else
            cand = [cand [x_c(k); y1; t1] [x_c(k); y2; t2]];
        end
    end
end

for k = 1:numel(cand(1, :))
    x = cand(1, k); y = cand(2, k);
    if z_d * cand(3, k) + z0 > I(y, x)
        sh_mask(y, x) = true;
    else
        break;
    end
end
    
    
