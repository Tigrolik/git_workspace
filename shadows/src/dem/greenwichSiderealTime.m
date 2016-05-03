function nu = greenwichSiderealTime(nu0, delta_psi, eps_v)

% apparent sidereal time at Greenwich at any given time, nu (in degrees)
nu = nu0 + delta_psi * cos(eps_v * pi / 180);
