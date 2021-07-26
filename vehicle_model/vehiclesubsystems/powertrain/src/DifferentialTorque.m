function [T_FL_Nm, T_FR_Nm, T_RL_Nm, T_RR_Nm] = DifferentialTorque(...
                        T_transmission_Nm, i_c, i_f, i_r, p_torque_rear)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function calculates the torque-deployment for each tire in reference
% to the differentials´ reduction ratios and the input torque that is 
% provided by the transmission. This function only respects spool-type
% locked  differentials.
% 
% Inputs: 
%   i_c                 - central differential ratio [-]
%   i_f                 - front differential ratio [-]
%   i_r                 - rear differential ratio [-]
%   p_torque_rear       - torque distribution to the rear (FWD 0, RWD 1) [-]
%   T_transmission_Nm   - input torque [Nm]
%   
% Outputs:
%   T_FL_Nm             - torque provided to FL tire [Nm]
%   T_FR_Nm             - torque provided to FR tire [Nm]
%   T_RL_Nm             - torque provided to RL tire [Nm]
%   T_RR_Nm             - torque provided to RR tire [Nm]


%% calculate torque distributions
% torques at front and rear axle
T_out_f_Nm = i_f(1) * i_f(2) * (1-p_torque_rear) * ...
             i_c(1) * i_c(2) * T_transmission_Nm;
T_out_r_Nm = i_r(1) * i_r(2) * p_torque_rear * ...
             i_c(1) * i_c(2) * T_transmission_Nm;

% torques at each tire
T_FL_Nm = 0.5 * T_out_f_Nm;
T_FR_Nm = 0.5 * T_out_f_Nm;
T_RL_Nm = 0.5 * T_out_r_Nm;
T_RR_Nm = 0.5 * T_out_r_Nm;
