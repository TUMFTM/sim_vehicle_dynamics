# Python package for vehicle dynamics simulation

### Overview
This tutorial provides information on how to generate python bindings for the PassengerVehicle and the nonlinear double-track simulink models.

### How to install

If you need a specific version of the python bindings it might be required to build the bindings from source. Follow these steps:

1. Go to py_binds/, create a virtual environment, activate it and install the requirements.txt
2. Download the build artifacts from the GenerateCode CI job for the software version you want to build
3. Extract the folder you received
4. Move the .zip folders in build to sim_vehicle_dynamics/py_binds/tum_vehdyn
5. Extract PassengerVehicle.zip to a new folder and rename it to PassengerVehicle
6. Extract nonlineardtm.zip to a new folder and rename it to nonlineardtm
7. Run python3 setup.py bdist_wheel (or only python if on Windows) in misc/py_binds/

**The wheel can be found in py_binds/dist and installed using pip.**
