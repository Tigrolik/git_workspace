function e0 = topocentricElevationAngle(latitude, delta_prime, Hprime)

% degrees => radians
q = pi / 180;
% auxiliary variables
lat_rad = latitude * q; delta_prime_rad = delta_prime * q;

% topocentric elevation angle without atmospheric refraction correction,
% e0 (in degrees)
e0 = asin(sin(lat_rad) * sin(delta_prime_rad) + ...
    cos(lat_rad) * cos(delta_prime_rad) * cos(Hprime * q)) / q;
