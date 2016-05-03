function m_vec = approxSunTransitRiseSet(m0, H0)

% auxiliary variable
q = H0 / 360;
m_vec = zeros(1, 3);
% approximate sun transit time, m0 (in fraction of day)
m_vec(1) = mod(m0, 1);
% approximate sunrise time, m1 (in fraction of day)
m_vec(2) = mod(m0 - q, 1);
% approximate sunset time, m2 (in fraction of day)
m_vec(3) = mod(m0 + q, 1);
