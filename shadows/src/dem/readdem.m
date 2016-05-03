function [I, res, latlon] = readdem(fn, varargin)

% function readdem(fn) reads a DEM from file fn. Function has optional
% parameter fext - extension in the filename, that is the type of DEM data
% input file formats:
% - .hgt (SRTM data)
% - images files (.tif, .jpeg, .png etc.)
% - text files containing data as vectors

minargsin = 1; maxargsin = 3;
narginchk(minargsin, maxargsin);
% get the extension of the file
ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
% process input parameters
if nargin > 1
    lastargin = varargin{end};
    is_cell = iscell(lastargin);
    % if the last parameter is a cell then it means that is rc = {rows,
    % cols}
    if is_cell
        % get the extension of the file
        f_ext = fn(ext_ind:end);
        % the last argument is cell {rows, cols}
        rc = lastargin;
    else
        f_ext = lastargin;
        if nargin > 2
            % size of image crop
            rc = varargin{1};
        end
    end
else
    f_ext = fn(ext_ind:end);
    is_cell = false;
end

switch lower(f_ext)
    case {'.dt0', '.dt1', '.dt2'}
        % proccess dted data
        if (nargin > 1) && is_cell
            [I, res, latlon] = readdemdtn(fn, rc);
        else
            [I, res, latlon] = readdemdtn(fn);
        end
    case '.hgt'
        % process hgt data file from SRTM
        if (nargin > 2) || is_cell
            [I, res, latlon] = readdemhgt(fn, rc, ext_ind);
        else
            [I, res, latlon] = readdemhgt(fn, ext_ind);
        end
    case {'.tif', '.tiff', '.jpg', '.png', '.jpeg', '.bmp', '.cur', ...
            '.gif', '.hdf', '.pbm', '.pgm', '.ppm', '.ras', '.xwd', ...
            '.zip'}
        % process image file
        if (nargin > 2) || is_cell
            [I, res, latlon] = readdemimg(fn, rc, ext_ind);
        else
            [I, res, latlon] = readdemimg(fn, ext_ind);
        end
    case {'.txt'} % process text file
        [I, res] = readdemtxt2img(load(fn));
        if nargout > 2
            latlon = NaN;
        end
    otherwise
        fprintf('Wrong file ... aborting\n');
        return;
end
