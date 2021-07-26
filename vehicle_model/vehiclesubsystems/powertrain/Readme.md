# Powertrain
### Overview
The following Readme explains the available powertrain types

### List of software components in this repository
* `models`: Contains the .slx models for a combustion and electric powertrain.
* `src`: Source folder.
* `test`: Contains the .slx models to test the combustion and electric powertrain.

### Installation
This is a brief description on how to set up the powertrain models.

1. In `...\parameters` open the vehicle folder and the according powertrain .ini file.
2. Change any model parameters to your likings.
3. The parameters under [MODE] determine the powertrain type.
    * For the combustion powertrain set `activate_CombustionEngine` to 1, for electric to 0.
    * For a manual gearbox set `activate_ManualGearbox` to 1, for automatic to 0.
    * For a manual throttle position set `activate_ThrottleInterface` to 1, for a automatic force request to 0.
4. Load the according parameters to the vehicle.sldd by typing `configureSimParams('il','db','pa')` in the command window, depending on the vehicle.

Author: Dominik Staerk
