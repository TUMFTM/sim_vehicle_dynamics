function [par_TIR] = read_tireparameters(filepath_tireparameters)

    %#codegen

    %% Import

    fid = fopen(filepath_tireparameters, 'r');

    % Alle relevanten Zeilen auslesen und in Cell Array "content" speichern
    content = {};

    bool_isavailable_mfsimple = false;
    bool_isavailable_mfextended = false;

    while ~feof(fid)
        line = fgetl(fid);
        if ~isempty(line)
            if strcmp(line(1), '!') == 0 && strcmp(line(1), '$') == 0 && strcmp(line(1), '[') == 0 && strcmp(line(1), '{') == 0 && strcmp(line(1), '''') == 0
                content = [content; line];
            end
        end

        % get which tire model parameters are available
        % options: five parameter MF, extended MF, both

        if contains(line, "[MFSIMPLE]")
            bool_isavailable_mfsimple = true;

        elseif contains(line, "[UNITS]")
            bool_isavailable_mfextended = true;
        end

    end

    fclose(fid);

    %% Bearbeitung: Struct erstellen und befuellen

    % Alle Leerzeichen aus den einzelnen Zellen entfernen
    for i = 1 : length(content)
        content{i} = strrep(content{i}, ' ', '');       % Leerzeichen loeschen
        content{i} = regexprep(content{i}, '\t', '');   % Tabs loeschen
    end

    if bool_isavailable_mfsimple

        % [MFSIMPLE]
        % read parameters for 5 param Pacejka tire model
        par_TIR.MFSIMPLE.PacLong_B                  = read_parameters_sub(content,'PacLong_B',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLong_C                  = read_parameters_sub(content,'PacLong_C',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLong_D                  = read_parameters_sub(content,'PacLong_D',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLong_E                  = read_parameters_sub(content,'PacLong_E',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLong_Fznom            	= read_parameters_sub(content,'PacLong_Fznom',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLong_eps_load        	= read_parameters_sub(content,'PacLong_eps_load',filepath_tireparameters);

        par_TIR.MFSIMPLE.PacLat_B                   = read_parameters_sub(content,'PacLat_B',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLat_C                   = read_parameters_sub(content,'PacLat_C',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLat_D                   = read_parameters_sub(content,'PacLat_D',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLat_E                   = read_parameters_sub(content,'PacLat_E',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLat_Fznom               = read_parameters_sub(content,'PacLat_Fznom',filepath_tireparameters);
        par_TIR.MFSIMPLE.PacLat_eps_load           	= read_parameters_sub(content,'PacLat_eps_load',filepath_tireparameters);

        par_TIR.MFSIMPLE.r_tire_m                   = read_parameters_sub(content,'r_tire_m',filepath_tireparameters);
        par_TIR.MFSIMPLE.Iyy_Wheel_kgm2             = read_parameters_sub(content,'Iyy_Wheel_kgm2',filepath_tireparameters);

    end

    if bool_isavailable_mfextended

        % [UNITS]
        ANGLE_temp                      = read_parameters_sub(content,'ANGLE',filepath_tireparameters);

        switch lower(ANGLE_temp)
            case ('degrees')
                par_TIR.ANGLE = 180 / pi;                   % unit conversion [rad] -> [degree]
            case ('radians')
                par_TIR.ANGLE = 1;
            otherwise
                error('Winkeleinheit konnte nicht bestimmt werden!');
        end

        % [MODEL]
        TYRESIDE_temp                    = read_parameters_sub(content,'TYRESIDE',filepath_tireparameters);

        switch lower(TYRESIDE_temp)
            case ('left')
                par_TIR.TYRESIDE = 1;
            case ('right')
                par_TIR.TYRESIDE = -1;
            case ('symmetric')
                par_TIR.TYRESIDE = 0;
            otherwise
                error('TYRESIDE konnte nicht bestimmt werden!');
        end

        par_TIR.USE_MODE                 = read_parameters_sub(content,'USE_MODE',filepath_tireparameters);
        par_TIR.LONGVL                              = read_parameters_sub(content,'LONGVL',filepath_tireparameters);

        % [INERTIAL]
        par_TIR.INERTIAL.m_Wheel_kg                 = read_parameters_sub(content,'m_Wheel_kg',filepath_tireparameters);
        par_TIR.INERTIAL.Iyy_Wheel_kgm2             = read_parameters_sub(content,'Iyy_Wheel_kgm2',filepath_tireparameters);

        % [WHEEL]
        par_TIR.WHEEL.br_Nmsprad                    = read_parameters_sub(content,'br_Nmsprad',filepath_tireparameters);
        par_TIR.WHEEL.FNOMIN                        = read_parameters_sub(content,'FNOMIN',filepath_tireparameters);
        par_TIR.WHEEL.NORMPRES                      = read_parameters_sub(content,'NORMPRES',filepath_tireparameters);
        par_TIR.WHEEL.TYRE_RADIUS_MOD           	= read_parameters_sub(content,'TYRE_RADIUS_MOD',filepath_tireparameters);
        par_TIR.WHEEL.T_RelaxationLong           	= read_parameters_sub(content,'T_RelaxationLong',filepath_tireparameters);
        par_TIR.WHEEL.T_RelaxationLat           	= read_parameters_sub(content,'T_RelaxationLat',filepath_tireparameters);
        par_TIR.WHEEL.T_RelaxationMy           	    = read_parameters_sub(content,'T_RelaxationMy',filepath_tireparameters);

        % [DIMENSION]
        par_TIR.DIMENSION.UNLOADED_RADIUS           = read_parameters_sub(content,'UNLOADED_RADIUS',filepath_tireparameters);
        par_TIR.DIMENSION.WIDTH                     = read_parameters_sub(content,'WIDTH',filepath_tireparameters);
        par_TIR.DIMENSION.ASPECT_RATIO              = read_parameters_sub(content,'ASPECT_RATIO',filepath_tireparameters);
        par_TIR.DIMENSION.RIM_RADIUS                = read_parameters_sub(content,'RIM_RADIUS',filepath_tireparameters);
        par_TIR.DIMENSION.RIM_WIDTH                 = read_parameters_sub(content,'RIM_WIDTH',filepath_tireparameters);

        % [VERTICAL]
        par_TIR.VERTICAL.VERTICAL_STIFFNESS         = read_parameters_sub(content,'VERTICAL_STIFFNESS',filepath_tireparameters);
        par_TIR.VERTICAL.VERTICAL_DAMPING           = read_parameters_sub(content,'VERTICAL_DAMPING',filepath_tireparameters);
        par_TIR.VERTICAL.BREFF                      = read_parameters_sub(content,'BREFF',filepath_tireparameters);
        par_TIR.VERTICAL.DREFF                      = read_parameters_sub(content,'DREFF',filepath_tireparameters);
        par_TIR.VERTICAL.FREFF                      = read_parameters_sub(content,'FREFF',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.VERTICAL.Q_RE0                      = read_parameters_sub(content,'Q_RE0',filepath_tireparameters);
        par_TIR.VERTICAL.Q_V1                       = read_parameters_sub(content,'Q_V1',filepath_tireparameters);
        par_TIR.VERTICAL.Q_V2                       = read_parameters_sub(content,'Q_V2',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FZ1                      = read_parameters_sub(content,'Q_FZ1',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FZ2                      = read_parameters_sub(content,'Q_FZ2',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FZ3                      = read_parameters_sub(content,'Q_FZ3',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FCX                      = read_parameters_sub(content,'Q_FCX',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FCY                      = read_parameters_sub(content,'Q_FCY',filepath_tireparameters);
        par_TIR.VERTICAL.Q_FCY2                     = read_parameters_sub(content,'Q_FCY2',filepath_tireparameters);
        par_TIR.VERTICAL.PFZ1                       = read_parameters_sub(content,'PFZ1',filepath_tireparameters);

        % [SIMULATION]
        par_TIR.SIMULATION.KPUMIN                   = read_parameters_sub(content,'KPUMIN',filepath_tireparameters);
        par_TIR.SIMULATION.KPUMAX                   = read_parameters_sub(content,'KPUMAX',filepath_tireparameters);
        par_TIR.SIMULATION.ALPMIN                   = read_parameters_sub(content,'ALPMIN',filepath_tireparameters);
        par_TIR.SIMULATION.ALPMAX                   = read_parameters_sub(content,'ALPMAX',filepath_tireparameters);
        par_TIR.SIMULATION.CAMMIN                   = read_parameters_sub(content,'CAMMIN',filepath_tireparameters);
        par_TIR.SIMULATION.CAMMAX                   = read_parameters_sub(content,'CAMMAX',filepath_tireparameters);
        par_TIR.SIMULATION.FZMIN                    = read_parameters_sub(content,'FZMIN',filepath_tireparameters);
        par_TIR.SIMULATION.FZMAX                    = read_parameters_sub(content,'FZMAX',filepath_tireparameters);
        par_TIR.SIMULATION.LONGVL                   = read_parameters_sub(content,'LONGVL',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.SIMULATION.VXLOW                    = read_parameters_sub(content,'VXLOW',filepath_tireparameters);
        par_TIR.SIMULATION.PRESMIN               	= read_parameters_sub(content,'PRESMIN',filepath_tireparameters);
        par_TIR.SIMULATION.PRESMAX               	= read_parameters_sub(content,'PRESMAX',filepath_tireparameters);

        % [SCALING_COEFFICIENTS]
        par_TIR.SCALING.LFZO                     = read_parameters_sub(content,'LFZO',filepath_tireparameters);
        par_TIR.SCALING.LCX                      = read_parameters_sub(content,'LCX',filepath_tireparameters);
        par_TIR.SCALING.LMUX                     = read_parameters_sub(content,'LMUX',filepath_tireparameters);
        par_TIR.SCALING.LEX                      = read_parameters_sub(content,'LEX',filepath_tireparameters);
        par_TIR.SCALING.LKX                      = read_parameters_sub(content,'LKX',filepath_tireparameters);
        par_TIR.SCALING.LHX                      = read_parameters_sub(content,'LHX',filepath_tireparameters);
        par_TIR.SCALING.LVX                      = read_parameters_sub(content,'LVX',filepath_tireparameters);
        par_TIR.SCALING.LGAX                     = read_parameters_sub(content,'LGAX',filepath_tireparameters);
        par_TIR.SCALING.LCY                      = read_parameters_sub(content,'LCY',filepath_tireparameters);
        par_TIR.SCALING.LMUY                     = read_parameters_sub(content,'LMUY',filepath_tireparameters);
        par_TIR.SCALING.LEY                      = read_parameters_sub(content,'LEY',filepath_tireparameters);
        par_TIR.SCALING.LKY                      = read_parameters_sub(content,'LKY',filepath_tireparameters);
        par_TIR.SCALING.LHY                      = read_parameters_sub(content,'LHY',filepath_tireparameters);
        par_TIR.SCALING.LVY                      = read_parameters_sub(content,'LVY',filepath_tireparameters);
        par_TIR.SCALING.LGAY                     = read_parameters_sub(content,'LGAY',filepath_tireparameters);
        par_TIR.SCALING.LTR                      = read_parameters_sub(content,'LTR',filepath_tireparameters);
        par_TIR.SCALING.LRES                     = read_parameters_sub(content,'LRES',filepath_tireparameters);
        par_TIR.SCALING.LGAZ                     = read_parameters_sub(content,'LGAZ',filepath_tireparameters);
        par_TIR.SCALING.LXAL                     = read_parameters_sub(content,'LXAL',filepath_tireparameters);
        par_TIR.SCALING.LYKA                     = read_parameters_sub(content,'LYKA',filepath_tireparameters);
        par_TIR.SCALING.LVYKA                    = read_parameters_sub(content,'LVYKA',filepath_tireparameters);
        par_TIR.SCALING.LS                       = read_parameters_sub(content,'LS',filepath_tireparameters);
        par_TIR.SCALING.LSGKP                    = read_parameters_sub(content,'LSGKP',filepath_tireparameters);
        par_TIR.SCALING.LSGAL                    = read_parameters_sub(content,'LSGAL',filepath_tireparameters);
        par_TIR.SCALING.LGYR                     = read_parameters_sub(content,'LGYR',filepath_tireparameters);
        par_TIR.SCALING.LMX                      = read_parameters_sub(content,'LMX',filepath_tireparameters);
        par_TIR.SCALING.LVMX                     = read_parameters_sub(content,'LVMX',filepath_tireparameters);
        par_TIR.SCALING.LMY                      = read_parameters_sub(content,'LMY',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.SCALING.LMUV                     = read_parameters_sub(content,'LMUV',filepath_tireparameters);
        par_TIR.SCALING.LCZ                      = read_parameters_sub(content,'LCZ',filepath_tireparameters);
        par_TIR.SCALING.LMPHI                    = read_parameters_sub(content,'LMPHI',filepath_tireparameters);

        % [LONGITUDINAL_COEFFICIENTS]
        par_TIR.LONGITUDINAL.PCX1                     = read_parameters_sub(content,'PCX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PDX1                     = read_parameters_sub(content,'PDX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PDX2                     = read_parameters_sub(content,'PDX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PDX3                     = read_parameters_sub(content,'PDX3',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PEX1                     = read_parameters_sub(content,'PEX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PEX2                     = read_parameters_sub(content,'PEX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PEX3                     = read_parameters_sub(content,'PEX3',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PEX4                     = read_parameters_sub(content,'PEX4',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PKX1                     = read_parameters_sub(content,'PKX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PKX2                     = read_parameters_sub(content,'PKX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PKX3                     = read_parameters_sub(content,'PKX3',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PHX1                     = read_parameters_sub(content,'PHX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PHX2                     = read_parameters_sub(content,'PHX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PVX1                     = read_parameters_sub(content,'PVX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PVX2                     = read_parameters_sub(content,'PVX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.RBX1                     = read_parameters_sub(content,'RBX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.RBX2                     = read_parameters_sub(content,'RBX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.RCX1                     = read_parameters_sub(content,'RCX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.REX1                     = read_parameters_sub(content,'REX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.REX2                     = read_parameters_sub(content,'REX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.RHX1                     = read_parameters_sub(content,'RHX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PTX1                     = read_parameters_sub(content,'PTX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PTX2                     = read_parameters_sub(content,'PTX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PTX3                     = read_parameters_sub(content,'PTX3',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.LONGITUDINAL.PPX1                     = read_parameters_sub(content,'PPX1',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PPX2                     = read_parameters_sub(content,'PPX2',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PPX3                     = read_parameters_sub(content,'PPX3',filepath_tireparameters);
        par_TIR.LONGITUDINAL.PPX4                     = read_parameters_sub(content,'PPX4',filepath_tireparameters);
        par_TIR.LONGITUDINAL.RBX3                     = read_parameters_sub(content,'RBX3',filepath_tireparameters);

        % [OVERTURNING_COEFFICIENTS]
        par_TIR.OVERTURNING.QSX1                     = read_parameters_sub(content,'QSX1',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX2                     = read_parameters_sub(content,'QSX2',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX3                     = read_parameters_sub(content,'QSX3',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.OVERTURNING.QSX4                     = read_parameters_sub(content,'QSX4',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX5                     = read_parameters_sub(content,'QSX5',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX6                     = read_parameters_sub(content,'QSX6',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX7                     = read_parameters_sub(content,'QSX7',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX8                     = read_parameters_sub(content,'QSX8',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX9                     = read_parameters_sub(content,'QSX9',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX10                    = read_parameters_sub(content,'QSX10',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX11                    = read_parameters_sub(content,'QSX11',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX12                    = read_parameters_sub(content,'QSX12',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX13                    = read_parameters_sub(content,'QSX13',filepath_tireparameters);
        par_TIR.OVERTURNING.QSX14                    = read_parameters_sub(content,'QSX14',filepath_tireparameters);
        par_TIR.OVERTURNING.PPMX1                    = read_parameters_sub(content,'PPMX1',filepath_tireparameters);

        % [LATERAL_COEFFICIENTS]
        par_TIR.LATERAL.PCY1                     = read_parameters_sub(content,'PCY1',filepath_tireparameters);
        par_TIR.LATERAL.PDY1                     = read_parameters_sub(content,'PDY1',filepath_tireparameters);
        par_TIR.LATERAL.PDY2                     = read_parameters_sub(content,'PDY2',filepath_tireparameters);
        par_TIR.LATERAL.PDY3                     = read_parameters_sub(content,'PDY3',filepath_tireparameters);
        par_TIR.LATERAL.PEY1                     = read_parameters_sub(content,'PEY1',filepath_tireparameters);
        par_TIR.LATERAL.PEY2                     = read_parameters_sub(content,'PEY2',filepath_tireparameters);
        par_TIR.LATERAL.PEY3                     = read_parameters_sub(content,'PEY3',filepath_tireparameters);
        par_TIR.LATERAL.PEY4                     = read_parameters_sub(content,'PEY4',filepath_tireparameters);
        par_TIR.LATERAL.PKY1                     = read_parameters_sub(content,'PKY1',filepath_tireparameters);
        par_TIR.LATERAL.PKY2                     = read_parameters_sub(content,'PKY2',filepath_tireparameters);
        par_TIR.LATERAL.PKY3                     = read_parameters_sub(content,'PKY3',filepath_tireparameters);
        par_TIR.LATERAL.PHY1                     = read_parameters_sub(content,'PHY1',filepath_tireparameters);
        par_TIR.LATERAL.PHY2                     = read_parameters_sub(content,'PHY2',filepath_tireparameters);
        par_TIR.LATERAL.PHY3                     = read_parameters_sub(content,'PHY3',filepath_tireparameters);
        par_TIR.LATERAL.PVY1                     = read_parameters_sub(content,'PVY1',filepath_tireparameters);
        par_TIR.LATERAL.PVY2                     = read_parameters_sub(content,'PVY2',filepath_tireparameters);
        par_TIR.LATERAL.PVY3                     = read_parameters_sub(content,'PVY3',filepath_tireparameters);
        par_TIR.LATERAL.PVY4                     = read_parameters_sub(content,'PVY4',filepath_tireparameters);
        par_TIR.LATERAL.RBY1                     = read_parameters_sub(content,'RBY1',filepath_tireparameters);
        par_TIR.LATERAL.RBY2                     = read_parameters_sub(content,'RBY2',filepath_tireparameters);
        par_TIR.LATERAL.RBY3                     = read_parameters_sub(content,'RBY3',filepath_tireparameters);
        par_TIR.LATERAL.RCY1                     = read_parameters_sub(content,'RCY1',filepath_tireparameters);
        par_TIR.LATERAL.REY1                     = read_parameters_sub(content,'REY1',filepath_tireparameters);
        par_TIR.LATERAL.REY2                     = read_parameters_sub(content,'REY2',filepath_tireparameters);
        par_TIR.LATERAL.RHY1                     = read_parameters_sub(content,'RHY1',filepath_tireparameters);
        par_TIR.LATERAL.RHY2                     = read_parameters_sub(content,'RHY2',filepath_tireparameters);
        par_TIR.LATERAL.RVY1                     = read_parameters_sub(content,'RVY1',filepath_tireparameters);
        par_TIR.LATERAL.RVY2                     = read_parameters_sub(content,'RVY2',filepath_tireparameters);
        par_TIR.LATERAL.RVY3                     = read_parameters_sub(content,'RVY3',filepath_tireparameters);
        par_TIR.LATERAL.RVY4                     = read_parameters_sub(content,'RVY4',filepath_tireparameters);
        par_TIR.LATERAL.RVY5                     = read_parameters_sub(content,'RVY5',filepath_tireparameters);
        par_TIR.LATERAL.RVY6                     = read_parameters_sub(content,'RVY6',filepath_tireparameters);
        par_TIR.LATERAL.PTY1                     = read_parameters_sub(content,'PTY1',filepath_tireparameters);
        par_TIR.LATERAL.PTY2                     = read_parameters_sub(content,'PTY2',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.LATERAL.PEY5                     = read_parameters_sub(content,'PEY5',filepath_tireparameters);
        par_TIR.LATERAL.PKY4                     = read_parameters_sub(content,'PKY4',filepath_tireparameters);
        par_TIR.LATERAL.PKY5                     = read_parameters_sub(content,'PKY5',filepath_tireparameters);
        par_TIR.LATERAL.PKY6                     = read_parameters_sub(content,'PKY6',filepath_tireparameters);
        par_TIR.LATERAL.PKY7                     = read_parameters_sub(content,'PKY7',filepath_tireparameters);
        par_TIR.LATERAL.PPY1                     = read_parameters_sub(content,'PPY1',filepath_tireparameters);
        par_TIR.LATERAL.PPY2                     = read_parameters_sub(content,'PPY2',filepath_tireparameters);
        par_TIR.LATERAL.PPY3                     = read_parameters_sub(content,'PPY3',filepath_tireparameters);
        par_TIR.LATERAL.PPY4                     = read_parameters_sub(content,'PPY4',filepath_tireparameters);
        par_TIR.LATERAL.PPY5                     = read_parameters_sub(content,'PPY5',filepath_tireparameters);
        par_TIR.LATERAL.RBY4                     = read_parameters_sub(content,'RBY4',filepath_tireparameters);

        % [ROLLING_COEFFICIENTS]
        par_TIR.ROLLING.QSY1                     = read_parameters_sub(content,'QSY1',filepath_tireparameters);
        par_TIR.ROLLING.QSY2                     = read_parameters_sub(content,'QSY2',filepath_tireparameters);
        par_TIR.ROLLING.QSY3                     = read_parameters_sub(content,'QSY3',filepath_tireparameters);
        par_TIR.ROLLING.QSY4                     = read_parameters_sub(content,'QSY4',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.ROLLING.QSY5                     = read_parameters_sub(content,'QSY5',filepath_tireparameters);
        par_TIR.ROLLING.QSY6                     = read_parameters_sub(content,'QSY6',filepath_tireparameters);
        par_TIR.ROLLING.QSY7                     = read_parameters_sub(content,'QSY7',filepath_tireparameters);
        par_TIR.ROLLING.QSY8                     = read_parameters_sub(content,'QSY8',filepath_tireparameters);

        % [ALIGNING_COEFFICIENTS]
        par_TIR.ALIGNING.QBZ1                     = read_parameters_sub(content,'QBZ1',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ2                     = read_parameters_sub(content,'QBZ2',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ3                     = read_parameters_sub(content,'QBZ3',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ4                     = read_parameters_sub(content,'QBZ4',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ5                     = read_parameters_sub(content,'QBZ5',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ9                     = read_parameters_sub(content,'QBZ9',filepath_tireparameters);
        par_TIR.ALIGNING.QBZ10                    = read_parameters_sub(content,'QBZ10',filepath_tireparameters);
        par_TIR.ALIGNING.QCZ1                     = read_parameters_sub(content,'QCZ1',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ1                     = read_parameters_sub(content,'QDZ1',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ2                     = read_parameters_sub(content,'QDZ2',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ3                     = read_parameters_sub(content,'QDZ3',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ4                     = read_parameters_sub(content,'QDZ4',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ6                     = read_parameters_sub(content,'QDZ6',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ7                     = read_parameters_sub(content,'QDZ7',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ8                     = read_parameters_sub(content,'QDZ8',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ9                     = read_parameters_sub(content,'QDZ9',filepath_tireparameters);
        par_TIR.ALIGNING.QEZ1                     = read_parameters_sub(content,'QEZ1',filepath_tireparameters);
        par_TIR.ALIGNING.QEZ2                     = read_parameters_sub(content,'QEZ2',filepath_tireparameters);
        par_TIR.ALIGNING.QEZ3                     = read_parameters_sub(content,'QEZ3',filepath_tireparameters);
        par_TIR.ALIGNING.QEZ4                     = read_parameters_sub(content,'QEZ4',filepath_tireparameters);
        par_TIR.ALIGNING.QEZ5                     = read_parameters_sub(content,'QEZ5',filepath_tireparameters);
        par_TIR.ALIGNING.QHZ1                     = read_parameters_sub(content,'QHZ1',filepath_tireparameters);
        par_TIR.ALIGNING.QHZ2                     = read_parameters_sub(content,'QHZ2',filepath_tireparameters);
        par_TIR.ALIGNING.QHZ3                     = read_parameters_sub(content,'QHZ3',filepath_tireparameters);
        par_TIR.ALIGNING.QHZ4                     = read_parameters_sub(content,'QHZ4',filepath_tireparameters);
        par_TIR.ALIGNING.SSZ1                     = read_parameters_sub(content,'SSZ1',filepath_tireparameters);
        par_TIR.ALIGNING.SSZ2                     = read_parameters_sub(content,'SSZ2',filepath_tireparameters);
        par_TIR.ALIGNING.SSZ3                     = read_parameters_sub(content,'SSZ3',filepath_tireparameters);
        par_TIR.ALIGNING.SSZ4                     = read_parameters_sub(content,'SSZ4',filepath_tireparameters);
        par_TIR.ALIGNING.QTZ1                     = read_parameters_sub(content,'QTZ1',filepath_tireparameters);
        par_TIR.ALIGNING.MBELT                    = read_parameters_sub(content,'MBELT',filepath_tireparameters);
        % added for matlab tire model
        par_TIR.ALIGNING.QBZ6                     = read_parameters_sub(content,'QBZ6',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ10                    = read_parameters_sub(content,'QDZ10',filepath_tireparameters);
        par_TIR.ALIGNING.QDZ11                    = read_parameters_sub(content,'QDZ11',filepath_tireparameters);
        par_TIR.ALIGNING.PPZ1                    = read_parameters_sub(content,'PPZ1',filepath_tireparameters);
        par_TIR.ALIGNING.PPZ2                    = read_parameters_sub(content,'PPZ2',filepath_tireparameters);

        % TURNSLIP completely added for Matlab tire MODEL
        % [TURNSLIP]
        par_TIR.TURNSLIP.PDXP1                     = read_parameters_sub(content,'PDXP1',filepath_tireparameters);
        par_TIR.TURNSLIP.PDXP2                     = read_parameters_sub(content,'PDXP2',filepath_tireparameters);
        par_TIR.TURNSLIP.PDXP3                     = read_parameters_sub(content,'PDXP3',filepath_tireparameters);
        par_TIR.TURNSLIP.PKYP1                     = read_parameters_sub(content,'PKYP1',filepath_tireparameters);
        par_TIR.TURNSLIP.PDYP1                     = read_parameters_sub(content,'PDYP1',filepath_tireparameters);
        par_TIR.TURNSLIP.PDYP2                     = read_parameters_sub(content,'PDYP2',filepath_tireparameters);
        par_TIR.TURNSLIP.PDYP3                     = read_parameters_sub(content,'PDYP3',filepath_tireparameters);
        par_TIR.TURNSLIP.PDYP4                     = read_parameters_sub(content,'PDYP4',filepath_tireparameters);
        par_TIR.TURNSLIP.PHYP1                     = read_parameters_sub(content,'PHYP1',filepath_tireparameters);
        par_TIR.TURNSLIP.PHYP2                     = read_parameters_sub(content,'PHYP2',filepath_tireparameters);
        par_TIR.TURNSLIP.PHYP3                     = read_parameters_sub(content,'PHYP3',filepath_tireparameters);
        par_TIR.TURNSLIP.PHYP4                     = read_parameters_sub(content,'PHYP4',filepath_tireparameters);
        par_TIR.TURNSLIP.PECP1                     = read_parameters_sub(content,'PECP1',filepath_tireparameters);
        par_TIR.TURNSLIP.PECP2                     = read_parameters_sub(content,'PECP2',filepath_tireparameters);
        par_TIR.TURNSLIP.QDTP1                     = read_parameters_sub(content,'QDTP1',filepath_tireparameters);
        par_TIR.TURNSLIP.QCRP1                     = read_parameters_sub(content,'QCRP1',filepath_tireparameters);
        par_TIR.TURNSLIP.QCRP2                     = read_parameters_sub(content,'QCRP2',filepath_tireparameters);
        par_TIR.TURNSLIP.QBRP1                     = read_parameters_sub(content,'QBRP1',filepath_tireparameters);
        par_TIR.TURNSLIP.QDRP1                     = read_parameters_sub(content,'QDRP1',filepath_tireparameters);
        par_TIR.TURNSLIP.QDRP2                     = read_parameters_sub(content,'QDRP2',filepath_tireparameters);

        % CONTACTPATCH completely added for Matlab tire MODEL
        % [CONTACTPATCH]
        par_TIR.CONTACTPATCH.Q_RA1                   = read_parameters_sub(content,'Q_RA1',filepath_tireparameters);
        par_TIR.CONTACTPATCH.Q_RA2                   = read_parameters_sub(content,'Q_RA2',filepath_tireparameters);
        par_TIR.CONTACTPATCH.Q_RB1                   = read_parameters_sub(content,'Q_RB1',filepath_tireparameters);
        par_TIR.CONTACTPATCH.Q_RB2                   = read_parameters_sub(content,'Q_RB2',filepath_tireparameters);

        % STRUCTURAL completely added for Matlab tire MODEL
        % [STRUCTURAL]
        par_TIR.STRUCTURAL.LONGITUDINAL_STIFFNESS     = read_parameters_sub(content,'LONGITUDINAL_STIFFNESS',filepath_tireparameters);
        par_TIR.STRUCTURAL.LATERAL_STIFFNESS          = read_parameters_sub(content,'LATERAL_STIFFNESS',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFX1                      = read_parameters_sub(content,'PCFX1',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFX2                      = read_parameters_sub(content,'PCFX2',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFX3                      = read_parameters_sub(content,'PCFX3',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFY1                      = read_parameters_sub(content,'PCFY1',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFY2                      = read_parameters_sub(content,'PCFY2',filepath_tireparameters);
        par_TIR.STRUCTURAL.PCFY3                      = read_parameters_sub(content,'PCFY3',filepath_tireparameters);

        % GENERAL completely added for Matlab tire MODEL
        % [GENERAL]
        par_TIR.CONTACTPATCH.k1_TireFB_PT1              = read_parameters_sub(content,'k1_TireFB_PT1',filepath_tireparameters);
        par_TIR.CONTACTPATCH.k1_WheelsFB_PT1            = read_parameters_sub(content,'k1_WheelsFB_PT1',filepath_tireparameters);
        par_TIR.CONTACTPATCH.k2_TireFB_PT1              = read_parameters_sub(content,'k2_TireFB_PT1',filepath_tireparameters);
        par_TIR.CONTACTPATCH.p_Tires_Pa                 = read_parameters_sub(content,'p_Tires_Pa',filepath_tireparameters);

    end

end
