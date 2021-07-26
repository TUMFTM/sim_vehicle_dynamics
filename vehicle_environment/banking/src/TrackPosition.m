function [relative_yaw_angle_rad, bankingangle_rad, index, info] = TrackPosition(ref_banking, States)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik St�rk (dominik.staerk@tum.de)
%
% Start Date:   17.09.2020
%
% Description:
% In reference to the current track position and yaw angle this function
% interpolates the coresponding banking angle and heading offset. The
% data is provided by the 'ref_banking' entry in the track�s data
% dictionary.
%
% Inputs:
%   ref_banking
%   States
%
% Outputs:
%   rel_yaw_agngle  - yaw angle offset to raceline yaw angle dataset
%   bankingangle_rad     - banking angle
%   index           - current index in raceline dataset
%   info            - more info of the current track position


%% init
x_m             = States(1);
y_m             = States(2);
psi_rad         = States(3);

x_ref_m         = ref_banking.x_ref_m;
y_ref_m         = ref_banking.y_ref_m;


%% get banking angle and relative yaw angle
% get the index of the current track position t2 out of ref_banking in
% track.sldd
[vdp, xy_loc_m, index] = getIndex(x_m, y_m, x_ref_m, y_ref_m);

% get raceline vectors to interpolate
[Scenario32, Scenario21, length32_m, length21_m, progress_m, offset_m, sgn] = ...
                getRacelineVectors(xy_loc_m, vdp, index, x_ref_m, y_ref_m);

% interpolate the actual banking angle, relative yaw angle offset and track
% width to the left and right corresponding to the active Scenario
if Scenario32 == true
   DX = [0, length32_m];
   if index == vdp
   DY_eps = [ref_banking.bankingangle_rad(vdp),...
            ref_banking.bankingangle_rad(1)];
   DY_psi = [ref_banking.psi_racetraj_rad(vdp),...
            ref_banking.psi_racetraj_rad(1)];
   DY_w_l = [ref_banking.width_left_m(vdp),...
            ref_banking.width_left_m(1)];
   DY_w_r = [ref_banking.width_right_m(vdp),...
            ref_banking.width_right_m(1)];
   else
   DY_eps = [ref_banking.bankingangle_rad(index),...
            ref_banking.bankingangle_rad(index+1)];
   DY_psi = [ref_banking.psi_racetraj_rad(index),...
            ref_banking.psi_racetraj_rad(index+1)];
   DY_w_l = [ref_banking.width_left_m(index),...
            ref_banking.width_left_m(index+1)];
   DY_w_r = [ref_banking.width_right_m(index),...
            ref_banking.width_right_m(index+1)];
   end
   bankingangle_rad      = InterpLin(DX,DY_eps,progress_m);
   psi_racetraj_rad = InterpLin(DX,DY_psi,progress_m);
   track_w_l_m      = InterpLin(DX,DY_w_l,progress_m);
   track_w_r_m      = InterpLin(DX,DY_w_r,progress_m);

elseif Scenario21 == true
   DX = [0, length21_m];
   if index == 1
   DY_eps = [ref_banking.bankingangle_rad(vdp),...
            ref_banking.bankingangle_rad(1)];
   DY_psi = [ref_banking.psi_racetraj_rad(vdp),...
            ref_banking.psi_racetraj_rad(1)];
   DY_w_l = [ref_banking.width_left_m(vdp),...
            ref_banking.width_left_m(1)];
   DY_w_r = [ref_banking.width_right_m(vdp),...
            ref_banking.width_right_m(1)];
   else
   DY_eps = [ref_banking.bankingangle_rad(index-1),...
            ref_banking.bankingangle_rad(index)];
   DY_psi = [ref_banking.psi_racetraj_rad(index-1),...
            ref_banking.psi_racetraj_rad(index)];
   DY_w_l = [ref_banking.width_left_m(index-1),...
            ref_banking.width_left_m(index)];
   DY_w_r = [ref_banking.width_right_m(index-1),...
            ref_banking.width_right_m(index)];
   end
   bankingangle_rad      = InterpLin(DX,DY_eps,progress_m);
   psi_racetraj_rad = InterpLin(DX,DY_psi,progress_m);
   track_w_l_m      = InterpLin(DX,DY_w_l,progress_m);
   track_w_r_m      = InterpLin(DX,DY_w_r,progress_m);
else
   bankingangle_rad      = ref_banking.bankingangle_rad(index);
   psi_racetraj_rad = ref_banking.psi_racetraj_rad(index);
   track_w_l_m      = ref_banking.width_left_m(index);
   track_w_r_m      = ref_banking.width_right_m(index);
end

% return the relative yaw angle offset
rot_psi_rad  = [cos(psi_rad),-sin(psi_rad);sin(psi_rad),...
                  cos(psi_rad)] * [0;1];
ref             = [0,-1;1,0]*rot_psi_rad;
rot             = [cos(psi_racetraj_rad),-sin(psi_racetraj_rad);...
                  sin(psi_racetraj_rad),cos(psi_racetraj_rad)];

% fix to avoid error due to numerical inaccuracy
beta = acos(calc_acosInput(rot*[0;1],ref));

relative_yaw_angle_rad = beta - pi/2;

% return data to calculate the track profile, if ndtm is selected
info = [sgn, offset_m, track_w_l_m, track_w_r_m];
