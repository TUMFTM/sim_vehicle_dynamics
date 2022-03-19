//
// File: simulink_model_wrapper_class.h
// Created: 24-April-2020
//
// Author: Matthias Rowold
// Contact: matthias.rowold@tum.de
//
#pragma once

// Insert the name of the Simulink model here:
#define SIMULINK_MODEL_NAME nonlineardtm

// Macros to concatenate the variable names
// Append
#define _NAME_AFFIX(NAME, AFFIX)    NAME##AFFIX
#define NAME_AFFIX(NAME, AFFIX)     _NAME_AFFIX(NAME, AFFIX)
// Prefix
#define PREFIX_NAME_(PREFIX, NAME)  PREFIX##NAME
#define PREFIX_NAME(PREFIX, NAME)   PREFIX_NAME_(PREFIX, NAME)

// Macro for dynamic include file name
#define QUOTEME(x)      QUOTEME_1(x)
#define QUOTEME_1(x)    #x
#define INCLUDE_FILE(x) QUOTEME(x.h)

// All needed variable and function names depending on the name of the Simulink model
#define SIMULINK_MODEL_NAME_M           NAME_AFFIX(SIMULINK_MODEL_NAME, _M)                         // <model_name>_M
#define RT_MODEL_SIMULINK_MODEL_NAME_T  PREFIX_NAME(RT_MODEL_, NAME_AFFIX(SIMULINK_MODEL_NAME, _T)) // RT_MODEL_<model_name>_T
#define SIMULINK_MODEL_NAME_initialize  NAME_AFFIX(SIMULINK_MODEL_NAME, _initialize)                // <model_name>_initialize
#define SIMULINK_MODEL_NAME_terminate   NAME_AFFIX(SIMULINK_MODEL_NAME, _terminate)                 // <model_name>_terminate
#define SIMULINK_MODEL_NAME_step0   NAME_AFFIX(SIMULINK_MODEL_NAME, _step0)                         // <model_name>_step0
#define SIMULINK_MODEL_NAME_step2   NAME_AFFIX(SIMULINK_MODEL_NAME, _step2)                         // <model_name>_step2
#define SIMULINK_MODEL_NAME_step3   NAME_AFFIX(SIMULINK_MODEL_NAME, _step3)                         // <model_name>_step3

// Simulink type definitions
#include "rtwtypes.h"
// logging includes
#include <iostream>
#include <fstream>
// Include the top level Simulink model header files
#include INCLUDE_FILE(SIMULINK_MODEL_NAME)                      // #include "<model_name>.h"
#include INCLUDE_FILE(NAME_AFFIX(SIMULINK_MODEL_NAME, _types))  // #include "<model_name_types>.h"

// Class to wrap the C++ code generated for the Simulink model
class DoubleTrackModelWrapper {
    private:
        // Flags and counters from the rt_OneStep function in ert_main.cpp are class attributes and
        // MUST NOT be static! The remaining rt_OneStep function is copied into simulink_model_Class::step()
        boolean_T OverrunFlag = false;

        // Main pointer to the model
        RT_MODEL_SIMULINK_MODEL_NAME_T *SIMULINK_MODEL_NAME_M;

    public:
        // Constructor and deconstructor
        DoubleTrackModelWrapper();
        ~DoubleTrackModelWrapper();
        // Model step function
        void step();

        //
        // Actuator commands
        //
        void set_DriveTorque(real_T* DriveTorque_Nm);
        void set_BrakePressure(real_T* p_BrakePressure_pa);
        void set_SteeringAngle(real_T SteeringAngle_rad);
        void set_externalForce(real_T* extForce_N);
        void set_externalTorque(real_T* extTorque_Nm);

        void set_lambdaMuex(real_T* lambdaMuex);
        void set_lambdaMuey(real_T* lambdaMuey);
        
        //
        // Vehicle dynamic state:
        //
        real_T get_x_m();
        real_T get_y_m();
        real_T get_psi_rad();
        real_T get_dPsi_radps();
        real_T get_vx_mps();
        real_T get_vy_mps();
        real_T get_ax_mps2();
        real_T get_ay_mps2();
        real_T get_SteeringAngle_rad();
        real_T get_T_DriveTorqueFL_Nm();
        real_T get_T_DriveTorqueFR_Nm();
        real_T get_T_DriveTorqueRL_Nm();
        real_T get_T_DriveTorqueRR_Nm();
        real_T get_BrakePressureFL_pa();
        real_T get_BrakePressureFR_pa();
        real_T get_BrakePressureRL_pa();
        real_T get_BrakePressureRR_pa();
        real_T get_omegaWheelFL_radps();
        real_T get_omegaWheelFR_radps();
        real_T get_omegaWheelRL_radps();
        real_T get_omegaWheelRR_radps();

        // Parameter handling
        int set_parameter(std::string param, double value);
        double get_parameter(std::string param);
        int find_parameter_idx(std::string param);
        int find_parameter_dt(std::string param);
};
