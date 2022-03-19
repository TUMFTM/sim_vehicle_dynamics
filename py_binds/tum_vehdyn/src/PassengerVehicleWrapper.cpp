//
// File: PassengerVehicleWrapper.cpp
// Created: 19-June-2020
//
// Author: Alexander Wischnewski
// Contact: alexander.wischnewski@tum.de
//
#pragma once

#include "PassengerVehicleWrapper.h"
#include "rtw_modelmap.h"

// Constructor
PassengerVehicleWrapper::PassengerVehicleWrapper() {
    // Allocate memory and return a pointer
    SIMULINK_MODEL_NAME_M = SIMULINK_MODEL_NAME();
    // Initialize model
    SIMULINK_MODEL_NAME_initialize(SIMULINK_MODEL_NAME_M);
    }

// Deconstructor
PassengerVehicleWrapper::~PassengerVehicleWrapper() {
    // Terminate model and free memory
    SIMULINK_MODEL_NAME_terminate(SIMULINK_MODEL_NAME_M);
}

// Step function from ert_main.cpp
// All static variables have been changed to class attributes
void PassengerVehicleWrapper::step(){
    // Check for overrun
    if (OverrunFlag) {
      rtmSetErrorStatus(PassengerVehicle_M, "Overrun");
      return;
    }

    OverrunFlag = true;

    // Save FPU context here (if necessary)
    // Re-enable timer or interrupt here
    // Set model inputs here

    // Step the model for base rate
    PassengerVehicle_step(PassengerVehicle_M);

    // Get model outputs here

    // Indicate task complete
    OverrunFlag = false;

    // Disable interrupts here
    // Restore FPU context here (if necessary)
    // Enable interrupts here
    }

int PassengerVehicleWrapper::set_parameter(std::string param, double value)
{
  int idx = find_parameter_idx(param);
  if(idx >= 0)
  {
    // load data type index
    int dt_idx = find_parameter_dt(param); 
    // define data type labels used in generated code from simulink
    std::string double_str = "real_T";
    std::string boolean_str = "boolean_T";
    // check if the data type index is matched to a double variable in the data type map
    if(double_str.compare(SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Maps.dataTypeMap[dt_idx].mwDataName) == 0)
    {
      // get pointer to value
      double* ptr = (double*)SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.InstanceMap.dataAddrMap[idx];
      // write value
      *ptr = (double)value;
      return idx;
    }
    // check if the data type index is matched to a boolean variable in the data type map
    if(boolean_str.compare(SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Maps.dataTypeMap[dt_idx].mwDataName) == 0)
    {
      // get pointer to value
      unsigned char* ptr = (unsigned char*)SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.InstanceMap.dataAddrMap[idx];
      // write value
      *ptr = (unsigned char)value;
      return idx;
    }
  }
  // if no valid index was found return failure
  return -1;
}

double PassengerVehicleWrapper::get_parameter(std::string param)
{
  int idx = find_parameter_idx(param);
  if(idx >= 0)
  {
    // load data type index
    int dt_idx = find_parameter_dt(param);
    // define data type labels used in generated code from simulink
    std::string double_str = "real_T";
    std::string boolean_str = "boolean_T";
    // check if the data type index is matched to a double variable in the data type map
    if(double_str.compare(SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Maps.dataTypeMap[dt_idx].mwDataName) == 0)
    {
      // get pointer to value
      double* ptr = (double*)SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.InstanceMap.dataAddrMap[idx];
      return *ptr;
    }
    // check if the data type index is matched to a boolean variable in the data type map
    if(boolean_str.compare(SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Maps.dataTypeMap[dt_idx].mwDataName) == 0)
    {
      // get pointer to value
      unsigned char* ptr = (unsigned char*)SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.InstanceMap.dataAddrMap[idx];
      return *ptr;
    }
  }
  // if no valid index was found return failure
  return 0;
}

int PassengerVehicleWrapper::find_parameter_idx(std::string param)
{
  // find parameter in data map
  int nParam = SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Params.numModelParameters;
  for(int i = 0; i<nParam; i++)
  {
    // check if requested signal matches value
    if(param.compare(SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.staticMap->Params.modelParameters[i].varName) == 0)
    {
      // get address index
      int dataidx = SIMULINK_MODEL_NAME_M
        ->DataMapInfo.mmi.staticMap->Params.modelParameters[i].addrMapIndex;
      // stop execution if one successful match was found
      return dataidx;
    }
  }
  // if there was no match, return failure
  return -1;
}

int PassengerVehicleWrapper::find_parameter_dt(std::string param)
{
  // find parameter in data map
  int nParam = SIMULINK_MODEL_NAME_M->DataMapInfo.mmi.staticMap->Params.numModelParameters;
  for(int i = 0; i<nParam; i++)
  {
    // check if requested signal matches value
    if(param.compare(SIMULINK_MODEL_NAME_M
      ->DataMapInfo.mmi.staticMap->Params.modelParameters[i].varName) == 0)
    {
      // get data index
      int dataidx = SIMULINK_MODEL_NAME_M
        ->DataMapInfo.mmi.staticMap->Params.modelParameters[i].dataTypeIndex;
      // stop execution if one successful match was found
      return dataidx;
    }
  }
  // if there was no match, return failure
  return -1;
}


//
// Vehicle start point
//
void PassengerVehicleWrapper::set_VehicleStartPoint(real_T* VehicleStartPoint) {
    for (int i = 0; i < 4; i++) {
        SIMULINK_MODEL_NAME_M->inputs->VehicleStartPoint[i] = VehicleStartPoint[i];
    }
}
//
// tpamap reference
//
void PassengerVehicleWrapper::set_tpamapReference(real_T* tpa_map, real_T* interpTime, real_T tpa_map_mode) {
    for (int j = 0; j < 57500; j++){
        SIMULINK_MODEL_NAME_M->inputs->in_tpamapReference.tpa_map[j] = tpa_map[j];
    }
    for (int i = 0; i < 10; i++) {
        SIMULINK_MODEL_NAME_M->inputs->in_tpamapReference.interpTime[i] = interpTime[i];
    }
    SIMULINK_MODEL_NAME_M->inputs->in_tpamapReference.tpa_map_mode = tpa_map_mode;
}

//
// steering angle
//
void PassengerVehicleWrapper::set_SteeringAngle(real_T SteeringAngle) {
    SIMULINK_MODEL_NAME_M->inputs->SteeringAngle_Rad = SteeringAngle;
}
//
// drive force
//
void PassengerVehicleWrapper::set_DriveForce(real_T DriveForce) {
    SIMULINK_MODEL_NAME_M->inputs->DriveForce_act_N = DriveForce;
}

//
// Sim real state
//
real_T PassengerVehicleWrapper::get_x_m() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.x_m;
}

real_T PassengerVehicleWrapper::get_y_m() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.y_m;
}

real_T PassengerVehicleWrapper::get_psi_rad() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.psi_rad;
}

real_T PassengerVehicleWrapper::get_dPsi_radps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.dPsi_radps;
}

real_T PassengerVehicleWrapper::get_vx_mps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.vx_mps;
}

real_T PassengerVehicleWrapper::get_vy_mps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.vy_mps;
}

real_T PassengerVehicleWrapper::get_ax_mps2() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.ax_mps2;
}

real_T PassengerVehicleWrapper::get_ay_mps2() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_k.ay_mps2;
}
