#!/bin/bash

cd build

echo "######################################################################################"
date +"%T"

#echo "Cmake"
#cmake .. 

echo "make"
make

echo "run SimVehicleDynamics"
./Sim_Vehicle_Dynamics