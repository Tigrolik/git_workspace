function lambda = apparentSunLongitude(theta_v, delta_psi, delta_tau)

% apparent Sun longitude, lambda (in degrees)
lambda = theta_v + delta_psi + delta_tau;
