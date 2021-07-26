function [vdp, xy_loc_m, index] = getIndex(x_m, y_m, x_ref_m, y_ref_m)
%__________________________________________________________________________
%% Documentation       
%
% Author:       Dominik Stärk (dominik.staerk@tum.de)
% 
% Start Date:   26.11.2020
% 
% Description: 
% In reference to a dataset of raceline coordinates this function 
% determines the current dataset index in reference to the current track 
% position´s xy-coordinates.  
% 
% Inputs:
%   x_m         - current x-coordinate of track position
%   y_m         - current y-coordinate of track position
%   x_ref_m     - x-coordinates of raceline datapoints
%   y_ref_m     - y-coordinates of raceline datapoints
%
% Outputs: 
%   vdp         - valid data points in dataset
%   xy_loc_m    - current location in x and y 
%   index       - index in dataset of coordinates that points on current
%                 track position


%% get the index
% valid datapoints
vdp         = nnz(x_ref_m);     
% concatenate x and y coordinates of raceline datapoints
R           = [x_ref_m(1:vdp), y_ref_m(1:vdp)];
% get current track location
xy_loc_m    = [x_m, y_m];
% find the index that holds the nearest datapoint in the raceline dataset
d           = bsxfun(@minus,R,xy_loc_m);
[~,index]   = min(abs(hypot(d(:,1),d(:,2))));
