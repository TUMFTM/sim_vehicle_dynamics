function configureSimBuildModelConfig(target)
%
% Author: Alexander Wischnewski     Date: 21-12-2018
%
% Description:
%   configures the vehicle dynamics simulation repository to use
%   a specific model configuration. This is necessary as there are multiple
%   build targets.
%
% Input:
%   target: Target code string, e.g. 'Speedgoat' or 'GRT'

% configure model simulation configs
modelConfigDD = ...
Simulink.data.dictionary.open('simulation_modelconfig.sldd');
ConfigurationsDD = getSection(modelConfigDD,'Configurations');
buildConfigEntry = getEntry(ConfigurationsDD,'Physics');
newConfigEntry = getEntry(ConfigurationsDD, ['Physics_' target]);
newConfig = getValue(newConfigEntry);
newConfig.Name = 'Physics';
setValue(buildConfigEntry, newConfig);
