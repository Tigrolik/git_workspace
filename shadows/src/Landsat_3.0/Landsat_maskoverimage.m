function I = Landsat_maskoverimage(img, mask, clr_)

max_val = max(img(:));
if max_val > 256
    r = 65535;
elseif max_val > 1
    r = 255;
elseif ~islogical(img)
    r = max_val;
else
    r = 1;
end

% If the user doesn't specify the color, use white.
if nargin < 3
    clr = [1, 1, 1] * r;
else
    assert(~isempty(clr_), 'imoverlay:badInputSize', ...
        'Input color argument must not be empty.');
    rgb_values = [eye(3); 1 - eye(3); 1, 1, 1; 0, 0, 0];
    if ischar(clr_)
        clr_short_names = 'rgbcmywk';
        clr_long_names = {'red', 'green', 'blue', 'cyan', 'magenta', ...
            'yellow', 'white', 'black'};
        [is_mem, clr_ind] = ismember(clr_, clr_short_names);
        if ~is_mem
            [is_mem, clr_ind] = ismember(clr_, clr_long_names);
            assert(all(is_mem),' imoverlay:badInputContents', ...
                sprintf(['Color input can only be the characters '...
                '''rgbcmywk'' or strings\n''red'' ''green'' ''blue''' ...
                '''cyan'' ''magenta'' ''yellow'' ''white'' ''black''\n' ...
                'or rgb triple values [a b c]']));
        end
        clr = rgb_values(clr_ind, :) * r;
    elseif isnumeric(clr_) || islogical(clr_)
        assert(numel(clr_) == 3,'convert_color:badInputSize', ...
            'Numeric input must be a 1-by-3 vector');
        clr = clr_ / max(clr_) * r;
    else  % Input is an invalid type
        error('convert_color:badInputType', ...
            'Input must be a character or numeric array.');
    end
end

% Force the 2nd input to be logical.
if ~islogical(mask)
    mask = logical(mask);
end

% Initialize the red, green, and blue output channels.
if ndims(img) == 3
    % Input is RGB truecolor.
    out_red   = img(:,:,1);
    out_green = img(:,:,2);
    out_blue  = img(:,:,3);
else
    % Input is grayscale.  Initialize all output channels the same.
    out_red   = img;
    out_green = img;
    out_blue  = img;
end

% Replace output channel values in the mask locations with the appropriate
% color value.
out_red(mask)   = clr(1);
out_green(mask) = clr(2);
out_blue(mask)  = clr(3);

% Form an RGB truecolor image by concatenating the channel matrices along
% the third dimension.
I = cat(3, out_red, out_green, out_blue);
