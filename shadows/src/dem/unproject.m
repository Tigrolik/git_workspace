% UNPROJECT - add unit element to column vectors
%
% y = unproject(x)
% y = unproject(x, rho)
%
% Returns a matrix with one more rows than in input.
% This is the conversion from inhomogenous to homogenous coordinates.
%
% Argument rho can be
% - undefined: vectors are augmented with 1, as the normal case
% - scalar: all vectors are augmented with the constant rho
% - row vector: vectors are augmented with respective rho elements

function y = unproject(x, rho);

if nargin < 2
	rho = 1;
end

N = size(x, 2);

if length(rho) == 1
	y = [x; (rho * ones(1, N))];
else
	y = [x; rho];
end
