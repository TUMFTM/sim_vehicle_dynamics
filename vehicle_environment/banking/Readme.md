# Road banking angle

### Overview
The software within this folder allows to simulate the influence of road banking onto vehicle dynamics. This Readme explains how road banking information of specific racetracks can be included into the vehicle dynamics simulation.

### List of software components in this repository
* `datadict`: Contains the banking data dictionary.
* `models`: Contains the `.slx` models that aggregate the calculations necessary to obtain the banking influence onto the vehicle dynamics model.
* `src`: Contains functions to calculate the banking influence onto the single- and double-track vehicle dynamics model.

### Disclaimer
Banking angle information has to be provided within the racetrack file which is loaded. Otherwise, the vehicle will drive on a completely even road surface.

### Installation
This is a brief tutorial how to introduce banking angle information to your simulation.
The sim_vehicle_dynamics repository holds the scripts that process the influence of a banking angle onto vehicle dynamics.

1. In `./racetracks/`, add your custom racetrack `.csv` file filled with data according to the example-file `traj_ltpl_cl_example.csv`.
2. Load the racetrack data dictionary that was just created (eg. `traj_ltpl_cl_Munich.csv`) by running `loadRacetrack('Munich')` in the Matlab command line. This will write the racetrack data into `racetrack.sldd`, which is then used for simulation.

**Note: The provided banking angle is assumed to be present along the normal vectors of the racetrack's centerline.**

### Influence of the banking angle on vehicle dynamics
This serves as a short explanation on how a banking angle influences the vehicle dynamics while running simulations in the mod_control repository.

1. The entire banking angle information is provided through the racetrack's data dictionary.
2. The BankingInfluence subsystem in PassengerVehicle.slx automatically checks whether banking angle information is provided or not.
3. According to the vehicle's position and heading the current banking angle is received by an interpolation algorithm.
4. The effects on the vehicle dynamics are applied as external forces which act on the vehicle.

### Notes
The `.\banking\src\TrackProfile_ndtm.m` file provides the possibility to calculate the track-profile's displacement for each tire. This function is set inactive by default because of missing double differentiability of the banking angle.

Author: Dominik Staerk
