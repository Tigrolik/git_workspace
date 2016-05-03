function H = homography_svd(p_in, p_out)

% homography_svd finds a homography from point pairs
% H = homography_svd(p_in, p_out) takes a 2xN matrix of input vectors and
% a 2xN matrix of output vectors, and returns the homogeneous
% transformation matrix that maps the inputs to the outputs, to some
% approximation if there is noise.
% This uses the SVD method of
% http://www.robots.ox.ac.uk/%7Evgg/presentations/bmvc97/criminispaper/node3.html

if ~isequal(size(p_in), size(p_out))
    error('Points matrices different sizes');
end

if size(p_in, 1) < 2
    error('Points matrices must have two or three rows');
end

n = size(p_in, 2);
if n < 4
    error('Need at least 4 matching points');
end

% Solve equations using SVD
x = p_out(1, :); y = p_out(2,:); X = p_in(1,:); Y = p_in(2,:);
rows0 = zeros(3, n);
rowsXY = -[X; Y; ones(1,n)];
hx = [rowsXY; rows0; x.*X; x.*Y; x];
hy = [rows0; rowsXY; y.*X; y.*Y; y];
h = [hx hy];

if n >= 4
    [U, ~, ~] = svd(h);
else
    [U, ~, ~] = svd(h, 'econ');
end

H = (reshape(U(:,9), 3, 3))';
