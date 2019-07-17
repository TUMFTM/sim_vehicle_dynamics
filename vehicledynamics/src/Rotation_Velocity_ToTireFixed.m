function Y = Rotation_Velocity_ToTireFixed(X,A_K_F,A_Rfl_F,A_Rfr_F,A_down_up)
%% Input parameters:
% A_K_F [---]    Rotation Matrix from RearAxle Fixed Coordinate System to VehicleFixed Coordinate System
% X     [---]    Original Input Vectors [x1 x2 x3 x4] [3x4]
% Output parameters:
% Y     [---]    Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%% Output of transformed vectors
% Quarter Vehicle Model along Vehicle Fixed z-Axis: Rotation from VehicleFixed Coordinate System into TireFixed Coordinate System
% Y=[(A_down_up*A_Rfl_F*transpose(A_K_F)*X(:,1)) (A_down_up*A_Rfr_F*transpose(A_K_F)*X(:,2)) (A_down_up*transpose(A_K_F)*X(:,3)) (A_down_up*transpose(A_K_F)*X(:,4))];

% Quarter Vehicle Model along Rear Axle Fixed z-Axis: Rotation from RearAxleFixed Coordinate System into TireFixed Coordinate System
Y=[(A_down_up*A_Rfl_F*X(:,1)) (A_down_up*A_Rfr_F*X(:,2)) (A_down_up*X(:,3)) (A_down_up*X(:,4))];

% Quarter Vehicle Model according MATLAB-Documentation
% Y=[(A_down_up*A_Rfl_F*X(:,1)) (A_down_up*A_Rfr_F*X(:,2)) (A_down_up*X(:,3)) (A_down_up*X(:,4))];

end

