function [r_I_IS1_m,r_I_IS2_m,r_I_IS3_m,A_S1_I,A_S2_I,A_S3_I] = Transformation_Sensor(r_I_IK_m,A_K_I,r_K_KS1_m,r_K_KS2_m,r_K_KS3_m,phi0_K_KS1_rad,phi0_K_KS2_rad,phi0_K_KS3_rad)
%% Computation Sensor Position and Orientation
% Input parameters:
% phi   [rad]    Vehicle Rotation Angles [Phi Theta Psi]
% chi   [rad]    Road Cardan Angles [chi_x chi_y Psi]
% delta [rad]    Steering Angles [deltaFL deltaFR deltaRL deltaRR]
% X     [---]    Original Input Vectors in Vehicle Fixed Coordinate System [x1 x2x3 x4] [3x4]
% Output parameters:
% Y     [---]    Transformed Output Vectors [y1 y2 y3 y4] [3x4]

%% Definition of rotation matrices

% General Rotation Matrix between Coordinate Systems
A =@(phi) reshape([cos(phi(3))*cos(phi(2)),-cos(phi(1))*sin(phi(3))+cos(phi(3))*sin(phi(2))*sin(phi(1)),sin(phi(3))*sin(phi(1))+cos(phi(3))*cos(phi(1))*sin(phi(2)),cos(phi(2))*sin(phi(3)),cos(phi(3))*cos(phi(1))+sin(phi(3))*sin(phi(2))*sin(phi(1)),-cos(phi(3))*sin(phi(1))+cos(phi(1))*sin(phi(3))*sin(phi(2)),-sin(phi(2)),cos(phi(2))*sin(phi(1)),cos(phi(2))*cos(phi(1))],[3,3]);

% Rotation from Vehicle Fixed Reference Frame into Sensor Fixed Reference Frame of Sensor 1 (Kardan-Rotation)
A_S1_K = A(phi0_K_KS1_rad);
% Rotation from Vehicle Fixed Reference Frame into Sensor Fixed Reference Frame of Sensor 2 (Kardan-Rotation)
A_S2_K = A(phi0_K_KS2_rad);
% Rotation from Vehicle Fixed Reference Frame into Sensor Fixed Reference Frame of Sensor 3 (Kardan-Rotation)
A_S3_K = A(phi0_K_KS3_rad);

%% Output of transformed sensors

% Absolute Position of Sensors in Inertial Reference Frame
r_I_IS1_m = r_I_IK_m + transpose(A_K_I)*r_K_KS1_m;
r_I_IS2_m = r_I_IK_m + transpose(A_K_I)*r_K_KS2_m;
r_I_IS3_m = r_I_IK_m + transpose(A_K_I)*r_K_KS3_m;

% Absolute Orientation of Sensors in Inertial Reference Frame
A_S1_I = A_S1_K*A_K_I;
A_S2_I = A_S2_K*A_K_I;
A_S3_I = A_S3_K*A_K_I;

end
