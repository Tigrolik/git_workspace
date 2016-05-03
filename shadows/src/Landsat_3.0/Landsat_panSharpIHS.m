function I = Landsat_panSharpIHS(bands, pan_band)

if ~(strcmpi(class(pan_band), 'single') || ...
        strcmpi(class(pan_band), 'double'))
    pan_band = single(pan_band);
end

[s1, s2] = size(pan_band);

r_ = imresize(bands{3}, [s1, s2]);
g_ = imresize(bands{2}, [s1, s2]);
b_ = imresize(bands{1}, [s1, s2]);

delta = pan_band - ((r_ + g_ + b_) / 3);

I = cat(3, r_ + delta, g_ + delta, b_ + delta);
