function img = Landsat_imshowcolour(bands, varargin)

if nargin < 2
    if numel(bands) == 7 % assume Landsat 5 or 7 (7 bands)
        img = cat(3, bands{3:-1:1});
    else % Landsat 8 (11 bands)
        img = cat(3, bands{4:-1:2});
    end
else
    par_val = varargin{end};
    if isstruct(par_val) % metadata is given
        if par_val.LNUM == 8
            img = cat(3, bands{4:-1:2});
        else % LNUM = 7 or 5
            img = cat(3, bands{3:-1:1});
        end
    else % bands' order is given
        img = cat(3, bands{par_val});
    end
end
