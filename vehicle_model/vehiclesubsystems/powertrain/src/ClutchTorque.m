function [delta_rpm, T_cap_Nm, T_loss_Nm, T_clutch_Nm] = ClutchTorque(...
                              T_engine_Nm, ...
                              w_engine_in_radps, w_transmission_radps, ...
                              wdot_transmission_radps2, gear, T_max_cap_Nm, ...
                              I_drivetrain_kgm2, clutch_act)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   07.01.2021
% 
% Description: 
% This function calculates the clutch torques. 
%
% Inputs: 
%   T_engine_Nm                 - input torque that the engine delivers [Nm]
%   w_engine_in_radps           - engine angular velocity [radps]
%   w_transmission_radps        - driveshaft angular velocity [radps]
%   wdot_transmission_radps2    - driveshaft angular acceleration [radps2]
%   gear                        - currently selected gear [-]
%   T_max_cap_Nm                - max manageable capacative torque [Nm]
%   I_drivetrain_kgm2           - drivetrain inertia [kgm2]
%   clutch_act                  - clutch engagement [-]
%     
% Outputs:
%   T_clutch_Nm         - output clutch torque [Nm]
%   T_cap_Nm            - capacative clutch torque [Nm]
%   T_loss_Nm           - torque loss due to mechanical accelerations [Nm]
%   delta_rpm           - difference in engine and transmission angular
%                         velocity [rpm]


%% calculate clutch output torque
% calculate delta_rpm
delta_rpm = (w_engine_in_radps-w_transmission_radps) * (60/(2*pi));

% calculate capacative torque
D = -0.01;
x = delta_rpm;
sgn = (1/(exp(D*x)+1)) + ((-1)/(exp(-D*x)+1));
if gear ~= 0
   T_cap_Nm = sgn * T_max_cap_Nm * clutch_act;
else
   T_cap_Nm = 0;
end

% output clutch torque
%T_clutch_Nm = (clutch_act * T_cap_Nm) - wdot_transmission_radps2 * I_drivetrain_kgm2;
T_clutch_Nm = T_cap_Nm - wdot_transmission_radps2 * I_drivetrain_kgm2;

% torque loss
T_loss_Nm = max(0, T_engine_Nm-T_clutch_Nm);


