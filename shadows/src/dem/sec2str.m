function time_str = sec2str(t)

% function time_str = sec2str(t) converts seconds given in a number into a
% string dividing time into seconds, minutes, hours and days if needed

if t < 60
    % simple string, no calculation, keep only 2 numbers after the comma
    time_str = sprintf('%.2fs', t);
elseif t < 3600
    % number of minutes and seconds
    time_str = sprintf('%dm %.2fs', floor(t / 60), rem(t, 60));
elseif t < 86400
    % number of hours, minutes and seconds
    time_str = sprintf('%dh %dm %.2fs', floor(t / 3600), ...
        floor(rem(t, 3600) / 60), rem(t, 60));
else
    % number of days, hours, minutes and seconds
    time_str = sprintf('%dd %dh %dm %.2fs', floor(t / 86400), ...
        floor(rem(t, 86400) / 3600), floor(rem(t, 3600) / 60), rem(t, 60));
end
