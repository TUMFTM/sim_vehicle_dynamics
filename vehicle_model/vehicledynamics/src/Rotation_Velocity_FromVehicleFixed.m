function [Y] = Rotation_Velocity_FromVehicleFixed(X,A_K_F)
%% Input parameters:
% A_K_F [---]    Rotation Matrix from RearAxle Fixed Coordinate System to VehicleFixed Coordinate System
% X     [---]    Original Input Vectors [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y     [---]    Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%% Output of transformed vectors
% Quarter Vehicle Model along Vehicle Fixed z-Axis: No Rotation required
% Y=[(eye(3,3)*X(:,1)) (eye(3,3)*X(:,2)) (eye(3,3)*X(:,3)) (eye(3,3)*X(:,4))];

% Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from VehicleFixed Coordinate System into RearAxleFixed Coordinate System
Y=[(transpose(A_K_F)*X(:,1)) (transpose(A_K_F)*X(:,2)) (transpose(A_K_F)*X(:,3)) (transpose(A_K_F)*X(:,4))];

% Quarter Vehicle Model according MATLAB-Documentation
% Y=[(eye(3,3)*X(:,1)) (eye(3,3)*X(:,2)) (eye(3,3)*X(:,3)) (eye(3,3)*X(:,4))];

end

