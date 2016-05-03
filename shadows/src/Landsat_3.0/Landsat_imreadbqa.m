function band_bqa = Landsat_imreadbqa(file_MTL, meta, rc)

% get the path to the images directory and fix the last slash if needed
pathtofiles = fileparts(file_MTL);
if ~isempty(pathtofiles)
    if ~isequal(pathtofiles(end), filesep)
        pathtofiles = [pathtofiles filesep];
    end
end

f_ns = [pathtofiles meta.FILE_NAME_BAND_QUALITY];

if nargin > 2
    % crop numbers of rows and cols if they exceed the size of the image
    % and read the image
    if meta.ISNEWMTL
        rc = {min(max(rc{1}, 1), meta.REFLECTIVE_LINES), ...
            min(max(rc{2},1), meta.REFLECTIVE_SAMPLES)};
        band_bqa = single(imread(f_ns, 'PixelRegion', rc));
    else
        rc = {min(max(rc{1}, 1), meta.PRODUCT_LINES_REF), ...
            min(max(rc{2},1), meta.PRODUCT_SAMPLES_REF)};
        band_bqa = single(imread(f_ns, 'PixelRegion', rc));
    end
else
    band_bqa = single(imread(f_ns));
end
