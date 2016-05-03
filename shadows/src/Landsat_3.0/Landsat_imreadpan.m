function pan_band = Landsat_imreadpan(file_MTL, meta, rc)

pathtofiles = fileparts(file_MTL);
if ~isempty(pathtofiles)
    if ~isequal(pathtofiles(end), filesep)
        pathtofiles = [pathtofiles filesep];
    end
end

fprintf('reading the panchromatic image ... ');

if meta.ISNEWMTL
    if nargin > 2
        pan_band = single(imread([pathtofiles meta.FILE_NAME_BAND_8], ...
            'PixelRegion', {min(max(rc{1}, 1), meta.REFLECTIVE_LINES), ...
            min(max(rc{2},1), meta.REFLECTIVE_SAMPLES)}));
    else
        pan_band = single(imread([pathtofiles meta.FILE_NAME_BAND_8]));
    end
else
    if nargin > 2
        pan_band = single(imread([pathtofiles meta.FILE_NAME_BAND_8], ...
            'PixelRegion', {min(max(rc{1}, 1), meta.PRODUCT_LINES_REF), ...
            min(max(rc{2},1), meta.PRODUCT_SAMPLES_REF)}));
    else
        pan_band = single(imread([pathtofiles meta.BAND8_FILE_NAME]));
    end
end

% correct the panchromatic image
%{
fprintf('correcting the image ... ');
if meta.LNUM == 8
    pan_band = (meta.REFLECTANCE_MULT_BAND_8 * ...
        (meta.RADIANCE_MULT_BAND_8 * pan_band + ...
        meta.RADIANCE_ADD_BAND_8) + meta.REFLECTANCE_ADD_BAND_8) / ...
        sin(meta.SUN_ELEVATION);
else
    if meta.ISNEWMTL
        Lmin = meta.RADIANCE_MINIMUM_BAND_8;
        Qcalmin = meta.QUANTIZE_CAL_MIN_BAND_8;
        pan_band = ((meta.RADIANCE_MAXIMUM_BAND_8 - Lmin) / ...
            (meta.QUANTIZE_CAL_MAX_BAND_8 - Qcalmin)) * (pan_band - ...
            Qcalmin) + Lmin;
    else
        Lmin = meta.LMIN_BAND8;
        Qcalmin = meta.QCALMIN_BAND8;
        pan_band = ((meta.LMAX_BAND8 - Lmin) / (meta.QCALMAX_BAND8 - ...
            Qcalmin)) * (pan_band - Qcalmin) + Lmin;
    end
end
%}
fprintf('done\n');
