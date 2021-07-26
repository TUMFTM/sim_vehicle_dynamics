function bankingForces_N = BankingInfluence(relative_yaw_angle_rad, ...
    banking_rad, ay_mps2, act_TrackProfile, VEH__VehicleData__m_Vehicle_kg)
%__________________________________________________________________________
%% Documentation ndtm
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   15.09.2020
% 
% Description: 
% In reference to a banking angle this function calculates all 
% external forces acting on a vehicle in its coordinate system.
% It then subtracts them from the forces which would occur on an
% unbanked track. The force-deltas will then be applied as external forces
% 
% Inputs: 
%   relative_yaw_angle_rad 
%   ay_mps2
%   banking_angle_rad
%   VEHICLE (Vehicle Parameters)
%   act_TrackProfile
% 
% Outputs:
%   external forces [1 x 3]


% calculate banking angles in vehicle coordinates
eps_K_x = banking_rad * cos(relative_yaw_angle_rad);
eps_K_y = banking_rad * -sin(relative_yaw_angle_rad);

% calculate delta-forces in vehicle coordinates resulting 
% from lat/long accelerations on banked track
dFy_acc = -(ay_mps2*VEH__VehicleData__m_Vehicle_kg) * (1-cos(eps_K_x));
dFz_acc = (ay_mps2*VEH__VehicleData__m_Vehicle_kg) * -sin(banking_rad);

% calculate delta-forces in vehicle coordinates resulting from 
% weight on banked track
dFx_w = VEH__VehicleData__m_Vehicle_kg * 9.81 * sin(eps_K_y);
dFy_w = VEH__VehicleData__m_Vehicle_kg * 9.81 * sin(-eps_K_x);
dFz_w = -VEH__VehicleData__m_Vehicle_kg * 9.81 * (1-cos(banking_rad));

% transform Forces back to 2D track 
if act_TrackProfile ~= 0
   dFx_banked = dFx_w;
   dFy_banked = dFy_acc + dFy_w;
   dFz_banked = dFz_acc + dFz_w;     
else   
   dFx_banked = dFx_w * cos(abs(eps_K_y));
   dFy_banked = (dFy_acc + dFy_w) * cos(abs(eps_K_x));
   dFz_banked = (dFz_acc + dFz_w) * cos(abs(banking_rad));
end

bankingForces_N = [dFx_banked; dFy_banked; dFz_banked];

