function [lambda_mue_x, lambda_mue_y] = tpa_map_interp_pos(States, ref_tpa_map)
%__________________________________________________________________________
%% Documentation       
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   26.10.2020
% 
% Description: 
% In reference to the current track position this function
% interpolates the coresponding local scaling factors for the friction 
% coefficients lambda_mue_x and lambda_mue_y. The ref_tpamap is provided 
% by tpamaps_Interp which interpolates the time-dependent scaling factors. 
% 
% Inputs: 
%   [2500 x 23] ref_tpamap (tpa_map_Reference.sldd)
%   States (x_m, y_m)
%
% Outputs: 
%   lambda_mue_x corresponding to current xy-track-position
%   lambda_mue_y corresponding to current xy-track-position


%% init
x_m                 = States(1);
y_m                 = States(2); 

x_ref_m             = ref_tpa_map(:,2);
y_ref_m             = ref_tpa_map(:,3);
lambda_mue_x_ref    = ref_tpa_map(:,4);
lambda_mue_y_ref    = ref_tpa_map(:,5);


%% get the current location and corresponding tpamap-index
% found in tpa_map_Reference.sldd
[vdp, xy_loc_m, index] = getIndex(x_m, y_m, x_ref_m, y_ref_m);


%% Start interpolation algorithm
% set interp_Mode
if vdp >= 5 && vdp < 2500
    interp_Mode = 1;
elseif vdp < 5
    interp_Mode = 2;
else
    interp_Mode = 2;
end

% initialize outputs
lambda_mue_x = 1;
lambda_mue_y = 1;

% start algorithm
switch interp_Mode
    case 1
    % Advanced interpolation algorithm    
        
        % get raceline vectors to interpolate
        [Scenario32, Scenario21, length32_m, length21_m, progress_m, ~, ~] = ...
                          getRacelineVectors(xy_loc_m, vdp, index, x_ref_m, y_ref_m);

        % interpolate the actual lambda_mue_x and lambda_mue_y
        if Scenario32 == true
           DX = [0, length32_m];
           if index == vdp
           DY_mue_x = [lambda_mue_x_ref(vdp),...
                       lambda_mue_x_ref(1)];
           DY_mue_y = [lambda_mue_y_ref(vdp),...
                       lambda_mue_y_ref(1)];
           else
           DY_mue_x = [lambda_mue_x_ref(index),...
                       lambda_mue_x_ref(index+1)];
           DY_mue_y = [lambda_mue_y_ref(index),...
                       lambda_mue_y_ref(index+1)];
           end
           lambda_mue_x = InterpLin(DX,DY_mue_x,progress_m);
           lambda_mue_y = InterpLin(DX,DY_mue_y,progress_m);

        elseif Scenario21 == true
           DX = [0, length21_m];
           if index == 1
              DY_mue_x = [lambda_mue_x_ref(vdp),...
                          lambda_mue_x_ref(1)];
              DY_mue_y = [lambda_mue_y_ref(vdp),...
                          lambda_mue_y_ref(1)];
           else
              DY_mue_x = [lambda_mue_x_ref(index-1),...
                          lambda_mue_x_ref(index)];
              DY_mue_y = [lambda_mue_y_ref(index-1),...
                          lambda_mue_y_ref(index)];
           end
              lambda_mue_x = InterpLin(DX,DY_mue_x,progress_m);
              lambda_mue_y = InterpLin(DX,DY_mue_y,progress_m);
        else    
              lambda_mue_x = lambda_mue_x_ref(index);
              lambda_mue_y = lambda_mue_y_ref(index);
        end  


    case 2
    % Reduced interpolation algorithm
        
        lambda_mue_x = lambda_mue_x_ref(index);
        lambda_mue_y = lambda_mue_y_ref(index);
 
end

% replace NaN-entries for error avoidance - normally NaNs not present
if any(isnan(lambda_mue_x))
   lambda_mue_x = lambda_mue_x_ref(index);
end
if any(isnan(lambda_mue_y))
   lambda_mue_y = lambda_mue_y_ref(index);
end


