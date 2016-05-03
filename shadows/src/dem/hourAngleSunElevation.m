function H0 = hourAngleSunElevation(latitude, delta0, h0_prime)

% value if the Sun is above or below the horizon for that day
H0 = -99999;
% degrees => radians
q = pi / 180;
% auxiliary variables
lat_rad = latitude * q; del_rad = delta0 * q;

% Calculate the local hour angle corresponding to the Sun elevation equals
% 0.8333 degrees
acos_arg = (sin(h0_prime * q) - sin(lat_rad) * sin(del_rad)) / ...
    (cos(lat_rad) * cos(del_rad));

% if the argument of arccosine is not in the range from -1 to 1 then the
% Sun is always above or below the horizon for that day
if abs(acos_arg) <= 1
    H0 = mod(acos(acos_arg) / q, 180);
end
