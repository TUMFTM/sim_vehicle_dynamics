function F_DriveForce_N = ElectricEngine(F_x_request_N, p_torque_rear)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   05.01.2020
% 
% Description: 
% This function deploys the drive force of the electric engine according 
% to the drive type to the wheels.
% 
% Inputs: 
%   F_x_request_N   - drive request [N]
%   p_torque_rear   - torque distribution to the rear (0-FWD 1-RWD)
%   
% Outputs:
%   F_DriveForce_N  - drive force [N]   


%% calculate the drive torque
F_DriveForce_N = zeros(1,4);

F_DriveForce_N(:,1) = 0.5 * (1-p_torque_rear) * F_x_request_N;
F_DriveForce_N(:,2) = 0.5 * (1-p_torque_rear) * F_x_request_N;
F_DriveForce_N(:,3) = 0.5 * p_torque_rear * F_x_request_N;
F_DriveForce_N(:,4) = 0.5 * p_torque_rear * F_x_request_N;
