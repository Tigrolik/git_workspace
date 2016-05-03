% close all; clear all

format long G

% set directory where DEM files are stored (parameter fs represent slash or
% backslash, depending on OS)
fs = filesep;
% dirpath = ['..' fs '..' fs 'images' fs 'DEM' fs];
dirpath = ['..' fs '..' fs 'images' fs 'DEM' fs];
% dirpath = ['home' fs 'Data' fs 'my_files' fs 'studies' fs 'LUT' fs ...
%     'doctoral_studies' fs 'shadows' fs 'images' fs 'DEM' fs];
% if ~exist(dirpath, 'dir')
%     dirpath = '.';
% end
% define a file
% fn = [dirpath 'n30_w088_1arc_v1.tiff'];
% fn = [dirpath 'n30_w104_1arc_v1.dt2'];
% fn = [dirpath 'TIFF' fs 'n34_w111_1arc_v3.tif'];
% fn = [dirpath 'N17W066' fs 'N04E096.hgt'];
% fn = [dirpath 'TXT' fs 'IC278.txt'];
% dirpath = ['..' fs '..' fs 'images' fs 'test' fs 'SRTM' fs 'raw' fs];
% fn = [dirpath 'TIFF' fs 'n04_e033_3arc_v1.tiff'];
% fn = [dirpath 'HGT' fs 'N31E078.hgt'];
% fn = [dirpath 'HGT' fs 'N28E081.hgt'];

fn = [dirpath 'TIFF' fs 'n28_e081_3arc_v2.tif'];
time_p = [2011, 1, 18, 4, 56, 25];
% time_p.year = 2011;
% time_p.month = 1;
% time_p.day = 18;
% time_p.hours = 4;
% time_p.minutes = 56;
% time_p.seconds = 25;

% fn = [dirpath 'TIFF' fs 'n04_e097_3arc_v1.tiff'];
% fn = [dirpath 'TIFF' fs 'bardia_ast_clip.tif'];
% fn = ['F:' fs 'my_files' fs 'studies' fs 'LUT' fs 'doctoral_studies' ...
%     fs 'shadows' fs 'images' fs 'DEM' fs 'TIFF' fs 'bardia_ast_clip.tif'];
% fn = [dirpath 'TIFF' fs 'n31_e078_3arc_v2.tif'];
% fn = ['Y:' fs 'users' fs 'a0315930' fs 'N36W111.hgt'];
% fn = ['Y:' fs 'users' fs 'a0315930' fs 'N35W112.hgt'];
% dirpath = ['..' fs '..' fs 'images' fs 'test' fs 'SRTM_void_filled' ...
%     fs 'raw' fs];
% fn = [dirpath 'n27_e084_3arc_v2.tif'];

if ~exist('fn', 'var')
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
        fn = [ptf fn];
    end
elseif ~exist(fn, 'file')
    fprintf('Wrong file... aborting\n');
    clear fn;
    return;
end

fprintf('Processing file %s ...\n', fn);

% specify part of the image to be read
% rows = [1; 2701]; cols = [500; img_info.Width];
% rows = [1700; 2499]; cols = [1700; 2499];
% rows = [700; 1099]; cols = [700; 1099];

% if exist('rows', 'var') && exist('cols', 'var')
%     rc = {rows, cols};
% end

% read DEM data from every specified file
% sun azimuth and zenith (these are testing values, for real values it
% necessary to provide them either manually or from a metadata file)
% azi = 140.17589718; zen = 45.86074249;
% azi = 128.3999366; zen = 51.4048697;
% azi = 152.10181852; zen = 32.07551912;
azi = 148.6871608; zen = 33.8828316;
% azi = 145.02274968; zen = 47.26407798;
% azi = 146.59819922; zen = 48.49303224;
% azi = 149.0112589; zen = 46.32136145;
% azi = 145.40173333; zen = 43.66376729;
% sun_ang = [azi, zen];
% sun_ang = [azi - 90, zen];
% sun_ang = [azi - 90, 90 - zen];
% degrees => radians
rad = pi / 180;
azi = azi * rad; zen = zen * rad;

tic
% [sh_mask, I, resimg, geo_loc] = shadowovertime(fn, time_p);
toc

% name of the shadow mask file (remove the original file extension,
% append _sh_mask mark and use extension .png
% fn_str = sprintf('%s_sumsh.png', fn(1:ext_ind(end) - 1));
% if exist(fn_str, 'file')
%     fprintf('Rewriting sum shadow mask into file %s ...\n', fn_str);
% else
%     fprintf('Writing sum shadow mask into file %s ...\n', fn_str);
% end
% imwrite(rs, fn_str, 'png');


% fn_info = imfinfo(fn);
% resimg = zeros(fn_info.Height, fn_info.Width);
% for j = 1:20
%     fprintf('Layer %d ...\n', j);
%     time_p.hours = round(j/2) + 3;
%     time_p.minutes = 30 * mod(j+1,2);
%     [sh_mask, I, geo_loc] = shadowovertime(fn, time_p);
%     resimg = resimg + sh_mask;
%     clear sh_mask I geo_loc
%     figure(); imshow(sh_mask); zoom on
% end
% read DEM data
% [I res latlon] = readdem(fn, fn(ext_ind:end));
% tic;
% [sh_mask, I_dem, geo_dem] = demfile2shadowfile(fn, sun_ang);
% t_elp = toc;