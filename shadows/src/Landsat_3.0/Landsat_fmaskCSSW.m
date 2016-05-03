function [cs_final, similar_num, cspt] = Landsat_fmaskCSSW(bands, ...
    water, snow, cloud, shadow, meta)

% History of revisions:
% - cloud shadow do not have to overlap with potential cloud shadow layer
% (Zhe Zhu 04/24/2011);
% - exclude small cloud object <= 25 pixels (zhe Zhu 3/07/2011);
% - dilate shadow again (3 pixels as default) (Zhe Zhu 12/23/2010);
% - similarity < 0.95 (Zhe Zhu 11/06/2010);
% - boosts data by >5/9 (Zhe Zhu 12/08/2009);
% - use temperature to narrow iteration height (Zhe Zhu 12/09/2009);
% - fixed bug for height (Zhe Zhu 12/09/2009);
% - cloud DEM by thermal in cloud and shadow match (Zhe Zhu 1/03/2009)

fprintf('Read in potential mask (function fcssm_1_6_3sav)\n');

% solar elevation angle
deg2radcoeff = pi / 180;
sun_ele_rad = (90 - meta.SUN_ELEVATION) * deg2radcoeff;

% solar azimuth anngle
sun_tazi_rad = (meta.SUN_AZIMUTH - 90) * deg2radcoeff;

if meta.ISNEWMTL
    mask_size = [meta.REFLECTIVE_LINES, meta.REFLECTIVE_SAMPLES];
else
    mask_size = [meta.PRODUCT_LINES_REF, meta.PRODUCT_SAMPLES_REF];
end

nodata_val = min(bands{1}(:));
% potential cloud & shadow layer
cloud_test = false(mask_size); cloud_cal = cloud_test;
shadow_test = cloud_test;      shadow_cal = cloud_test;
cs_final = cloud_test;

%{
cloud_test = zeros(ijdim_ref, 'uint8');
shadow_test = zeros(ijdim_ref, 'uint8');

% matched cloud & shadow layer
shadow_cal = zeros(ijdim_ref, 'uint8');
cloud_cal = zeros(ijdim_ref, 'uint8');

% cloud_height = zeros(ijDim);% cloud relative height (m) boundary layer
boundary_test = zeros(ijdim_ref, 'uint8');

% final cloud, shadow and snow mask
cs_final = zeros(ijdim_ref, 'uint8');
%}
% get potential mask values

shadow_test(shadow) = true;% plshadow layer
boundary_test = bands{1} > nodata_val; % boundary layer
cloud_test(cloud) = true; % plcloud layer
% clear plsim plcim; % empty memory

% revised percent of cloud on the scene after plcloud
revised_ptm = sum(cloud_test(:)) / sum(boundary_test(:));
% no t test = > more than 98 % clouds and partly cloud over land = > no
% match = > rest are definite shadows

% cloud covers more than 90% of the scene = > no match = > rest are
% definite shadows fprintf('Cloud and cloud shadow matching ...\n');

if (ptm <= 0.1) || (revised_ptm >= 0.9)
    % fprintf('No Shadow Match due to too much cloud (>90 percent)\n');
    cloud_cal(cloud_test) = true;
    shadow_cal(~cloud_test) = true;
    similar_num = -1;
    % height_num = -1;
    
else
    % fprintf('Shadow Match in processing\n');
    
    % define constants
    Tsimilar = 0.30;
    % threshold for matching buffering
    Tbuffer = 0.98;
    % minimum matched cloud object (pixels)
    num_cldoj = 25;
    % number of inward pixels (240m) for cloud base temperature
    num_pix = 8;
    % enviromental lapse rate 6.5 degrees/km
    % dry adiabatic lapse rate 9.8 degrees/km
    rate_elapse = 6.5;
    rate_dlapse = 9.8;
    
    % fprintf('Set cloud similarity = %.3f\n', Tsimilar); fprintf('Set
    % matching buffer = %.3f\n', Tbuffer); fprintf('Shadow match for
    % cloud object > = %d pixels\n', num_cldoj);
    % move 2 pixel at a time
    reso_ref = meta.GRID_CELL_SIZE_REF;
    i_step = 2 * reso_ref * tan(sun_ele_rad);
    
    % get moving direction
    [rows, cols] = find(boundary_test);
    [y_ul, num] = min(rows);
    x_ul = cols(num);
    
    [y_lr, num] = max(rows);
    x_lr = cols(num);
    
    [x_ll, num] = min(cols);
    y_ll = rows(num);
    
    [x_ur, num] = max(cols);
    y_ur = rows(num);
    
    % get view angle geometry
    [A, B, C, omega1, omega2] =...
        Landsat_viewgeo(x_ul, y_ul, x_ur, y_ur, x_ll, y_ll, x_lr, y_lr);
    
    % Segmentate each cloud
    % fprintf('Cloud segmentation & matching\n');
    L = bwlabeln(cloud_test, 8);
    s = regionprops(L, 'area');
    area = [s.Area];
    
    % filter out cloud object < than num_cldoj pixels
    idx = find(area >= num_cldoj);
    segm_cloud_tmp = ismember(L, idx);
    [segm_cloud, num] = bwlabeln(segm_cloud_tmp, 8);
    
    s = regionprops(segm_cloud, 'area');
    area_final = [s.Area];
    obj_num = area_final;
    
    % Get the x, y of each cloud Matrix used in recording the x, y
    xys = regionprops(segm_cloud, 'PixelList');
    
    % Use iteration to get the optimal move distance Calulate the moving
    % cloud shadow
    
    % height_num = zeros(1, num); % cloud relative height (m)
    similar_num = zeros(1, num); % cloud shadow match similarity (m)
    
    for cloud_type = 1:num
        %fprintf('Shadow Match of the %d/%d_th cloud with %d pixels\n',
        %cloud_type, num, obj_num(cloud_type));
        
        % moving cloud xys
        XY_type = zeros(obj_num(cloud_type), 2);
        
        % record the max threshold moving cloud xys
        tmp_XY_type = zeros(obj_num(cloud_type), 2);
        
        % corrected for view angle xys
        tmp_xys = zeros(obj_num(cloud_type), 2);
        
        % record the original xys
        orin_xys = zeros(obj_num(cloud_type), 2);
        
        % record the original xys
        orin_xys(:, :) = xys(cloud_type, 1).PixelList(:, :);
        
        % record this orinal ids
        orin_cid = sub2ind(ijdim_ref, orin_xys(:, 2), orin_xys(:, 1));
        
        % Temperature of the cloud object
        temp_obj = bands{6}(orin_cid);
        
        % the base temperature for cloud assume object is round r_obj is
        % radium of object
        r_obj = sqrt(obj_num(cloud_type) / pi);
        
        % number of inward pixes for correct temperature
        % num_pix = 8;
        % (1 - num_pix / r_obj) ^ 2
        pct_obj = (r_obj - num_pix) ^ 2 / r_obj ^ 2;
        
        % pct of edge pixel should be less than 1
        pct_obj = min(pct_obj, 1);
        t_obj = quantile(temp_obj(:), pct_obj);
        
        % put the edge of the cloud the same value as t_obj
        temp_obj(temp_obj > t_obj) = t_obj;
        
        % wet adiabatic lapse rate 6.5 degrees/km dry adiabatic lapse rate
        % 9.8 degrees/km
        % rate_wlapse = 6.5;% degrees/km rate_dlapse = 9.8;%
        % degrees/km
        Max_cl_height = 12000;% Max cloud base height (m)
        Min_cl_height = 200; % Min cloud base height (m)
        
        % refine cloud height range (m)
        Min_cl_height = max(Min_cl_height, 10 * (t_templ - 400 - t_obj)...
            / rate_dlapse);
        Max_cl_height = min(Max_cl_height, 10 * (t_temph + 400 - t_obj));
        
        % initialize height and similarity info
        record_h = 0;
        record_thresh = 0;
        
        % iterate in height (m)
        for base_h = Min_cl_height : i_step : Max_cl_height
            
            % Get the true postion of the cloud calculate cloud DEM with
            % initial base height
            h = (10 * (t_obj - temp_obj) / rate_elapse + base_h);
            [tmp_xys(:, 1), tmp_xys(:, 2)] = Landsat_mat_truecloud(...
                orin_xys(:, 1), orin_xys(:,2), h, A, B, C, omega1, omega2);
            
            % shadow moved distance (pixel) i_xy = h *
            % cos(sun_tazi_rad)/(reso_ref * tan(sun_ele_rad));
            i_xy = h / (reso_ref * tan(sun_ele_rad));
            if azi < 180
                XY_type(:, 2) = round(tmp_xys(:, 1) - i_xy * ...
                    cos(sun_tazi_rad)); % X is for j, 2
                XY_type(:, 1) = round(tmp_xys(:, 2) - i_xy * ...
                    sin(sun_tazi_rad)); % Y is for i, 1
            else
                XY_type(:, 2) = round(tmp_xys(:, 1) + i_xy * ...
                    cos(sun_tazi_rad)); % X is for j, 2
                XY_type(:, 1) = round(tmp_xys(:, 2) + i_xy * ...
                    sin(sun_tazi_rad)); % Y is for i, 1
            end
            
            tmp_j = XY_type(:, 2); % col
            tmp_i = XY_type(:, 1); % row
            
            % the id that is out of the image
            out_id = (tmp_i < 1) | (tmp_i > win_h) | (tmp_j < 1) | ...
                (tmp_j > win_w);
            out_all = sum(out_id(:));
            tmp_ii = tmp_i(out_id == 0);
            tmp_jj = tmp_j(out_id == 0);
            tmp_id = sub2ind(mask_size, tmp_ii, tmp_jj);
            
            % the id that is matched (exclude original cloud)
            match_id = (~boundary_test(tmp_id)) | ...
                ((segm_cloud(tmp_id) ~= cloud_type) & ...
                ((cloud_test(tmp_id) > 0) | (shadow_test(tmp_id) == 1)));
            matched_all = sum(match_id(:)) + out_all;
            
            % the id that is the total pixel (exclude original cloud)
            total_id = (segm_cloud(tmp_id) ~= cloud_type);
            total_all = sum(total_id(:)) + out_all;
            thresh_match = matched_all / total_all;
            if (thresh_match >= Tbuffer * record_thresh) && ...
                    (base_h < Max_cl_height - i_step) && ...
                    (record_thresh < 0.95)
                if thresh_match > record_thresh
                    record_thresh = thresh_match;
                    record_h = h;
                end
            elseif record_thresh > Tsimilar
                similar_num(cloud_type) = record_thresh;
                i_vir = record_h / (reso_ref * tan(sun_ele_rad));
                % height_num = record_h;
                
                if azi < 180
                    tmp_XY_type(:, 2) = round(tmp_xys(:, 1) - ...
                        i_vir * cos(sun_tazi_rad)); % X is for col j, 2
                    tmp_XY_type(:, 1) = round(tmp_xys(:, 2) - ...
                        i_vir * sin(sun_tazi_rad)); % Y is for row i, 1
                else
                    tmp_XY_type(:, 2) = round(tmp_xys(:, 1) + ...
                        i_vir * cos(sun_tazi_rad)); % X is for col j, 2
                    tmp_XY_type(:, 1) = round(tmp_xys(:, 2) + ...
                        i_vir * sin(sun_tazi_rad)); % Y is for row i, 1
                end
                
                tmp_scol = tmp_XY_type(:, 2);
                tmp_srow = tmp_XY_type(:, 1);
                
                % put data within range
                tmp_srow(tmp_srow < 1) = 1;
                tmp_srow(tmp_srow > win_h) = win_h;
                tmp_scol(tmp_scol < 1) = 1;
                tmp_scol(tmp_scol > win_w) = win_w;
                
                tmp_sid = sub2ind(ijdim_ref, tmp_srow, tmp_scol);
                
                % give shadow_cal = 1
                shadow_cal(tmp_sid) = 1;
                % record matched cloud
                % cloud_cal(orin_cid) = 1;
                % cloud_height(orin_cid) = record_h;
                break;
            else
                record_thresh = 0;
                continue;
            end
        end
    end
    
    % % dilate each cloud and shadow object by 3 and 6 pixel outward in 8
    % connect directions
    % cldpix = 3; % number of pixels to be dilated for cloud sdpix = 3;
    % % number of pixels to be dilated for shadow
    fprintf(['Dilate %d pixels for cloud & %d pixels for shadow ' ...
        'objects\n'], cldpix, sdpix);
    SEc = strel('square', 2 * cldpix + 1);
    SEs = strel('square', 2 * sdpix + 1);
    
    % dilate shadow first
    shadow_cal = imdilate(shadow_cal, SEs);
    % % find shadow within plshadow shadow_cal(shadow_test~ = 1) = 0; %
    % dilate shadow again with the more accurate cloud shadow
    % shadow_cal = imdilate(shadow_cal, SEs);
    
%     cloud_cal = segm_cloud_tmp;
    cloud_cal = imdilate(segm_cloud_tmp, SEc);
end

cs_final(water) = 1;

% mask from plcloud step 1 snow or unknow
cs_final(snow) = 3; % snow

% step 2 shadow above snow and everyting
cs_final(shadow_cal) = 2; %shadow

% step 3 cloud above all
cs_final(cloud_cal) = 4; % cloud
cs_final(~boundary_test) = 255;

% reedit dir_im
%{
norln = regexp(filename, '.*(?=\.)', 'match');
Landsat_enviwrite([norln{1} 'Fmask_1_6_3sav'], cs_final, ...
    'uint8', reso_ref, ul, 'bsq', zc);

% record cloud and cloud shadow percent;
tmpcs = (cs_final == 1) | (cs_final == 3);
cspt = 100 * sum(tmpcs(:)) / sum(boundary_test(:));
%}
