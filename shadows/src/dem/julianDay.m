function JD = julianDay(y_v, mon_v, day_v, h_v, min_v, sec_v, dut, tz)

% function JD = julianDay(y_v, mon_v, day_v, h_v, min_v, sec_v, dut, tz)
% returns the Julian Day for a given time point, fractional second
% difference between UTC and UT and observer time zone

% if M > 2, then Y and M are not changed, but if M = 1 or 2, then Y = Y-1
% and M = M + 12
if mon_v < 3
    y_v = y_v - 1;
    mon_v = mon_v + 12;
end

% decimal day
day_d = day_v + (h_v - tz + (min_v + (sec_v + dut) / 60) / 60) / 24;

% Julian day
JD = fix(365.25*(y_v + 4716)) + fix(30.6001*(mon_v + 1)) + day_d - 1524.5;

% B is equal to 0 for the Julian calendar (JD < 2299160, October 4 (15),
% 1582), and equal to (2 - A + INT (A/4)) for the Gregorian calendar
% (JD > 2299160), where A = fix(Y/100)
if JD > 2299160
    A = fix(y_v * 0.01);
    JD = JD + 2 - A + fix(A * 0.25);
end
