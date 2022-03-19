function [ lambdaF, lambdaR, alphaF, alphaR ] = TireSlips(DeltaSteer_rad, VehicleStates, tyreradius_front_m, tyreradius_rear_m, l_front_m, l_rear_m)

% calculation of longitudinal and lateral tire slips

% minimum speed for slip calculations
vx_min = 0.5; 

% get states 
vx = VehicleStates(1); 
vy = VehicleStates(2);
dPsi = VehicleStates(3); 
omegaF = VehicleStates(4); 
omegaR = VehicleStates(5); 

% check if velocity is high enough that there are significant slips 
if(vx > vx_min) 
  % calculate side slip angles based on exact side slip formulas
  alphaF = DeltaSteer_rad - atan((vy + dPsi*l_front_m)/vx);
  alphaR = - atan((vy - dPsi*l_rear_m)/vx);
  lambdaF = (omegaF - vx/tyreradius_front_m)/(vx/tyreradius_front_m);
  lambdaR = (omegaR - vx/tyreradius_rear_m)/(vx/tyreradius_rear_m);
else
  alphaF = 0;
  alphaR = 0;
  lambdaF = 0;
  lambdaR = 0;
end


