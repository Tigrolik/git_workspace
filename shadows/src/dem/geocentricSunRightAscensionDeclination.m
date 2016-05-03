function [nu, alpha_v, delta_v] = ...
    geocentricSunRightAscensionDeclination(JD, delta_t)

JDE = julianEphemerisDay(JD, delta_t);
JC  = julianCentury(JD);
JCE = julianEphemerisCentury(JDE);
JME = julianEphemerisMillenium(JCE);
[L, B, R] = helioLongitudeLatitudeRadius(JME);
theta_v = geocentricLongitude(L);
beta_v = geocentricLatitude(B);
[Dpsi, Deps] = nutation(JCE);
eps0 = elipticMeanObliquity(JME);
eps_v = elipticTrueObliquity(Deps, eps0);
Dtau = aberrationCorrection(R);
lambda_v = apparentSunLongitude(theta_v, Dpsi, Dtau);
nu0 = greenwichMeanSiderealTime(JD, JC);
nu  = greenwichSiderealTime(nu0, Dpsi, eps_v);
alpha_v = geocentricRightAscension(lambda_v, eps_v, beta_v);
delta_v = geocentricDeclination(beta_v, eps_v, lambda_v);
