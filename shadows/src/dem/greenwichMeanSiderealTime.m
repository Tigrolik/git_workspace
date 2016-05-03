function nu0 = greenwichMeanSiderealTime(JD, JC)

% mean sidereal time at Greenwich, nu0 (in degrees)
nu0 = mod(280.46061837 + 360.98564736629 * (JD - 2451545) + ...
    JC * JC * (0.000387933 - JC / 38710000), 360);
