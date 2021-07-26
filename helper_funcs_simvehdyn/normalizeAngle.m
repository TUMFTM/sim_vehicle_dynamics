function y = normalizeAngle(u)
%#codegen
% normalize angles in radians to a range between -pi and pi
y = u;

y(u>pi) = mod(u(u>pi) + pi, 2*pi) - pi;
y(u<-pi) = -(mod(-(u(u<-pi) - pi), 2*pi) - pi);
