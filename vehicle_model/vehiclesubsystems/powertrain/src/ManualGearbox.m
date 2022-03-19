function [gear, shift_request] = ManualGearbox(gear_in, ...
                    gear_desired, w_engine_radps, i_gearset, shift_delay_s)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function serves as a saftey system. It allows downshifts if the 
% engine rpm is below the rpm downshift-limit of the currently selected gear.
%
% Inputs: 
%   gear_in             - currently selected gear
%   gear_desired        - desired gear
%   w_engine_radps      - engine angular velocity [radps]
%   i_gearset           - available gearset 
%   shift_delay_s       - time since last gear shift [s]
%   
% Outputs:
%   gear                - output gear
%   shift_request       - shift request [bool]

%% gear shift logic
% init rpm limits
radps_lb = i_gearset(3, gear_in) * ((2*pi)/60);

% prevent gear jumping
if shift_delay_s >= 0.05
    % upshift
    if i_gearset(1, gear_in)<i_gearset(1, end) && gear_desired>gear_in
       gear = gear_in + 1;
       shift_request = 1;
    % downshift
    elseif w_engine_radps<=radps_lb && i_gearset(1, gear_in)>1 && gear_desired<gear_in
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

