function [I, res, latlon] = readdemhgt(fn, varargin)

minargsin = 1; maxargsin = 3;
narginchk(minargsin, maxargsin);
% SRTM data comes in two resolutions
sz1 = [3601, 3601]; % SRTM1 tile size (USA only)
sz3 = [1201, 1201]; % SRTM3 tile size
sz3_num = 1442401; % number of pixels for sz3 (1201 * 1201)

% open and read
fid = fopen(fn, 'rb', 'ieee-be'); % big endian for SRTM data
fprintf('Reading hgt data ... ');
I = fread(fid, '*int16');
fclose(fid);

if nargin > 1
    lastargin = varargin{end};
    is_cell = iscell(lastargin);
    if is_cell
        % get the extension of the file
        ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
        % the last argument is cell {rows, cols}
        rows = lastargin{1};
        cols = lastargin{2};
    else
        ext_ind = lastargin;
        if nargin > 2
            % size of image crop
            rows = varargin{1}{1};
            cols = varargin{1}{2};
        end
    end
else
    ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
    is_cell = false;
end

if nargout > 2
    [lat, lon] = readdemlatlon(fn, ext_ind);
end

% transform the vector data into an image matrix
if numel(I) == sz3_num
    I = permute(reshape(I, sz3), [2 1]);
%     I = rot90(reshape(I, sz3));
%     I = reshape(I, sz3);
%     I = fliplr(reshape(I, sz3));
    if nargout > 1
        res = [90, 90];
%         res = [30, 30];
    end
    % combine latitude and longitude in one variable
    if nargout > 2
        sz_t1 = sz3(1) - 1; sz_t2 = sz3(2) - 1;
        latlon = [lat + (1 / sz_t1 ) * (0:sz_t1); ...
            lon + (1 / sz_t2 ) * (0:sz_t2)];
%         latlon = [linspace(lat + 1, lat, sz3(1)); ...
%             linspace(lon, lon + 1, sz3(2))];
    end
    if (nargin > 2) || is_cell
        rows = min(max(rows, 1), sz3(1));
        cols = min(max(cols, 1), sz3(2));
        I = I((rows(1):rows(2)), cols(1):cols(2));
    end
else
    I = permute(reshape(I, sz1), [2 1]);
%     I = reshape(I, sz1);
    if nargout > 1
        res = [30, 30];
%         res = [7.5, 7.5];
    end
    if nargout > 2
        latlon = [linspace(lat + 1, lat, sz1(1)); ...
            linspace(lon, lon + 1, sz1(2))];
    end
    if (nargin > 2) || is_cell
        rows = min(max(rows, 1), sz1(1));
        cols = min(max(cols, 1), sz1(2));
        I = I((rows(1):rows(2)), cols(1):cols(2));
    end

end

fprintf('done\n');
