function [I, res, latlon] = readdemimg(fn, varargin)

minargsin = 1; maxargsin = 3;
narginchk(minargsin, maxargsin);
% specify the resolution
% SRTM data comes in two resolutions
sz1 = [3601; 3601]; % SRTM1 tile size (USA only)
sz3 = [1201; 1201]; % SRTM3 tile size
sz3_num = 1442401; % number of pixels for sz3 (1201 * 1201)

% reading the image
fprintf('Reading image ... ');

% reading image information
img_info = imfinfo(fn);

if nargin > 1
    lastargin = varargin{end};
    is_cell = iscell(lastargin);
    if is_cell
        % get the extension of the file
        ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
        % the last argument is cell {rows, cols}
        rc = lastargin;
    else
        ext_ind = lastargin;
        if nargin > 2
            % size of image crop
            rc = varargin{1};
        end
    end
else
    ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
    is_cell = false;
end

if nargout > 2
    [lat, lon] = readdemlatlon(fn, ext_ind);
end

% choose a resolution
if nargout > 1
    if (img_info.Height * img_info.Width) == sz3_num
        res = [90, 90];
        % combine latitude and longitude in one variable
        if nargout > 2
            latlon = [linspace(lat + 1, lat, sz3(1)); ...
                linspace(lon, lon + 1, sz3(2))];
        end
    else
        res = [30, 30];
        if nargout > 2
            latlon = [linspace(lat + 1, lat, sz1(1)); ...
                linspace(lon, lon + 1, sz1(2))];
        end
    end
end

if (nargin > 2) || is_cell
    I = imread(fn, 'PixelRegion', rc);
else
    I = imread(fn);
end

fprintf('done\n');
