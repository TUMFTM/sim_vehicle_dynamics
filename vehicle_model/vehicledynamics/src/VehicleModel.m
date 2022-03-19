function [ExactMeasurements, DifferentialStates] = VehicleModel(DeltaWheel_rad, DriveForce_act_N, extForces_N, extTorques_Nm, States, vp)

% differential equations for the nonlinear single track model

%% parameter mapping
tw_front_m = vp.tw_front_m; 
tw_rear_m = vp.tw_rear_m; 
l_front_m = vp.l_front_m; 
l_rear_m = vp.l_total_m - vp.l_front_m; 
m = vp.m_Vehicle_kg; 
J = vp.VehicleInertia_kgm2;

Tvy = vp.T_LatVel_s; 
TdPsi = vp.T_YawRate_s; 
cD = vp.cDrag; 
roh = 1.22; 
A_ref = vp.Aref_m2; 

cF = vp.cRollFriction_Npmps; 

PacFrontLat = vp.PacLatF; 
PacRearLat = vp.PacLatR;
PacFrontLong = vp.PacLongF; 
PacRearLong = vp.PacLongR; 
tyreradius_front_m = vp.r_tireF_m; 
tyreradius_rear_m = vp.r_tireR_m; 
WheelInertia_Front_kgm2 = vp.WheelInertiaF_kgm2; 
WheelInertia_Rear_kgm2 = vp.WheelInertiaR_kgm2; 

cF_max = vp.MaxRollFriction_N;
vx_b = vp.switchModelVel_mps; 
vx_d = vp.switchModelBlend_mps; 
PowertrainLimitLowVelocities_N = vp.PTLimitLowVel_N; 
T_Tire = vp.T_Tire_s; 
cW_F = -1 * vp.cLiftF; 
cW_R = -1 * vp.cLiftR; 
vx_min = vx_b/2; 

% initialize outputs
DifferentialStates = zeros(15, 1); 
ExactMeasurements = zeros(9, 1); 

% get states 
vx_mps = States(1); 
vy_mps = States(2);
dPsi_rad = States(3); 
omega_rad = States(4:7); 
lambda_perc = States(8:11); 
alpha_rad = States(12:15); 

PowertrainTotalForce_N = sum(DriveForce_act_N); 
% handle negative force requests for low velocities (brake in standstill) 
if(PowertrainTotalForce_N < 0 && vx_mps < vx_min) 
  % limit the powertrain forces for slow velocities 
  DriveForce_act_N(1) = max(DriveForce_act_N(1), PowertrainLimitLowVelocities_N);
  DriveForce_act_N(2) = max(DriveForce_act_N(2), PowertrainLimitLowVelocities_N);
  DriveForce_act_N(3) = max(DriveForce_act_N(3), PowertrainLimitLowVelocities_N);
  DriveForce_act_N(4) = max(DriveForce_act_N(4), PowertrainLimitLowVelocities_N);
  % in case the powertrain forces are small or negative, no powertrain forces should be
  % given to the powertrain (this is necessary for proper standstill) 
  NegativeForceFactor = max(vx_mps/vx_min, 0);
  DriveForce_act_N(1) = DriveForce_act_N(1)*NegativeForceFactor; 
  DriveForce_act_N(2) = DriveForce_act_N(2)*NegativeForceFactor; 
  DriveForce_act_N(3) = DriveForce_act_N(3)*NegativeForceFactor; 
  DriveForce_act_N(4) = DriveForce_act_N(4)*NegativeForceFactor; 
end
% powertrain bias front rear
FxPT_N = DriveForce_act_N; 
% wheel inertia factor matrix 
wheelInertia_factors = [tyreradius_front_m/WheelInertia_Front_kgm2;...
  tyreradius_front_m/WheelInertia_Front_kgm2;...
  tyreradius_rear_m/WheelInertia_Rear_kgm2;...
  tyreradius_rear_m/WheelInertia_Rear_kgm2];

%% calculate friction, aero and tire forces 
% limit friction to 200N
FxFriction = max(min(cF*vx_mps, cF_max), 0) + 0.5*cD*roh*A_ref*vx_mps^2;

Fz_N = [ones(2, 1).*((m*9.81+extForces_N(3))*l_rear_m/(l_rear_m+l_front_m)/2 + 0.5*0.5*roh*cW_F*A_ref*vx_mps.^2);...
  ones(2, 1).*((m*9.81+extForces_N(3))*l_front_m/(l_rear_m+l_front_m)/2 + 0.5*0.5*roh*cW_R*A_ref*vx_mps.^2)]; 

[Fx_N, Fy_N] = TireModel(lambda_perc, alpha_rad, Fz_N, PacFrontLat, PacRearLat, PacFrontLong, PacRearLong);

%% calculate single track model 
% calculate equivalent single track accelerations
FxF_N = sum(Fx_N(1:2)); 
FxR_N = sum(Fx_N(3:4)); 
FyF_N = sum(Fy_N(1:2)); 
FyR_N = sum(Fy_N(3:4)); 
% calculate accelerations
ax_stm = (FxF_N*cos(DeltaWheel_rad) - FyF_N*sin(DeltaWheel_rad) + FxR_N - FxFriction + extForces_N(1))/m;
ay_stm = (FyF_N*cos(DeltaWheel_rad) + FxF_N*sin(DeltaWheel_rad) + FyR_N + extForces_N(2))/m; 
dvx_stm = ax_stm + dPsi_rad*vy_mps; 
dvy_stm = ay_stm - dPsi_rad*vx_mps; 
ddPsi_stm = ((FyF_N*cos(DeltaWheel_rad) + FxF_N*sin(DeltaWheel_rad))*l_front_m - FyR_N*l_rear_m + extTorques_Nm(3))/J; 
domega_stm = (FxPT_N - Fx_N).*wheelInertia_factors;
%% calculate kinematic model 
% same for longitudinal dynamics as they are not affected by small slip angle problems
ax_km = (sum(FxPT_N)-FxFriction)/m;
dvx_km = ax_km;
% using the assumption that the centre of gravity is located at 50/50 the following
% relation holds: beta = delta/2. With the small angle assumption and a first order low
% pass dynamics, this results in: 
NeutralSteerBeta = DeltaWheel_rad/2;
dvy_km = 1/Tvy*(NeutralSteerBeta*vx_mps - vy_mps);
%  set the target yaw rate via neutral steer yaw rate for small velocity and combine it
%  with a first order low pass to account for vehicle inertia
NeutralSteerYawRate = DeltaWheel_rad*vx_mps/(l_front_m+l_rear_m);
ddPsi_km = 1/TdPsi*(NeutralSteerYawRate - dPsi_rad);
% calculate slip updates
[lambda_T_perc, alpha_T_rad] = calcWheelSlips(omega_rad, [vx_mps; vy_mps; dPsi_rad],...
  DeltaWheel_rad, tw_front_m, tw_rear_m, l_front_m, l_rear_m, tyreradius_front_m, tyreradius_rear_m, vx_min);
dalpha_rad_stm = 1/T_Tire*(alpha_T_rad - alpha_rad); 
dlambda_perc_stm = 1/T_Tire*(lambda_T_perc - lambda_perc); 
% in case of kinematic model, target slips are zero 
dalpha_rad_km = 1/T_Tire*(0 - alpha_rad); 
dlambda_perc_km = 1/T_Tire*(0 - lambda_perc); 
% set wheelspeed target speed to free rolling 
omega_rolling_radps = [vx_mps - dPsi_rad*tw_front_m*0.5;...
  vx_mps + dPsi_rad*tw_front_m*0.5;...
  vx_mps - dPsi_rad*tw_rear_m*0.5;...
  vx_mps + dPsi_rad*tw_rear_m*0.5;]...
  ./[tyreradius_front_m;tyreradius_front_m;...
  tyreradius_rear_m;tyreradius_rear_m]; 
domega_km = 1/T_Tire*(omega_rolling_radps - omega_rad); 
% calculate alternative lateral acceleration for small velocities based on kinematic model
% yaw rate 
ay_km = dPsi_rad*vx_mps; 

%% overblend kinematic model and single track model 
% calc weighting factors 
w_stm = 0.5*(tanh((vx_mps - vx_b)/vx_d) + 1);
w_km = 1 - w_stm; 
% blend process
dvx = dvx_km * w_km + dvx_stm * w_stm;
dvy = dvy_km * w_km + dvy_stm * w_stm;
ddPsi = ddPsi_km * w_km + ddPsi_stm * w_stm;
domega_rad = domega_km * w_km + domega_stm * w_stm;
dalpha_rad = dalpha_rad_km * w_km + dalpha_rad_stm * w_stm; 
dlambda_perc = dlambda_perc_km * w_km + dlambda_perc_stm * w_stm; 
ax = ax_km * w_km + ax_stm * w_stm; 
ay = ay_km * w_km + ay_stm * w_stm; 

% write derivatives to output
DifferentialStates = [dvx;dvy;ddPsi;domega_rad;dlambda_perc;dalpha_rad;]; 
ExactMeasurements = [vx_mps;vy_mps;dPsi_rad;ax;ay;omega_rad;]; 