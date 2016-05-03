function [bands, sat_mask] = Landsat_imcorrect(bands, meta)

num_bands = numel(bands);
id_missing = bands{1} == 0;
for j = 2:num_bands
    id_missing = id_missing | (bands{j} == 0);
end

switch meta.LNUM
    case 8
        % find pixels that are saturated in the visible bands
        sat_mask = cell(1, 3);
        for j = 2:4
            sat_mask{j} = bands{j} == 65535;
        end
        % correction for Landsat 8
        temp_num = 10000 / cos(meta.SUN_ELEVATION * pi / 180);
        % the 8th band is ignored - it is panchromatic
        f_ind = [1:7 9:11];
        for j = 1:8
            j_str = num2str(f_ind(j));
            Rmin = meta.(['REFLECTANCE_MINIMUM_BAND_' j_str]);
            Qcalmin = meta.(['QUANTIZE_CAL_MIN_BAND_' j_str]);
            bands{j} = (((meta.(['REFLECTANCE_MAXIMUM_BAND_' j_str]) - ...
                Rmin) / (meta.(['QUANTIZE_CAL_MAX_BAND_' j_str]) - ...
                Qcalmin)) * (bands{j} - Qcalmin) + Rmin) * temp_num;
        end
        for j = 9:10
            j_str = num2str(f_ind(j));
            Rmin = meta.(['RADIANCE_MINIMUM_BAND_' j_str]);
            Qcalmin = meta.(['QUANTIZE_CAL_MIN_BAND_' j_str]);
            % convert from Kelvin to Celcius with 0.01 scale_facor
            bands{j} = 100 * (meta.(['K2_CONSTANT_BAND_' j_str]) ./ ...
                log(meta.(['K1_CONSTANT_BAND_' j_str]) ./ ...
                (((meta.(['RADIANCE_MAXIMUM_BAND_' j_str]) - Rmin) / ...
                (meta.(['QUANTIZE_CAL_MAX_BAND_' j_str]) - Qcalmin)) * ...
                (bands{j} - Qcalmin) + Rmin) + 1) - 273.15);
        end
    case 7
        % correction for Landsat 7
        % find pixels that are saturated in the visible bands
        sat_mask = cell(1, 3);
        for j = 1:3
            sat_mask{j} = bands{j} == 255;
        end
        % thermal constants
        K1 = 666.09;
        K2 = 1282.71;
        % exo-atmospheric solar irradiance
        ESUN = [1970, 1842, 1547, 1044, 225.7, -1.0, 82.06];
        if meta.ISNEWMTL
            if ~isfield(meta, 'EARTH_SUN_DISTANCE')
                temp_num = (10 ^ 4 * pi * Landsat_EarthSunDist(...
                    str2double(meta.LANDSAT_SCENE_ID(14:16))) ^ 2) / ...
                    cos(meta.SUN_ELEVATION * pi / 180);
            else
                temp_num = (10 ^ 4 * pi * meta.EARTH_SUN_DISTANCE ^ 2) ...
                    / cos(meta.SUN_ELEVATION * pi / 180);
            end
            for j = [1:5 7]
                j_str = num2str(j);
                Lmin = meta.(['RADIANCE_MINIMUM_BAND_' j_str]);
                Qcalmin = meta.(['QUANTIZE_CAL_MIN_BAND_' j_str]);
                bands{j} = (((meta.(['RADIANCE_MAXIMUM_BAND_' j_str]) ...
                    - Lmin) / (meta.(['QUANTIZE_CAL_MAX_BAND_' j_str]) ...
                    - Qcalmin)) * (bands{j} - Qcalmin) + Lmin) * ...
                    temp_num / ESUN(j);
            end
            Lmin = meta.RADIANCE_MINIMUM_BAND_6_VCID_1;
            Qcalmin = meta.QUANTIZE_CAL_MIN_BAND_6_VCID_1;
            bands{6} = 100 * (K2 ./ log((K1 ./ ((( ...
                meta.RADIANCE_MAXIMUM_BAND_6_VCID_1 - Lmin) / ...
                (meta.QUANTIZE_CAL_MAX_BAND_6_VCID_1 - Qcalmin)) * ...
                (bands{6} - Qcalmin) + Lmin)) + 1) - 273.15);
        else
            if ~isfield(meta, 'EARTH_SUN_DISTANCE')
                day_info = meta.DATEHOUR_CONTACT_PERIOD;
                if ischar(day_info)
                    ESDist = ...
                        Landsat_EarthSunDist(str2double(day_info(4:6)));
                else
                    % use the last two digits as day's number
                    ESDist = Landsat_EarthSunDist(day_info - ...
                        floor(day_info / 100) * 100);
                end
                % auxilliary variable to use inside the loops
                temp_num = (10 ^ 4 * pi * ESDist ^ 2) / ...
                    cos(meta.SUN_ELEVATION * pi / 180);
            else
                temp_num = (10 ^ 4 * pi * meta.EARTH_SUN_DISTANCE ^ 2) ...
                    / cos(meta.SUN_ELEVATION * pi / 180);
            end
            for j = [1:5 7]
                j_str = num2str(j);
                Lmin = meta.(['LMIN_BAND' j_str]);
                Qcalmin = meta.(['QCALMIN_BAND' j_str]);
                bands{j} = temp_num * (((meta.(['LMAX_BAND' j_str]) - ...
                    Lmin) / (meta.(['QCALMAX_BAND' j_str]) - Qcalmin)) ...
                    * (bands{j} - Qcalmin) + Lmin) / ESUN(j);
            end
            Lmin = meta.LMIN_BAND61;
            Qcalmin = meta.QCALMIN_BAND61;
            bands{6} = 100 * (K2 ./ log((K1 ./ (((meta.LMAX_BAND61 - ...
                Lmin) / (meta.QCALMAX_BAND61 - Qcalmin)) * (bands{6} - ...
                Qcalmin) + Lmin)) + 1) - 273.15);
        end
    case 5
        % correction for Landsat 5
        % find pixels that are saturated in the visible bands
        sat_mask = cell(1, 3);
        for j = 1:3
            sat_mask{j} = bands{j} == 255;
        end
        % thermal constants
        K1 = 607.76;
        K2 = 1260.56;
        % exo-atmospheric solar irradiance
        ESUN = [1983.0, 1796.0, 1536.0, 1031.0, 220.0, -1.0, 83.44];
        if meta.ISNEWMTL
            if ~isfield(meta, 'EARTH_SUN_DISTANCE')
                temp_num = (10 ^ 4 * pi * Landsat_EarthSunDist(...
                    str2double(meta.LANDSAT_SCENE_ID(14:16))) ^ 2) / ...
                    cos(meta.SUN_ELEVATION * pi / 180);
            else
                temp_num = (10 ^ 4 * pi * meta.EARTH_SUN_DISTANCE ^ 2) ...
                    / cos(meta.SUN_ELEVATION * pi / 180);
            end
            for j = [1:5 7]
                j_str = num2str(j);
                Lmin = meta.(['RADIANCE_MINIMUM_BAND_' j_str]);
                Qcalmin = meta.(['QUANTIZE_CAL_MIN_BAND_' j_str]);
                bands{j} = temp_num *(((meta.(['RADIANCE_MAXIMUM_BAND_'...
                    j_str]) - Lmin) / (meta.(['QUANTIZE_CAL_MAX_BAND_' ...
                    j_str]) - Qcalmin)) * (bands{j} - Qcalmin) + Lmin) ...
                    / ESUN(j);
            end
            Lmin = meta.RADIANCE_MINIMUM_BAND_6;
            Qcalmin = meta.QUANTIZE_CAL_MIN_BAND_6;
            bands{6} = 100 * (K2 ./ log((K1 ./ ((( ...
                meta.RADIANCE_MAXIMUM_BAND_6 - Lmin) / ...
                (meta.QUANTIZE_CAL_MAX_BAND_6 - Qcalmin)) * ...
                (bands{6} - Qcalmin) + Lmin)) + 1) - 273.15);
        else
            if ~isfield(meta, 'EARTH_SUN_DISTANCE')
                day_info = meta.DATEHOUR_CONTACT_PERIOD;
                if ischar(day_info)
                    ESDist = ...
                        Landsat_EarthSunDist(str2double(day_info(4:6)));
                else
                    % use the last two digits as day's number
                    ESDist = Landsat_EarthSunDist(day_info - ...
                        floor(day_info / 100) * 100);
                end
                % auxilliary variable to use inside the loops
                temp_num = (10 ^ 4 * pi * ESDist ^ 2) / ...
                    cos(meta.SUN_ELEVATION * pi / 180);
            else
                temp_num = (10 ^ 4 * pi * meta.EARTH_SUN_DISTANCE ^ 2) ...
                    / cos(meta.SUN_ELEVATION * pi / 180);
            end
            for j = [1:5 7]
                j_str = num2str(j);
                Lmin = meta.(['LMIN_BAND' j_str]);
                Qcalmin = meta.(['QCALMIN_BAND' j_str]);
                bands{j} = temp_num * (((meta.(['LMAX_BAND' j_str]) - ...
                    Lmin) / (meta.(['QCALMAX_BAND' j_str]) - Qcalmin)) ...
                    * (bands{j} - Qcalmin) + Lmin) / ESUN(j);
            end
            Lmin = meta.LMIN_BAND6;
            Qcalmin = meta.QCALMIN_BAND6;
            bands{6} = 100 * (K2 ./ log((K1 ./ (((meta.LMAX_BAND6 - ...
                Lmin) / (meta.QCALMAX_BAND6 - Qcalmin)) * (bands{6} - ...
                Qcalmin) + Lmin)) + 1) - 273.15);
        end
    otherwise
        fprintf('Incorrect or old Landsat mission number\n');
end

for j = 1:num_bands
    bands{j}(id_missing) = -9999;
end
