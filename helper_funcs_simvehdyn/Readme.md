# Package overview
This folder contains several functions to calculate different tasks. For further details consult documentation within each file.

### List of software component in this repository
* `read_parameters`: Contains functions which are necessary to read the .ini and .tir parameter files and convert them into Simulink data dictionaries.
* `configureSimBuildModelConfig.m`: This function configures the vehicle dynamics simulation repository to use a specific model configuration. This is necessary as there are multiple build targets.
* `configureSimParams.m`: This function configures the vehicle dynamics simulation repository to use a specific vehicle parameter set.
* `normalizeAngle.m`: This function normalizes angles in radians to a range between -pi and pi.
