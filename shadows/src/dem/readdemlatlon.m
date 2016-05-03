function [lat, lon] = readdemlatlon(fn, ext_ind)

% function latlon = readdemlatlon(fn, ext_ind) reads the latitude and
% longitude from file's name. For example, SRTM files have name in the
% following format: N34W119.hgt. The first seven characters indicate the
% southwest corner of the block, with N, S, E, and W referring to north,
% south, east, and west. Thus, the "N34W119.hgt" file covers latitudes 34
% to 35 North and longitudes 118-119 West Input: fn - filename
%        ext_ind - optional parameter, the index of a dot before the
%        extension in the file name

if nargin < 2
    % get the indices of dots to identify where the extension is
    ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
elseif size(ext_ind) > 1
    ext_ind = ext_ind(end);
end

% get latitude and longitude from file's name
fs_ind = numel(fn) - regexp(fliplr(fn), filesep, 'once') + 1;

% filename without extension
if isempty(fs_ind)
    filebody = fn(1:ext_ind - 1);
else
    filebody = fn(fs_ind + 1:ext_ind - 1);
end

% digits' groups in file's name and their indices
[dig, dig_ind] = regexp(filebody, '\d+', 'match');
invalid_f = false;

if length(dig_ind) > 1
    % 's' (south hemisphere)
    if strcmpi(filebody(dig_ind(1) - 1), 's')
        lat = -str2double(dig{1});
    elseif strcmpi(filebody(dig_ind(1) - 1), 'n')
        lat = str2double(dig{1});
    else
        invalid_f = true;
    end
    
    % 'w' (west hemishpere)
    if strcmpi(filebody(dig_ind(2) - 1), 'w')
        lon = -str2double(dig{2});
    elseif strcmpi(filebody(dig_ind(2) - 1), 'e')
        lon = str2double(dig{2});
    else
        invalid_f = true;
    end
else
    invalid_f = true;
end

if invalid_f
    % try to look for a separate .txt file with the same name
    fn_txt = [fn(1:ext_ind) 'txt'];
    if exist(fn_txt, 'file')
        fid_in = fopen(fn_txt);
        for j = 1:10
            str = fgetl(fid_in);
            % longitude value
            if strcmpi(str(1:9), 'xllcorner')
                lon = str2double(str(11:end));
            end
            % latitude value
            if strcmpi(str(1:9), 'yllcorner')
                lat = str2double(str(11:end));
            end
        end
        fclose(fid_in);
    else
        error(['Could not extract latitude/longitude values: filename ' ...
            'is not in a suitable form or no separate file with the ' ...
            'same name containing the geographic information']);
    end
end
