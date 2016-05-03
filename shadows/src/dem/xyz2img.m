function img = xyz2img(X, Y, Z)

if isvector(Z)
    img = reshape(Z, numel(unique(Y(:))), numel(unique(X(:))));
else
    img = Z;
end

if max(Z(:)) - min(Z(:)) > 255
    img = uint16(img);
else
    img = uint8(img);
end
