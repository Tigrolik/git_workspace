function r = sunRiseSet(m, h, delta_prime, latitude, h0_prime, Hprime)

% function r = sunRiseSet(m, h, delta_prime, latitude, h0_prime, Hprime)
% calculates sunrise or sunset time, depending on the input
% m1 or m2  - approximate sunrise or sunset time
% H0' - local hour angle for the sun transit

% degrees => radians
q = pi / 180;

% Calculate the sunrise or sunset, R (in fraction of day)
r = m + (h - h0_prime) / (360 * cos(delta_prime * q) * ...
    cos(latitude * q) * sin(Hprime * q));
