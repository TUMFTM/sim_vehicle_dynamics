function [FxT_N, FyT_N] = TireModel(lambda_perc, alpha_rad, Fz_N, PacFrontLat, PacRearLat, PacFrontLong, PacRearLong)
  % Pacjeka tire model based on a four coefficient approach
  % evaluates the lateral and longitudinal tire forces using the specified 
  % pacjeka models for front and rear 
  
  % initialize
  FxT_N = zeros(4, 1); 
  FyT_N = zeros(4, 1); 
  
  FxT_N(1:2) = PacModel(lambda_perc(1:2)./100, PacFrontLong, Fz_N(1:2)); 
  FxT_N(3:4) = PacModel(lambda_perc(3:4)./100, PacRearLong, Fz_N(3:4));  
  FyT_N(1:2) = PacModel(alpha_rad(1:2), PacFrontLat, Fz_N(1:2)); 
  FyT_N(3:4) = PacModel(alpha_rad(3:4), PacRearLat, Fz_N(3:4)); 
end

function F = PacModel(x, Pac, Fz_N) 
% evaluate the pacejka model for a given slip quantity x and pacejka coefficients Pac
% http://www.edy.es/dev/docs/pacejka-94-parameters-explained-a-comprehensive-guide/

% in addition, Pac(6) provides a factor load degressivity: eps_load <= 0

  F = Fz_N.*(Pac(3)+Pac(6)*((Fz_N-Pac(5))/Pac(5))).*sin(Pac(2).*atan(Pac(1).*x - Pac(4).*(Pac(1).*x - atan(Pac(1).*x)))); 

end
