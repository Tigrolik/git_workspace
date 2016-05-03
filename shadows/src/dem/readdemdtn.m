function [I, res, latlon] = readdemdtn(fn, rc)

% function [I res] = readdemdtn(fn, rows, cols) reads Digital Terrain
% Elevation Data (DTED) represented in files with extenstion .dtn, where n
% can be 0, 1 or 2. The bigger the n the better the resolution

% SRTM data comes in two resolutions
% sz1 = [3601, 3601]; % SRTM1 tile size (USA only)
% sz3 = [1201, 1201]; % SRTM3 tile size
% sz3_num = 1442401; % number of pixels for sz3 (1201 * 1201)

fprintf('Reading dted data ... ');

dt_n = str2double(fn(end));
f_num = str2double(fn(end - 5:end - 4));

switch dt_n
    case 0  %DTED 0
        if f_num > 79
            fprintf('Out of range\n')
            return;
        elseif f_num > 69
            lon_num = 31;  % longitude points
        elseif f_num > 49
            lon_num = 61;
        else
            lon_num = 121;
        end
        res = [90, 90];
        lat_num = 121; % latitude points
        row_num = 254; % number of rows
    case 1  %DTED 1
        if f_num > 79
            lon_num = 201;
        elseif f_num > 69
            lon_num = 301;
        elseif f_num > 49
            lon_num = 601;
        else
            lon_num = 1201;
        end
        res = [90, 90];
        lat_num = 1201;
        row_num = 2414;
    case 2 %DTED 2
        if f_num > 79
            fprintf('Out of range\n')
            return
        elseif f_num > 69
            lon_num = 901;
        elseif f_num > 49
            lon_num = 1801;
        else
            lon_num = 3601; % longitude points
        end
        res = [7.5, 7.5];
        lat_num = 3601; % latitude points
        row_num = 7214; % number of rows
end

fid = fopen(fn, 'rb');
c = fread(fid, 3428, 'uint8=>char');
M = fread(fid, [row_num inf], 'uint8');
fclose(fid);

if nargout > 2
    % longitude of origin (lower left corner of data)
    lon = str2double(c(5:7));
    % latitude of origin (lower left corner of data)
    lat = str2double(c(13:15));
    % combine lat and lon in one variable
    latlon = {linspace(lat, lat + 1, lat_num); ...
        linspace(lon, lon + 1, lon_num)};
end
% process data
M = M(9 : 2 * lat_num + 8, :);
M1 = M(1 : 2 : end, :);
M2 = M(2 : 2 : end, :);
I = reshape(M1(:) * 2 ^ 8 + M2(:), size(M, 1) * 0.5, size(M, 2));

if nargin > 1
    rows = min(max(rc{1}(:), 1), size(I, 1));
    cols = min(max(rc{2}(:), 1), size(I, 2));
    I = I((rows(1):rows(2)), cols(1):cols(2));
end

fprintf('done\n');
