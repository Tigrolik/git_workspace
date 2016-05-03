function [JD, sun_transit, sun_rise, sun_set] = ...
    solarPosition(time_p, geo_p)

% For application of atmospheric refraction correction
sunRadius = 0.26667; % Apparent Sun Radius in degrees
atmRef = 0.5667; % Refraction of the sun on the horizon in degrees
h0_prime = -sunRadius - atmRef;

if isstruct(time_p)
    y_v = time_p.year; mon_v = time_p.month; day_v = time_p.day;
    h_v = time_p.hours; min_v = time_p.minutes; sec_v = time_p.seconds;
    tz  = time_p.tz; dut = time_p.dut1; dT = time_p.DT;
elseif isvector(time_p)
    y_v = time_p(1); mon_v = time_p(2); day_v = time_p(3);
    h_v = time_p(4); min_v = time_p(5); sec_v = time_p(6);
    tz  = time_p.(7); dut = time_p.(8); dT = time_p.(9);
end

if isstruct(geo_p)
    longitude = geo_p.lon; latitude = geo_p.lat; elev = geo_p.elev;
    slope = geo_p.slope; temperature = geo_p.T; pressure = geo_p.P;
    azm_rot = geo_p.azm_rot;
else
    longitude = geo_p(1); latitude = geo_p(2); elev = geo_p(3);
    slope = geo_p(4); temperature = geo_p(5); pressure = geo_p(6);
    azm_rot = geo_p(7);
end

JD = julianDay(y_v, mon_v, day_v, h_v, min_v, sec_v, dut, tz);
[nu, alpha_v, delta_v] = ...
    geocentricSunRightAscensionDeclination(JD, dT);

[sun_transit, sun_rise, sun_set] = ...
    eotSunTransitRiseSet(y_v, mon_v, day_v, dT, longitude, latitude, ...
    h0_prime, tz);






