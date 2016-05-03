function delta_e = atmosphericRefractionCorrection(P, T, e0, h0_prime)

% degrees => radians
q = pi / 180;
% atmospheric refraction correction, delta e (in degrees)
% - P is the annual average local pressure (in millibars)
% - T is the annual average local temperature (in degrees C)
% h0_prime = -SunRadius - AtmosRefract;
if e0 >= h0_prime
    % P/1010 * 283/(273 + T)*1.02/(60 * tan(q*(e0 + 10.3/(e0 + 5.11))));
    delta_e = P * 288.66 / (60600 * (273 + T) * ...
        tan((e0 + 10.3 / (e0 + 5.11)) * q));
else % Sun is below the horizon
    delta_e = 0;
end
