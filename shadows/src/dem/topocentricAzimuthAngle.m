function azimuth = topocentricAzimuthAngle(azimuth_astro)

% topocentric azimuth angle, PHI for navigators and solar radiation users
azimuth = mod(azimuth_astro + 180, 360);
