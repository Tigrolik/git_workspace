function [sh_mask, I] = dem2shadow2(I, res, azi, zen)

% function sh_mask = dem2shadow(I, x_res, y_res, azi, zen) calculates
% shadow pixels using digital elevation information from matrix I,
% resolution res (can be a single value => x and y resolutions are equal
% or can be a 2-element vector) and sun angular information: a vector
% whose both elements are azimuth and zenith (azi, zen). Optional
% parameter: mode (for now only parameter 'interp' is available) allows
% triggering of DEM data interpolation

% identify resolutions
if numel(res) < 2
    x_res = res; y_res = res;
else
    x_res = res(1); y_res = res(2);
end

% value defining when there is no data below this value
NaN_LL = -32000;
% value defining when there is no data above this value
NaN_TL = 65000;

% additional parameters
tan_zen = tan(zen);
tan_azi = tan(azi);
cot_azi = cot(azi);
x_aux = -cos(azi) / (tan_zen * x_res);
y_aux = sin(azi) / (tan_zen * y_res);

% additional parameters
% tan_zen = tan(zen);
% tan_azi = tan(azi);
% cot_azi = cot(azi);
% x_aux = -cos(azi) / (tan_zen * x_res);
% y_aux = sin(azi) / (tan_zen * y_res);

% upper boundaries for coordinates (they function as image size for
% initialization of other matrices as well)
[y_lim, x_lim] = size(I);

% initialize the shadow matrix with zeros
sh_mask = false(y_lim, x_lim);

% sort the image and store indices
[z_elev, xy_ind] = sort(I(:), 'descend');
z_elev = double(z_elev);
n_elev = length(z_elev);

% rescale indices
[y_ind, x_ind] = ind2sub([y_lim, x_lim], xy_ind);

% the lowest elevation value
z_lowlim = z_elev(n_elev);

% how often the waitbar is updated, in percent. For example, upd_rate = 10
% every tenth time the info is updated
upd_rate = 10;

% how big is one step for upd_rate coefficient
upd_step = n_elev * upd_rate / 100;

% number of spaces allocated for variables (fields' width values)
val_str = num2str(numel(num2str(n_elev))); % for values
time_str = num2str(numel('99d 23h 59m 59s')); % for time
spc_margin = '   '; % interval between words.

% count for steps in waitbar
upd_count = 0;

% initialize output string
out_str = '';
fprintf(['---------------------------  Number ' spc_margin ' Percent' ...
    spc_margin '    Time Elapsed  ' spc_margin ' Time Remaining\n']);
fprintf('Processing height values... ');
tic;

% check if the angle is in the areas where sine of azimuth is bigger than
% the cosine meaning that shifts in y axis are bigger
if ((azi > pi * 0.25) && (azi < pi * 0.75)) || ...
        ((azi > pi * 1.25) && (azi < pi * 1.75))
    
    % check the direction of the shift
    if y_aux > 0
        for j = 1:n_elev
            
            % update when the number of steps reaches next step in waitbar
            if j >= upd_count * upd_step
                
                % elapsed time
                t_elp = toc;
                
                % \b - removes string s in order to update it
                fprintf(repmat('\b', 1, numel(out_str)));
                
                % select outputs and set width values (update out_str
                % output) sec2str() function: convert numbers to strings,
                % dividing into minutes, hours and days if necessary
                % ceil(upd_count * upd_rate) - percent,
                % t_elp * (n_elev / j - 1) - remaining time
                if upd_count < 1
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), '      calculating...');
                else
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), ...
                        sec2str(t_elp * (n_elev / j - 1)));
                end
                
                % print the outputs
                fprintf('%s', out_str);
                
                % next step in waitbar count
                upd_count = upd_count + 1;
            end
            
            % the coordinates and value of the current highest point
            x_top = x_ind(j); y_top = y_ind(j); z_top = z_elev(j);
            
            % if the pixels are not in shadow and within the limits
            if (~sh_mask(y_top, x_top))&&(z_top>NaN_LL)&&(z_top < NaN_TL)
                
                % the height at the current point
                h = z_top - z_lowlim;
                
                % calculate the shift in y direction
                y_d = h * y_aux;
                y_n = ceil(y_d);
                y_p = y_top:y_top + y_n;
                
                % go through x coordinates to avoid ambuguities
                % every x coordinate may have two or more corresponding y
                % coordinates (in other words, two different y coordinates
                % may point to the same x coordinate)
                for k = 2:y_n
                    y_t1 = y_p(k);
                    y_t2 = y_p(k+1);
                    
                    % calculate two x coordiantes assigned for the two y
                    % coordinates
                    x_c1 = round(x_top + cot_azi * (y_top - y_t1));
                    x_c2 = round(x_top + cot_azi * (y_top - y_t2));
                    
                    % check whether the points are within the image limits
                    if (x_c1 > 0) && (x_c1 <= x_lim) && (y_t1 > 0) && ...
                            (y_t1 <= y_lim)
                        
                        % ratio for the current pair of coordinates
                        t = (y_top - y_t1) / y_d;
                        
                        % calculate the height of the line in the current
                        % coordinates pair
                        h_c = h * t + z_top;
                        
                        % compare the height of the line in the current
                        % point with the height at this point in the image
                        if h_c > I(y_t1, x_c1)
                            
                            % if the line is above the terrain then the
                            % shadow is cast from the top point towards
                            % the current pair of coordinates (point)
                            sh_mask(y_t1, x_c1) = true;
                            
                        % if the line is not above the terrain at the
                        % current point then check the neighbouring
                        % pixel whether two different y coordinates
                        % point to the same x coordinate
                        elseif (x_c1 == x_c2) && (y_t2 > 0) && ...
                                (y_t2 <= y_lim)
                            if h_c > I(y_t2, x_c1)
                                sh_mask(y_t2, x_c1) = true;
                            else
                                break;
                            end
                        else
                            break;
                        end
                    end
                end
            end
        end
    else % other direction of the shift in y axis
        for j = 1:n_elev
            if j >= upd_count * upd_step
                t_elp = toc;
                fprintf(repmat('\b', 1, numel(out_str)));
                if upd_count < 1
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), '      calculating...');
                else
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), ...
                        sec2str(t_elp * (n_elev / j - 1)));
                end
                fprintf('%s', out_str);
                upd_count = upd_count + 1;
            end
            
            x_top = x_ind(j); y_top = y_ind(j); z_top = z_elev(j);
            if (~sh_mask(y_top, x_top)) && (z_top > NaN_LL) && ...
                    (z_top < NaN_TL)
                h = z_top - z_lowlim;
                y_d = h * y_aux;
                y_n = ceil(-y_d);
                y_p = y_top:-1:y_top - y_n;
                for k = 2:y_n
                    y_t1 = y_p(k);
                    y_t2 = y_p(k+1);
                    x_c1 = round(x_top + cot_azi * (y_top - y_t1));
                    x_c2 = round(x_top + cot_azi * (y_top - y_t2));
                    if (x_c1 > 0) && (x_c1 <= x_lim) && (y_t1 > 0) && ...
                            (y_t1 <= y_lim)
                        t = (y_top - y_t1) / y_d;
                        h_c = h * t + z_top;
                        if h_c > I(y_t1, x_c1)
                            sh_mask(y_t1, x_c1) = true;
                        elseif (x_c1 == x_c2) && (y_t2 > 0) && ...
                                (y_t2 <= y_lim)
                            if h_c > I(y_t2, x_c1)
                                sh_mask(y_t2, x_c1) = true;
                            else
                                break;
                            end
                        else
                            break;
                        end
                    end
                end
            end
        end
    end
else
    % cosine of azimuth is bigger than sine (shifts in x axis are bigger)
    if x_aux > 0 % check the direction of the shift
        for j = 1:n_elev
            if j >= upd_count * upd_step
                t_elp = toc;
                fprintf(repmat('\b', 1, numel(out_str)));
                if upd_count < 1
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), '      calculating...');
                else
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), ...
                        sec2str(t_elp * (n_elev / j - 1)));
                end
                fprintf('%s', out_str);
                upd_count = upd_count + 1;
            end
            
            x_top = x_ind(j); y_top = y_ind(j); z_top = z_elev(j);
            if (~sh_mask(y_top, x_top)) && (z_top > NaN_LL) && ...
                    (z_top < NaN_TL)
                h = z_top - z_lowlim;
                x_d = -h * x_aux;
                x_n = ceil(-x_d);
                x_p = x_top:-1:x_top - x_n;
                for k = 2:x_n
                    x_t1 = x_p(k);
                    x_t2 = x_p(k+1);
                    y_c1 = round(y_top + tan_azi * (x_top - x_t1));
                    y_c2 = round(y_top + tan_azi * (x_top - x_t2));
                    if (x_t1 > 0) && (x_t1 <= x_lim) && (y_c1 > 0) && ...
                            (y_c1 <= y_lim)
                        t = (x_top - x_t1) / x_d;
                        h_c = h * t + z_top;
                        if h_c > I(y_c1, x_t1)
                            sh_mask(y_c1, x_t1) = true;
                        elseif (y_c1 == y_c2) && (x_t2 > 0) && ...
                                (x_t2 <= x_lim)
                            if h_c > I(y_c1, x_t2)
                                sh_mask(y_c1, x_t2) = true;
                            else
                                break;
                            end
                        else
                            break;
                        end
                    end
                end
            end
        end
    else
        for j = 1:n_elev
            if j >= upd_count * upd_step
                t_elp = toc;
                fprintf(repmat('\b', 1, numel(out_str)));
                if upd_count < 1
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), '      calculating...');
                else
                    out_str = sprintf(['%' val_str 'd' spc_margin ...
                        '%6.2f%%' spc_margin '%' time_str 's' ...
                        spc_margin '%' time_str 's'], j, upd_count * ...
                        upd_rate, sec2str(t_elp), ...
                        sec2str(t_elp * (n_elev / j - 1)));
                end
                fprintf('%s', out_str);
                upd_count = upd_count + 1;
            end
            
            x_top = x_ind(j); y_top = y_ind(j); z_top = z_elev(j);
            if (~sh_mask(y_top, x_top)) && (z_top > NaN_LL) && ...
                    (z_top < NaN_TL)
                h = z_top - z_lowlim;
                x_d = -h * x_aux;
                x_n = ceil(x_d);
                x_p = x_top:x_top + x_n;
                for k = 2:x_n
                    x_t1 = x_p(k);
                    x_t2 = x_p(k+1);
                    y_c1 = round(y_top + tan_azi * (x_top - x_t1));
                    y_c2 = round(y_top + tan_azi * (x_top - x_t2));
                    if (x_t1 > 0) && (x_t1 <= x_lim) && (y_c1 > 0) && ...
                            (y_c1 <= y_lim)
                        t = (x_top - x_t1) / x_d;
                        h_c = h * t + z_top;
                        if h_c > I(y_c1, x_t1)
                            sh_mask(y_c1, x_t1) = true;
                        elseif (y_c1 == y_c2) && (x_t2 > 0) && ...
                                (x_t2 <= x_lim)
                            if h_c > I(y_c1, x_t2)
                                sh_mask(y_c1, x_t2) = true;
                            else
                                break;
                            end
                        else
                            break;
                        end
                    end
                end
            end
        end
    end
end

fprintf('\n');

end % end main function (dem2shadow)