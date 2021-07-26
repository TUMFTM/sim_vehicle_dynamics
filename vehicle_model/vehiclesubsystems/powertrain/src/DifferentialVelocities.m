function w_differential_radps = DifferentialVelocities(...
 i_c, i_f, i_r, p_torque_rear, w_FL_radps, w_FR_radps, w_RL_radps, w_RR_radps)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function processes the tire´s angular velocities and outputs the 
% angular velocity that is fed to the transmission.
% 
% Inputs: 
%   i_c             - central differential ratio [-]
%   i_f             - front differential ratio [-]
%   i_r             - rear differential ratio [-]
%   p_torque_rear   - torque distribution to the rear (FWD 0, RWD 1) [-]
%   w_FL_radps      - FL angular velocity [radps]
%   w_FR_radps      - FR angular velocity [radps]
%   w_RL_radps      - RL angular velocity [radps]
%   w_RR_radps      - RR angular velocity [radps]
%   
% Outputs:
%   w_differential_radps [radps]


%% calculate angular velocity
w_differential_radps = i_c * ...
                (((1-p_torque_rear)*i_f*((w_FL_radps+w_FR_radps)/2)) + ...
               (p_torque_rear*i_r*((w_RL_radps+w_RR_radps)/2)));
