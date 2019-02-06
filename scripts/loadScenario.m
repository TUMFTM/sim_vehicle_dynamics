function loadScenario(scenario)
% Author: Alexander Wischnewski     Date: 21-12-2018
%         Thomas Herrmann
% 
% Description: 
%   loads a scenario from the tracks folder to the necessary data
%   dictionary and configures it appropriatly
% 
% Input: 
%   scenario:   name of the scenario to be loaded 

% open scenario data dictionary 
DD = Simulink.data.dictionary.open('ScenarioDefinition.sldd');

% clear all subreferences 
for i = 1:1:length(DD.DataSources)
    removeDataSource(DD, DD.DataSources{i}); 
end

% load new scenario
addDataSource(DD, [scenario '.sldd']);
% % get 'Raceline' in dictionary object
% dDataSectObj = getSection(DD,'Design Data');
% rlObj = getEntry(dDataSectObj,'Raceline');
% rlObj_val = getValue(rlObj);
% % Updates entry 'ValidPointCnt_Op' in the model's workspace for opponent
% % vehicles if V2X system exists. Otherwise V2X lookups fail to initialize.
% try
%     load_system('externalVehicles\models\trajectoryReplay.slx');
%     hws = get_param(bdroot, 'modelworkspace');
%     hws.assignin('ValidPointCnt_Op', rlObj_val.ValidPointCnt);
% catch
%     disp('No V2X system loaded, therefore no ValidPointCnt entry was updated!');
% end