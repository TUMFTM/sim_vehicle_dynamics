close all

%%
throttle_steps = [0 30 50 65 70 80 100]./100;

factor_losses = 1.1;
conversion_rpm2radps = 2 * pi * 1/60;
% original data is in "mechanical" horsepower with factor: 1.3410
% metric horsepower factor: 1.3596
conversion_watt2hp = 1.3410 * 1/1000;

cell_legend = {};
for i=1:length(throttle_steps)
    cell_legend{i} = horzcat('throttle at ', num2str(throttle_steps(i)), ' %');
end

range_rpm = [500:1000:3500, 4000:500:7500];

range_throttle = 0:0.1:1;

% get data from excel sheet
engine_rpm = table2array(IACdynodataTUM(3:end,1));
enginetorque_Nm = table2array(IACdynodataTUM(3:end,2:2:end))*factor_losses;
enginepower_hp = table2array(IACdynodataTUM(3:end,3:2:end));

engine_fullrange_rpm = 500:100:7500;
engine_fullrange_rpm = engine_fullrange_rpm';

% calculate torque for const power output
range_power = 50:100:450;
torque_iso = range_power ./ (engine_fullrange_rpm * conversion_rpm2radps) / conversion_watt2hp;


% thin out data 

interpolated_enginetorque_Nm = interp1(engine_rpm, enginetorque_Nm, engine_fullrange_rpm);


%% prepare final lookup table

table2d_map = interpolated_enginetorque_Nm;

breakpoints_x = engine_fullrange_rpm;
breakpoints_y = throttle_steps;

%% plot

figure;
hold on, grid on

plot(engine_rpm, enginetorque_Nm(:,1))
plot(engine_rpm, enginetorque_Nm(:,2))
plot(engine_rpm, enginetorque_Nm(:,3))
plot(engine_rpm, enginetorque_Nm(:,4))
plot(engine_rpm, enginetorque_Nm(:,5))
plot(engine_rpm, enginetorque_Nm(:,6))
plot(engine_rpm, enginetorque_Nm(:,7))

%plot(engine_fullrange_rpm, torque_iso, 'k--')

xlabel('engine revs in rpm')
ylabel('torque in Nm')

ylim([-250, 600]);

legend(cell_legend)

figure;

[X, Y] = meshgrid(breakpoints_x, breakpoints_y);
mesh(X, Y, table2d_map')
xlabel('engine revs in rpm')
ylabel('throttle in perc')
zlabel('torque in Nm')

% figure;
% hold on, grid on
% 
% plot(engine_rpm, enginepower_hp(:,1)*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,2))*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,3))*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,4))*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,5))*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,6))*factor_losses)
% plot(engine_rpm, str2double(enginepower_hp(:,7))*factor_losses)

