function m0 = approxSunTransitTime(alpha0, longitude, nu)

% function m0 = approxSunTransitTime(alpha0, longitude, nu) calculates the
% approximate sun transit time in fraction of day
% alpha0    - 
% longitude -
% nu        -
m0 = (alpha0 - longitude - nu) / 360.0;
