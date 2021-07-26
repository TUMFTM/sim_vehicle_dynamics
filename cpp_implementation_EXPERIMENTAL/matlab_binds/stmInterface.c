#include "matlab_wrapper.h"

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  stmInterface

#include "simstruc.h"


static void mdlInitializeSizes(SimStruct *S){

    //set width of input ports 
    if (!ssSetNumInputPorts(S, 6)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortWidth(S, 1, 4);
    ssSetInputPortWidth(S, 2, 4);
    ssSetInputPortWidth(S, 3, 3);
    ssSetInputPortWidth(S, 4, 3);
    ssSetInputPortWidth(S, 5, 15);


    //set direct feed through for Port
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortDirectFeedThrough(S, 3, 1);
    ssSetInputPortDirectFeedThrough(S, 4, 1);
    ssSetInputPortDirectFeedThrough(S, 5, 1);

    //set width of output ports
    if (!ssSetNumOutputPorts(S, 2)) return;
    ssSetOutputPortWidth(S, 0, 12);
    ssSetOutputPortWidth(S, 1, 18);

    ssSetNumSampleTimes(S, 1);

    //reserve space for the model in the pointer 
    ssSetNumPWork(S, 1);

    // Specify applicable options of S-function -> always at the end of mdlInitializeSizes
    ssSetOptions(S, SS_OPTION_WORKS_WITH_CODE_REUSE | SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S){

    // referenced models containing this S-function can inherit their sample times from their parent model
    ssSetModelReferenceSampleTimeDefaultInheritance(S); 
}


#define MDL_START  
#if defined(MDL_START) 
  static void mdlStart(SimStruct *S)
  {
    //set up a wrapper to store the needed structs for the single track model 
    Wrapper_stm *wrapper;

    wrapper = (Wrapper_stm*)malloc(sizeof(SingleTrackModel)+sizeof(VehicleState));

    wrapper->stm = stm_new();
    wrapper->vehstate = vehstate_new();

    //set parameters from the single track model 
    setParameters_stm(wrapper->stm);

    //print the path to the used paramter file and test if one value is set correctly 
    ssPrintf("Search path stored in cwd: \n %s \n", wrapper->stm->cwd);
    ssPrintf("Check parameter cw_LongitudinalDrag: %f  - should be 1.4 for db \n", wrapper->stm->cw_LongitudinalDrag);
    
    //get step size from the matlab model and set the stm parameter accordingly 
    wrapper->stm->timestep = (double) ssGetFixedStepSize(S);
    ssPrintf("Current time step: \t %f \n", wrapper->stm->timestep);
    
    //store wrapper in the PWork pointer 
    ssSetPWorkValue(S, 0, wrapper);
  }                                                  
#endif


static void mdlOutputs(SimStruct *S, int_T tid){

//at the start of the simulation get the initial values from input port 3 and set them in vehstate
if(ssGetT(S) == ssGetTStart(S)){
    Wrapper_stm *wrapper; 
    
    wrapper = ssGetPWorkValue(S, 0);

    //set initia Values from port 5 
    InputRealPtrsType init_state = ssGetInputPortRealSignalPtrs(S, 5);

    wrapper->vehstate->vx_veh_mps                        = *init_state[0];
    wrapper->vehstate->vy_veh_mps                        = *init_state[1];
    wrapper->vehstate->dpsi_veh                          = *init_state[2];
    wrapper->vehstate->tirestate_fl.omega_radps          = *init_state[3];
    wrapper->vehstate->tirestate_fr.omega_radps          = *init_state[4];
    wrapper->vehstate->tirestate_rl.omega_radps          = *init_state[5];
    wrapper->vehstate->tirestate_rr.omega_radps          = *init_state[6];
    wrapper->vehstate->tirestate_fl.kappa                = *init_state[7]/100.0;
    wrapper->vehstate->tirestate_fr.kappa                = *init_state[8]/100.0;
    wrapper->vehstate->tirestate_rl.kappa                = *init_state[9]/100.0;
    wrapper->vehstate->tirestate_rr.kappa                = *init_state[10]/100.0;
    wrapper->vehstate->tirestate_fl.alpha                = *init_state[11];
    wrapper->vehstate->tirestate_fr.alpha                = *init_state[12];
    wrapper->vehstate->tirestate_rl.alpha                = *init_state[13];
    wrapper->vehstate->tirestate_rr.alpha                = *init_state[14];

    //rotation of veh by 90 degrees to align the coordinate systems
    wrapper->vehstate->psi_ini = 1.57079632679489661923;
}


if(ssIsMajorTimeStep(S)){

    Wrapper_stm *wrapper; 
    
    wrapper = ssGetPWorkValue(S, 0);

    SingleTrackModel *stm;
    stm = wrapper->stm;

    VehicleState *vehstate;
    vehstate = wrapper->vehstate;


    //Get pointer to input signal 
    InputRealPtrsType steeringAngle =       ssGetInputPortRealSignalPtrs(S, 0);
    InputRealPtrsType tireDriveTorque =     ssGetInputPortRealSignalPtrs(S, 1);
    InputRealPtrsType brakePressure =       ssGetInputPortRealSignalPtrs(S, 2);     
    InputRealPtrsType f_ext =               ssGetInputPortRealSignalPtrs(S, 3);
    InputRealPtrsType m_ext =               ssGetInputPortRealSignalPtrs(S, 4);


    //get correct value because the address of the input singals is not continious! 
    int_T element;
    int_T portWidth2 = ssGetInputPortWidth(S, 1);
    int_T portWidth3 = ssGetInputPortWidth(S, 2);

    real_T d_tireDriveTorque[4];
    real_T d_brakePressure[4];

    for(element=0; element<portWidth2; element++){
        d_tireDriveTorque[element] = *tireDriveTorque[element];
        d_brakePressure[element] = *brakePressure[element];
    }


    //get pointer to output signal
    real_T *vehstate_out =      ssGetOutputPortRealSignal(S, 0);
    real_T *differentialStates =ssGetOutputPortRealSignal(S, 1);
    
    //set vehstate to values of input of the block
    vehstate->steeringangle = *steeringAngle[0];

    vehstate->tirestate_fl.tireDriveTorque = d_tireDriveTorque[0];
    vehstate->tirestate_fr.tireDriveTorque = d_tireDriveTorque[1];
    vehstate->tirestate_rl.tireDriveTorque = d_tireDriveTorque[2];
    vehstate->tirestate_rr.tireDriveTorque = d_tireDriveTorque[3];

    vehstate->tirestate_fl.brakePressure_Pa = d_brakePressure[0];
    vehstate->tirestate_fr.brakePressure_Pa = d_brakePressure[1];
    vehstate->tirestate_rl.brakePressure_Pa = d_brakePressure[2];
    vehstate->tirestate_rr.brakePressure_Pa = d_brakePressure[3];

    vehstate->fx_ext_N = *f_ext[0];
    vehstate->fy_ext_N = *f_ext[1];
    vehstate->fz_ext_N = *f_ext[2];

    vehstate->mx_ext_Nm = *m_ext[0];
    vehstate->my_ext_Nm = *m_ext[1];
    vehstate->mz_ext_Nm = *m_ext[2];

    //calculate single track model 
    
    //EULER SOLVER
    // calcLongForce_stm(stm, vehstate);
    // vehicleModel(stm, vehstate);
    // integrate_update_stm(stm, vehstate);
    
    //HEUN SOLVER
    heun(stm, vehstate);

    //get results and store it in the output  
    vehstate_out[0] = vehstate->xpos_ini0_m;
    vehstate_out[1] = vehstate->ypos_ini0_m;
    vehstate_out[2] = vehstate->psi_ini;
    vehstate_out[3] = vehstate->vx_veh_mps;
    vehstate_out[4] = vehstate->vy_veh_mps;
    vehstate_out[5] = vehstate->dpsi_ini;
    vehstate_out[6] = vehstate->ax_veh_mps2;
    vehstate_out[7] = vehstate->ay_veh_mps2;
    vehstate_out[8] = vehstate->tirestate_fl.omega_radps;
    vehstate_out[9] = vehstate->tirestate_fr.omega_radps;
    vehstate_out[10] = vehstate->tirestate_rl.omega_radps;
    vehstate_out[11] = vehstate->tirestate_rr.omega_radps;
    

    differentialStates[0] = stm->m_diffS[0];
    differentialStates[1] = stm->m_diffS[1];
    differentialStates[2] = stm->m_diffS[2];
    differentialStates[3] = stm->m_diffS[3];
    differentialStates[4] = stm->m_diffS[4];
    differentialStates[5] = stm->m_diffS[5];
    differentialStates[6] = stm->m_diffS[6];
    differentialStates[7] = stm->m_diffS[7];
    differentialStates[8] = stm->m_diffS[8];
    differentialStates[9] = stm->m_diffS[9];
    differentialStates[10] = stm->m_diffS[10]*100.0;
    differentialStates[11] = stm->m_diffS[11]*100.0;
    differentialStates[12] = stm->m_diffS[12]*100.0;
    differentialStates[13] = stm->m_diffS[13]*100.0;
    differentialStates[14] = stm->m_diffS[14];
    differentialStates[15] = stm->m_diffS[15];
    differentialStates[16] = stm->m_diffS[16];
    differentialStates[17] = stm->m_diffS[17];

}    
    UNUSED_ARG(tid); 

}

static void mdlTerminate(SimStruct *S){
    //free memory used by the S function
    Wrapper_stm *wrapper; 
    wrapper = ssGetPWorkValue(S, 0);

    stm_free(wrapper->stm);
    vehstate_free(wrapper->vehstate);
    free(ssGetPWorkValue(S, 0)); 

}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
