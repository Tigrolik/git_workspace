function [sun_transit, sun_rise, sun_set] = ...
    eotSunTransitRiseSet(y_v, mon_v, day_v, dT, longitude, latitude, ...
    h0_prime, tz)

% M = sunMeanLongitude(JME);
% EOT = equationOfTime(M, alpha_v, delta_psi, eps_v);
JD = julianDay(y_v, mon_v, day_v, 0, 0, 0, 0, 0);

n = 3;
alpha_vec = zeros(1, n); delta_vec = alpha_vec;

[nu, ~, ~] = geocentricSunRightAscensionDeclination(JD, dT);

JD = JD - 1;
for j = 1:n
    [~, alpha_vec(j), delta_vec(j)] = ...
        geocentricSunRightAscensionDeclination(JD, 0);
    JD = JD + 1;
end

H0 = hourAngleSunElevation(latitude, delta_vec(1), h0_prime);

if H0 >= 0
    m0 = approxSunTransitTime(alpha_vec(1), longitude, nu);
    m_vec = approxSunTransitRiseSet(m0, H0);
    nu_vec = zeros(1, n); n_vec = nu_vec; Hprime_vec = nu_vec;
    alpha_prime_vec = nu_vec; delta_prime_vec = nu_vec; h_vec = nu_vec;
    dT_v = dT / 86400;
    for j = 1:n
        nu_vec(j) = nu + 360.985647 * m_vec(j);
        n_vec(j) = m_vec(j) + dT_v;
        alpha_prime_vec(j) = alphaDeltaPrime(alpha_vec, n_vec(j));
        delta_prime_vec(j) = alphaDeltaPrime(delta_vec, n_vec(j));
        Hprime_temp = mod(nu_vec(j) + longitude - alpha_prime_vec(j), 360);
        if Hprime_temp > 180
            Hprime_temp = Hprime_temp - 360;
        elseif Hprime_temp < -180
            Hprime_temp = Hprime_temp + 360;
        end
        Hprime_vec(j) = Hprime_temp;
        h_vec(j) = ...
            sunAltitudeRTS(latitude, delta_prime_vec(j), Hprime_vec(j));
    end
    tz_v = tz / 24;
    sun_transit = mod(sunTransit(m_vec(1), Hprime_vec(1)) + tz_v, 1) * 24;
    sun_rise = mod(sunRiseSet(m_vec(2), h_vec(2), delta_prime_vec(2), ...
        latitude, h0_prime, Hprime_vec(2)) + tz_v, 1) * 24;
    sun_set = mod(sunRiseSet(m_vec(3), h_vec(3), delta_prime_vec(3), ...
        latitude, h0_prime, Hprime_vec(3)) + tz_v, 1) * 24;
else
    sun_set = -99999; sun_transit = sun_set; sun_rise = sun_set;
end







