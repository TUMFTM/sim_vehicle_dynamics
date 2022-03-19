function loadRacetrack(filename_racetrack, mode)
%
% Author:
%   Leonhard Hermansdorfer      Date: 03.12.2020
%
% Description:
%   function used to load a racetrack for simulating racetrack specific topology, e.g. road banking.
%
% Input:
%   filename_racetrack:  name of file containing the racetrack to be loaded
%                       data format:
%                       - delimiter: ';'
%                       - header char: '#'
%                       - max. number of s-coordinates: Variable "int_max_datapoints"
%                       - contained data:
%                       [s_m;x_m;y_m;psi_rad;kappa_radpm;vx_mps;ax_mps2]
%   mode:               mode in which this functions is called "default", "ci"

%% user input

% fixed length of racetrack data arrays
int_max_datapoints = 5000;

DDname = "racetrack.sldd";


%% check if optional mode argument is provided

if (~exist('mode', 'var'))
    mode = "default";
end


%% read csv-file which contains the racetrack

    % add .csv to filename if not already included
    if ~contains(filename_racetrack, ".csv")
        filename_racetrack = strcat(filename_racetrack,'.csv');
    end

    bool_use_examplefile = false;

    % raise error when no racetrack file with specified name is found
    if isempty(which(filename_racetrack))
        warning(strcat('No racetrack file found with name: "', filename_racetrack, '"!'))
        filename_racetrack = 'traj_ltpl_cl_example.csv';
        bool_use_examplefile = true;
    end

    % find first line without comment char '#' to determine where to start
    % reading the racetrack file
    fid = fopen(filename_racetrack);
    tline = fgetl(fid);

    int_row_start = 0;
    bool_isavailable_banking = false;

    while contains(tline, '#')
        tline = fgetl(fid);
        int_row_start = int_row_start + 1;

        % check if banking angle is available
        if contains(tline, "banking") && ~bool_isavailable_banking && ~bool_use_examplefile
            bool_isavailable_banking = true;
            disp("Racetrack banking angle available.");
        end
    end

    if ~bool_isavailable_banking
        disp("No banking angle found in racetrack file.");
    end

    % start reading racetrack file at first row which contains relevant data
    racetrack_data = dlmread(filename_racetrack,';',int_row_start,0);


%% preprocess and reshape racetrack data

    % get length of original racetrack
    size_racetrack_init = size(racetrack_data);

    % get factor for reducing number of data points in output racetrack array if it is above specified limit
    dist = ceil(size_racetrack_init(1) / int_max_datapoints);

    % discard last row, if x,y-coordinates are the same (trajectory is closed)
    if abs(racetrack_data(1, 2) - racetrack_data(end, 2)) <= 0.1 && ...
        abs(racetrack_data(1, 3) - racetrack_data(end, 3)) <= 0.1

        int_count_validpoints = size_racetrack_init(1) - 1;

    else
        int_count_validpoints = size_racetrack_init(1);

    end

    % crop racetrack data to fit maximum number of data points (rows)
    racetrack_data_cropped = racetrack_data(1:dist:int_count_validpoints, :);
    size_racetrack_cropped = size(racetrack_data_cropped,1);

    % fill racetrack array with zeros to match max number of data points (rows)
    racetrack_data_out = [racetrack_data_cropped;
                zeros((int_max_datapoints - size_racetrack_cropped), size_racetrack_init(2))];

    % create racetrack struct which is then stored in racetrack data dictionary
    Racetrack.ValidPointCnt = length(racetrack_data(1:dist:int_count_validpoints,1));
    Racetrack.x_ref_m = racetrack_data_out(:, 1);
    Racetrack.y_ref_m = racetrack_data_out(:, 2);
    Racetrack.width_right_m = racetrack_data_out(:, 3);
    Racetrack.width_left_m = racetrack_data_out(:, 4);
    Racetrack.x_normvec_m = racetrack_data_out(:, 5);
    Racetrack.y_normvec_m = racetrack_data_out(:, 6);

    Racetrack.psi_racetraj_rad = racetrack_data_out(:, 9);

    if bool_isavailable_banking
        Racetrack.bankingangle_rad = racetrack_data_out(:,13);
    else
        Racetrack.bankingangle_rad = zeros(size(racetrack_data_out, 1), 1);
    end


%% assign struct to data dictionary

    try

        % write passenger vehicle data dictionary
        datadict = Simulink.data.dictionary.open('PassengerVehicle.sldd');
        % delete old data dictionary content
        dDataSectObj = getSection(datadict,'Design Data');
        dDataEntryObj = getEntry(dDataSectObj,'activate_Banking');

        if bool_isavailable_banking && ~bool_use_examplefile && ~(mode == "ci")
            setValue(dDataEntryObj, 1)
            disp("Activate track banking by default!")
        else
            setValue(dDataEntryObj, 0)
            disp("Deactivate track banking by default!")
        end

        % save and close data dictionary
        datadict.saveChanges()
        datadict.close();

        % write racetrack data dictionary
        datadict = Simulink.data.dictionary.open(DDname);

        % delete old data dictionary content
        dDataSectObj = getSection(datadict,'Design Data');
        list_struct_entries = find(dDataSectObj, 'DataSource', DDname);

        % delete all data dict entries of type struct
        for i=1:length(list_struct_entries)
            deleteEntry(dDataSectObj, list_struct_entries(i).Name)
        end

        % write racetrack, start position and racetrack file info to data dictionary
        disp(strcat('Write racetrack "', filename_racetrack, '" to racetrack data dictionary...'));

        addEntry(dDataSectObj, "Racetrack", Racetrack)

        % TODO: double check what this means ??
        addEntry(dDataSectObj, "activate_TrackProfile", 0)

        % add name of current racetrack
        addEntry(dDataSectObj, 'current_racetrack', filename_racetrack)

        % save and close data dictionary
        datadict.saveChanges()
        datadict.close();

    catch e
        warning(['Something went wrong during configuration of ' ...
                'racetrack data dictionary']);
        disp('******************************************');
        disp('Exception: ');
        disp(getReport(e))
        disp('******************************************');

    end

end
