function azimuth_astro = ...
    topocentricAstronomersAzimuthAngle(Hprime, latitude, delta_prime)

% degrees => radians
q = pi / 180;
% auxiliary variables
lat_rad = latitude * q; Hprime_rad = Hprime * q;

% topocentric astronomers azimuth angle, Gamma (in degrees)
azimuth_astro = mod(atan2(sin(Hprime_rad), cos(Hprime_rad) * ...
    sin(lat_rad) - tan(delta_prime * q) * cos(lat_rad)) / q, 360);
