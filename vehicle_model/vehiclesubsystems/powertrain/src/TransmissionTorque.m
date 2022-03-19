function T_transmission_Nm = TransmissionTorque(T_clutch_Nm, gear, i_gearset)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik St�rk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function calculates the output torque of the transmission.
% The input torque that is provided by the clutch is processed 
% corresponding to the available gearset and the current gear.
%
% Inputs: 
%   T_clutch_Nm         - input torque [Nm]
%   gear                - currently selected gear
%   i_gearset           - available gearset information
%   
% Outputs:
%   T_transmission_Nm   - output torque [Nm]


%% calculate output torque
%calculate reduction ratio
i_g = i_gearset(2, gear)*i_gearset(4, gear);

if i_g ~= 0
    T_transmission_Nm = (i_g * T_clutch_Nm); 
else 
    T_transmission_Nm = 0;
end