function H = observerHourAngle(nu, longitude, alpha_v)

% observer local hour angle, H (in degrees)
H = mod(nu + longitude - alpha_v, 360);
