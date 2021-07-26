%%test run VehicleModel from script 
%function [ExactMeasurements, DifferentialStates, debug] = 
% VehicleModel(DeltaWheel_rad, DriveForce_act_N, extForces_N, extTorques_Nm, States, vp)

%set values 
DriveForce_act_N = zeros(4, 1);
extForces_N = zeros(3, 1);
extTorques_Nm = zeros(3, 1);
States = zeros(15, 1);

%STATES vx_mps = States(1); vy_mps = States(2);dPsi_rad = States(3); 
%omega_rad = States(4:7); lambda_perc = States(8:11); alpha_rad = States(12:15); 

DeltaWheel_rad = 0.0;

States(1)               = 3.0;
State(2)                = 0.0;
State(3)                = 0.0;
States(4:7)             = 2.5;
States(8:11)            = 5.0;
States(12:15)           = 0.0;

DriveForce_act_N(1:4)   = 20.0;


%% parameter mapping
p.tw_front_m = 1.7; 
p.tw_rear_m = 1.7;
p.l_front_m = 1.6;
p.l_total_m = 3.4;
p.m_Vehicle_kg = 1300;
p.VehicleInertia_kgm2 = 1500;

p.T_LatVel_s = 0.15; 
p.T_YawRate_s = 0.15;
p.cDrag = 2.3; 
p.Aref_m2 = 1;

p.cRollFriction_Npmps = 200;

p.PacLatF = [5 2.35 4500 1 3000]; 
p.PacLatR = [5 2.35 4500 1 3000];
p.PacLongF = [4.7 2 6000 1 3000]; 
p.PacLongR = [4.7 2 6000 1 3000]; 
p.r_tireF_m = 0.42;
p.r_tireR_m = 0.42;
p.WheelInertiaF_kgm2 = 2.0; 
p.WheelInertiaR_kgm2 = 2.0; 

p.MaxRollFriction_N = 200;
p.switchModelVel_mps = 3;
p.switchModelBlend_mps = 0.5; 
p.PTLimitLowVel_N = -500; 
p.T_Tire_s = 0.02;
p.cLiftF = -1.8; 
p.cLiftR = -2.1; 




[ExactMeasurements, DifferentialStates, debug] = VehicleModel(DeltaWheel_rad, DriveForce_act_N, extForces_N, extTorques_Nm, States, p); 
