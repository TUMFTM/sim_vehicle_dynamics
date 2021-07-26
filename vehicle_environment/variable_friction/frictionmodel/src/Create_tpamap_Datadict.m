function Create_tpamap_Datadict
%__________________________________________________________________________
%% Documentation
%
% Author:       Dominik Staerk (dominik.staerk@tum.de)
%
% Start Date:   18.11.2020
%
% Description: Put your tpamap_tum_mcs.csv in opttraj-format into the
% folder \tpa_map_gui_py\outputs\ and run this script.
% Delimiters to be used are semicolons ','.
% A data dict will be created in
% variable_friction\frictionmodel\datadict\tpa_map_Reference.sldd.
% The Datadict will serve the simulink-based models to handle variable
% friction. Make sure the tpamap_tum_mcs.csv is created by using the
% main_tpaGUI.py in GUImode 1.
%
% Inputs: tpamap_tum_mcs.csv [2502 x 23]
%           - tpamap_Mode = [1,1]
%           - interpTime  = [2,1:10]
%           - tpamap      = [3:end,:]


%% init paths
path            = strsplit(pwd,"sim_vehicle_dynamics");
path2module     = strcat(path(1), "sim_vehicle_dynamics");

filepath2tpamap = strcat(path2module, "\vehicle_environment\variable_friction\tpamap_tum_mcs.csv");

filepath2sldd   = strcat(path2module, "\vehicle_environment\variable_friction\frictionmodel\datadict\frictionmodel.sldd");


%% Preprocess
% Read in
csvPath         = filepath2tpamap;
% Start reading from row startReadRow
inM             = dlmread(csvPath,',');
% Create new data dict
dictPath        = filepath2sldd;
% Check if dict already exists
try
    Simulink.data.dictionary.closeAll('frictionmodel.sldd','-discard');
end
try
    if exist(dictPath)
       DictionaryObj    = Simulink.data.dictionary.open(dictPath);
       % Get design data
       dDataSectObj     = getSection(DictionaryObj,'Design Data');
    else
       DictionaryObj    = Simulink.data.dictionary.create(dictPath);
       % Get design data
       dDataSectObj     = getSection(DictionaryObj,'Design Data');
       % Create new entries in the DD
       addEntry(dDataSectObj,'tpa_map_Reference',...
           struct('tpa_map',[],'interpTime',[],'tpa_map_mode',[]));
    end
catch
     fprintf('Error: Datadict creation failed');
end


%% Add data to DD object
rlObj     = getEntry(dDataSectObj,'tpa_map_Reference');
rlObj_val = getValue(rlObj);
% fill structs
rlObj_val.tpa_map        = inM(3:end,:);
rlObj_val.tpa_map        = reshape(rlObj_val.tpa_map.',1,[]);
rlObj_val.interpTime     = inM(2,1:10);
rlObj_val.tpa_map_mode   = inM(1,1);
% Set new values into DD object and save changes
setValue(rlObj,rlObj_val);


%% Save new values to new data dict
fprintf('\nEntries in new DD are:\n');
DictionaryObj.listEntry;
saveChanges(DictionaryObj);


end
