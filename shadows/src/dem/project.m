% PROJECT - divide column vectors by their last element
%
% y = project(x)
%
% Returns a matrix with one less row than in input.
% This is the conversion from homogenous to inhomogenous coordinates.

function y = project(x);

N = size(x, 1) - 1;
y = x(1:N, :) ./ repmat(x(N+1, :), N, 1);
