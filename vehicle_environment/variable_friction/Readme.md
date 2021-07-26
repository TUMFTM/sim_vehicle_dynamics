# Variable tire-road friction coefficients

### Overview
The following Readme explains how variable friction coefficients are integrated individually for each tire and implemented into the various simulations in the mod_control repository by tpa-maps. The default setting provides constant friction (lambda_mue = 1)

### List of software components in this repository
* `archive`: outdated models
* `frictionmodel`: Contains the tools and algorithms to process "tpa-maps" which are used to simulate time- & location-varying road surface conditions (friction coefficients).

### Disclaimer
If you want to use this variable-friction-interface within the mod_control simulations, it only works with the nonlinear double-track-model (`P_PassengerVehicleSimModel` = 2). Furthermore, `activate_VariableFriction` must be set to `1`. Both are manually settable in the `PassengerVehicle.sldd` data dictionary in the mod_control repository.

### Installation
This is a brief tutorial how to setup your simulation interface to work with varying fiction coefficients.

1. Create your desired variable friction scenario `tpamap_tum_mcs.csv` by using a GUI which can be found on [github](https://github.com/TUMFTM/tpa_map_functions/tree/develop/tpa_map_gui).
2. Copy the output file into the folder `/vehicle_environment/variable_friction/`.
2. Run the matlab script `/vehicle_environment/variable_friction/frictionmodel/src/Create_tpamap_Datadict.m` in the command window, which will set up the `frictionmodel.sldd` data dictionary.
3. You can test the implementation by simulating the test model `...\frictionmodel\test\test_frictionmodel.slx`

### Process pipeline
This serves as a short explanation on how the processing of the tpa-maps, holding the variable friction data, works.

1. The entire variable friction scenario is provided through `tpamap_tum_mcs.csv`. This .csv file contains:
    * global coordinates: `s_m`,`x_m`,`y_m`.
    * concatenated tpa-maps (max 10): variable friction coefficients in lateral and longitudinal direction, dependent in time and global xy-coordinate.
    * tpa_map_mode: info on wether variable or constant friction is active.
2. This data is saved into the `frictionmodel.sldd` data dictionary (see installation steps above).
3. For each time-step, the following pipeline is run through:
    * Regarding the current simulation-time a corresponding reference map is interpolated. For example: at time 0s map1 is 100% active with a global coefficient of 1.1 and at time 10s map2 is 100% active with a global coefficient of 0.9. Therefore, at time 5s, the global coefficient will be 1.0. This interpolation is done for every friction coefficient in the global s_m dataset and time-step.
    * Afterwards an interpolation will happen between the two global s_m coordinates which represent the upper and lower boundary of the vehicle's current track position.

### Notes
For further information every matlab function provides a description on its functionality.

Author: Dominik Staerk
