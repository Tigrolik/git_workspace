function theta_v = geocentricLongitude(L)

% geocentric longitude, theta (in degrees)
theta_v = L + 180;
if theta_v >= 360
    theta_v = theta_v - 360;
end
