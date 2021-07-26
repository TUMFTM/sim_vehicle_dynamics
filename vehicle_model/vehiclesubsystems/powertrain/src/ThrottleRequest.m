function [T_engine_Nm, p_throttle_pos] = ThrottleRequest(T_request_Nm, T_max_Nm, T_min_Nm)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function calculates the amount of a combustion engine´s 
% output-torque and throttle position in reference to a requested output 
% torque, its engine-map and the available min and max torque at a given 
% rpm figure.
% 
% Inputs: 
%   T_request_Nm    - requested output torque [Nm] 
%   T_max_Nm        - max available output torque [Nm]
%   T_min_Nm        - min available output torque [Nm]
%   
% Outputs:
%   T_engine_Nm     - engine output Torque [Nm]
%   p_throttle_pos  - required throttle position [-]


%% engine output torque 
T_engine_Nm     = max(T_min_Nm, min(T_max_Nm, T_request_Nm));


%% throttle position
T_range_Nm      = T_max_Nm - T_min_Nm;
T_p_Nm          = T_request_Nm - T_min_Nm;
throttle_pos    = T_p_Nm / T_range_Nm;
p_throttle_pos  = max(0, min(throttle_pos, 1));