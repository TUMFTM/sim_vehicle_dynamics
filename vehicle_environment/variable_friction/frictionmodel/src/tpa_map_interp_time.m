function [ref_tpamap] = tpa_map_interp_time(tpa_map, time_array, Time)
%__________________________________________________________________________
%% Documentation       
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   30.10.2020
% 
% Description: 
% This function interpolates between a custom amount of tpamaps according
% to their interpolation start time and the actual simulation time. It
% automatically checks the number of input tpamaps. The output will be a
% single tpamap, which holds the s_m, x_m, y_m columns and the interpolated
% value for the longitudinal and lateral lambda_mue in the fourth and fifth
% column.
% 
% Inputs (max 10 tpamaps):
%   [2500 x 23] horizontal concatenated tpamaps
%   [1 x 10] sim-times according to 100% activation of n-th tpamap
%
%
% Outputs:
%   [2500 x 5] ref_tpamap: s_m, x_m, y_m, lambda_mue_x, lambda_mue_y


%% Initialize the number of maps and their number of datapoints
% init
number_of_maps  = 1;
tpa_map_size    = size(tpa_map); 
rows            = 1;

% find number of provided maps
for j = 2:length(time_array)
    if time_array(j) ~= 0
        number_of_maps = number_of_maps + 1;
    end
end

% find number of valid datapoints
for m = 2:tpa_map_size(1)
    if tpa_map(m,1) ~= 0
        rows = rows + 1;
    end
end


%% Define between which maps the interpolation has to happen
% init
interpTime                    = zeros(1,11);
interpTime(1:number_of_maps)  = time_array(1:number_of_maps);
interpTime(number_of_maps+1)  = time_array(number_of_maps)+1;

% search for active map in number of maps
active_map = 1;
for k = 1:number_of_maps
    
    if Time >= interpTime(k) && Time < interpTime(k+1)
        active_map = k;        
    elseif Time >= interpTime(number_of_maps)
        active_map = number_of_maps;
    end
    
end


%% Create output reference tpa_map
% init
ref_tpamap              = zeros(2500,5);
ref_tpamap(1:rows,1:3)  = tpa_map(1:rows,1:3);

% interpolate through rows
for i = 1:1:rows
DX                  = zeros(1,2);
DY_long             = zeros(1,2);
DY_lat              = zeros(1,2);

    if active_map < number_of_maps
        DX(1)           = interpTime(active_map);
        DX(2)           = interpTime(active_map+1);
        DY_long(1)      = tpa_map(i,4+(active_map-1)*2);
        DY_long(2)      = tpa_map(i,4+active_map*2);
        DY_lat(1)       = tpa_map(i,5+(active_map-1)*2);
        DY_lat(2)       = tpa_map(i,5+active_map*2);
        
        ref_tpamap(i,4) = InterpLin(DX,DY_long,Time);
        ref_tpamap(i,5) = InterpLin(DX,DY_lat,Time);        
        
    elseif active_map == number_of_maps
        ref_tpamap(i,4) = tpa_map(i,4+(active_map-1)*2);
        ref_tpamap(i,5) = tpa_map(i,5+(active_map-1)*2);
    else
        error('interpolation failed');        
    end
    
end

end