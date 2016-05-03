function incidence = ...
    surfaceIncidenceAngle(zenith, azimuth_astro, azm_rotation, slope)

% degrees => radians
q = pi / 180;
% auxiliary variables
zenith_rad = zenith * q; slope_rad = slope * q;

% - omega is the slope of the surface measured from the horizontal plane
% - g_s (small gamma) is the surface azimuth rotation angle, measured from
% south to the projection of the surface normal on the horizontal plane,
% positive or negative if oriented west or east from south, respectively
incidence = acos(cos(zenith_rad) * cos(slope_rad) + sin(slope_rad) * ...
    sin(zenith_rad) * cos((azimuth_astro - azm_rotation) * q)) / q;
