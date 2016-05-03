function bands = Landsat_imread(file_MTL, meta, rc)

% get the path to the images directory and fix the last slash if needed
pathtofiles = fileparts(file_MTL);
if ~isempty(pathtofiles)
    if ~isequal(pathtofiles(end), filesep)
        pathtofiles = [pathtofiles filesep];
    end
end

switch meta.LNUM
    case 8
        % Landsat 8 provides eleven bands
        num_bands = 10;
        f_ind = [1:7 9:11];
        % store files paths in a cell array
        f_ns = cell(1, num_bands);
        for j = 1:num_bands
            % extract file's name
            f_ns{j} = [pathtofiles meta.(['FILE_NAME_BAND_' ...
                num2str(f_ind(j))])];
        end
    case 7
        % Landsat 7 provides seven bands
        num_bands = 7;
        f_ns = cell(1, num_bands);
        if meta.ISNEWMTL
            % new style MTL file's convention of files 'indexing'
            f_ind = {1, 2, 3, 4, 5, '6_VCID_1', num_bands};
            for j = 1:num_bands
                f_ns{j} = [pathtofiles meta.(['FILE_NAME_BAND_' ...
                    num2str(f_ind{j})])];
            end
        else
            % old style MTL file's convention of files 'indexing'
            f_ind = [1:5 61 7];
            for j = 1:num_bands
                f_ns{j} = [pathtofiles meta.(['BAND' num2str(f_ind(j)) ...
                    '_FILE_NAME'])];
            end
        end
    case 5
        % Landsat 5 provides seven bands as well
        num_bands = 7;
        f_ns = cell(1, num_bands);
        if meta.ISNEWMTL
            for j = 1:num_bands
                f_ns{j} = [pathtofiles meta.(['FILE_NAME_BAND_' ...
                    num2str(j)])];
            end
        else
            for j = 1:num_bands
                f_ns{j} = [pathtofiles meta.(['BAND' num2str(j) ...
                    '_FILE_NAME'])];
            end
        end
    otherwise
        fprintf('Either incorrect or old Landsat mission number\n');
end

% Store all bands in a cell array
bands = cell(1, num_bands);

% if rows and columns are given then process the files correspondingly
fprintf('reading images ... ');
if nargin > 2
    % crop numbers of rows and cols if they exceed the size of the image
    % and read the images
    if meta.ISNEWMTL
        rc = {min(max(rc{1}, 1), meta.REFLECTIVE_LINES), ...
            min(max(rc{2},1), meta.REFLECTIVE_SAMPLES)};
        if matlabpool('size')
            parfor j = 1:num_bands
                bands{j} = single(imread(f_ns{j}, 'PixelRegion', rc));
            end
        else
            for j = 1:num_bands
                bands{j} = single(imread(f_ns{j}, 'PixelRegion', rc));
            end
        end
    else
        rc = {min(max(rc{1}, 1), meta.PRODUCT_LINES_REF), ...
            min(max(rc{2},1), meta.PRODUCT_SAMPLES_REF)};
        if matlabpool('size')
            parfor j = 1:num_bands
                bands{j} = single(imread(f_ns{j}, 'PixelRegion', rc));
            end
        else
            for j = 1:num_bands
                bands{j} = single(imread(f_ns{j}, 'PixelRegion', rc));
            end
        end
    end
else
    % just read all images
    if matlabpool('size')
        parfor j = 1:num_bands
            bands{j} = single(imread(f_ns{j}));
        end
    else
        for j = 1:num_bands
            bands{j} = single(imread(f_ns{j}));
        end
    end
end
fprintf('done\n');
