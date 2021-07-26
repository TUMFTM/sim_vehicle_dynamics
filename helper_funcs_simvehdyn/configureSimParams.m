% Author: Leonhard Hermansdorfer       Date: 10.07.2020

function configureSimParams(vehicle)
% Description:
%   configures the vehicle dynamics simulation repository to use a specific
%   parameter set
%
% Input:
% vehicle: The vehicle code which should be used (e.g. db, rc, pa, ...)

    % vehicles: contains possible vehicle configurations
    vehicles = {'db', 'pa', 'il'};

    % raise error when provided vehicle name is not existing
    if ~any(strcmp(vehicles,vehicle))
        error(['parameters for vehicle "', vehicle,'" are not available'])
    end

  	% DDname: The main component data dictionary which shall be configured
    DDname = 'vehicleparameters_vehdynsim.sldd';

    % DON'T CHANGE ORDER OF FILENAMES
    filenames_vehparams = { [vehicle '_sim_vehicleparameters.ini']; ...
                            [vehicle '_sim_powertrainparameters.ini']; ...
                            [vehicle '_sim_initialparameters.ini']; ...
                            [vehicle '_sim_dtm_suspensionparameters.ini']; ...
                            [vehicle '_sim_tireparameters.tir']; ...
                            [vehicle '_sim_tireparameters_front.tir']; ...
                            [vehicle '_sim_tireparameters_rear.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_frontleft.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_frontright.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_rearleft.tir']; ...
                            [vehicle '_sim_dtm_tireparameters_rearright.tir']};

    % fetch path to parameter files within simulink project
    filepath_vehparams = cell(size(filenames_vehparams));

    for i=1:size(filenames_vehparams, 1)
        filepath_vehparams{i} = which(filenames_vehparams{i});
    end

    % raise error when vehicle specifier is valid but no parameter files
    % are found
    if ~any(isfile(filepath_vehparams))
        error(['No parameters files found for vehicle : "', vehicle, '"'])
    end

    % check which files are mandatory for stm and which are not
    % if filename does not contain "dtm" it is necessary for both models
    array = zeros(size(filepath_vehparams, 1), 1);
    idx_first_tirefile = 0;

    for i=1:size(filenames_vehparams, 1)
        if ~contains(filenames_vehparams(i), 'dtm') && isfile(filepath_vehparams(i))
            array(i) = true;
        end

        if contains(filenames_vehparams(i), 'tire') && idx_first_tirefile == 0
            idx_first_tirefile = i;
        end
    end

    array = logical(array);


	%% read vehicle parameter files

    disp(['Read vehicle parameter files for vehicle : "', vehicle, '"']);

    % check availability of vehicle parameter files -----------------------

    if all(isfile(filepath_vehparams(array))) ...
            && ~any(isfile(filepath_vehparams(~array)))

        available_vehparams = 'stm';
        counter = 3;

        disp('Only single-track model parameters found.');

    elseif all(isfile(filepath_vehparams(1:idx_first_tirefile - 1))) ...
            && any(isfile(filepath_vehparams(idx_first_tirefile:end)))
        available_vehparams = 'dtm';
        counter = 4;

        disp('Single-track and double-track model parameters found.');

    else
        error('No valid paramter files found for STM or DTM');

    end

    % only one tire file provided
    if isfile(filepath_vehparams(idx_first_tirefile)) ...
            && all(~isfile(filepath_vehparams(idx_first_tirefile + 1:end)))
        filepath_tireparameters = filepath_vehparams(idx_first_tirefile);
        number_tirefiles = 1;

    % only one front and one rear tire file provided
    elseif ~isfile(filepath_vehparams(idx_first_tirefile)) ...
            && all(isfile(filepath_vehparams(idx_first_tirefile + 1:idx_first_tirefile + 2))) ...
            && all(~isfile(filepath_vehparams(idx_first_tirefile + 3:end)))
        filepath_tireparameters = filepath_vehparams(idx_first_tirefile + 1:idx_first_tirefile + 2);
        number_tirefiles = 2;

    % tire parameters provided for each tire separately
    elseif all(~isfile(filepath_vehparams(idx_first_tirefile:idx_first_tirefile + 2))) ...
            && all(isfile(filepath_vehparams(idx_first_tirefile + 3:end)))
        filepath_tireparameters = filepath_vehparams(idx_first_tirefile + 3:end);
        number_tirefiles = 4;

    else
        error('Something went wrong with DTM tire parameter files');

    end

    % read vehicle parameter files ----------------------------------------

    for i_count=1:counter
        cell_params = read_inifiles(cell2mat(filepath_vehparams(i_count)));

        if contains(cell2mat(filepath_vehparams(i_count)), 'vehicleparameters')
            VEHICLE = cell_params;

        elseif contains(cell2mat(filepath_vehparams(i_count)), 'powertrainparameters')
            POWERTRAIN = cell_params;

        elseif contains(cell2mat(filepath_vehparams(i_count)), 'suspensionparameters')
            SUSPENSION = cell_params;

        elseif contains(cell2mat(filepath_vehparams(i_count)), 'initialparameters')
            INITIAL = cell_params;

        end

    end

    % do some refactor necessary for matlab models
    VEHICLE.VehicleData.I_K_Vehicle_kgm2 = reshape(VEHICLE.VehicleData.I_K_Vehicle_kgm2, 3,3);

    % read tire files and asign to each tire
    for i_count=1:length(filepath_tireparameters)
        cell_params = read_tireparameters(cell2mat(filepath_tireparameters(i_count)));

        if number_tirefiles == 1
            cell_params.TYRESIDE = 1;
            TIRE_FL = cell_params;
            TIRE_RL = cell_params;

            cell_params.TYRESIDE = -1;
            TIRE_FR = cell_params;
            TIRE_RR = cell_params;

        elseif number_tirefiles == 2

            if contains(cell2mat(filepath_tireparameters(i_count)), 'front')
                cell_params.TYRESIDE = 1;
                TIRE_FL = cell_params;
                cell_params.TYRESIDE = -1;
                TIRE_FR = cell_params;

            elseif contains(cell2mat(filepath_tireparameters(i_count)), 'rear')
                cell_params.TYRESIDE = 1;
                TIRE_RL = cell_params;
                cell_params.TYRESIDE = -1;
                TIRE_RR = cell_params;

            end

        elseif number_tirefiles == 4

            if contains(cell2mat(filepath_tireparameters(i_count)), 'frontleft')
                cell_params.TYRESIDE = 1;
                TIRE_FL = cell_params;

            elseif contains(cell2mat(filepath_tireparameters(i_count)), 'frontright')
                cell_params.TYRESIDE = -1;
                TIRE_FR = cell_params;

            elseif contains(cell2mat(filepath_tireparameters(i_count)), 'rearleft')
                cell_params.TYRESIDE = 1;
                TIRE_RL = cell_params;

            elseif contains(cell2mat(filepath_tireparameters(i_count)), 'rearright')
                cell_params.TYRESIDE = -1;
                TIRE_RR = cell_params;

            end
        end
    end


%% prepare data to save variables as single entries

    disp('Deconstruct parameter structs to save as single variables...');

  	if strcmp(available_vehparams, 'stm')
        parameter_struct = struct(  'VEH', VEHICLE, ...
                                    'POWTR', POWERTRAIN, ...
                                    'tireFL', TIRE_FL, 'tireFR', TIRE_FR, ...
                                    'tireRL', TIRE_RL, 'tireRR', TIRE_RR);

    elseif strcmp(available_vehparams, 'dtm')
        parameter_struct = struct(  'VEH', VEHICLE, ...
                                    'POWTR', POWERTRAIN, ...
                                    'INIT', INITIAL, ...
                                    'SUS', SUSPENSION, ...
                                    'tireFL', TIRE_FL, 'tireFR', TIRE_FR, ...
                                    'tireRL', TIRE_RL, 'tireRR', TIRE_RR);

    end

    fields = fieldnames(parameter_struct);

    struct_save = struct();

    % loop through all fields of structs with multiple sub-structs
    for i = 1:numel(fields)
        strcut_ele = parameter_struct.(fields{i});

        if isstruct(strcut_ele)
            fields_inner = fieldnames(strcut_ele);

            for j = 1:numel(fields_inner)
                strcut_ele_inner = strcut_ele.(fields_inner{j});

                if isstruct(strcut_ele_inner)
                    fields_inner_inner = fieldnames(strcut_ele_inner);

                    for k = 1:numel(fields_inner_inner)
                        strcut_ele_inner_inner = strcut_ele_inner.(fields_inner_inner{k});
                        struct_save(1).(horzcat(fields{i}, '__', fields_inner{j}, '__', fields_inner_inner{k})) = strcut_ele_inner_inner;

                    end

                else
                    strcut_ele_inner = strcut_ele.(fields_inner{j});
                    struct_save(1).(horzcat(fields{i}, '__', fields_inner{j})) = strcut_ele_inner;

                end

            end

        else
            struct_save(1).(horzcat(fields{i})) = strcut_ele;

        end

    end

    % deconstruct arrays into single variables
    fields = fieldnames(struct_save);

    for i = 1:numel(fields)

        size_var = size(struct_save(1).(fields{i}));

        if size_var(2) > 1

            for j=1:size_var(2)

                if size_var(1) > 1

                    for k=1:size_var(1)
                        struct_save = setfield(struct_save, horzcat(fields{i}, '__', num2str(j), num2str(k)), struct_save(1).(fields{i})(j, k));

                   end

                else
                    struct_save = setfield(struct_save, horzcat(fields{i}, '__', num2str(j)), struct_save(1).(fields{i})(j));

                end

            end

            struct_save = rmfield(struct_save ,horzcat(fields{i}));

        end

    end


    %% assign struct to data dictionary
    try

        datadict = Simulink.data.dictionary.open(DDname);
        dDataSectObj = getSection(datadict,'Design Data');

        list_struct_entries = find(dDataSectObj, 'DataSource', DDname);

        disp('Deleting old variables from data dictionary...');

        % delete all data dict entries of type struct
        for i=1:length(list_struct_entries)
            deleteEntry(dDataSectObj, list_struct_entries(i).Name)
        end

        fields = fieldnames(struct_save);

        disp('Writing variables to data dictionary...');

        for i=1:length(fields)
            addEntry(dDataSectObj, fields{i,1}, struct_save(1).(fields{i, 1}))
        end

        addEntry(dDataSectObj, 'current_vehicleparameters', vehicle)
        addEntry(dDataSectObj, 'x0_stm_vehiclestates', [0;0;0;0;0;0;0;0])

        % save and close data dictionary
        datadict.saveChanges()
        datadict.close();

    catch e
        warning(['Something went wrong during configuration of ' ...
                'vehicle dynamics simulation parameters']);
        disp('******************************************');
        disp('Exception: ');
        disp(getReport(e))
        disp('******************************************');

    end

end
