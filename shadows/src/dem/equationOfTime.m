function E = equationOfTime(M, alpha_v, delta_psi, eps_v)

% function E = equationOfTime(M, alpha_v, delta_psi, eps_v) calculates the
% equation of time - difference between solar apparent and mean time
% M         - Sun mean longitude (in degrees)
% alpha_v   - geocentric right ascension value (in degrees)
% delta_psi - nutation in longitude (in degrees)
% eps_v     - obliquity of the ecliptic (in degrees)

% Multiply E by 4 to change its unit from degrees to minutes of time
E = 4 * (M - 0.0057183 - alpha_v + delta_psi * cos(eps_v * pi / 180));

% Limit E if its absolute value is greater than 20 minutes, by adding or
% subtracting 1440
if E > 20
    E = E - 1440;
elseif E < -20
    E = E + 1440;
end
