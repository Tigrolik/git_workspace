function [delta_alpha, delta_prime] = ...
    rightAscensionParallaxDeclination(latitude, elev, xi, H, delta_v)

% degrees => radians
q = pi / 180;
% auxiliary variables
lat_rad = latitude * q; elev_aux = elev / 6378140;
xi_rad = xi * q; H_rad = H * q; delta_rad = delta_v * q;

% term u (in radians)
u = atan(0.99664719 * tan(lat_rad));
x = cos(u) + elev_aux * cos(lat_rad);
y = 0.99664719 * sin(u) + elev_aux * sin(lat_rad);

% auxiliary variables
xi_sin = sin(xi_rad);
aux1 = -x * xi_sin;
aux2 = aux1 * cos(H_rad);
cos_delta = cos(delta_rad);

% parallax in the sun right ascension, delta alpha (in radians)
delta_alpha = atan2(aux1 * sin(H_rad), cos_delta + aux2);

% topocentric sun declination, delta' (in degrees)
delta_prime = atan2((sin(delta_rad) - y * xi_sin) * cos(delta_alpha), ...
    cos_delta + aux2) / q;

% delta alpha (in degrees)
delta_alpha = delta_alpha / q;
