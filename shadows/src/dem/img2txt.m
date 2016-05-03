% function T = img2txt(img, fname, res, orig)
function T = img2txt(img, varargin)
% function T = img2txt(IMG) writes the image IMG into a text file. If the
% image is given as a path to a file then the output filename is the same
% name as the image file with extension .txt. Otherwise, the file name is
% generated randomly.
%
% function T = img2txt(IMG, FILENAME) writes the image IMG into a text file
% with name FILENAME.
%
% function T = img2txt(IMG, ..., PARAM1, VALUE1, PARAM2, VALUE2) specifies
% parameters to control the image characheristics. The possible parameters
% are:
% - 'Resolution', the image resolution, may be given as a vector [a, b] or
%   as a single value if the resolution is the same for both x and y axis.
%   Default values are set to [90 90] as a common resolution for SRTM DEM
%   data.
% - 'Origin', the starting pixel coordinates for the top left corner of the
%   image, given as a vector [a, b]. Default values are [1, 1]

% function T = img2txt(img) reads an image from file or variable img and
% writes the image matrix into a text file. It is possible to set a desired
% name for the output file in parameter txt. Otherwise, there are two
% options: 1. If variable img is a filename then the function takes its
% name and replaces its extension with extension .txt 2. If variable img is
% an image variable then the output name is generated randomly

[fname, res, orig] = parse_inputs(img, varargin);

if ischar(img)
    % read image if it is given as a filename
    [I, res] = readdem(img);
elseif isnumeric(img)
    % image as a matrix is given (hello, Yoda)
    I = img;
else
    fprintf('Wrong input... aborting\n');
    return;
end

% get indices of meaningful data and corresponding values and put'em in
% vectors
if numel(size(I)) == 2 % grayscale image
    [T(:, 2), T(:, 1), j] = find(~isnan(I)); T(:, 3) = I(j);
    num_val = numel(j);
else % rgb image | image with many layers
    I_temp = I(:, :, 1);
    % save x and y coordinates
    [T(:, 2), T(:, 1), j] = find(~isnan(I_temp)); T(:, 3) = I_temp(j);
    num_val = numel(j);
    % put colour channels values in individual columns of data matrix T
    for k = 2:num_val
        I_temp = I(:, :, k);
        T(:, k + 2) = I_temp(j);
    end
end

for j = 1:2
    res_t = res(j);
    T(:, j) = (0 : res_t : (num_val - 1) * res_t)' + orig(j);
end

% define field width (add 3 for comma and 2 signs after)
n_str = num2str(numel(num2str(max(ceil(abs(T(:)))))) + 3);
% open file for writing
if exist('fname', 'file')
    fprintf('Rewriting file %s ... ', fname);
else
    fprintf('Generating file %s ... ', fname);
end
fid = fopen(fname, 'w');
% write data into file
fprintf(fid, ['%' n_str '.2f' repmat([' %' n_str '.2f'], 1, ...
    size(T, 2) - 1) '\n'], T');
% close file
fclose(fid);
fprintf('done\n');

function [fname, res, orig] = parse_inputs(img, varargin)

% The additional parameters for the main function might be:
% - filename (string variable), saved to variable fname
% - parameter 'Resolution' and the corresponding vector or value, saved to
%   variable res
% - parameter 'Origin' and the corresponding vector or value, saved to
%   variable orig

% default values for resolution and origin
res_def = [90, 90];
orig_def = [1, 1];

% logical values for controlling whether the values has been set or not
res_unset = true;
orig_unset = true;

n_args = length(varargin);

if mod(n_args, 2)
    par_ind = 2:2:n_args;
    % if the number of parameters is odd then the filename is given as the
    % first argument of varargin and then is followed by pairs
    % Parameter-Value
    class(varargin{1})
    fname = varargin{1};
else
    % if the number of parameters is even then the filename is not given,
    % we have only pairs Parameter-Value
    par_ind = 1:2:n_args;
    if ischar(img)
        % get the filename excluding the extension
        dot_ind = regexp(fn, '\.');
        fname = [img(1:dot_ind(end)) 'txt'];
    else
        % generate a filename randomly
        fname = sprintf('img%d.txt', randi([10000 99999], 1));
    end
end

% cicle through parameters
for j = par_ind
    % setting the resolution value
    if strcmpi(varargin{j}, 'resolution')
        % the value follows the parameter declaration
        res = varargin{j + 1};
        if ~isnumeric(res)
            fprintf(['The resolution parameter should be numeric, ' ...
                'setting the resolution to [%d, %d]\n'], res_def);
            res = res_def;
        end
        res_unset = false;
        % setting the origin value
    elseif strcmpi(varargin{j}, 'origin')
        orig = varargin{j + 1};
        if ~isnumeric(orig)
            fprintf(['The origin parameter should be numeric, ' ...
                'setting the origin to [%d, %d]\n'], orig_def);
            orig = orig_def;
        end
        orig_unset = false;
    else
        fprintf('Parameter %s is unknown, skipping...\n', varargin{j});
    end
end

% if resolution or/and origin have not been set then set to their default
% values
if res_unset
    res = res_def;
end
if orig_unset
    orig = orig_def;
end
