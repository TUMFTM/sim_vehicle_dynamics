# Friction Model Simulink
This folder contains everything which is related to the simulink friction model.

### Folder structure and content
*  datadict: contains dictionary for the Simulink model
    * `frictionmodel.sldd`
*  models: contains Simulink friction model
    * `frictionmodel.slx` - processes tpa map data (see `...\variable_friction\Readme.md`)
*  src: contains Matlab functions, which are used in the Simulink friction model
    * `ContactPatchPos.m` - depending on vehicle's position and heading, this function calculates every tire's xy-coordinate
    * `Create_tpamap_Datadict` - creates `frictionmodel.sldd` corresponding to the input tpa-map from `...\tpa_map_gui_py\outputs`
      (see tpa_map_gui_py\Readme.md)
    * `FrictionInfluence.m` - master-function that manages the calculation of each tire's variable friction coefficient from the tpa-maps
    * `tpa_map_interp_time.m` - slave-function that interpolates tpa-maps time-dependently
    * `tpa_map_interp_pos.m` - slave-function that interpolates output reference-tpa-map from `tpa_map_interp_time.m`location-dependently
*  test: contains testcase models and related datadicts, which verify the correct output of the Simulink friction model
    * `test_frictionmodel.sldd` - data dictionary for testing
    * `test_frictionmodel.slx` - test tpa slave-functions that interpolate the variable friction coefficients time- & location-dependently

Author: Dominik Staerk
