function DT = EphemerisDeltaT(year_v, mon_v)

% simple evaluation of delta T for time during the interval -1999 to +3000
% Next formula sets "y" for the middle of the month, which is accurate
% enough given the precision in the known values of delta T
y = year_v + (mon_v - 0.5) / 12;

% go through different periods of time
if (y < -500) || (y > 2150)
    DT =  -20 + 32 * ((y - 1820) * 0.01) ^ 2;
elseif y < 500
    u = y * 0.01;
    DT = 10583.6 - 1014.41 * u + 33.78311 * u^2 - 5.952053 * u^3 -...
        0.1798452 * u^4 + 0.022174192 * u^5 + 0.0090316521 * u^6;
elseif y < 1600
    u = (y - 1000) * 0.01;
    DT = 1574.2 - 556.01 * u + 71.23472 * u^2 + 0.319781 * u^3 - ...
        0.8503463 * u^4 - 0.005050998 * u^5 + 0.0083572073 * u^6;
elseif y < 1700
    u = y - 1600;
    DT = 120 - 0.9808 * u - 0.01532 * u^2 + u^3 / 7129;
elseif y < 1800
    u = y - 1700;
    DT = 8.83 + 0.1603 * u - 0.0059285 * u^2 + 0.00013336 * u^3 - ...
        u^4 / 1174000;
elseif y < 1860
    u = y - 1800;
    DT = 13.72 - 0.332447 * u + 0.0068612 * u^2 + 0.0041116 * u^3 ...
        - 0.00037436 * u^4 + 0.0000121272 * u^5 - 0.0000001699 * u^6 + ...
        0.000000000875 * u^7;
elseif y < 1900
    u = y - 1860;
    DT = 7.62 + 0.5737 * u - 0.251754 * u^2 + 0.01680668 * u^3 - ...
        0.0004473624 * u^4 + u^5 / 233174;
elseif y < 1920
    u = y - 1900;
    DT = -2.79 + 1.494119 * u - 0.0598939 * u^2 + 0.0061966 * u^3 ...
        - 0.000197 * u^4;
elseif y < 1941
    u = y - 1920;
    DT = 21.20 + 0.84493*u - 0.076100 * u^2 + 0.0020936 * u^3;
elseif y < 1961
    u = y - 1950;
    DT = 29.07 + 0.407*u - u^2/233 + u^3 / 2547;
elseif y < 1986
    u = y - 1975;
    DT = 45.45 + 1.067*u - u^2/260 - u^3 / 718;
elseif y < 2005
    u = y - 2000;
    DT = 63.86 + 0.3345 * u - 0.060374 * u^2 + 0.0017275 * u^3 + ...
        0.000651814 * u^4 + 0.00002373599 * u^5;
elseif y < 2050
    u = y - 2000;
    % This expression is derived from estimated values of detla T in the
    % years 2010 and 2050. The value for 2010 (66.9 seconds) is based on a
    % linearly extrapolation from 2005 using 0.39 seconds/year (average
    % from 1995 to 2005). The value for 2050 (93 seconds) is linearly
    % extrapolated from 2010 using 0.66 seconds/year (average rate from
    % 1901 to 2000)
    DT = 62.92 + 0.32217 * u + 0.005589 * u^2;
else % 2050 <= y <= 2150
    DT = -20 + 32 * ((y - 1820) * 0.01)^2 - 0.5628 * (2150 - y);
end

% optional parameter "c" used for solar eclipse evaluation
% All values of deltaT based on Morrison and Stephenson [2004] assume a
% value for the Moon's secular acceleration of -26 arcsec/cy^2. However,
% the ELP-2000/82 lunar ephemeris employed in the Canon uses a slightly
% different value of -25.858 arcsec/cy^2. Thus a small correction "c" must
% be added to the values derived from the polynomial expressions for
% delta T before they can be used in the Canon

% if (y < 1955) || (y > 2005)
%     c = -0.000012932 * (y - 1955)^2;
%     delta_T = delta_T + c;
% end
