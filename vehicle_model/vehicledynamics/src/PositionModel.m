function [ExactMeasurements, dxpos] = PositionModel(xveh, xpos)

% differential equations for the position of the vehicle

% initialize output
ExactMeasurements = zeros(3, 1); 
dxpos = zeros(3, 1); 

% load vehicle state variables
vx = xveh(1); 
vy = xveh(2); 
dPsi = xveh(3);

% load position state variables
Psi = xpos(3); 

% rotate vx and vy to global coordinates (ENU) 
dxpos(1) = cos(Psi+pi/2)*vx - sin(Psi+pi/2)*vy;
dxpos(2) = sin(Psi+pi/2)*vx + cos(Psi+pi/2)*vy; 
dxpos(3) = dPsi; 

% output state variables
ExactMeasurements = xpos; 