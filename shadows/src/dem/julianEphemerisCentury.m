function JCE = julianEphemerisCentury(JDE)

% Calculate the Julian Ephemeris Century (JCE) for the 2000 standard epoch
JCE = (JDE - 2451545) / 36525;
