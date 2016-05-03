% set directory where DEM files are stored (parameter fs represent slash or
% backslash, depending on OS)
fs = filesep;
dirpath = ['..' fs '..' fs 'images' fs 'DEM' fs];

dir_tiff = dir([dirpath 'TIFF' fs '*.tif*']);
for j = 1:numel(dir_tiff)
    dir_tiff(j).name = [dirpath 'TIFF' fs dir_tiff(j).name];
end
dir_hgt = dir([dirpath 'HGT' fs '*.hgt*']);
for j = 1:numel(dir_hgt)
    dir_hgt(j).name = [dirpath 'HGT' fs dir_hgt(j).name];
end
dir_dtn = dir([dirpath 'DTED' fs '*.dt*']);
for j = 1:numel(dir_dtn)
    dir_dtn(j).name = [dirpath 'DTED' fs dir_dtn(j).name];
end
fns = unique([{dir_tiff.name} {dir_hgt.name} {dir_dtn.name}]);

% if ~matlabpool('size')
%     matlabpool open
% end

% if matlabpool('size')
%     parfor j = 1:numel(fns)
%         dem2txt(fns{j});
%     end
% else

n = numel(fns);
for j = 1:n
    fn = fns{j};
    fprintf('Processing file %s (%d of %d)\n', fn, j, n);
    dot_ind = regexp(fn, '\.');
    img2txt(readdem(fn), [fn(1:dot_ind(end)) 'txt']);
end

% end

% if matlabpool('size')
%     matlabpool close
% end
