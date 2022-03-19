function [z_I_Ground_m, h_COGxy] = TrackProfile_ndtm(relative_yaw_angle_rad, banking_rad, act_TrackProfile, info, ...
    VEH__VehicleData__l_WheelbaseF_m, VEH__VehicleData__l_WheelbaseTotal_m, ...
    VEH__VehicleData__w_TrackF_m, VEH__VehicleData__w_TrackR_m)
%__________________________________________________________________________
%% Documentation       
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   03.10.2020
% 
% Description: 
% In reference to the current track position, yaw angle and banking angle
% this function calculates the displacement on every contact patch.
% 
% Inputs: 
%   rel_yaw_angle_rad
%   banking_rad
%   info
%   ndtm vehicle data


%% init
rel_psi_rad = relative_yaw_angle_rad;
eps_rad     = banking_rad;
sgn         = info(1);           %1 if position is right of ref line,
                                 %-1 if left
offset      = info(2);           %current offset from ref line
w_l_m       = info(3);           %racetrack width left from ref line
w_r_m       = info(4);           %racetrack width right from ref line
l_f         = VEH__VehicleData__l_WheelbaseF_m;
l_r         = VEH__VehicleData__l_WheelbaseTotal_m - VEH__VehicleData__l_WheelbaseF_m;


%% get the track profile 
% get the current height of the COG-coordinate due to the banking angle
if sign(eps_rad) < 0
   h_COGxy = max((w_l_m + sgn*offset) * tan(abs(eps_rad)),0);
elseif sign(eps_rad) > 0
   h_COGxy = max((w_r_m - sgn*offset) * tan(abs(eps_rad)),0);
else 
   h_COGxy = 0;
end

% get the contact patch locations in reference to the COG xy-coordinate as
% origin
FL_K_m = [l_f; VEH__VehicleData__w_TrackF_m/2; h_COGxy];
FR_K_m = [l_f; -VEH__VehicleData__w_TrackF_m/2; h_COGxy];
RL_K_m = [-l_r; VEH__VehicleData__w_TrackR_m/2; h_COGxy];
RR_K_m = [-l_r; -VEH__VehicleData__w_TrackR_m/2; h_COGxy];

% get the rotation-matrices 
R_x = [1,0,0;0,cos(eps_rad),-sin(eps_rad);0,sin(eps_rad),cos(eps_rad)];
R_z = [cos(rel_psi_rad),-sin(rel_psi_rad),0;...
      sin(rel_psi_rad),cos(rel_psi_rad),0;0,0,1];

% transform the contact patch locations regarding the rotations that result
% from the banking angle and the relative yaw angle offset
FL_K_new_m = R_x * R_z * FL_K_m;
FR_K_new_m = R_x * R_z * FR_K_m;
RL_K_new_m = R_x * R_z * RL_K_m;
RR_K_new_m = R_x * R_z * RR_K_m;

% get the track profile for each contact patch
h_FL = max(FL_K_new_m(3),0);
h_FR = max(FR_K_new_m(3),0);
h_RL = max(RL_K_new_m(3),0);
h_RR = max(RR_K_new_m(3),0);

% return z_I_Ground_m
if act_TrackProfile ~= 0
    z_I_Ground_m = [h_FL, h_FR, h_RL, h_RR];
else
    z_I_Ground_m = [0, 0, 0, 0];
end


