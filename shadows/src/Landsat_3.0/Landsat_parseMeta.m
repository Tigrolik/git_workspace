function meta = Landsat_parseMeta(file_MTL, style)

% function meta = Landsat_parseMeta(filename, style) reads the MTL Landsat
% metafile (filename) and saves information in a structure (meta),
% converting numeric data into double variables. Optional parameter style
% allows to save meta data as strings without change

if nargin < 2
    style = 'digital';
end

% read metadata from the file
buf_size = 65535;
fid_in = fopen(file_MTL, 'r');
info_scan = textscan(fid_in, '%q', 'BufSize', buf_size, ...
    'Delimiter', ' = ', 'MultipleDelimsAsOne', true);
fclose(fid_in);
geo_info = info_scan{1};

% remove unnecessary elements
geo_info(end) = [];
ind = find(strcmpi(geo_info, 'GROUP'));
geo_info([ind, ind+1]) = [];
ind = find(strcmpi(geo_info, 'END_GROUP'));
geo_info([ind, ind+1]) = [];
geo_info(strcmpi(geo_info, 'END')) = [];
geo_info(strcmpi(geo_info, '')) = [];

% number of elements
n = numel(geo_info);
% the first elements correspond to field names and the second elements
% correspond to data
data_elem = geo_info(2:2:n);

if ~strcmpi(style, 'original')
    % convert numeric fields into numbers:
    % ([-+])? = zero or one occurence of  the minus or plus sign
    % \d* = zero or more occurences of digits (zero allows to have a dot
    % without the preceding zero sign)
    % (\.)? = single dot or no dot at all \d+ = one or more occurences of
    % digits
    % ([eE]([-+])?)? = e or E (the exponential sign) optionally followed by
    % a single minus or plus sign and this combination occurs either once
    % or not at all
    % (([eE]([-+])?)?\d+)? = the previous combination is followed by at
    % least one digit and the whole exponential expression (e.g., e-14) is
    % matched if exists (and so the question mark again = zero or one
    % occurence)
    match_expr = '([-+])?(\d+(\.)?\d*|\d*(\.)?\d+)(([eE]([-+])?)?\d+)?';
    for j = 1:n*0.5
        temp = data_elem{j};
        match_str = regexp(temp, match_expr, 'match');
        if ~isempty(match_str)
            if numel(match_str{1}) == numel(temp)
                data_elem{j} = str2double(temp);
            end
        end
    end
end

% create structure from the cell array
meta = cell2struct(data_elem, geo_info(1:2:n));
