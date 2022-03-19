function [throttle_factor, counter_out] = manage_clutchgearshift(trigger_gearshift, counter_in, throttle_shiftbreak_s, tSPhysics)
%% Documentation       
%
% Author:       Leonhard Hermansdorfer (leo.hermansdorfer@tum.de)
% 
% Start Date:   15.09.2021
%
% Description:  this function applies throttle lifting if a gear shift happend.
%               This aims at increasing the vehicle stability during shifting. 
% 
% Inputs:
%   - trigger_gearshift         gear shift trigger (1 if shift happend, otherwise 0)
%   - counter_in                same value as counter_out from last timestep
%   - throttle_shiftbreak_s     time duration of throttle lift after gear shift
%
% Outputs:
%   - throttle_factor           multiply factor for throttle signal (either 1 or 0)
%   - counter_out               counter which is fed back into the function in the next timestep

    % detect gear shift (direction independent)
    trigger_gearshift = min(1, abs(trigger_gearshift));

    % start counter if a gear shift has happend
    if trigger_gearshift == 1
        counter_in = throttle_shiftbreak_s;
    end

    % count down to zero
    counter_out = counter_in - tSPhysics;

    % calculate throttle factor
    if counter_out > 0
        throttle_factor = 0;
    else
        throttle_factor = 1;
    end

end
