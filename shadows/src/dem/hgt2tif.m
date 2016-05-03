function img = hgt2tif(fn)

% convert and hgt file to image in tiff format
ext_ind = numel(fn) - regexp(fliplr(fn), '\.', 'once') + 1;
I = readdemhgt(fn, ext_ind);
imwrite(uint16(I), [fn(1:ext_ind(end)-1) '_h2t.tif'], 'tiff');
img = imread([fn(1:ext_ind(end)-1) '_h2t.tif']);

i = numel(fn) - regexp(fliplr(fn), '\\') + 1;
s = fn(i(1)+1:ext_ind(end)-1);

dr = dir([fn(1:i(2)) '/TIFF/' [s(1:3) '_' s(4:end)] '*']);
fn_new = dr(1).name;

if ~isempty(dr)
    [~, geo_ref] = geotiffread(fn_new);
    geotiffwrite(fn_new, img, geo_ref);
end

