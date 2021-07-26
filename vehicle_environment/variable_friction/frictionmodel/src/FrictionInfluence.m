function [lambda_mue_x, lambda_mue_y] = FrictionInfluence(States, tpa_map, interpTime, tpa_map_mode, Time)
%__________________________________________________________________________
%% Documentation       
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   22.11.2020
% 
% Description: 
% This function serves as master function to calculate variable friction
% coefficients (local scaling factors) for each tire.


%% init 
% constant friction
lambda_mue_x    = [1 1 1 1];
lambda_mue_y    = [1 1 1 1];


%% Check if variable friction is active
if tpa_map_mode ~= 0 
    
    % reshape tpamap from 1D to 2D
    tpa_map = reshape(tpa_map,[],2500).';
    % take all tpa-maps and perform a time-dependent interpolation  
    ref_tpa_map = tpa_map_interp_time(tpa_map, interpTime, Time);
    % take the processed map and perform a location-dependent interpolation
    % corresponding to the current location on the racetrack
    for i = 1:4
    [lambda_mue_x(i), lambda_mue_y(i)] = ...
                            tpa_map_interp_pos(States(1:2,i), ref_tpa_map);
    end
    
end

end