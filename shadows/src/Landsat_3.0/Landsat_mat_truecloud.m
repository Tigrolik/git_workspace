function [x_new, y_new] = ...
    Landsat_mat_truecloud(x, y, h, A, B, C, omega1, omega2)

% imput "x", j col imput "y", i row imput cloud height "h"

% average Landsat 7 height (m)
H = 705000;

% from the central perpendicular (unit: pixel)
% dist = (A * x + B * y + C) / sqrt(A ^ 2 + B ^ 2);
% dist_par = (A * x + B * y + C) / (sqrt(A ^ 2 + B ^ 2) * cos(omega2 - omega1));
% cloud move distance (m);
% dist_move = dist_par .* h / H;
dist_move = ((A * x + B * y + C) .*h) ...
    / (H * sqrt(A ^ 2 + B ^ 2) * cos(omega2 - omega1));
% delt_x = dist_move * cos(omega1);
% delt_y = dist_move * sin(omega1);

% new x, j
x_new = x + dist_move * cos(omega1);
% new y, i
y_new = y + dist_move * sin(omega1);
