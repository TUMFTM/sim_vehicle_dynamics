# Package overview
The *vehicledynamics* package collects all source code and models which is related to vehicle dynamics simulation. This includes e.g. chassis models like the nonlinear single track model and tire models like the Pacjeka model used.

Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)

# Models
* `nonlinearstm.slx` is a nonlinear single track model implementation with additional position states

# Source
* `PositionModel.m` differential equations for the position of the vehicle
* `TireModel.m` Pacjeka tire model based on a four coefficient approach
* `TireSlips.m` calculation of longitudinal and lateral tire slips
* `VehicleModel` differential equations for the nonlinear single track model

# Most important parameters
In the following, there is a list of the most important parameters for tuning of the state estimation module. They are sorted by the corresponding data dictionary. Take care that some data dictionaries have another, vehicle specific version. This is always named e.g. `db_mvdc_state_estimation.sldd`. If you change a parameter, you have to do it in the vehicle specific version.
