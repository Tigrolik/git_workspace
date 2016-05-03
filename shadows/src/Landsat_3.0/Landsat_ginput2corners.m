function [x, y] = Landsat_ginput2corners(I)

% Click to zoom to the corners in the following order: upper left, upper right,
% lower right and lower left. Then click right button using your computer mouse to
% choose the point best describing the corresponding corner. This function
% uses ginput2

% number of point to click... basically, four for corners
n = 4;

figure(); imshow(uint16(I) * 20); zoom on

% x = zeros(n, 1); y = zeros(n, 1);

[x, y] = ginput2(n);
