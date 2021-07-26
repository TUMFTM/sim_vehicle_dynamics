function [gear, shift_request] = AutomaticGearbox(drive_request, gear_in, ...
                            w_engine_radps, n_ub_rpm, i_gearset, shift_delay_s)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function serves as a gear shift logic. It upshifts if the engine rpm
% is above the rpm limit and downshifts if the engine rpm is below the rpm
% limit of the current gear.
%
% Inputs: 
%   gear_in             - currently selected gear
%   drive_request       - drive request [-]
%   w_engine_radps      - engine angular velocity [radps]
%   n_ub_rpm            - engine upper rpm limit [rpm]
%   i_gearset           - available gearset 
%   shift_delay_s       - time since last gear shift [s]
%   
% Outputs:
%   gear                - output gear
%   shift_request       - shift request [bool]

%% gear shift logic
% init rpm limits
radps_lb = i_gearset(3, gear_in+1) * ((2*pi)/60);
radps_ub = n_ub_rpm * ((2*pi)/60);

% prevent gear jumping
if shift_delay_s >= 0.05
    % upshift
    if w_engine_radps>=radps_ub && drive_request>0 && i_gearset(1, gear_in+1)<i_gearset(1, end)
       gear = gear_in + 1;
       shift_request = 1;
    % downshift
    elseif w_engine_radps<=radps_lb && drive_request<=0 && i_gearset(1, gear_in+1)>0
       gear = gear_in - 1;
       shift_request = 1;
    % stay in gear
    else
       gear = gear_in;
       shift_request = 0;
    end
else
    gear = gear_in;
    shift_request = 0;
end

