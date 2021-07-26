function w_tires_radps = WheelRotVelocities(v_x_mps, dPsi_radps, r_tires_m, ...
            track_f_m, track_r_m, wb_f_m, wb_total_m)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   07.01.2021
% 
% Description: 
% This function calculates, corresponding to the vehicle´s states and the 
% tire radii, the wheel angular velocities. This is needed if the wheel
% rotational velocities from SimRealState lead to numeric instability.
% 
% Inputs: 
%   v_x_mps     - vehicle´s v_x [mps]
%   dPsi_radps  - vehicle´s yaw rate [radps]
%   r_tires_m   - tire radii [m]
%   track_f_m   - front track width [m]
%   track_r_m   - rear track width [m]
%   wb_f_m      - distance cog to front axle [m]
%   wb_total_m  - wheelbase [m]
%   
% Outputs:
%   w_tires_radps - wheels´ rotation rates [radps]

%% calculate rotational velocities
% contact patch positions in vehicle coordinate system
r_K_FL_m = [wb_f_m; 0.5*track_f_m; 0];
r_K_FR_m = [wb_f_m; -0.5*track_f_m; 0];
r_K_RL_m = [-(wb_total_m-wb_f_m); 0.5*track_r_m; 0];
r_K_RR_m = [-(wb_total_m-wb_f_m); -0.5*track_r_m; 0];

% contact patch velocities due to yaw rate
v_K_FL_m = cross(r_K_FL_m, [0; 0; -dPsi_radps]);
v_K_FR_m = cross(r_K_FR_m, [0; 0; -dPsi_radps]);
v_K_RL_m = cross(r_K_RL_m, [0; 0; -dPsi_radps]);
v_K_RR_m = cross(r_K_RR_m, [0; 0; -dPsi_radps]);

% wheel v_x velocities
v_x_FL_m = v_x_mps + v_K_FL_m(1);
v_x_FR_m = v_x_mps + v_K_FR_m(1);
v_x_RL_m = v_x_mps + v_K_RL_m(1);
v_x_RR_m = v_x_mps + v_K_RR_m(1);

% wheel rotational velocities
w_tires_radps = [v_x_FL_m/r_tires_m(1); v_x_FR_m/r_tires_m(2);...
                 v_x_RL_m/r_tires_m(3); v_x_RR_m/r_tires_m(4)];
