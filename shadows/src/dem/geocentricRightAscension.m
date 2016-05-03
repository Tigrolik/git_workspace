function alpha_v = geocentricRightAscension(lambda_v, eps_v, beta_v)

% degrees => radians
q = pi / 180;
% auxiliary variables
lam_rad = lambda_v * q; eps_rad = eps_v * q;

% Sun right ascension, alpha (in radians => degrees)
alpha_v = mod(atan2(sin(lam_rad) * cos(eps_rad) - tan(beta_v * q) * ...
    sin(eps_rad), cos(lam_rad)) / q, 360);
