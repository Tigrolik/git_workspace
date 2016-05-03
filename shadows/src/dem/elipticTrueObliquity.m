function epsilon = elipticTrueObliquity(delta_eps, eps0)

% function epsilon = elipticTrueObliquity(delta_eps, eps0) returns true
% obliquity of the ecliptic (in degrees)
% delta_eps - nutation in obliquity (in degrees)
% eps0      - mean obliquity of the ecliptic (in arc seconds)

epsilon = eps0 / 3600 + delta_eps;
