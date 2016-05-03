function doy = dayofyear(y, m, d)

y_str = num2str(y);
d_str = [num2str(m) '-' num2str(d) '-' y_str];
y_begin = ['01-01-' y_str];
doy = datenum(d_str) - datenum(y_begin) + 1;
