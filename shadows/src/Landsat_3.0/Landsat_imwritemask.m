function Landsat_imwritemask(img, filename, mask_name, rows, cols)

% image format
fmt = 'png';

[pathtofiles, fname] = fileparts(filename);
if ~isequal(pathtofiles(end) ,'/')
    pathtofiles = [pathtofiles '/'];
end

% construct the new file name
if nargin == 5
    fn_str = [pathtofiles regexprep(upper(fname), '_MTL', ...
        ['_' upper(mask_name) '_' num2str(diff(rows) + 1) 'x' ...
        num2str(diff(cols) + 1) '.' fmt])];
else
    fn_str = [pathtofiles regexprep(upper(fname), '_MTL', ...
        ['_' upper(mask_name) '.' fmt])];
end

switch class(img)
    case 'logical'
        if exist(fn_str, 'file')
            fprintf('Rewriting %s mask into file %s ... ', ...
                mask_name, fn_str);
        else
            fprintf('Writing %s mask into file %s ... ', ...
                mask_name, fn_str);
        end
        imwrite(img, fn_str, fmt)
    otherwise
        if exist(fn_str, 'file')
            fprintf('Rewriting %s image into file %s ... ', ...
                mask_name, fn_str);
        else
            fprintf('Writing %s image into file %s ... ', ...
                mask_name, fn_str);
        end
        imwrite(uint16(img), fn_str, fmt)
end

fprintf('done\n');
