function delta_v = geocentricDeclination(beta_v, eps_v, lambda_v)

% degrees => radians
q = pi / 180;
% auxiliary variables
beta_rad = beta_v * q; eps_rad = eps_v * q;

% geocentric sun declination, delta (in degrees)
delta_v = asin(sin(beta_rad) * cos(eps_rad) + cos(beta_rad) * ...
    sin(eps_rad) * sin(lambda_v * q)) / q;
