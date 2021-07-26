function chi = RoadInclination_Arkustangens(z_I_Ground_m,rx_I_IAji_m,ry_I_IAji_m,phiz_IK_rad)
%% Computation of Road Angles from Street Profile in Inertial Frame
% Input parameters:
% phiz_IK_rad     [rad]    Euler-Angle around z-Axis from Inertial Reference Frame I to Vehicle Fixed Reference Frame K
% rx_I_IAji_m     [m]      Track x-Position [x1 x2 x3 x4] [1x4]
% ry_I_IAji_m     [m]      Track y-Position [y1 y2 y3 y4] [1x4]
% z_I_Ground_m    [m]      Input Vector with z-Profile of Street in Inertial Coordinate System at the Axle Locations [z1 z2 z3 z4] [3x4]
% Output parameters:
% chi_rad         [rad]    Approximated Cardan Angles from Inertial Reference Frame to Road Fixed Reference Frame [chi_x chi_y Psi] [3x1]


%% Computation of Road Angles

% Distances [dxl dxr dyf dyr] between suspension hardpoints
dxl=sqrt( (rx_I_IAji_m(1)-rx_I_IAji_m(3)).^2 + (ry_I_IAji_m(1)-ry_I_IAji_m(3)).^2 );
dxr=sqrt( (rx_I_IAji_m(2)-rx_I_IAji_m(4)).^2 + (ry_I_IAji_m(2)-ry_I_IAji_m(4)).^2 );
dyf=sqrt( (rx_I_IAji_m(1)-rx_I_IAji_m(2)).^2 + (ry_I_IAji_m(1)-ry_I_IAji_m(2)).^2 );
dyr=sqrt( (rx_I_IAji_m(3)-rx_I_IAji_m(4)).^2 + (ry_I_IAji_m(3)-ry_I_IAji_m(4)).^2 );

% Inclination Angle in x-direction for negative z-road-profile
chi_y = -atan( 0.5*((z_I_Ground_m(1)+z_I_Ground_m(2))-(z_I_Ground_m(3)+z_I_Ground_m(4)))/(0.5*(dxl+dxr)) );
% Inclination Angle in y-direction for negative z-road-profile
chi_x = -atan( 0.5*((z_I_Ground_m(1)+z_I_Ground_m(3))-(z_I_Ground_m(2)+z_I_Ground_m(4)))/(0.5*(dyf+dyr)) );

%% Output Parameters
chi = [chi_x;chi_y;phiz_IK_rad];

end
