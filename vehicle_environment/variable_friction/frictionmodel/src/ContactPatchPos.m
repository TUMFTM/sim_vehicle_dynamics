function [r_I_Tires_m] = ContactPatchPos(States, ...
    VEH__VehicleData__l_WheelbaseF_m, VEH__VehicleData__l_WheelbaseTotal_m, ...
    VEH__VehicleData__w_TrackF_m, VEH__VehicleData__w_TrackR_m)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   08.10.2020
% 
% Description: 
% This function calculates the xy-coordinates of every tire´s contact patch
% acording to the vehicle´s current xy-position and yaw angle.
% 
% Inputs: 
%   x_m 
%   y_m 
%   psi_rad 
%   Vehicle parameters (trackwidth & wheelbase)

% init
x_m     = States(1);
y_m     = States(2);
psi_rad = States(3);

% get the vehicle parameters according to the current model 
l_f_m       = VEH__VehicleData__l_WheelbaseF_m;
l_r_m       = VEH__VehicleData__l_WheelbaseTotal_m - VEH__VehicleData__l_WheelbaseF_m;
track_f_m   = VEH__VehicleData__w_TrackF_m;
track_r_m   = VEH__VehicleData__w_TrackR_m;

% calculate the rotation matrix acording to a rotation around the initial
% z-axis 
% Def: psi_rad is defined as the angle between the vehicle´s x-axis and the
% global y-axis
A_IK        = [cos(psi_rad+pi/2),-sin(psi_rad+pi/2),0;...
               sin(psi_rad+pi/2),cos(psi_rad+pi/2),0;
               0,0,1];
   
% calculate the contact patch locations in the vehicle coordinate system
r_K_FL_m    = [l_f_m; track_f_m/2; 0];
r_K_FR_m    = [l_f_m; -track_f_m/2; 0];
r_K_RL_m    = [-l_r_m; track_r_m/2; 0];
r_K_RR_m    = [-l_r_m; -track_r_m/2; 0];

% calculate the contact patch locations in the initial coordinate system
r_I_FL_m    = [x_m; y_m; 0] + (A_IK * r_K_FL_m);
r_I_FR_m    = [x_m; y_m; 0] + (A_IK * r_K_FR_m);
r_I_RL_m    = [x_m; y_m; 0] + (A_IK * r_K_RL_m);
r_I_RR_m    = [x_m; y_m; 0] + (A_IK * r_K_RR_m);

% return the contact patch locations

r_I_Tires_m = [r_I_FL_m, r_I_FR_m, r_I_RL_m, r_I_RR_m];







