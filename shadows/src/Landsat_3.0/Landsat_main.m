function [I, bands] = Landsat_main(pathtofiles, rc)

% find the MTL file
ind = regexp(pathtofiles, filesep);
if isempty(ind)
    file_MTL = [pathtofiles '_MTL.txt'];
else
    file_MTL = [pathtofiles pathtofiles(ind(end-1)+1:ind(end)-1) ...
        '_MTL.txt'];
end

fprintf([repmat('-', 1, 80) '\nProcessing folder %s\n'], pathtofiles);
if exist(file_MTL, 'file')
    % read meta data
    meta = Landsat_parseMeta(file_MTL);
    % check if the meta file is in a new or old style
    meta.ISNEWMTL = isfield(meta, 'LANDSAT_SCENE_ID');
    % extract the id of the Landsat mission (5, 7, 8 ...)
    meta.LNUM = str2double(meta.('SPACECRAFT_ID')(end));
    % cloud cover
    if ~isfield(meta, 'CLOUD_COVER')
        meta.CLOUD_COVER = 22.5;
    end
    if isfield(meta, 'CORNER_UL_PROJECTION_X_PRODUCT')
        meta.CORNER_UL_PROJECTION_X_PRODUCT = ...
            meta.CORNER_UL_PROJECTION_X_PRODUCT - 15;
    end
    if isfield(meta, 'CORNER_UL_PROJECTION_Y_PRODUCT')
        meta.CORNER_UL_PROJECTION_Y_PRODUCT = ...
            meta.CORNER_UL_PROJECTION_Y_PRODUCT + 15;
    end
    if isfield(meta, 'PRODUCT_UL_CORNER_MAPX')
        meta.PRODUCT_UL_CORNER_MAPX = meta.PRODUCT_UL_CORNER_MAPX - 15;
    end
    if isfield(meta, 'PRODUCT_UL_CORNER_MAPY')
        meta.PRODUCT_UL_CORNER_MAPY = meta.PRODUCT_UL_CORNER_MAPY + 15;
    end
    
    % read images
    if nargin > 1
        bands = Landsat_imread(file_MTL, meta, rc);
        if isfield(meta, 'FILE_NAME_BAND_QUALITY')
            band_bqa = Landsat_imreadbqa(file_MTL, meta, rc);
        end
    else
        bands = Landsat_imread(file_MTL, meta);
        if isfield(meta, 'FILE_NAME_BAND_QUALITY')
            band_bqa = Landsat_imreadbqa(file_MTL, meta);
        end
    end
    [bands, sat_mask] = Landsat_imcorrect(bands, meta);
    I = Landsat_imshowcolour(bands);
    [bands, cloud, snow, water, shadow, ~, ~] = ...
        Landsat_initmasks(bands, sat_mask, meta);
    img = Landsat_imshowcolour(bands);
%     imwrite(uint16(img) * 20, regexprep(upper(file_MTL), ...
%         '_MTL.TXT', '_COLOUR.png'), 'png');
%     Landsat_imwritemask(img, filename, mask_name, rows, cols)
%     I = Landsat_maskoverimage(img, shadow, 'r');
%     I = Landsat_maskoverimage(I, cloud, 'w');
%     I = Landsat_maskoverimage(I, snow,  'c');
%     I = Landsat_maskoverimage(I, water, 'b');
%     [cs_final, similar_num, cspt] = Landsat_fmaskCSSW(bands, ...
%         water, snow, cloud, shadow, meta);
else
    fprintf('Meta file %s is missing or has different name.\n', file_MTL);
end
