function [A_K_I,A_K_F,A_F_I,A_Rfl_F,A_Rfr_F,A_down_up] = Rotation_Matrices(phi,chi,delta)
%% Rotation from rear axle fixed coordinate system into vehicle fixed coordinate system
% Input parameters:
% phi       [rad]    Vehicle Rotation Angles [Phi Theta Psi] [3x1]
% chi       [rad]    Road Cardan Angles [chi_x chi_y Psi] [3x1]
% delta     [rad]    Steering Angles [deltaFL deltaFR 0 0] [1x4]
% Output parameters:
% A_K_I     [---]    Transformation Matrix A_K_I [3x3]
% A_K_F     [---]    Transformation Matrix A_K_F [3x3]
% A_F_I     [---]    Transformation Matrix A_F_I [3x3]
% A_Rfl_F   [---]    Transformation Matrix A_Rfl_F [3x3]
% A_Rfr_F   [---]    Transformation Matrix A_Rfr_F [3x3]
% A_down_up [---]    Transformation Matrix W := A_down_up [3x3]

%% Pre-Computation of trigonometric values
cphi=cos(phi);
sphi=sin(phi);
cchi=cos(chi);
schi=sin(chi);

%% Definition of rotation matrices

% rotation matrix from z-up coordinate system to z-down coordinate system
A_down_up = reshape([1 0 0,0 -1 0,0 0 -1],[3,3]);

% rotation matrix from inertial coordinate system to vehicle fixed coordinate system
A_K_I     = reshape([cphi(3)*cphi(2),-cphi(1)*sphi(3)+cphi(3)*sphi(2)*sphi(1),sphi(3)*sphi(1)+cphi(3)*cphi(1)*sphi(2),cphi(2)*sphi(3),cphi(3)*cphi(1)+sphi(3)*sphi(2)*sphi(1),-cphi(3)*sphi(1)+cphi(1)*sphi(3)*sphi(2),-sphi(2),cphi(2)*sphi(1),cphi(2)*cphi(1)],[3,3]);

% rotation matrix from rear axle fixed coordinate system to vehicle fixed coordinate system without road inclination
% A_K_F     = reshape([cphi(2),sphi(2)*sphi(1),cphi(1)*sphi(2),0,cphi(1),-sphi(1),-sphi(2),cphi(2)*sphi(1),cphi(2)*cphi(1)],[3,3]);

% rotation matrix from rear axle fixed coordinate system to vehicle fixed coordinate system over inertial coordinate system with road inclination
A_K_F     = reshape([cos(phi(2)-chi(2)),sin(phi(2)-chi(2))*sphi(1),sin(phi(2)-chi(2))*cphi(1),-sin(-chi(2)+phi(2))*schi(1),cchi(1)*cphi(1)+cphi(2)*cchi(2)*schi(1)*sphi(1)+sphi(2)*schi(1)*schi(2)*sphi(1),-cchi(1)*sphi(1)+cphi(2)*cchi(2)*cphi(1)*schi(1)+cphi(1)*sphi(2)*schi(1)*schi(2),-sin(-chi(2)+phi(2))*cchi(1),-cphi(1)*schi(1)+cphi(2)*cchi(1)*cchi(2)*sphi(1)+cchi(1)*sphi(2)*schi(2)*sphi(1),schi(1)*sphi(1)+cphi(2)*cchi(1)*cchi(2)*cphi(1)+cchi(1)*cphi(1)*sphi(2)*schi(2)],[3,3]);

% rotation matrix from inertial coordinate system to rear axle fixed coordinate system
A_F_I     = reshape([cphi(3)*cchi(2),-cchi(1)*sphi(3)+cphi(3)*schi(1)*schi(2),sphi(3)*schi(1)+cphi(3)*cchi(1)*schi(2),cchi(2)*sphi(3),cphi(3)*cchi(1)+sphi(3)*schi(1)*schi(2),-cphi(3)*schi(1)+cchi(1)*sphi(3)*schi(2),-schi(2),cchi(2)*schi(1),cchi(1)*cchi(2)],[3,3]);

% rotation matrix from rear axle fixed coordinate system to wheel fixed coordinate systems of front axle
A_Rfl_F   = reshape([cos(delta(1)),-sin(delta(1)),0,sin(delta(1)),cos(delta(1)),0,0,0,1],[3,3]);
A_Rfr_F   = reshape([cos(delta(2)),-sin(delta(2)),0,sin(delta(2)),cos(delta(2)),0,0,0,1],[3,3]);

end

