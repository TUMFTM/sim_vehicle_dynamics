function [Y] = Rotation_ForceMoment_FromTireFixed(X,A_K_F,A_Rfl_F,A_Rfr_F,A_down_up)
%% Input parameters:
% A_K_F     [---]   Rotation Matrix from RearAxle Fixed Coordinate System to VehicleFixed Coordinate System
% A_Rfl_F   [---]   Rotation Matrix from RearAxle Fixed Coordinate System to WheelFixed Coordinate System FrontLeft
% A_Rfr_F   [---]   Rotation Matrix from RearAxle Fixed Coordinate System to WheelFixed Coordinate System FrontRight
% A_down_up [...]   Orientation Change Matrix between z-up Orientation and z-down Orientation
% X         [---]   Original Input Vectors [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y         [---]   Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%% Output of transformed vectors
% Quarter Vehicle Model along Vehicle Fixed z-Axis: Rotation from TireFixed Coordinate System into VehicleFixed Coordinate System
% Y=[(A_K_F*transpose(A_Rfl_F)*A_down_up*X(:,1)) (A_K_F*transpose(A_Rfr_F)*A_down_up*X(:,2)) (A_K_F*A_down_up*X(:,3)) (A_K_F*A_down_up*X(:,4))];

% Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from TireFixed Coordinate System into RearAxleFixed Coordinate System
Y=[(transpose(A_Rfl_F)*A_down_up*X(:,1)) (transpose(A_Rfr_F)*A_down_up*X(:,2)) (A_down_up*X(:,3)) (A_down_up*X(:,4))];

% Quarter Vehicle Model according MATLAB-Documentation
% Y=[(transpose(A_Rfl_F)*A_down_up*X(:,1)) (transpose(A_Rfr_F)*A_down_up*X(:,2)) (A_down_up*X(:,3)) (A_down_up*X(:,4))];

end

