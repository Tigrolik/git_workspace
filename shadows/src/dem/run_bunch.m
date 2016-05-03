close all; clear all

format long G

%% find a file with DEM data
% fprintf('Preparing data... \n');
fs = filesep;
% set directory where DEM files are stored (parameter fs represent slash or
% backslash, depending on OS)
dirpath = ['..' fs '..' fs 'images' fs 'DEM' fs];

% dir_tiff = dir([dirpath 'TIFF' fs '*.tif*']);
% for j = 1:numel(dir_tiff)
%     dir_tiff(j).name = [dirpath 'TIFF' fs dir_tiff(j).name];
% end

dir_hgt1 = dir([dirpath 'HGT' fs '*26*.hgt*']);
dir_hgt2 = dir([dirpath 'HGT' fs '*27*.hgt*']);
dir_hgt3 = dir([dirpath 'HGT' fs '*28*.hgt*']);

for j = 1:numel(dir_hgt1)
    dir_hgt1(j).name = [dirpath 'HGT' fs dir_hgt1(j).name];
end
for j = 1:numel(dir_hgt2)
    dir_hgt2(j).name = [dirpath 'HGT' fs dir_hgt2(j).name];
end
for j = 1:numel(dir_hgt3)
    dir_hgt3(j).name = [dirpath 'HGT' fs dir_hgt3(j).name];
end

% dir_dtn = dir([dirpath 'DTED' fs '*.dt*']);
% for j = 1:numel(dir_dtn)
%     dir_dtn(j).name = [dirpath 'DTED' fs dir_dtn(j).name];
% end
% fns = {[dirpath 'n27_e085_3arc_v1.tif']}; % single file
% fns = {[dirpath 'n27_e085sdf_3arc_v1.tif'] [dirpath 'n28_e084_3arc_v1.tif'] ...
%     [dirpath 'n30_w088_1arc_v1.tiff'] [dirpath 'N30_w092_1arc_v1.tiff'] ...
%     [dirpath 'N17W066' fs 'N04E096.hgt'] [dirpath 'IC278.txt'] ...
%     [dirpath 'n04_e096_3arc_v2.tiff'] [dirpath 'dasdfs.dsfsa']};

% fns = unique([fns {dir_tiff.name} {dir_hgt.name} {dir_dtn.name}]);
fns = unique([{dir_hgt1.name} {dir_hgt2.name} {dir_hgt3.name}]);

% select a DEM file interactively if not specified manually above
% if ~exist('fn', 'var') || ~exist(fn, 'file')
if ~exist('fns', 'var')
    if ~exist(dirpath, 'dir')
        dirpath = '.';
    end
    % set file types to be chosen while file selection dialogue
    ft = {'*.tif; *.tiff; *.hdr; *.hgt', 'DEM Files';
        '*.tif; *.tiff; *.png; *.gif', 'All Image Files'; ...
        '*', 'All Files'};
    % open GUI to select a DEM file
    % ptf - path to file
    [fn, ptf] = uigetfile(ft, 'Select a DEM file', dirpath);
    % abort the script if the file has not been selected
    if isequal(fn, 0)
        fprintf('File not chosen... aborting\n');
        clear fn ptf;
        return;
    else
        fns = {[ptf fn]};
    end
elseif exist('fn', 'var')
    fns = {fn};
end

% specify part of the image to be read
% rows = [1; 2701]; cols = [500; img_info.Width];
% rows = [1700; 2499]; cols = [1700; 2499];
% rows = [700; 1099]; cols = [700; 1099];

%% read DEM data from every specified file
% sun azimuth and zenith (these are testing values, for real values it
% necessary to provide them either manually or from a metadata file)
% azi = 140.17589718; zen = 45.86074249;
azi = 146.59819922; zen = 48.49303224;
sun_ang = [azi - 90, zen];
% number of files to process
fns_num = numel(fns);

if fns_num > 1
    time_begin = clock;
    if ~matlabpool('size')
        matlabpool open
    end
    if matlabpool('size')
        parfor j = 1:fns_num
            % current file
            fn = fns{j};
            fprintf('Processing file (%d of %d) %s ...\n', j, fns_num, fn);
            if ~exist(fn, 'file')
                fprintf('File does not exist => next file ...\n');
                fprintf([repmat('*', 1, 100) '\n\n']);
                continue;
            end
            [sh_mask, I] = demfile2shadowfile(fn, sun_ang, 'interp');
        end
    else
        for j = 1:fns_num
            % current file
            fn = fns{j};
            fprintf('Processing file (%d of %d) %s ...\n', j, fns_num, fn);
            if ~exist(fn, 'file')
                fprintf('File does not exist => next file ...\n');
                fprintf([repmat('*', 1, 100) '\n\n']);
                continue;
            end
            [sh_mask, I] = demfile2shadowfile(fn, sun_ang, 'interp');
        end
    end
    if matlabpool('size')
        matlabpool close
    end
    time_end = etime(clock, time_begin);
end

