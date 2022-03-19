function [Y] = Rotation_AngVelocity_ToTireFixed(X,A_K_F,A_down_up)
%% Input parameters:
% A_K_F [---]    Rotation Matrix from RearAxle Fixed Coordinate System to VehicleFixed Coordinate System
% X     [---]    Original Input Vectors [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y     [---]    Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%% Output of transformed vectors
% Quarter Vehicle Model along Vehicle Fixed z-Axis: Rotation from VehicleFixed Coordinate System into TireFixed Coordinate System
% Y=[(A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X)];

% Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from RearAxleFixed Coordinate System into TireFixed Coordinate System
Y=[(A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X) (A_down_up*transpose(A_K_F)*X)];

% Quarter Vehicle Model according MATLAB-Documentation
% Y=[(A_down_up*eye(3,3)*X) (A_down_up*eye(3,3)*X) (A_down_up*eye(3,3)*X) (A_down_up*eye(3,3)*X)];

% Simplified Transformation without Steering Angle Ratios, Camber and Change in Road Inclination Angles
% Rotation Matrix A_Rfl_F and A_Rfr_F are irrelevant for Yaw Rate Computation

end

