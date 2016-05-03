function [sh_mask, I] = dem2shadow(I, res, sun_ang, sm_mode)

% function sh_mask = dem2shadow(I, x_res, y_res, azi, zen) calculates
% shadow pixels using digital elevation information from matrix I,
% resolution res (can be a single value => x and y resolutions are equal or
% can be a 2-element vector) and sun angular information: a vector whose
% both elements are azimuth and zenith (azi, zen). Optional parameter: mode
% (for now only parameter 'interp' is available) allows triggering of DEM
% data interpolation

% identify resolutions
if length(res) < 2
    x_res = res; y_res = res;
else
    x_res = res(1); y_res = res(2);
end

% degrees => radians
deg2radcoeff = pi / 180;
% azi_orig = sun_ang(1);
% azi = sun_ang(1); zen = sun_ang(2);
azi_temp = sun_ang(1) * deg2radcoeff;
% el = sun_ang(2) * deg2radcoeff;

% additional parameters
tan_par = tan(sun_ang(2) * deg2radcoeff);
x_par = cos(azi_temp) / (tan_par * x_res);
y_par = sin(azi_temp) / (tan_par * y_res);
% xy_ratio = abs(tan(azi));
% if xy_ratio < 1
%     xy_ratio = ceil(1 / xy_ratio);
% else
%     xy_ratio = ceil(xy_ratio);
% end

% upper boundaries for coordinates (they function as image size for
% initialization of other matrices as well)
[y_lim, x_lim] = size(I);
% value defining when there is no data below this value
no_data_low_val = -32000;
% value defining when there is no data above this value
no_data_hi_val = 65000;
% amount of no data pixel in percent when no interpolation is applied
no_data_lim = 0.1;
% if mode variable is present, then the data is to be interpolated boolean
% parameter to avoid interpolation when no need (that is, if b is false
% then interpolation is applied
no_interp = true;
if nargin == 6
    % 'interp' mode allows to "interpolate" DEM values in the places where
    % no data is present
    if strcmpi(sm_mode, 'interp')
        % mask for shadow pixels
        sh_mask = false(y_lim, x_lim);
        % store no data pixels temporarily in the shadow matrix
        sh_mask(I < no_data_low_val) = true;
        sh_mask(I > no_data_hi_val) = true;
        % if the amount of no data pixels is too large then no
        % interpolation is applied
        if sum(sh_mask(:)) / (y_lim * x_lim) > no_data_lim
            fprintf(['Too many pixels with no data ...' ...
                'continue without interpolation\n']);
        else
            no_interp = false;
            % fill no data regions and filter them to interpolate data
            fprintf('Running data interpolation ... ');
            J = roifilt2(fspecial('disk'), imfill(I, 'holes'), sh_mask);
            while sum(sum(I ~= J)) > 1000000
                I = J;
                J = roifilt2(fspecial('disk'), imfill(J,'holes'), sh_mask);
            end
            I = J;
            fprintf('done\n');
        end
    else
        % initialize the shadow matrix with zeros
        sh_mask = false(y_lim, x_lim);
        fprintf('Wrong mode... aborting\n');
        return
    end
end
% no modification to the DEM data, therefore, in the end of this function
% reassign pixels in the sh_mask which correspond to no data pixels in DEM
% matrix (I) with zeros
if no_interp
    I_nodata = false(y_lim, x_lim);
    % store no data pixels temporarily in a matrix
    I_nodata(I < no_data_low_val) = true;
    I_nodata(I > no_data_hi_val) = true;
end
% initialize the shadow matrix with zeros
sh_mask = false(y_lim, x_lim);

% sort the image and store indices
[z_elev, xy_ind] = sort(I(:), 'descend');
z_elev = double(z_elev);
n_elev = numel(z_elev);

% rescale indices
[y_ind, x_ind] = ind2sub([y_lim, x_lim], xy_ind);

% the lowest elevation value
z_lowlim = z_elev(n_elev);

% how often the waitbar is updated, in percent. For example, upd_rate = 10,
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

% initialize the timer
tic;
for j = 1:n_elev
    % the coordinates and value of the current highest point
    x_top = x_ind(j); y_top = y_ind(j); z_top = z_elev(j);
    
    % update when the number of steps reaches next step in waitbar
    if j >= upd_count * upd_step
        % elapsed time
        t_elp = toc;
        % \b - removes string s in order to update it
        fprintf(repmat('\b', 1, numel(out_str)));
        % select outputs and set width values (update out_str output)
        % sec2str() function: convert numbers to strings, dividing into
        % minutes, hours and days if necessary ceil(upd_count * upd_rate) -
        % percent, t_elp * (n_elev / j - 1) - remaining time
        if upd_count < 1
            out_str = sprintf(['%' val_str 'd' spc_margin '%6.2f%%' ...
                spc_margin '%' time_str 's' spc_margin '%' time_str ...
                's'], j, upd_count * upd_rate, sec2str(t_elp), ...
                '      calculating...');
        else
            out_str = sprintf(['%' val_str 'd' spc_margin '%6.2f%%' ...
                spc_margin '%' time_str 's' spc_margin '%' time_str ...
                's'], j, upd_count * upd_rate, sec2str(t_elp), ...
                sec2str(t_elp * (n_elev / j - 1)));
        end
        % print the outputs
        fprintf('%s', out_str);
        % next step in waitbar count
        upd_count = upd_count + 1;
    end
    
    % if the pixels are not in shadow and within limits
    if (~sh_mask(y_top, x_top)) && (z_top > no_data_low_val) && ...
            (z_top < no_data_hi_val)
        % "height" - the difference between the current highest and lowest
        % points
        z_dist = z_lowlim - z_top;
        % calculate x and y shifts
%         if azi_orig < 180
%             x_dist = -z_dist * x_par;
%             y_dist = -z_dist * y_par;
%         else
            x_dist = z_dist * x_par;
            y_dist = -z_dist * y_par;
%         end
        % how far the shadow may be cast lest obstacles interfere (we use
        % integer values since the coordinates in the image are integer)
        x_cur = floor(x_top + x_dist);
        y_cur = floor(y_top + y_dist);
        
        %% the line is composed in the following way:
        %(x - x_top) / (x_cur - x_top) = (y - y_top) / (y_cur - y_top) =
        %(z - z_top) / (z_cur - z_top) = t_ratio
        % Thereofore, since the ration (t_ratio) is common for x, y and z
        % then knowing its value we can compute new x, y and z values using
        % the ratio as a parameter:
        % v = (v_cur - v_top) * t_ratio + v_top, where v can be replaced
        % with x, y or z
        
        %% trimming the indices according to the image size
        % Firstly we compute the ratio and then adjust the coordinates and
        % the elevation value, that is "cutting" the line
        if y_cur < 1
            % compute the coefficient
            t_ratio = (1 - y_top) / y_dist;
            % recalculate values
            y_cur = 1;
            % reminder: we use integer for the coordinates
            x_cur = floor(x_dist * t_ratio + x_top);
            x_dist = x_cur - x_top;
            z_dist = z_dist * t_ratio;
        elseif y_cur > y_lim
            t_ratio = (y_lim - y_top) / y_dist;
            y_cur = y_lim;
            x_cur = floor(x_dist * t_ratio + x_top);
            x_dist = x_cur - x_top;
            z_dist = z_dist * t_ratio;
        end
        if x_cur < 1
            t_ratio = (1 - x_top) / x_dist;
            x_cur = 1;
            % make sure the y coordinate stays within the limits
            y_cur = min(max(floor(y_dist * t_ratio + y_top), 1), y_lim);
            z_dist = z_dist * t_ratio;
        elseif x_cur > x_lim
            t_ratio = (x_cur - x_top) / x_dist;
            x_cur = x_lim;
            y_cur = min(max(floor(y_dist * t_ratio + y_top), 1), y_lim);
            z_dist = z_dist * t_ratio;
        end
        
        %% define which coordinates qualify for potential shadow pixels
        if x_top > x_cur
            % collect all x coordinates within the line
            x_poten = x_top:-1:x_cur;
            % number of coordinates
            x_num_poten = x_top - x_cur + 1;
            % distance with direction
            x_dist = -x_num_poten;
        else
            x_poten = x_top:x_cur;
            x_num_poten = x_cur - x_top + 1;
            x_dist = x_num_poten;
        end
        % repeat for y coordinates
        if y_top > y_cur
            y_poten = y_top:-1:y_cur;
            y_num_poten = y_top - y_cur + 1;
            y_dist = -y_num_poten;
        else
            y_poten = y_top:y_cur;
            y_num_poten = y_cur - y_top + 1;
            y_dist = y_num_poten;
        end
        
        %% Go through all potential pixels and check for the "obstacles"
        % additional parameter to break the for loop if an "obstacle" is
        % met (a higher elevation value than the one on the line, that is
        % the line lies lower than the actual point)
        break_loop = false;
 
        % go through the coordinates whose list of potential values is
        % longer
        if abs(y_dist) > abs(x_dist)
            % the first value is the highest, so it is never in shadow and
            % we skip it
            for k = 2:y_num_poten - 1
                y_poten_cur = y_poten(k);
                t_poten_temp = (y_poten_cur - y_top) / y_dist;
                x_poten_temp = max(floor(x_dist * t_poten_temp + ...
                    x_top), 1);
                t_poten2 = (y_poten(k + 1) - y_top) / y_dist;
                x_poten2 = max(floor(x_dist * t_poten2 + x_top), 1);
                if abs(x_poten_temp - x_poten2) < 0.1
                    if z_dist * t_poten_temp + z_top > I(y_poten_cur, ...
                            x_poten_temp)
                        sh_mask(y_poten_cur, x_poten_temp) = true;
                    else
                        break;
                    end
                else
                    if z_dist * t_poten_temp + z_top > I(y_poten_cur, ...
                            x_poten_temp)
                        sh_mask(y_poten_cur, x_poten_temp) = true;
                    else
                        break_loop = true;
                    end
                    if z_dist * t_poten2 + z_top > I(y_poten_cur, x_poten2)
                        sh_mask(y_poten_cur, x_poten2) = true;
                        if break_loop
                            break;
                        end
                    else
                        break;
                    end
                end
            end
            y_poten_cur = y_poten(end);
            t_poten_temp = (y_poten_cur - y_top) / y_dist;
            x_poten_temp = max(floor(x_dist * t_poten_temp + x_top), 1);
            if z_dist * t_poten_temp + z_top > I(y_poten_cur, x_poten_temp)
                sh_mask(y_poten_cur, x_poten_temp) = true;
            end
        else
            for k = 2:x_num_poten - 1
                x_poten_cur = x_poten(k);
                t_poten_temp = (x_poten_cur - x_top) / x_dist;
                y_poten_temp = max(floor(y_dist * t_poten_temp + ...
                    y_top), 1);
                t_poten2 = (x_poten(k + 1) - x_top) / x_dist;
                y_poten2 = max(floor(y_dist * t_poten2 + y_top), 1);
                if abs(y_poten_temp - y_poten2) < 0.1
                    if z_dist * t_poten_temp + z_top > I(y_poten_temp, ...
                            x_poten_cur)
                        sh_mask(y_poten_temp, x_poten_cur) = true;
                    else
                        break;
                    end
                else
                    if z_dist * t_poten_temp + z_top > I(y_poten_temp, ...
                            x_poten_cur)
                        sh_mask(y_poten_temp, x_poten_cur) = true;
                    else
                        break_loop = true;
                    end
                    if z_dist * t_poten2 + z_top > I(y_poten2, x_poten_cur)
                        sh_mask(y_poten2, x_poten_cur) = true;
                        if break_loop
                            break;
                        end
                    else
                        break;
                    end
                end
            end
            x_poten_cur = x_poten(end);
            t_poten_temp = (x_poten_cur - x_top) / x_dist;
            y_poten_temp = max(floor(y_dist * t_poten_temp + y_top), 1);
            if z_dist * t_poten_temp + z_top > I(y_poten_temp, x_poten_cur)
                sh_mask(y_poten_temp, x_poten_cur) = true;
            end
        end
    end % end if shad_mask
end

% reassign pixels in the sh_mask which correspond to no data pixels in DEM
% matrix (I) with zeros
if no_interp
    sh_mask(I_nodata == true) = false;
end

% print 100% when all computations are completed
fprintf(repmat('\b', 1, numel(out_str)));
fprintf(['%' val_str 'd' spc_margin '100.00%%' spc_margin '%' time_str ...
    's' spc_margin '%' time_str 's' spc_margin ' ... done\n'], j, ...
    sec2str(toc), sec2str(0));
