function [azi, zen] = sunangles(time_p, geoloc)

% function udtSunCoord = sunangles(time_p, geoloc) calculates azimuth and
% elevation angles of the Sun with respect to Earth.
% INPUT: time_p - structure describing the moment in time with fields
%        year, month, day, hours, minutes and seconds: time_p.year,
%        time_p.month, time_p.day, time_p.hours, time_p.minutes,
%        time_p.seconds;
%        geoloc - structure describing location with fields lat and lon
%        (latitude and longitude): geoloc.lon and geoloc.lat.
% OUTPUT: [azi, zen] - solar azimuth and zenith

% % test data
time_p.year = 2014;
time_p.month = 1;
time_p.day = 16;
time_p.hours = 5;
time_p.minutes = 14;
time_p.seconds = 38;
% UL_LAT = 32.69090;
% UL_LON = 77.29296;
% UR_LAT = 32.74099;
% UR_LON = 79.90917;
% LL_LAT = 30.74611;
% LL_LON = 77.36967;
% LR_LAT = 30.79256;
% LR_LON = 79.93180;
% geoloc.lat = 0.25 * (UL_LAT + LL_LAT + UR_LAT + LR_LAT);
% geoloc.lon = 0.25 * (UL_LON + LL_LON + UR_LON + LR_LON);
% % corresponding solar angles
% %     SUN_AZIMUTH = 152.10181852
% %     SUN_ELEVATION = 32.07551912

% degrees => radians
rad = pi / 180;
% Earth radius in km
EarthR = 6371.01;
% Astronomical unit in km
AstroUnit = 149597890;

if isstruct(time_p)
    dhrs = time_p.hours + (time_p.minutes + time_p.seconds / 60 ) / 60;
    temp = (time_p.month - 14)/12;
    numJDays = (1461 * (time_p.year + 4800 + temp)) * 0.25 + (367 * ...
        (time_p.month - 2 - 12 * temp)) / 12 - (3 * ((time_p.year + ...
        4900 + temp) * 0.01)) * 0.25 + time_p.day - 32075.5 + dhrs / 24;
elseif isvector(time_p)
    dhrs = time_p(4) + (time_p(5) + time_p(6) / 60 ) / 60;
    temp = (time_p(2) - 14)/12;
    numJDays = (1461 * (time_p(1) + 4800 + temp)) * 0.25 + (367 * ...
        (time_p(2) - 2 - 12 * temp)) / 12 - (3 * ((time_p(1) + ...
        4900 + temp) * 0.01)) * 0.25 + time_p(3) - 32075.5 + dhrs / 24;
end
% Calculate difference between current Julian Day and JD 2451545
numJDays = numJDays - 2451545;

% Calculate ecliptic coordinates (ecliptic longitude and obliquity of the
% ecliptic in radians but without limiting the angle to be less than 2*Pi
% (i.e., the result may be greater than 2*Pi)
omega = 2.1429 - 0.0010394594 * numJDays;
meanAnomaly = 6.24006 + 0.0172019699 * numJDays;
eclipLon = 4.895063 + 0.017202791698 * numJDays + ...
    0.03341607 * sin(meanAnomaly) + 0.00034894 * sin(2 * meanAnomaly)- ...
    0.0001134 - 0.0000203 * sin(omega);
eclipObliq = 0.4090928 - 6.2140e-9 * numJDays + 0.0000396 * cos(omega);

% Calculate celestial coordinates (right ascension and declination) in
% radians but without limiting the angle to be less than 2*Pi (i.e., the
% result may be greater than 2*Pi)
sin_eclipLon = sin(eclipLon);
rightAsc = atan2(cos(eclipObliq) * sin_eclipLon, cos(eclipLon));
if rightAsc < 0
    rightAsc = rightAsc + 2 * pi;
end
dip = asin(sin(eclipObliq ) * sin_eclipLon);

% Calculate local coordinates (azimuth and zenith angle)
GWHMeanSidTime = 6.6974243242 + 0.0657098283 * numJDays + dhrs;

% geoloc may contain longitude and latitude values as matrices
localMeanSidTime = (GWHMeanSidTime * 15 + geoloc.lon) * rad;
hourAng = localMeanSidTime - rightAsc;
clear localMeanSidTime
latInRad = geoloc.lat * rad;
cos_Lat = cos(latInRad);
sin_Lat = sin(latInRad);
clear latInRad
cos_hourAng = cos(hourAng);
zen = (acos(cos_Lat .* cos_hourAng * cos(dip) + sin(dip) * sin_Lat));
dY = -sin(hourAng);
clear hourAng
dX = tan(dip) * cos_Lat - sin_Lat .* cos_hourAng;
clear cos_Lat sin_Lat cos_hourAng
azi = atan2(dY, dX);
clear dX dY
idx = azi < 0;
azi(idx) = azi(idx) + 2 * pi;
% azi = azi / rad;
% Parallax Correction
clear idx
prx = (EarthR / AstroUnit) * sin(zen);
zen = zen + prx;
% zen = 90 - (zen + prx) / rad;
clear prx
% azi = azi - 90 * rad;
zen = 90 * rad - zen;
