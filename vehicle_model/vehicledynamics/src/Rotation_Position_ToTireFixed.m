function [z_Tji_Ground_m,r_I_IRji_m,r_I_ITji_m] = Rotation_Position_ToTireFixed(z_I_Ground_m,A_K_I,A_F_I,r_I_IAji_m,h_ji_m,re_ji_m)
%% Rotation ground displacement from inertial fixed coordinate system into tire fixed coordinate systems
% Input parameters:
% A_K_I          [---]    Rotation Matrix from Inertial Frame to VehicleFixed Frame
% A_F_I          [---]    Rotation Matrix from Inertial Frame to RearAxleFixed Frame
% h_ji_m         [m]      Suspension Height [SuspHFL SuspHFR SuspHRL SuspHRR]
% re_ji_m        [m]      Effective Wheel Radii [ReFL ReFR ReRL ReRR]
% r_I_IAji       [m]      Absolut Position of Axles in Inertial Reference Frame [r_I_IAFL r_I_IAFR r_I_IARL r_I_IARR] [3x4]
% z_Ground_I_m   [---]    z-Coordinate of Road Displacement in Inertial Reference Frame [1x4]
% Output parameters:
% z_Ground_Tji_m [---]    Transformed Displacement Vector [r_TFL_ITFL r_TFR_ITFR r_TRL_ITRL r_TRR_ITRR] [1x4]

%% Wheel center points in inertial reference frame

% Quarter Vehicle Model along VehicleFixed z-Axis: Rotation from VehicleFixed Axis System into Inertial Frame
% r_I_IRji_m = [(r_I_IAji_m(:,1) + transpose(A_K_I)*[0;0;1]*(h_ji_m(1))) (r_I_IAji_m(:,2) + transpose(A_K_I)*[0;0;1]*(h_ji_m(2))) (r_I_IAji_m(:,3) + transpose(A_K_I)*[0;0;1]*(h_ji_m(3))) (r_I_IAji_m(:,4) + transpose(A_K_I)*[0;0;1]*(h_ji_m(4)))];

% Quarter Vehicle Model along RearAxleFixed z-Axis: Rotation from RearAxleFixed Axis System into Inertial Frame
r_I_IRji_m = [(r_I_IAji_m(:,1) + transpose(A_F_I)*[0;0;1]*(h_ji_m(1))) (r_I_IAji_m(:,2) + transpose(A_F_I)*[0;0;1]*(h_ji_m(2))) (r_I_IAji_m(:,3) + transpose(A_F_I)*[0;0;1]*(h_ji_m(3))) (r_I_IAji_m(:,4) + transpose(A_F_I)*[0;0;1]*(h_ji_m(4)))];

%% Contact points of road-tire-interface in inertial reference frame

% Quarter Vehicle Model along VehicleFixed z-Axis: Rotation from VehicleFixed Axis System into Inertial Frame
% r_I_ITji_m = [(r_I_IAji_m(:,1) + transpose(A_K_I)*[0;0;1]*(re_ji_m(1)+h_ji_m(1))) (r_I_IAji_m(:,2) + transpose(A_K_I)*[0;0;1]*(re_ji_m(2)+h_ji_m(2))) (r_I_IAji_m(:,3) + transpose(A_K_I)*[0;0;1]*(re_ji_m(3)+h_ji_m(3))) (r_I_IAji_m(:,4) + transpose(A_K_I)*[0;0;1]*(re_ji_m(4)+h_ji_m(4)))];

% Quarter Vehicle Model along RearAxleFixed z-Axis: Rotation from RearAxleFixed Axis System into Inertial Frame
r_I_ITji_m = [(r_I_IAji_m(:,1) + transpose(A_F_I)*[0;0;1]*(re_ji_m(1)+h_ji_m(1))) (r_I_IAji_m(:,2) + transpose(A_F_I)*[0;0;1]*(re_ji_m(2)+h_ji_m(2))) (r_I_IAji_m(:,3) + transpose(A_F_I)*[0;0;1]*(re_ji_m(3)+h_ji_m(3))) (r_I_IAji_m(:,4) + transpose(A_F_I)*[0;0;1]*(re_ji_m(4)+h_ji_m(4)))];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %% Elaborate Computation of Vertical Displacement 
% % The computation of the position vector of the road-tire interface
% % requires information about the rx_I_ITji_m and ry_I_ITji_m coordinates of the
% % road-tire-interface relative to the inertial frame and the vertical
% % displacement z_Ground_I_m.
% 
% %% Position Vector of Road-Tire-Interface around Orientation of the Quarter Vehicle Model
% 
% % Extracting (x,y)-Coordinates of r_I_ITji_m
% % rx_I_ITji_m = r_I_ITji_m(1,:);
% % ry_I_ITji_m = r_I_ITji_m(2,:);
% % 
% % Quarter Vehicle Model along VehicleFixed z-Axis: Rotation from Inertial Frame into VehicleFixed Axis System
% r_Ground_m = A_K_I*vertcat(rx_I_ITji_m,ry_I_ITji_m,+z_Ground_I_m);
% 
% % Quarter Vehicle Model along RearAxleFixed z-Axis: Rotation from Inertial Frame into RearAxleFixed Axis System
% r_Ground_m = A_F_I*vertcat(rx_I_ITji_m,ry_I_ITji_m,+z_Ground_I_m);
% 
% %% Orientation Change from z-down-Orientation to z-up-Orientation
% z_Ground_Tji_m = -r_Ground_m(3,:);
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Robust Computation of Vertical Displacement 
% A more robust computation of the Vertical Displacement is possible with
% the simplified z-displacement vector [0;0;1]*z_Ground_I_m under
% neglection of the rx_I_ITji_m and ry_I_ITji_m coordinates of the
% road-tire-interface relative to the inertial frame.

%% Vertical z-Displacement of Road-Tire-Interface around Orientation of the Quarter Vehicle Model

% Quarter Vehicle Model along VehicleFixed z-Axis: Rotation from Inertial Frame into VehicleFixed Axis System
% r_Ground_m = A_K_I*[0;0;1]*z_Ground_I_m;

% Quarter Vehicle Model along RearAxleFixed z-Axis: Rotation from Inertial Frame into RearAxleFixed Axis System
r_Ground_m = A_F_I*[0;0;1]*z_I_Ground_m;

%% Orientation Change from z-down-Orientation to z-up-Orientation
z_Tji_Ground_m = -r_Ground_m(3,:);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
end

