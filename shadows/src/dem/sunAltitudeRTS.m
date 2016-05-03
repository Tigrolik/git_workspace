function h = sunAltitudeRTS(latitude, delta_prime, H_prime)

% degrees => radians
q = pi / 180;
% auxiliary variables
lat_rad = latitude * q; del_rad = delta_prime * q;

% Calculate the sun altitude for the sun transit, sunrise, and sunset, h
% (in degrees)
h = asin(sin(lat_rad) * sin(del_rad) + cos(lat_rad) * cos(del_rad) * ...
    cos(H_prime * q)) / q;
