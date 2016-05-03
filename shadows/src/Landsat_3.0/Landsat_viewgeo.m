function [A, B, C, omega1, omega2] = ...
    Landsat_viewgeo(x_ul, y_ul, x_ur, y_ur, x_ll, y_ll, x_lr, y_lr)

% input "x", j input "y", i input cloud height "h"

x_u = 0.5 * (x_ul + x_ur); x_l = 0.5 * (x_ll + x_lr);
y_u = 0.5 * (y_ul + y_ur); y_l = 0.5 * (y_ll + y_lr);

% get the angle of parallel lines k (in pi)
omega1 = atan(0.5 * ((y_ul - y_ur) / (x_ul - x_ur) + (y_ll - y_lr) / ...
    (x_ll - x_lr)));

% AX(j) + BY(i) + C = 0
A = y_u - y_l;
B = x_l - x_u;
C = y_l * x_u - x_l * y_u;

% get the angle which is perpendicular to the trace line
omega2 = atan(B / A);
