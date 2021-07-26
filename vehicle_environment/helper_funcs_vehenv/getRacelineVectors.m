function [Scenario32, Scenario21, length32_m, length21_m, progress_m, offset_m, sgn] = ...
                 getRacelineVectors(xy_loc_m, vdp, index, x_ref_m, y_ref_m)
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik St�rk (dominik.staerk@tum.de)
%
% Start Date:   26.11.2020
%
% Description:
% In reference to a set of raceline coordinates this function determines
% the current track postion relative to the nearest receline datapoints.
%
% Inputs:
%   vdp         - valid data points in dataset
%   index       - index of nearest raceline datapoint in dataset
%   x_ref_m     - x-coordinates of raceline dataset
%   y_ref_m     - y-coordinates of raceline dataset
%
% Outputs:
%   Scenario32  -bool- true if driving away from nearest datapoint
%   Scenario21  -bool- true if driving towards nearest datapoint
%   length32_m  - vector length from nearest datapoint to next one
%   length21_m  - vector length from nearest datapoint to previous one
%   progress_m  - vehicle�s progress in length32 respectively length21
%   offset_m    - offset to raceline
%   sgn         - 1 if raceline is right of current position, -1 if left


%% calculate the current track postion relative to the raceline
% get the vectors which represent the deltas of the raceline dataset steps
% corresponding to the two datapoints before till two datapoints after the
% current datapoint
r2    = [x_ref_m(index), y_ref_m(index)];
if index == vdp-1
   r0 = [x_ref_m(index-2), y_ref_m(index-2)];
   r1 = [x_ref_m(index-1), y_ref_m(index-1)];
   r3 = [x_ref_m(index+1), y_ref_m(index+1)];
   r4 = [x_ref_m(1), y_ref_m(1)];
elseif index == vdp
   r0 = [x_ref_m(index-2), y_ref_m(index-2)];
   r1 = [x_ref_m(index-1), y_ref_m(index-1)];
   r3 = [x_ref_m(1), y_ref_m(1)];
   r4 = [x_ref_m(2), y_ref_m(2)];
elseif index == 1
   r0 = [x_ref_m(vdp-1), y_ref_m(vdp-1)];
   r1 = [x_ref_m(vdp), y_ref_m(vdp)];
   r3 = [x_ref_m(index+1), y_ref_m(index+1)];
   r4 = [x_ref_m(index+2), y_ref_m(index+2)];
elseif index == 2
   r0 = [x_ref_m(vdp), y_ref_m(vdp)];
   r1 = [x_ref_m(index-1), y_ref_m(index-1)];
   r3 = [x_ref_m(index+1), y_ref_m(index+1)];
   r4 = [x_ref_m(index+2), y_ref_m(index+2)];
else
   r0 = [x_ref_m(index-2), y_ref_m(index-2)];
   r1 = [x_ref_m(index-1), y_ref_m(index-1)];
   r3 = [x_ref_m(index+1), y_ref_m(index+1)];
   r4 = [x_ref_m(index+2), y_ref_m(index+2)];
end

% calculate the vectors� length
r10  = r1-r0;
r21  = r2-r1;
r32  = r3-r2;
r43  = r4-r3;
lr10 = hypot(r10(1),r10(2));
lr21 = hypot(r21(1),r21(2));
lr32 = hypot(r32(1),r32(2));
lr43 = hypot(r43(1),r43(2));

% get vectors from current track position t2 to r0, r1, r2, r3, r4 and
% their length. r2 represents the index with the nearest corresponding
% raceline dataset-point
d0  = r0-xy_loc_m;
d1  = r1-xy_loc_m;
d2  = r2-xy_loc_m;
d3  = r3-xy_loc_m;
d4  = r4-xy_loc_m;
ld0 = hypot(d0(1),d0(2));
ld1 = hypot(d1(1),d1(2));
ld2 = hypot(d2(1),d2(2));
ld3 = hypot(d3(1),d3(2));
ld4 = hypot(d4(1),d4(2));

% Scenario definition: -Scenario21 true if driving towards r2
%                      -Scenario32 true if driving away from r2

% get the offset of the current track position to the raceline
if acos(calc_acosInput(d2,r32+r21)) > pi/2
   Sc32 = true;
   Sc21 = false;
   offset_m = sin(acos(calc_acosInput(d2,r32))) * ld2;

elseif acos(calc_acosInput(d2,r32+r21)) < pi/2
   Sc32 = false;
   Sc21 = true;
   offset_m = sin(acos(calc_acosInput(d2,r21))) * ld2;

else
   Sc32 = false;
   Sc21 = false;
   offset_m = sin(acos(calc_acosInput(d2,r32+r21))) * ld2;

end

% calculate length32 and length21
% sgn = 1 if track position is right of raceline, -1 if left
sgn     = sign(acos(calc_acosInput(d2,[0,1;-1,0]*(r32+r21)')) - pi/2);
ld32    = lr32 -...
          sgn*(offset_m/tan(acos(calc_acosInput(r32,[0,1;-1,0]*(r32+r21)')))) +...
          sgn*(offset_m/tan(acos(calc_acosInput(r32,[0,1;-1,0]*(r43+r32)'))));
ld21    = lr21 -...
          sgn*(offset_m/tan(acos(calc_acosInput(r21,[0,1;-1,0]*(r21+r10)')))) +...
          sgn*(offset_m/tan(acos(calc_acosInput(r21,[0,1;-1,0]*(r32+r21)'))));

% calculate progress between the two relevant raceline datapoints
% with the law of sines
if Sc32 == true
   x = (ld2/sin(pi-acos(calc_acosInput(r32,sgn*[0,1;-1,0]*(r32+r21)')))) *...
       sin(acos(calc_acosInput(d2,sgn*[0,-1;1,0]*(r32+r21)')));

elseif Sc21 == true
   x = ld21 - ((ld2/sin(acos(calc_acosInput(r21,sgn*[0,1;-1,0]*(r32+r21)')))) *...
       sin(acos(calc_acosInput(d2,sgn*[0,-1;1,0]*(r32+r21)'))));

else
   x = 0;

end

% outputs
Scenario32 = Sc32;
Scenario21 = Sc21;
length32_m = ld32;
length21_m = ld21;
progress_m = x;
