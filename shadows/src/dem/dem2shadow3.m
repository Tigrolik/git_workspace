function f = dem2shadow3(I, res, sun_ang)

if numel(res) < 2
    x_res = res; y_res = res;
else
    x_res = res(1); y_res = res(2);
end

scale = 1;
% value defining when there is no data below this value
no_data_low_val = -32000;
% value defining when there is no data above this value
no_data_hi_val = 65000;

% degrees = > radians
deg2radcoeff = pi / 180;
azi_deg = sun_ang(1);
zen_deg = sun_ang(2);
azi_rad = azi_deg * deg2radcoeff;
zen_rad = zen_deg * deg2radcoeff;

I = double(I);
sizex = size(I,2);
sizey = size(I,1);
% initialisation parameters
f = I;
dx = 0;
dy = 0;
dz = 0;
ds = 0;
temp = zeros(sizey,sizex);
index = 1;
% main loop
while ((max(max(I)) >= dz) && (dx <= sizex) && (dy <= sizey))
    if ((pi/4 <= azi_rad) && (azi_rad < 3*pi/4)) || ((5*pi/4 <= azi_rad)...
            &&(azi_rad<7*pi/4))
        dy = sign(sin(azi_rad)) * index;
        dx = -1 * sign(cos(azi_rad)) * abs(round(index/(tan(azi_rad))));
        ds = abs(1/sin(azi_rad));
    else
        dy = sign(sin(azi_rad)) * abs(round(index*tan(azi_rad)));
        dx = -1*sign(cos(azi_rad))*index;
        ds = abs(1/cos(azi_rad));
    end
    % note: dx and dy represent absolute values while ds is an incremental
    % value
    dz = ds*index*tan(zen_rad)/scale;
    temp(1:sizex,1:sizey) = 0;
    xc1 = ((dx+abs(dx))/2)+1;
    xc2 = (sizex+(dx-abs(dx))/2);
    yc1 = ((dy+abs(dy))/2)+1;
    yc2 = (sizey+(dy-abs(dy))/2);
    xp1 = -((dx-abs(dx))/2)+1;
    xp2 = (sizex-(dx+abs(dx))/2);
    yp1 = -((dy-abs(dy))/2)+1;
    yp2 = (sizey-(dy+abs(dy))/2);
    temp(xp1:xp2,yp1:yp2) = I(xc1:xc2,yc1:yc2)-dz;
    f = max(f,temp);
    index = index+1;
end
f = f-I;
f = not(not(f));
f = double(f);