function eps0 = elipticMeanObliquity(JME)

% mean obliquity of the ecliptic, eps0 (in arc seconds)
u = 0.1 * JME;
eps0 = 84381.448 + u * (-4680.93 + u * (-1.55 + u * (1999.25 + u * ...
    (-51.38 + u * (-249.67 + u * (-39.05 + u * (7.12 + u * (27.87 + ...
    u * (5.79 + u * 2.45)))))))));
