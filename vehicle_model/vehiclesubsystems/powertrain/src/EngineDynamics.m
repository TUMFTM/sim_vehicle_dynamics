function wdot_engine_radps2 = EngineDynamics(T_engine_Nm, I_engine_kgm2, ...
                              I_output_kgm2, delta_rpm, T_cap_Nm)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   07.01.2021
% 
% Description: 
% This function calculates the angular acceleration that the engine 
% experiences. 
%
% Inputs: 
%   T_engine_Nm         - input torque that the engine delivers [Nm]
%   T_cap_Nm            - capacitive torque that is provided by the clutch [Nm]
%   delta_rpm           - angular velocity difference between engine and 
%                         gear shaft [radps]
%   I_engine_kgm2       - engine inertia [kgm2]
%   I_output_kgm2       - drivetrain inertia [kgm2]
%   
% Outputs:
%   wdot_engine_radps2  - output capacitive torque [Nm]


%% calculate angular acceleration
% calculate inertia deployment
D = -2;
x = delta_rpm;
sgn = (1/(exp(D*x)+1)) + ((-1)/(exp(-D*x)+1));
I_drivetrain_kgm2 = I_output_kgm2 - (abs(sgn) * ...
                                    (I_output_kgm2-I_engine_kgm2));

% calculate engine angular acceleration
wdot_engine_radps2 = (T_engine_Nm-T_cap_Nm) / I_drivetrain_kgm2;