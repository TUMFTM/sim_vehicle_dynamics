# Autonomous Driving Control Software of TUM Roborace Team
### Overview
This software stack has been developed and used for the Roborace Event at the Berlin Formula-E Track 2018. It achieved approximately 150kph and 80% of the combined lateral and longitudinal acceleration potential of the DevBot. The overall research project is a joint effort of the Chair of Automotive Technology and the Chair of Automatic Control.

This software component covers the trajectory tracking, state estimation and vehicle dynamics control aspects of the stack. It takes trajectories from the planner as the main input and delivers appropriate steering, powertrain and brake commands. Furthermore, it handles vehicle startup and emergency brake situations.

To get started, take a look at the `veh_passenger` repository and follow the tutorial for the example vehicle.

# Simulation - Vehicle Dynamics
This repository contains everything which is tightly related to vehicle dynamics simulation. This includes tire models, vehicle/chassis models, actuator and sensor models and combinations thereof.

# List of components
* `actuators`: dynamic models of the vehicle control actuators (e.g. steering and powertrain). Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)  
* `interfaces`: Contains interpackage interface definitions. Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)
* `scripts`: A collection of useful scripts for operating this module. Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)
* `sensors`: Sensor models imitating the correct interfaces and noise properties. Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)
* `tracks`: Collection of racelines which can be driven. Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)
* `vehicledynamics`: All models related to vehicle dynamics, e.g. nonlinear single track model and tire models. Contact person: [Alexander Wischnewski](mailto:alexander.wischnewski@tum.de)
