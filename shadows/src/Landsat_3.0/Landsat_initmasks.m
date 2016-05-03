function [bands, cloud, snow, water, shadow, t_templ, t_temph] = ...
    Landsat_initmasks(bands, sat_mask, meta, cldprob)

mask_size = size(bands{1});

if nargin < 4
    if isfield(meta, 'CLOUD_COVER')
        cldprob = meta.CLOUD_COVER;
    else
        cldprob = 22.5;
    end
end

fprintf('Read in TOA ref (plcloud_1.6.3sav)\n');

nodata_val = -9999;
% masks
% process only the overlap area
mask = bands{6} > nodata_val;

if ~any(mask(:))
    error('There is no data in the images');
end

cloud = false(mask_size); snow = cloud; water = cloud; shadow = cloud;

% potential cloud layer - pass one, vegetation and snow indices
NDVI = (bands{4} - bands{3}) ./ (bands{4} + bands{3});
NDSI = (bands{2} - bands{5}) ./ (bands{2} + bands{5});

NDVI((bands{4} + bands{3}) == 0) = 0.01;
NDSI((bands{2} + bands{5}) == 0) = 0.01;

% Basic cloud test
idcld = (NDSI < 0.8) & (NDVI < 0.8) & (bands{7} > 300) & (bands{6}< 2700);

% snow test. It takes every snow pixels including snow pixel under thin
% clouds or icy clouds
snow((NDSI > 0.15) & (bands{6} < 380) & (bands{4} > 1100) & ...
    (bands{2} > 1000)) = true;
snow(~mask) = false;

% Zhe's water test (works over thin cloud)
water(((NDVI < 0.01) & (bands{4} < 1100)) | ((NDVI < 0.1) & ...
    (NDVI > 0) & (bands{4} < 500))) = true;
water(~mask) = false;

% Whiteness test visible bands flatness (sum(abs)/mean < 0.6  => brigt and
% dark cloud )
visimean = sum(cat(3, bands{1:3}), 3) / 3;
whiteness = (abs(bands{1} - visimean) + abs(bands{2} - visimean) + ...
    abs(bands{3} - visimean)) ./ visimean;
clear visimean;

% saturation in the three visible bands
sat_sum = sum(cat(3, sat_mask{1:3}), 3) == 1;

% update idplcd: If one visible is saturated whiteness == 0
whiteness(sat_sum) = 0;
idcld = idcld & (whiteness < 0.7);

% Haze test
idcld = idcld & (((bands{1} - 0.5 * bands{3} - 800) > 0) | sat_sum);
% clear HOT; % need to find thick warm cloud

% Ratio4/5 > 0.75 cloud test
idcld = idcld & ((bands{4} ./ bands{5}) > 0.75);

%constants
l_pt = 0.175; % low percent
h_pt = 1 - l_pt; % high percent

% temperature & snow test test whether use thermal or not
mask_sum = 100 / sum(mask(:));
idclr = (~idcld) & mask;
ptm = mask_sum * sum(idclr(:)); % percent of clear pixel
idlnd = idclr & (~water);
lndptm = mask_sum * sum(idlnd(:));

if ptm <=  0.1 % no thermal test  = > meanless for snow detection (0~1)
    cloud(idcld) = true; % all cld
    % improving by majority filtering
    cloud = bwmorph(cloud, 'majority'); % exclude < 5/9
    shadow(~cloud) = true;
    bands{6} = -1;
    t_templ = -1;
    t_temph = -1;
else
    if lndptm <  0.1
        F_temp = bands{6}(idclr); % get clear temperature
    else
        F_temp = bands{6}(idlnd); % get land temperature
    end
    L_pt = 100 * l_pt;
    H_pt = 100 * h_pt;
    % Brightness test (over water)
    Brightness_prob = bands{5} ./ 1100;
    Brightness_prob(Brightness_prob > 1) = 1;
    
    % Get cloud prob over water temperature test (over water) get clear
    % water temperature
    % Final prob mask (water) cloud over water probability
    % wfinal_prob = 0.25 * (prctile(bands{6}((water) & ...
    % (bands{7} <= 300)), H_pt) - bands{6}) .* Brightness_prob;
    
    % Temperature test
    % 0.175 percentile background temperature (low)
    t_templ = prctile(F_temp, L_pt);
    % 0.825 percentile background temperature (high)
    t_temph = prctile(F_temp, H_pt);
    
    Temp_prob = (t_temph + 400 - bands{6}) / (t_temph - t_templ + 800);
    % Temperature can have prob > 1
    Temp_prob(Temp_prob < 0) = 0;
    
    NDSI(sat_mask{2} & (NDSI < 0)) = 0;
    NDVI(sat_mask{3} & (NDVI > 0)) = 0;
    
    % Final prob mask (land) cloud over land probability
    final_prob = (Temp_prob .* (1 - max(max(abs(NDSI), abs(NDVI)),...
        whiteness))) * 100;
    
    % dynamic threshold (land)
    % clr_max = prctile(final_prob(idlnd), H_pt) + cldprob;
    
    % fprintf('pcloud probability threshold (land) = .2f%\n', clr_max);
    id_final_cld = (idcld & (final_prob > (prctile(final_prob(idlnd), ...
        H_pt) + cldprob))& ~water) | (idcld & ((prctile(bands{6}(water ...
        & (bands{7} <= 300)), H_pt) - bands{6}) .* Brightness_prob > ...
        200) & water) | ((final_prob > 99) & ~water) | (bands{6} < ...
        t_templ - 3500);
    clear Brightness_prob;
    % Start with potential cloud mask potential cloud mask
    cloud(id_final_cld) = true;
    % improving by majority filtering
    cloud = bwmorph(cloud, 'majority'); % exclude < 5/9
    
    % Start with potential cloud shadow mask band 4 flood fill
    nir = bands{4};
    % estimating background (land) Band 4 ref
    nir(~mask) = prctile(nir(idlnd), L_pt);
    
    % band 5 flood fill
    swir = bands{5};
    % estimating background (land) Band 4 ref
    swir(~mask) = prctile(swir(idlnd), L_pt);
    
    % fill in regional minimum Bands 4 and 5 ref and compute shadow
    % probability
    shadow(min(imfill(nir) - bands{4}, imfill(swir) - bands{5}) > 200) ...
        = true;
    
    % release remory
    clear sat_mask NDSI NDVI whiteness Vari_prob Temp_prob final_prob ...
        clear wfinal_prob clear id_final_cld nir swir shadow_prob;
end

% refine water mask - Zhe's water mask (no confusion water/cloud)
water(water & ~cloud) = true;
cloud(~mask) = false;
shadow(~mask) = false;
