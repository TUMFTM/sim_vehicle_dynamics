//
// File: SingleTrackModelWrapper.cpp
// Created: 19-June-2020
//
// Author: Alexander Wischnewski
// Contact: alexander.wischnewski@tum.de
//
#pragma once

#include "SingleTrackModelWrapper.h"
#include "rtw_modelmap.h"

// Constructor
SingleTrackModelWrapper::SingleTrackModelWrapper() {
    // Allocate memory and return a pointer
    SIMULINK_MODEL_NAME_M = SIMULINK_MODEL_NAME();
    // Initialize model
    SIMULINK_MODEL_NAME_initialize(SIMULINK_MODEL_NAME_M);
    }

// Deconstructor
SingleTrackModelWrapper::~SingleTrackModelWrapper() {
    // Terminate model and free memory
    SIMULINK_MODEL_NAME_terminate(SIMULINK_MODEL_NAME_M);
}

// Step function from ert_main.cpp
// All static variables have been changed to class attributes
void SingleTrackModelWrapper::step(){
    // Check for overrun
    if (OverrunFlag) {
      rtmSetErrorStatus(SIMULINK_MODEL_NAME_M, "Overrun");
      return;
    }

    OverrunFlag = true;

    // Save FPU context here (if necessary)
    // Re-enable timer or interrupt here
    // Set model inputs here

    // Step the model for base rate
    nonlinearstm_step(SIMULINK_MODEL_NAME_M);

    // Get model outputs here

    // Indicate task complete
    OverrunFlag = false;

    // Disable interrupts here
    // Restore FPU context here (if necessary)
    // Enable interrupts here
    }

int SingleTrackModelWrapper::set_parameter(std::string param, double value)
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

double SingleTrackModelWrapper::get_parameter(std::string param)
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

int SingleTrackModelWrapper::find_parameter_idx(std::string param)
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

int SingleTrackModelWrapper::find_parameter_dt(std::string param)
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
// wheel torque for each individual wheel
//
void SingleTrackModelWrapper::set_DriveTorque(real_T* DriveTorque_Nm) {
  for (int i = 0; i < 4; i++) {
          SIMULINK_MODEL_NAME_M->inputs->T_DriveTorque_Nm[i] = DriveTorque_Nm[i];
  }
}
//
// brake pressure for each individual wheel
//
void SingleTrackModelWrapper::set_BrakePressure(real_T* p_BrakePressure_pa) {
  for (int i = 0; i < 4; i++) {
          SIMULINK_MODEL_NAME_M->inputs->p_Brake_pa[i] = p_BrakePressure_pa[i];
  }
}
//
// steering angle
//
void SingleTrackModelWrapper::set_SteeringAngle(real_T SteeringAngle) {
    SIMULINK_MODEL_NAME_M->inputs->DeltaWheel_rad = SteeringAngle;
}
//
// external Force working on vehicle body
//
void SingleTrackModelWrapper::set_externalForce(real_T* extForce_Nm) {
  for (int i = 0; i < 3; i++) {
          SIMULINK_MODEL_NAME_M->inputs->F_K_Extern_N[i] = extForce_Nm[i];
  }
}
//
// external torque working on vehicle body
//
void SingleTrackModelWrapper::set_externalTorque(real_T* extTorque_N) {
  for (int i = 0; i < 3; i++) {
          SIMULINK_MODEL_NAME_M->inputs->T_K_Extern_Nm[i] = extTorque_N[i];
  }
}


//
// Sim real state
//
real_T SingleTrackModelWrapper::get_x_m() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.x_m;
}

real_T SingleTrackModelWrapper::get_y_m() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.y_m;
}

real_T SingleTrackModelWrapper::get_psi_rad() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.psi_rad;
}

real_T SingleTrackModelWrapper::get_dPsi_radps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.dPsi_radps;
}

real_T SingleTrackModelWrapper::get_vx_mps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.vx_mps;
}

real_T SingleTrackModelWrapper::get_vy_mps() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.vy_mps;
}

real_T SingleTrackModelWrapper::get_ax_mps2() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.ax_mps2;
}

real_T SingleTrackModelWrapper::get_ay_mps2() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.ay_mps2;
}

// get input signals

real_T SingleTrackModelWrapper::get_SteeringAngle_rad() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.DeltaWheel_rad;
}

real_T SingleTrackModelWrapper::get_T_DriveTorqueFL_Nm() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.T_DriveTorqueFL_Nm;
}

real_T SingleTrackModelWrapper::get_T_DriveTorqueFR_Nm() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.T_DriveTorqueFR_Nm;
}

real_T SingleTrackModelWrapper::get_T_DriveTorqueRL_Nm() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.T_DriveTorqueRL_Nm;
}

real_T SingleTrackModelWrapper::get_T_DriveTorqueRR_Nm() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.T_DriveTorqueRR_Nm;
}

real_T SingleTrackModelWrapper::get_BrakePressureFL_pa() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.p_BrakeFL_pa;
}

real_T SingleTrackModelWrapper::get_BrakePressureFR_pa() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.p_BrakeFR_pa;
}

real_T SingleTrackModelWrapper::get_BrakePressureRL_pa() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.p_BrakeRL_pa;
}

real_T SingleTrackModelWrapper::get_BrakePressureRR_pa() {
    return SIMULINK_MODEL_NAME_M->outputs->SimRealState_l.p_BrakeRR_pa;
}
