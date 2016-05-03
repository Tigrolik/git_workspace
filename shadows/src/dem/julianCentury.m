function JC = julianCentury(JD)

% Calculate the Julian century (JC) for the 2000 standard epoch
JC = (JD - 2451545) / 36525;
