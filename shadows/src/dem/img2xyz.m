function [X, Y, Z] = img2xyz(img)

[h, w] = size(img);
[X, Y] = meshgrid(1:w, 1:h);
Z = double(img);
