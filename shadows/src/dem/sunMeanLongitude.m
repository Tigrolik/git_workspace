function M = sunMeanLongitude(JME)

% Sun's mean longitude (in degrees)
M = mod((280.4664567 + JME * (360007.6982779 + JME * (0.03032028 + ...
    JME * (1/49931 + JME * (-1/15300 - 0.0000005 * JME))))), 360);
