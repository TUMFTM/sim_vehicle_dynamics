close all
clear filepath_tireparams
%% USER INPUT

    vehicle = 'il';

    % input for variable steps
    SR_steps = -0.5 : 0.01 : 0.5;                                               % []q
    SA_steps = -8 : 0.2 : 8;                                                    % [�]
    % inclination angle ??
    IA_steps = 0;                                                               % [�]
    FZ_steps = 2000:1000:8000;                                                  % [N]


    VX = 20;                                                                    % [m/s]
    mounted_side = 1;

    what_to_plot = "a";

    % 2d plot (plot_dim = 2) (kamm circle) or 3d plot (plot_dim = 3)
    plot_dim = 3;
    

%% read tire parameter file

    filename_tireparams = { [vehicle '_sim_tireparameters.tir']; ...
                            [vehicle '_sim_tireparameters_front.tir']; ...
                            [vehicle '_sim_tireparameters_rear.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_frontleft.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_frontright.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_rearleft.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_rearright.tir']};

    for i=1:size(filename_tireparams, 1)
        filepath_tireparams{i} = which(filename_tireparams{i});
    end

    if isfile(filepath_tireparams(1)) && all(~isfile(filepath_tireparams(2:end)))
        filepath_tireparams_front = filepath_tireparams{1};
        filepath_tireparams_rear = filepath_tireparams{1};

    elseif ~isfile(filepath_tireparams(1)) && all(isfile(filepath_tireparams(2:3))) && all(~isfile(filepath_tireparams(4:end)))
        filepath_tireparams_front = filepath_tireparams{2};
        filepath_tireparams_rear = filepath_tireparams{3};

    elseif ~isfile(filepath_tireparams(1:4)) && all(isfile(filepath_tireparams(4:end)))
        filepath_tireparams_front = filepath_tireparams{4};
        filepath_tireparams_rear = filepath_tireparams{6};

    end


%% PREPARATIONS

    % unit conversion
    SA_steps = SA_steps / 180 * pi;
    IA_steps = IA_steps / 180 * pi;

    % read tire file
    par_TIR_front = read_tireparameters(filepath_tireparams_front);
    par_TIR_rear = read_tireparameters(filepath_tireparams_rear);

    PacFrontLong = [par_TIR_front.MFSIMPLE.PacLong_B, par_TIR_front.MFSIMPLE.PacLong_C, ...
                    par_TIR_front.MFSIMPLE.PacLong_D, par_TIR_front.MFSIMPLE.PacLong_E, ...
                    par_TIR_front.MFSIMPLE.PacLong_Fznom, par_TIR_front.MFSIMPLE.PacLong_eps_load];
    PacFrontLat = [par_TIR_front.MFSIMPLE.PacLat_B, par_TIR_front.MFSIMPLE.PacLat_C, ...
                    par_TIR_front.MFSIMPLE.PacLat_D, par_TIR_front.MFSIMPLE.PacLat_E, ...
                    par_TIR_front.MFSIMPLE.PacLat_Fznom, par_TIR_front.MFSIMPLE.PacLat_eps_load];

    PacRearLong = [par_TIR_rear.MFSIMPLE.PacLong_B, par_TIR_rear.MFSIMPLE.PacLong_C, ...
                    par_TIR_rear.MFSIMPLE.PacLong_D, par_TIR_rear.MFSIMPLE.PacLong_E, ...
                    par_TIR_rear.MFSIMPLE.PacLong_Fznom, par_TIR_rear.MFSIMPLE.PacLong_eps_load];
    PacRearLat = [par_TIR_rear.MFSIMPLE.PacLat_B, par_TIR_rear.MFSIMPLE.PacLat_C, ...
                    par_TIR_rear.MFSIMPLE.PacLat_D, par_TIR_rear.MFSIMPLE.PacLat_E, ...
                    par_TIR_rear.MFSIMPLE.PacLat_Fznom, par_TIR_rear.MFSIMPLE.PacLat_eps_load];


%% CALCULATE RESPONSE

if what_to_plot == "kammcircle"

    switch plot_dim

        case 2

            FX_front = zeros(length(SA_steps), length(SR_steps));
            FX_rear = zeros(length(SA_steps), length(SR_steps));

            FY_front = zeros(length(SA_steps), length(SR_steps));
            FY_rear = zeros(length(SA_steps), length(SR_steps));


            for j = 1 : length(SA_steps)

                [FX_front(j, :), FY_front(j, :), MX, MY, MZ] = MF_52(FZ_steps(1), SR_steps(1,:), SA_steps(1,j), IA_steps, VX, par_TIR_front, mounted_side);
                [FX_rear(j, :), FY_rear(j, :), MX, MY, MZ] = MF_52(FZ_steps(1), SR_steps(1,:), SA_steps(1,j), IA_steps, VX, par_TIR_rear, mounted_side);

            end


        case 3

            FX_front = zeros(length(SA_steps), length(SR_steps), length(FZ_steps));
            FX_rear = zeros(length(SA_steps), length(SR_steps), length(FZ_steps));

            FY_front = zeros(length(SA_steps), length(SR_steps), length(FZ_steps));
            FY_rear = zeros(length(SA_steps), length(SR_steps), length(FZ_steps));


            for j = 1 : length(SA_steps)

                for k = 1 : length(FZ_steps)

                    [FX_front(j, :, k), FY_front(j, :, k), MX, MY, MZ] = MF_52(FZ_steps(1,k), SR_steps(1,:), SA_steps(1,j), IA_steps, VX, par_TIR_front, mounted_side);
                    [FX_rear(j, :, k), FY_rear(j, :, k), MX, MY, MZ] = MF_52(FZ_steps(1,k), SR_steps(1,:), SA_steps(1,j), IA_steps, VX, par_TIR_rear, mounted_side);

                end

            end

    end

else

    FX_front = zeros(length(FZ_steps), length(SR_steps));
    FX_rear = zeros(length(FZ_steps), length(SR_steps));

    FY_front = zeros(length(FZ_steps), length(SA_steps));
    FY_rear = zeros(length(FZ_steps), length(SA_steps));

    FX_front_simple = zeros(length(FZ_steps), length(SR_steps));
    FX_rear_simple = zeros(length(FZ_steps), length(SR_steps));
    FY_front_simple = zeros(length(FZ_steps), length(SA_steps));
    FY_rear_simple = zeros(length(FZ_steps), length(SA_steps));

    for i = 1 : length(FZ_steps)
        [FX_front(i, :), ~, MX, MY, MZ] = MF_52(FZ_steps(i), SR_steps, 0, IA_steps, VX, par_TIR_front, mounted_side);
        [FX_rear(i, :), ~, MX, MY, MZ] = MF_52(FZ_steps(i), SR_steps, 0, IA_steps, VX, par_TIR_rear, mounted_side);
        [~, FY_front(i, :), MX, MY, MZ] = MF_52(FZ_steps(i), 0, SA_steps, IA_steps, VX, par_TIR_front, mounted_side);
        [~, FY_rear(i, :), MX, MY, MZ] = MF_52(FZ_steps(i),0, SA_steps, IA_steps, VX, par_TIR_rear, mounted_side);

        % PacModel(x, Pac, Fz_N)
        for j = 1:length(SR_steps)
            FX_front_simple(i, j) = PacModel(SR_steps(j), PacFrontLong, FZ_steps(i));
            FX_rear_simple(i, j) = PacModel(SR_steps(j), PacRearLong, FZ_steps(i));
        end

        for k = 1:length(SA_steps)
            FY_front_simple(i, k) = PacModel(SA_steps(k), PacFrontLat, FZ_steps(i));
            FY_rear_simple(i, k) = PacModel(SA_steps(k), PacRearLat, FZ_steps(i));
        end

    end

end


%% TRANSFORM TO COORDINATE CONVENTIONS

% positive slip angle leads to positive Fy force

FY_front = -1 * FY_front;
FY_rear = -1 * FY_rear;


%% plot

if what_to_plot == "kammcircle"

    switch plot_dim

        case 2

            figure

            for j = 1 : length(SA_steps)

                plot(FX_front(j, :), FY_front(j, :))
                hold on

                legend_txt{j} = ['alpha=', num2str(SA_steps(j)*180/pi), '� (front)'];

            end

            legend(legend_txt);

            xlabel('long. force in N')
            ylabel('lat. force in N')

            grid on

        case 3

            figure
            FZ = zeros(size(SR_steps));

            for k = 1 : length(FZ_steps)

                    FZ(:) = FZ_steps(k);

                    for j = 1 : length(SA_steps)

                        plot3(FX_front(j, :, k), FY_front(j, :, k), FZ)
                        hold on

                    end

            end

    end

else

    % longitudinal slip
    figure;
    hold on, grid on;

    legend_txt = cell(2 * length(FZ_steps), 1);

    for i = 1 : length(FZ_steps)
        j = 2 * i - 1;
        plot(SR_steps*100, FX_front(i, :));
        plot(SR_steps*100, FX_rear(i, :), 'LineStyle', '--');
        legend_txt{j} = ['FZ=', num2str(FZ_steps(i)), 'N (front)'];
        legend_txt{j + 1} = ['FZ=', num2str(FZ_steps(i)), 'N (rear)'];
    end

    xlabel('long. Slip in perc')
    ylabel('Longitudinal force in N')
    % yticks(-6000 : 500 : 6000);

    title('Double-track tire model (MF52)');
    legend(legend_txt, 'Location', 'best');


    % lateral slip
    figure
    hold on
    grid on

    legend_txt = cell(2 * length(FZ_steps), 1);

    for i = 1 : length(FZ_steps)
        j = 2 * i - 1;
        plot(SA_steps, FY_front(i, :));
        plot(SA_steps, FY_rear(i, :), 'LineStyle', '--');
        legend_txt{j} = ['FZ=', num2str(FZ_steps(i)), 'N (front)'];
        legend_txt{j + 1} = ['FZ=', num2str(FZ_steps(i)), 'N (rear)'];
    end

    xlabel('Slip angle in rad')
    ylabel('Lateral force in N')
    % yticks(-6000 : 500 : 6000);

    title('Double-track tire model (MF52)');
    legend(legend_txt, 'Location', 'best');


    %%

    % longitudinal slip
    figure;
    hold on, grid on;

    legend_txt = cell(2 * length(FZ_steps), 1);

    for i = 1 : length(FZ_steps)
        j = 2 * i - 1;
        plot(SR_steps*100, FX_front_simple(i, :));
        plot(SR_steps*100, FX_rear_simple(i, :), 'LineStyle', '--');
        legend_txt{j} = ['FZ=', num2str(FZ_steps(i)), 'N (front)'];
        legend_txt{j + 1} = ['FZ=', num2str(FZ_steps(i)), 'N (rear)'];
    end

    xlabel('long. Slip in perc')
    ylabel('Longitudinal force in N')
    % yticks(-6000 : 500 : 6000);

    title('Single-track tire model (5 Param. MF)')
    legend(legend_txt, 'Location', 'best');


    % lateral slip
    figure
    hold on
    grid on

    legend_txt = cell(2 * length(FZ_steps), 1);

    for i = 1 : length(FZ_steps)
        j = 2 * i - 1;
        plot(SA_steps, FY_front_simple(i, :));
        plot(SA_steps, FY_rear_simple(i, :), 'LineStyle', '--');
        legend_txt{j} = ['FZ=', num2str(FZ_steps(i)), 'N (front)'];
        legend_txt{j + 1} = ['FZ=', num2str(FZ_steps(i)), 'N (rear)'];
    end

    xlabel('Slip angle in rad')
    ylabel('Lateral force in N')
    % yticks(-6000 : 500 : 6000);

    title('Single-track tire model (5 Param. MF)')
    legend(legend_txt, 'Location', 'best');



end

%%

function F = PacModel(x, Pac, Fz_N)
% evaluate the pacejka model for a given slip quantity x and pacejka coefficients Pac
% http://www.edy.es/dev/docs/pacejka-94-parameters-explained-a-comprehensive-guide/

  F = Fz_N.*(Pac(3)+Pac(6)*((Fz_N-Pac(5))/Pac(5))).*sin(Pac(2).*atan(Pac(1).*x - Pac(4).*(Pac(1).*x - atan(Pac(1).*x))));
end
