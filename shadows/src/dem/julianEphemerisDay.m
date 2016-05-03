function JDE = julianEphemerisDay(JD, delta_t)

% Calculate the Julian Ephemeris Day (JDE)
JDE = JD + delta_t / 86400;
