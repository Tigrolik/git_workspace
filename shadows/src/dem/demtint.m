function img = demtint(I)

% value defining when there is no data below this value
no_data_low_val = -32000;
% value defining when there is no data above this value
no_data_hi_val = 65000;

I = single(I);

min_val = min(I(:));
max_val = max(I(:));

if min_val <= no_data_low_val
    I = imfill(I, 'holes');
    min_val = min(I(:));
end

if max_val >= no_data_hi_val
    I = imfill(I, 'holes');
    max_val = max(I(:));
end

color_stops = {'E5E5E5', 'B2B2B2', '797979', '7C2123', '9A4600', ...
    'E4CF7E', '248234', '006246'};
n = numel(color_stops);
dec_clr = zeros(n, 3);
for j = 1:n
    hex_c = color_stops{j};
    dec_clr(j, :) = [hex2dec(hex_c(1:2)), hex2dec(hex_c(3:4)), ...
        hex2dec(hex_c(5:6))];
end
r_low = min(dec_clr(:, 1)); r_hi =  max(dec_clr(:, 1));
g_low = min(dec_clr(:, 2)); g_hi =  max(dec_clr(:, 2));
b_low = min(dec_clr(:, 3)); b_hi =  max(dec_clr(:, 3));

A = (I - min_val) / (max_val - min_val);
% R = A / 255;
R = A;

I_r = R * (r_hi - r_low) + r_low;
I_g = R * (g_hi - g_low) + g_low;
I_b = R * (b_hi - b_low) + b_low;

img = cat(3, I_r, I_g, I_b);
