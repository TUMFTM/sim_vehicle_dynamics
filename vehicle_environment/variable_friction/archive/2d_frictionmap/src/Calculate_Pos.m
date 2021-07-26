function [y_indices, x_indices] = Calculate_Pos(Pos_Wheel_m, Gridmap_Ident)
%Calculate_Pos: Returns rows and columns from given input coordinates
%Definition Pos_Wheel_m
%--------------------------
%VL VR HL HR
%x  x  x  x
%y  y  y  y

% get coordinates information
x_min       = Gridmap_Ident(1,1);
x_max       = Gridmap_Ident(1,2);
y_min       = Gridmap_Ident(2,1);
y_max       = Gridmap_Ident(2,2);
pixel_x     = Gridmap_Ident(3,2);
pixel_y     = Gridmap_Ident(3,1);

%Calculate row, column, row interpolation step & column interpolation step
y_indices   = ((y_max - Pos_Wheel_m(2,:))/(y_max - y_min))*pixel_y;
x_indices   = ((Pos_Wheel_m(1,:) - x_min)/(x_max - x_min))*pixel_x;
    
y_indices(y_indices<1)=1;
y_indices(y_indices>pixel_y)=pixel_y;
x_indices(x_indices<1)=1;
x_indices(x_indices>pixel_x)=pixel_x;
y_indices=y_indices.';
x_indices=x_indices.';
    
end
