function ad_prime = alphaDeltaPrime(ad_vec, n)

% auxiliary variables
a = ad_vec(2) - ad_vec(1);
b = ad_vec(3) - ad_vec(2);

% If the absolute value of a or b is greater than 2, then limit its value
% between 0 and 1
if abs(a) >= 2
    a = mod(a, 1);
end
if abs(b) >= 2
    b = mod(b, 1);
end
% Calculate the values alpha' and delta' (in degrees)
ad_prime = ad_vec(1) + 0.5 * n * (a + b + (b - a) * n);
