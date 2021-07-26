function T_request_Nm = ForceRequestConverter(F_x_request_N, ...
                        tire_radius_m, i_c, i_f, i_r, i_gearset, ...
                        p_torque_rear, gear_in)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function converts the requested overall longitudinal force 
% in a torque request for the engine. The effects of gear-ratios and 
% -efficiencies as well as differentials and acceleration-losses are taken
% into account.
% 
% Inputs: 
%   F_x_request_N   - requested overall longitudinal force [N] 
%   tire_radius_m   - tire`s radius [m]
%   i_c [2x1]       - central differential ratio and efficiency [-, -]
%   i_f [2x1]       - front differential ratio and efficiency [-, -]
%   i_r [2x1]       - rear differential ratio and efficiency [-, -]
%   i_gearset [4x7] - gear information 
%   gear_in         - currently selected gear
%
% Outputs:
%   T_request_Nm    - requested engine torque [Nm]


%% request engine torque
T_Nm = F_x_request_N * tire_radius_m;

if gear_in ~= 0
    T_request_Nm = T_Nm / (i_c(1)*i_c(2) * ...
      ((1-p_torque_rear)*i_f(1)*i_f(2) + p_torque_rear*i_r(1)*i_r(2)) * ...
      i_gearset(2, gear_in+1)*i_gearset(4, gear_in+1));
else
    T_request_Nm = T_Nm / (i_c(1)*i_c(2) * ...
      ((1-p_torque_rear)*i_f(1)*i_f(2) + p_torque_rear*i_r(1)*i_r(2)) * ...
      i_gearset(2, gear_in+2)*i_gearset(4, gear_in+1));
end