function chi = RoadInclination_Arkussinus(z_I_Ground_m,l_WheelbaseFB_m,w_TrackFB_m,phiz_IK_rad)
%% Computation of Road Angles from Street Profile in Inertial Frame
% Input parameters:
% phiz_IK_rad     [rad]    Euler-Angle around z-Axis from Inertial Reference Frame I to Vehicle Fixed Reference Frame K [Psi]
% w_TrackFB_m     [m]      Track width at Front and Rear Axle [w_TrackF_m w_TrackR_m]
% l_WheelbaseFB_m [m]      Wheelbase from Cog to Front and Rear Axle [l_WheelbaseF_m l_WheelbaseR_m]
% z_I_Ground_m    [m]      Input Vector with z-Profile of Street in Inertial Coordinate System at the Axle Locations [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y               [rad]    Approximated Cardan Angles from Inertial Reference Frame to Road Fixed Reference Frame [chi_x chi_y Psi] [3x1]

%% Computation of Road Angles
% Inclination Angle in x-direction for negative z-road-profile
chi_y = -asin( 0.5*((z_I_Ground_m(1)+z_I_Ground_m(2))-(z_I_Ground_m(3)+z_I_Ground_m(4)))/sum(abs(l_WheelbaseFB_m)) );
% Inclination Angle in y-direction for negative z-road-profile
chi_x = -asin( 0.5*((z_I_Ground_m(1)+z_I_Ground_m(3))-(z_I_Ground_m(2)+z_I_Ground_m(4)))/mean(abs(w_TrackFB_m)) );

%% Output Parameters
chi = [chi_x;chi_y;phiz_IK_rad];

