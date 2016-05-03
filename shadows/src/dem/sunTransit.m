function T = sunTransit(m0, H0_prime)

% function T = sunTransit(m0, H0_prime) calculates the sun transit, T (in
% fraction of day)
% m0  - approximate Sun transit time
% H0' - local hour angle for the sun transit

T = m0 - H0_prime / 360;
