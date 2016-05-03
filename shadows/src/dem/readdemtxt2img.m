function [I, res] = readdemtxt2img(D, rc)

% function I = txt2img(D) converts text data (D) into a grayscale image
% (I). If D is a name of a file then the function loads data. Otherwise,
% the function proceeds - the data is assumed to be a matrix of columns,
% each column representing data: 1st and 2nd columns are x and y
% coordinates (the order might differ) 3rd column represent the actual
% values. Warning: the output image's class is double. If you want to
% display image then convert it to uint8/uint16 or any other class you need

% resize z data according to the number of different x any y indices x =
% T(:, 1); y = T(:, 2); z = T(:,3); T = load(T);

fprintf('Reading text data ... ');

if ischar(D) % load data from the file
    T = load(D);
elseif isnumeric(D) % data is a numeric matrix
    T = D;
end

rows_lim = numel(unique(T(:, 2)));
cols_lim = numel(unique(T(:, 1)));
if nargin > 2
    rows = min(max(rc{1}, 1), rows_lim);
    cols = min(max(rc{2}, 1), cols_lim);
end

n = size(T, 2);
if n < 4
    I = reshape(T(:, 3), rows_lim, cols_lim);
    if nargin > 2
        I = I((rows(1):rows(2)), cols(1):cols(2));
    end
else
    I = reshape(T(:, 3:n), rows_lim, cols_lim, n - 2);
    I = I((rows(1):rows(2)), cols(1):cols(2), :);
end

if nargout > 1
    res = [abs(T(2, 1) - T(1, 1)), abs(T(2, 2) - T(1, 2))];
end

fprintf('done\n');
