% equation of time
format long g

% degrees => radians
rad = pi / 180;
% Earth radius in km
EarthR = 6371.01;
% Astronomical unit in km
AstroUnit = 149597890;

% For application of atmospheric refraction correction
sunRadius = 0.26667; % Apparent Sun Radius in degrees
atmRef = 0.5667; % Refraction of the sun on the horizon in degrees
h0_prime = -sunRadius - atmRef;

% test data
time_p.year = 2003;
time_p.month = 10;
time_p.day = 17;
time_p.hours = 12;
time_p.minutes = 30;
time_p.seconds = 30;
time_p.tz = -7;
time_p.dut1 = 0;
time_p.DT = 67;
geo_p.lon = -105.1786;
geo_p.lat = 39.742476;
geo_p.elev = 1830.14;
geo_p.slope = 30;
geo_p.T = 11;
geo_p.P = 820;
geo_p.azm_rot = -10;

[JD, sun_transit, sun_rise, sun_set] = solarPosition(time_p, geo_p);

% longitude = geo_p.lon;
% latitude = geo_p.lat;
% elev = geo_p.elev;
% slope = geo_p.slope;
% T = geo_p.T;
% P = geo_p.P;
% azm_rot = geo_p.azm_rot;
% 
% % retrieve the time parameters
% if isstruct(time_p)
%     year_v = time_p.year; mon_v = time_p.month; day_v = time_p.day;
%     hour_v = time_p.hours; min_v = time_p.minutes; sec_v = time_p.seconds;
%     tz  = time_p.tz; dut1 = time_p.dut1; DT = time_p.DT;
% elseif isvector(time_p)
%     year_v = time_p(1); mon_v = time_p(2); day_v = time_p(3);
%     hour_v = time_p(4); min_v = time_p(5); sec_v = time_p(6);
%     tz  = time_p.(7); dut1 = time_p.(8); DT = time_p.(9);
% end
% 
% %% Julian and Julian Ephemeris Day, Century, and Millennium
% JD = julianDay(year_v, mon_v, day_v, hour_v, min_v, sec_v, dut1, tz);
% 
% % Delta T is the difference between the Earth rotation time and the
% % Terrestrial Time
% if ~exist('DT', 'var')
%     DT = EphemerisDeltaT(year_v, mon_v);
% end
% 
% JDE = julianEphemerisDay(JD, DT);
% JC  = julianCentury(JD);
% JCE = julianEphemerisCentury(JDE);
% JME = julianEphemerisMillenium(JCE);
% 
% %% Earth heliocentric longitude, latitude, and distance to the Sun
% [L, B, R] = helioLongitudeLatitudeRadius(JME);
% 
% %% geocentric longitude and latitude
% theta_v = geocentricLongitude(L);
% beta_v = geocentricLatitude(B);
% 
% %% nutation in longitude and obliquity
% [Dpsi, Deps] = nutation(JCE);
% 
% %% true obliquity of the ecliptic
% eps0 = elipticMeanObliquity(JME);
% eps_v = elipticTrueObliquity(Deps, eps0);
% 
% %% aberration correction, deltaTau (in degrees)
% Dtau = aberrationCorrection(R);
% 
% %% apparent Sun longitude, lambda (in degrees)
% lambda_v = apparentSunLongitude(theta_v, Dpsi, Dtau);
% 
% %% apparent sidereal time at Greenwich at any given time
% nu0 = greenwichMeanSiderealTime(JD, JC);
% nu  = greenwichSiderealTime(nu0, Dpsi, eps_v);
% 
% %% Sun right ascension, alpha (in degrees)
% alpha_v = geocentricRightAscension(lambda_v, eps_v, beta_v);
% 
% %% geocentric sun declination, delta (in degrees)
% delta_v = geocentricDeclination(beta_v, eps_v, lambda_v);
% 
% %% observer local hour angle, H (in degrees)
% H = observerHourAngle(nu, longitude, alpha_v);
% 
% %% topocentric Sun right ascension and declination alpha' and delta'
% % equatorial horizontal parallax of the sun, Xi (in degrees)
% xi = sunEquatorialHorizontalParallax(R);
% 
% % parallax in the sun right ascension, delta alpha and topocentric sun
% % declination, delta' (in degrees)
% [delta_alpha, delta_prime] = ...
%     rightAscensionParallaxDeclination(latitude, elev, xi, H, delta_v);
% 
% % topocentric sun right ascension alpha' (in degrees)
% alpha_prime = topocentricRightAscension(alpha_v, delta_alpha);
% 
% %% topocentric local hour angle, H' (in de  grees)
% Hprime = topocentricLocalHourAngle(H, delta_alpha);
% 
% %% topocentric zenith angle
% % topocentric elevation angle without atmospheric refraction correction,
% % e0 (in degrees)
% e0 = topocentricElevationAngle(latitude, delta_prime, Hprime);
% 
% % atmospheric refraction correction, delta e (in degrees)
% delta_e = atmosphericRefractionCorrection(P, T, e0, h0_prime);
% 
% % corrected topocentric elevation angle, e (in degrees)
% e = topocentricElevationAngleCorrected(e0, delta_e);
% 
% % topocentric zenith angle, zenith (in degrees)
% zenith = topocentricZenithAngle(e);
% 
% %% topocentric azimuth angle
% % topocentric astronomers azimuth angle, Gamma (in degrees)
% G = topocentricAstronomersAzimuthAngle(Hprime, latitude, delta_prime);
% 
% % topocentric azimuth angle, PHI for navigators and solar radiation users
% azimuth = topocentricAzimuthAngle(G);
% 
% %% incidence angle for a surface oriented in any direction
% inc = surfaceIncidenceAngle(zenith, G, azm_rot, slope);
% 
% %% Equation of Time
% % Sun's mean longitude (in degrees)
% M = sunMeanLongitude(JME);
% 
% % Equation of Time -  difference between solar apparent and mean time
% EOT = equationOfTime(M, alpha_v, Dpsi, eps_v);


%% Sunrise, Sun Transit, and Sunset


% Appoximate Sun transit time
% hour_v = 0; min_v = 0; sec_v = 0;
% tz = 0;
% dut1 = 0;
% 
% JD = fix(365.25 * (year_v + 4716)) + fix(30.6001 * (mon_v + 1)) + ...
%     day_v + B_par - 1524.5;



















% 
% m0 = (alph0 - sig - nu) / 360;
% 
% % sun_hour_angle_at_rise_set
% H_B0 = -9999;
% H_B0_arg = acos(sin(h0_prime * rad) - sin_phi * sin(del0 * rad) / ...
%     (cos_phi * cos(del0 * rad)));
% if abs(H_B0_arg) <= 1
%     H_B0 = mod(acos(H_B0_arg) / rad, 180);
% end
% 
% %% approx_sun_rise_and_set
% H_B0_frac = H_B0 / 360;
% 
% % approximate sunrise time (in fraction of day)
% m1 = m0 - H_B0_frac;
% 
% % approximate sunset time (in fraction of day)
% m2 = m0 + H_B0_frac;
% m0 = mod(m0, 1); m1 = mod(m1, 1); m2 = mod(m2, 1);

% rts_alpha_delta_prime

% double a = ad[JD_ZERO] - ad[JD_MINUS];
% double b = ad[JD_PLUS] - ad[JD_ZERO];
% 
% if (fabs(a) >= 2.0) a = limit_zero2one(a);
%     if (fabs(b) >= 2.0) b = limit_zero2one(b);
%         
%         return ad[JD_ZERO] + n * (a + b + (b-a)*n)/2.0;
        




























