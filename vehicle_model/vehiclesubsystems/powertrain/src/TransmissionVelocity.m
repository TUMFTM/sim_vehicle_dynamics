function w_transmission_radps = TransmissionVelocity(i_gearset, ...
                                gear, w_diff_radps)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   21.12.2020
% 
% Description: 
% This function calculates the angular velocity of the gear shaft, which is
% connected to the clutch, corresponding to the available gearset and the 
% currently selected gear. The input angular velocity is provided by the 
% differentials.
%
% Inputs: 
%   w_differential_radps    - input angular velocity [radps]
%   gear                    - currently selected gear
%   i_gearset               - available gearset information
%   
% Outputs:
%   w_transmission_radps    - output angular velocity [radps]


%% calculate angular velocity
i_g = i_gearset(2, gear);
w_transmission_radps = w_diff_radps * i_g;
                            