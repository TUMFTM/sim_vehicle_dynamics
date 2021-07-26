# Interfaces
This folder contains a interface data dictionary which specifies the different simulink buses used to aggregate single signals and to manage in- and outputs from and to other modules. The modelconfig data dictionary provides simulation relevant information, e.g. simulation timestep and solver settings.

## Model Configuration:
Simulink requires to specify the Target Hardware in the modelconfig. The project uses a quite complex structure to maintain these modelconfigs. This emerged from the need to support mulitple targets with the same code and very different configs. The configs are located in `/sim_vehicle_dynamics/interfaces/datadict/simulation_modelconfig.sldd`. The standard config used for the passenger vehicle repository is called GRT. Adjust the configuration according to your needs, e.g. Target Hardware and save everything. It is required to reload the project to apply the changes to all models.
