%H2D_TRANS N-D homography transformation
%
% [Xn] = hnd_trans(X_,H_)
%
% Transform N-D coordinates X_ using the transformation matrix H_.
%
% Output:
%  Xn - DxN (inhomogeneous) or (D+1)xN (homogeneous) coordinates
%
% Input:
%  X - DxN (inhomogeneous) or (D+1)xN (homogeneous) coordinates
%  H - (D+1)x(D+1) transform matrix (2D and 3D in ref. [1])
%
% References:
%
%  [1] Hartley, R., Zisserman, A., Multiple View Geometry in
%  Computer Vision, 2nd ed, Cambridge Univ. Press, 2003.
%
% Author(s):
%    Joni Kamarainen <Joni.Kamarainen@lut.fi>
%
% Copyright:
%
%   Homography estimation toolbox is Copyright (C) 2008 by Joni-Kristian
%   Kamarainen.
%
%   $Name:  $ $Revision: 1.1 $  $Date: 2009/04/07 10:02:18 $
%
%%
function [Xn] = hnd_trans(X_, H_);

D = size(H_,1)-1;

%
% Construct homogeneous vectors if not
if (size(X_,1) == D)
  % non-homogenous (return same)
  Xn = H_*[X_; ones(1,size(X_,2))];
  Xn = Xn(1:D,:)./repmat(Xn(D+1,:),[D 1]);
else
  % homogenous (return same)
  Xn = H_*X_;
end;
