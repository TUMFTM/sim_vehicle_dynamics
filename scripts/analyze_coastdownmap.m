
vehiclemass_kg = 750;
rho_kgpm3 = 1.20;
f_roll = 0.02;

array_velocity = [IL15CoastDown.Speed, IL15CoastDown.Speed1, IL15CoastDown.Speed2, IL15CoastDown.Speed3];
array_time = [IL15CoastDown.Time, IL15CoastDown.Time1, IL15CoastDown.Time2, IL15CoastDown.Time3];

cw_A_all = [];
Fx_all = [];

for i=1:size(array_velocity,2)
    velocity = array_velocity(:,i) * 1.63 /3.6;
    
    [v_min, idx_vmin] = min(velocity);
    [v_max, idx_vmax] = max(velocity);

    delta_t = array_time(idx_vmin, i) - array_time(idx_vmax, i);
    delta_v = v_min - v_max;
    ax_aero = delta_v / delta_t
    
    cw_A = (vehiclemass_kg * ax_aero + f_roll * vehiclemass_kg * 9.81) * (-2) / (rho_kgpm3 * ((v_min  + v_max)/2)^2)
    Fx = 0.5 * rho_kgpm3 * cw_A * (150*1.63/3.6)^2

    cw_A_all = [cw_A_all, cw_A];
    Fx_all = [Fx_all, Fx];
end

figure;
hold on, grid on
scatter(1:4, cw_A_all)
xlim([0,5])
ylim([0,2])

yyaxis right
scatter(1:4, Fx_all)
xlim([0,5])
ylim([0,3000])


figure;
hold on, grid on

plot(IL15CoastDown.Time-IL15CoastDown.Time(1), IL15CoastDown.Speed)
plot(IL15CoastDown.Time1-IL15CoastDown.Time1(1), IL15CoastDown.Speed1)
plot(IL15CoastDown.Time2-IL15CoastDown.Time2(1), IL15CoastDown.Speed2)
plot(IL15CoastDown.Time3-IL15CoastDown.Time3(1), IL15CoastDown.Speed3)

xlabel('time in s')
ylabel('velocity in mph')
