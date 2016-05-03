clear all; close all
format long g;

fs = filesep;
path_fns = {['E:' fs 'my_files' fs 'studies' fs 'LUT' fs ...
    'doctoral_studies' fs 'shadows' fs 'images' fs 'Landsat' fs ...
    'LE71420412003102ASN00' fs], ['E:' fs 'my_files' fs 'studies' fs ...
    'LUT' fs 'doctoral_studies' fs 'shadows' fs 'images' fs 'Landsat' fs ...
    'L5142041_04120111003' fs], ['E:' fs 'my_files' fs 'studies' fs 'LUT' ...
    fs 'doctoral_studies' fs 'shadows' fs 'images' fs 'Landsat' fs ...
    'LT50230302011290PAC01' fs], ['..' fs '..' fs 'images' fs 'Landsat' ...
    fs 'LC81430402013256LGN00' fs], ['..' fs '..' fs 'images' fs ...
    'Landsat' fs 'L71171057_05720000125' fs]};

% define rows and columns to define the region to read from images
%      -- rows --    -- cols --
rc = {[1762, 4717], [1126, 5324]};
% rc = {[700; 1099], [700; 1099]};

if ~matlabpool('size')
    matlabpool open
end

tic;
if exist('rc', 'var')
    parfor j = 1:numel(path_fns)
        bands = Landsat_main(path_fns{j}, rc);
    end
else
    for j = 1:numel(path_fns)
        bands = Landsat_main(path_fns{j});
    end
end
t_elp = toc;

if matlabpool('size')
    matlabpool close
end
