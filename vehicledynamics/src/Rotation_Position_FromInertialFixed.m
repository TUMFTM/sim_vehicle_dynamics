function Y = Rotation_Position_FromInertialFixed(X,A_K_I,A_F_I)
%% Input parameters:
% A_F_I [---]    Rotation Matrix from Inertial Frame to RearAxleFixed Coordinate System
% A_K_I [---]    Rotation Matrix from Inertial Frame to VehicleFixed Coordinate System
% X     [---]    Original Input Vectors [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y     [---]    Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %% Elaborate Computation of Vertical Displacement 
% % The elaborate computation of the position vector of the hardpoint locations
% % requires information about the rx_I_IAji_m and ry_I_IAji_m coordinates of the
% % hardpoint locations relative to the inertial frame and the vertical
% % displacement rz_I_IAji_m.
% 
%% Elaborate Computation of Vertical Displacement
% % Quarter Vehicle Model along Vehicle Fixed z-Axis: Rotation from Inertial Frame into VehicleFixed Coordinate System
% Y=[(A_K_I*X(:,1)) (A_K_I*X(:,2)) (A_K_I*X(:,3)) (A_K_I*X(:,4))];
% 
% % Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from Inertial Frame into RearAxleFixed Coordinate System
% % Y=[(A_F_I*X(:,1)) (A_F_I*X(:,2)) (A_F_I*X(:,3)) (A_F_I*X(:,4))];
% 
% % Quarter Vehicle Model according MATLAB-Documentation for Road Inclination
% % Y=[(A_F_I*X(:,1)) (A_F_I*X(:,2)) (A_F_I*X(:,3)) (A_F_I*X(:,4))];
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Robust Computation of Vertical Displacement 
% A more robust computation of the Vertical Displacement is possible with
% the simplified z-displacement vector [0;0;1]*z_Ground_Aji_m under
% neglection of the rx_I_IAji_m and ry_I_IAji_m coordinates of the
% hardpoint locations relative to the inertial frame.

%% Robust Computation of Vertical Displacement
% % Quarter Vehicle Model along Vehicle Fixed z-Axis: Rotation from Inertial Frame into VehicleFixed Coordinate System
% Y=[(A_K_I*[0;0;1]*X(3,1)) (A_K_I*[0;0;1]*X(3,2)) (A_K_I*[0;0;1]*X(3,3)) (A_K_I*[0;0;1]*X(3,4))];

% Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from Inertial Frame into RearAxleFixed Coordinate System
Y=[(A_F_I*[0;0;1]*X(3,1)) (A_F_I*[0;0;1]*X(3,2)) (A_F_I*[0;0;1]*X(3,3)) (A_F_I*[0;0;1]*X(3,4))];
 
% Quarter Vehicle Model according MATLAB-Documentation for Road Inclination
% Y=[(A_F_I*[0;0;1]*X(3,1)) (A_F_I*[0;0;1]*X(3,2)) (A_F_I*[0;0;1]*X(3,3)) (A_F_I*[0;0;1]*X(3,4))];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

end

