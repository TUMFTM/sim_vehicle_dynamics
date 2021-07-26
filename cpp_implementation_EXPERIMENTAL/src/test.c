#include "../include/test.h"
//#include "../include/Param_dtm.h"
#include "../include/VehicleBody.h"
//#include "../include/SingleTrackModel.h"

#include "../include/TireModel.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef M_PI
    #define M_PI      3.14159265358979323846
#endif

    /*
        order calculations STM:      
        1. LongForce
        2. friction 
        3. Fz 
        4. tire Model 
        5. acc stm 
        6. wheel speeds stm
        7. acc km 
        8. wheelSlpis 
    */


void test_paramsetting_dtm(){
    printf("\n\e[1;37m\e[4;37mStart test_paramsetting\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    Parameters_dtm *param_dtm;
    param_dtm = param_dtm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();


    printf("Set Parameters\n\n");
    setParameters(param_dtm);

    printf("Set timestep\n\n");
    param_dtm->vehicleparameters.timestep = 0.02;

    printf("Set tireDriveTorque FL\n\n");
    vehstate->tirestate_fl.tireDriveTorque = 10.0;
    vehstate->tirestate_fr.tireDriveTorque = 10.0;
    
    printf("Set brakePressure_Pa FL\n\n");
    vehstate->tirestate_fl.brakePressure_Pa = 0.1;

    printf("Set vx to non zero value FL\n\n");
    vehstate->vx_veh_mps = 1.5;

    printf("\e[1;37mVEHICLE\e[0m \tVehiclemass: %f\n\n", param_dtm->vehicleparameters.m_Vehicle_kg);
    printf("\e[1;37mSUSPENSION\e[0m \tmue brakepad kinematic: %f\n\n", param_dtm->vehicleparameters.mue_BrakePadsFrRe_kinetic[0]);
    printf("\e[1;37mTIRE\e[0m \t\tunloaded raadius FL: %f\n\n", param_dtm->tirefl.unloaded_radius);
    printf("\e[1;37mSTATUS\e[0m \t\tdrive torque: %f\n\n", vehstate->tirestate_fl.tireDriveTorque);
    printf("\e[1;37mSTATUS\e[0m \t\tbrake pressure: %f\n\n", vehstate->tirestate_fl.brakePressure_Pa);

    printf("\e[1;37mTIRE\e[0m \t\ttyreside FL: %s\n\n", param_dtm->tirefl.tyreside);
    printf("\e[1;37mTIRE\e[0m \t\ttyreside FR: %s\n\n", param_dtm->tirefr.tyreside);
    printf("\e[1;37mTIRE\e[0m \t\ttyreside RL: %s\n\n", param_dtm->tirerl.tyreside);
    printf("\e[1;37mTIRE\e[0m \t\ttyreside RR: %s\n\n", param_dtm->tirerr.tyreside);
    
    printf("\e[1;37mVEHICLE\e[0m \tPajeka front lat 0: %f\n\n", param_dtm->vehicleparameters.m_pac_front_lat[0]);
    printf("\e[1;37mVEHICLE\e[0m \tPajeka front lat 1: %f\n\n", param_dtm->vehicleparameters.m_pac_front_lat[1]);
    printf("\e[1;37mVEHICLE\e[0m \tPajeka front lat 2: %f\n\n", param_dtm->vehicleparameters.m_pac_front_lat[2]);


    printf("\e[1;37mSUSPENSION\e[0m \tk_HeightVSSteerF_mprad: %f\n\n", param_dtm->suspensionparam.k_HeightVSSteerF_mprad);

    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    param_dtm_free(param_dtm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);

}


void test_paramsetting_stm(){
    printf("\n\e[1;37m\e[4;37mStart test_paramsetting\e[0m\n\n");

    //######################
    //### CREATE Structs ##
    //######################

    SingleTrackModel *stm;
    stm = stm_new();
    
    printf("Set Parameters STM\n\n");
    setParameters_stm(stm);

    printf("Set timestep\n\n");
    stm->timestep = 0.02;


    printf("\e[1;37mVEHICLE\e[0m \tVehiclemass: %f\n\n", stm->m_Vehicle_kg);
    printf("\e[1;37mSUSPENSION\e[0m \tmue brakepad kinematic: %f\n\n", stm->mue_BrakePadsFrRe_kinetic[0]);
    printf("\e[1;37mTIRE\e[0m \t\tunloaded raadius FL: %f\n\n", stm->r_tireF_m);

    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLat: %f - should be 5\n\n", stm->m_pac_front_lat[0]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLat: %f - should be 2.35\n\n", stm->m_pac_front_lat[1]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLat: %f - should be 4500\n\n", stm->m_pac_front_lat[2]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLat: %f - should be 1\n\n", stm->m_pac_front_lat[3]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLat: %f - should be 3000\n\n", stm->m_pac_front_lat[4]);

    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLong: %f - should be 4.7\n\n", stm->m_pac_front_long[0]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLong: %f - should be 2\n\n", stm->m_pac_front_long[1]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLong: %f - should be 6000\n\n", stm->m_pac_front_long[2]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLong: %f - should be 1\n\n", stm->m_pac_front_long[3]);
    printf("\e[1;37mTIRE\e[0m \t\tPacjeka pacFrontLong: %f - should be 3000\n\n", stm->m_pac_front_long[4]);


    //for w_stm
    printf("switchModelVel_mps: %f\n\n", stm->switchModelVel_mps);
    printf("switchModelBlend_mps: %f\n\n", stm->switchModelBlend_mps);
    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    stm_free(stm);
}


void test_calctirestatus(){
    printf("\n\e[1;37m\e[4;37mStart test_calctirestatus\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    Parameters_dtm *param_dtm;
    param_dtm = param_dtm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct Vehicleparameters *vehparam;
    vehparam = &param_dtm->vehicleparameters;


    printf("Set Parameters\n\n");
    setParameters(param_dtm);

    printf("Set timestep\n\n");
    param_dtm->vehicleparameters.timestep = 0.02;

    printf("Set tireDriveTorque FL\n\n");
    vehstate->tirestate_fl.tireDriveTorque = 10.0;
    vehstate->tirestate_fr.tireDriveTorque = 10.0;
    
    printf("Set brakePressure_Pa FL\n\n");
    vehstate->tirestate_fl.brakePressure_Pa = 0.0;

    printf("Set vx to non zero value FL\n\n");
    vehstate->vx_veh_mps = 1.5;
    
    printf("Set dpsi to non zero value FL\n\n");
    vehstate->dpsi_veh = 0.1;
    
    printf("\e[1;37mCalc TireStatus\e[0m\n\n");
    //calcTirestatus(param_dtm, vehstate);

    printf("Wheelspeed FL: %f\n\n", vehstate->tirestate_fl.roh);

    printf("Kappa FL: %f\n\n", vehstate->tirestate_fl.kappa);


    printf("\e[1;37mCalc TireStatus\e[0m\n\n");
    //calcTirestatus(param_dtm, vehstate);

    printf("Wheelspeed FL: %f\n\n", vehstate->tirestate_fl.roh);
    
    printf("Kappa FL: %f\n\n", vehstate->tirestate_fl.kappa);

    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    param_dtm_free(param_dtm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);


}

void test_vehbody(){

    printf("\n\e[1;37m\e[4;37mStart test_vehbody\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    Parameters_dtm *param_dtm;
    param_dtm = param_dtm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct Tireparameters *tireparam_fl = &param_dtm->tirefl;

    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct Tireparameters *tireparam_fr = &param_dtm->tirefr;

    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct Tireparameters *tireparam_rl = &param_dtm->tirerl;

    struct TireState *tirestate_rr = &vehstate->tirestate_rr;
    struct Tireparameters *tireparam_rr = &param_dtm->tirerr;

    struct Vehicleparameters *vehparam = &param_dtm->vehicleparameters;


    //#########################
    //### SET initial state ###
    //#########################
    
    double torquePerWheel, brakePressurePerWheel, timestep, v_initialize, psi_initialize;

    torquePerWheel          = 50.0;
    brakePressurePerWheel   = 0.0;

    timestep                = 0.02;

    v_initialize            = 0.0;
    psi_initialize          = 0.0;

    printf("Set Parameters\n\n");
    setParameters(param_dtm);

    printf("Set timestep to %.2f \n\n", timestep);
    param_dtm->vehicleparameters.timestep = timestep;

    printf("Set tireDriveTorque FL/FR to %.2f Nm\n\n", torquePerWheel);
    vehstate->tirestate_fl.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_fr.tireDriveTorque = torquePerWheel;
    
    printf("Set brakePressure_Pa FL/FR to %.2f bar\n\n", brakePressurePerWheel);
    vehstate->tirestate_fl.brakePressure_Pa = brakePressurePerWheel;

    printf("Set vx to %.2f m/s\n\n", v_initialize);
    vehstate->vx_veh_mps = v_initialize;
    
    printf("Set dpsi to %.2f rad/s\n\n", psi_initialize);
    vehstate->dpsi_veh = psi_initialize;

    vehstate->pos_ini_0[0] = 1.0;
    vehstate->pos_ini_0[1] = 1.0;

    printf("\n\t\e[1;37m\e[4;37mInitial State\e[0m\n\n");
    printvehstate(vehstate);

    //#############################
    //### CALL tested functions ###
    //#############################

    //ITERATION 1 
    printf("\n\t\e[1;37m\e[4;37mITERATION 1\e[0m\n\n");
    printf("\n\t\e[1;37m\e[4;37mCalcLongForce and Fz\e[0m\n\n");
    calcLongForce(param_dtm, vehstate);
    calcFz(param_dtm, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mWheelSpeeds and Slips\e[0m\n\n");
    calcWheelSpeed(param_dtm, vehstate);
    calcWheelSlips(param_dtm, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mMagicFormula\e[0m\n\n");
    magicFormula52_c(tireparam_fl, tirestate_fl, vehstate);
    magicFormula52_c(tireparam_fr, tirestate_fr, vehstate);
    magicFormula52_c(tireparam_rl, tirestate_rl, vehstate);
    magicFormula52_c(tireparam_rr, tirestate_rr, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mBodyAngles\e[0m\n\n");
    // calcBodyAngles(vehparam, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mBodyStatus\e[0m\n\n");
    // calcBodyStatus(param_dtm, vehparam, vehstate);
    printvehstate(vehstate);

    /*
    calcWheelSpeed(param_dtm, vehstate);
    calcWheelSlips(param_dtm, vehstate);
    */

    //ITERATION 2 
    printf("\n\t\e[1;37m\e[4;37mITERATION 2\e[0m\n\n");
    printf("\n\t\e[1;37m\e[4;37mCalcLongForce and Fz\e[0m\n\n");
    calcLongForce(param_dtm, vehstate);
    calcFz(param_dtm, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mWheelSpeeds and Slips\e[0m\n\n");
    calcWheelSpeed(param_dtm, vehstate);
    calcWheelSlips(param_dtm, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mMagicFormula\e[0m\n\n");
    magicFormula52_c(tireparam_fl, tirestate_fl, vehstate);
    magicFormula52_c(tireparam_fr, tirestate_fr, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mBodyAngles\e[0m\n\n");
    // calcBodyAngles(vehparam, vehstate);
    printvehstate(vehstate);

    printf("\n\t\e[1;37m\e[4;37mBodyStatus\e[0m\n\n");
    // calcBodyStatus(param_dtm, vehparam, vehstate);
    printvehstate(vehstate);

    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    param_dtm_free(param_dtm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);
}


void test_loop_vehstate(){

    printf("\n\e[1;37m\e[4;37mStart test_loop_vehsate\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    Parameters_dtm *param_dtm;
    param_dtm = param_dtm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct Tireparameters *tireparam_fl = &param_dtm->tirefl;

    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct Tireparameters *tireparam_fr = &param_dtm->tirefr;

    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct Tireparameters *tireparam_rl = &param_dtm->tirerl;

    struct TireState *tirestate_rr = &vehstate->tirestate_rr;
    struct Tireparameters *tireparam_rr = &param_dtm->tirerr;

    struct Vehicleparameters *vehparam = &param_dtm->vehicleparameters;


    //#########################
    //### SET initial state ###
    //#########################
    
    double torquePerWheel, brakePressurePerWheel, timestep, v_initialize, psi_initialize, dpsi_initialize, steeringangle, log_time;
    char logging, timing;
    int timecap, loop_steps, log_steps;
    struct timespec begin, end; 

    torquePerWheel          = 0.0;
    brakePressurePerWheel   = 0.0;

    timestep                = 0.0005;

    v_initialize            = 0.0;
    psi_initialize          = 0.0;
    dpsi_initialize         = 0.0;
    steeringangle           = 0.0;

    logging                 = '0';
    log_time                = 0.1;
    log_steps               = log_time/timestep;
    
    timecap                 = 800;
    loop_steps              = timecap/timestep;

    timing                  = '0';

    printf("Set Parameters\n\n");
    setParameters(param_dtm);

    printf("Set timestep to %.5f \n", timestep);
    param_dtm->vehicleparameters.timestep = timestep;

    printf("Activate(1)/ Deactivate(0) logging: %c \n", logging);

    printf("Set tireDriveTorque FL/FR to %.2f Nm\n", torquePerWheel);
    vehstate->tirestate_fl.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_fr.tireDriveTorque = torquePerWheel;
    
    printf("Set brakePressure_Pa FL/FR to %.2f bar\n", brakePressurePerWheel);
    vehstate->tirestate_fl.brakePressure_Pa = brakePressurePerWheel;

    printf("Set vx to %.2f m/s\n", v_initialize);
    vehstate->vx_veh_mps = v_initialize;
    
    printf("Set psi_ini to %.2f rad\n", psi_initialize);
    vehstate->psi_ini = psi_initialize;

    printf("Set dpsi_ini to %.2f rad/s\n", dpsi_initialize);
    vehstate->dpsi_ini = dpsi_initialize;

    printf("Set SteeringAngle to %.2f rad\n\n", steeringangle);
    vehstate->steeringangle = steeringangle;

    vehstate->xpos_ini0_m = 0.0;
    vehstate->ypos_ini0_m = 0.0;

    if(logging == '1'){
        create_logfile_dtm_angles(param_dtm, vehstate);
        // create_logfile_dtm_runge(param_dtm, vehstate);
    }

    //#############################
    //### CALL tested functions ###
    //#############################

    // if(timing == '1'){
    //     // CLOCK_REALTIME           return Wall time 
    //     // CLOCK_PROCESS_CPUTIME_ID return CPU time 
    //     clock_gettime() is not defined on WINDOWS !!! 
    //     clock_gettime(CLOCK_REALTIME, &begin);
    // }

    for(int i=0; i<loop_steps;i++){

        calcLongForce(param_dtm, vehstate);
        calcFz(param_dtm, vehstate);

        calcWheelSpeed(param_dtm, vehstate);
        calcWheelSlips(param_dtm, vehstate);

        // magicFormula52_c(tireparam_fl, tirestate_fl, vehstate);
        // magicFormula52_c(tireparam_fr, tirestate_fr, vehstate);
        // magicFormula52_c(tireparam_rl, tirestate_rl, vehstate);
        // magicFormula52_c(tireparam_rr, tirestate_rr, vehstate);
        Pacejka5Param(param_dtm, vehstate);
  
        //calcBodyAngles(vehparam, vehstate);
        // calcBodyAngles_new(vehparam, vehstate);
        
        // calcBodyStatus(param_dtm, vehparam, vehstate);
        // calcBodyStatus_runge(param_dtm, vehparam, vehstate);
        
        // calcDerivatives(param_dtm, vehparam, vehstate);
        // stepVehBody(param_dtm, vehparam, vehstate);
        // adams_bashforth(param_dtm, vehparam, vehstate);
        runge_kutta(param_dtm, vehparam, vehstate);

        if(logging == '1' && i%log_steps==0){
            write_logfile_dtm_angles(param_dtm, vehstate, i*param_dtm->vehicleparameters.timestep);
        }

        // if(i*param_dtm->vehicleparameters.timestep > 150.0){
        //     int j = 1;
        // }
        if(i*param_dtm->vehicleparameters.timestep > 3.0 && vehstate->tirestate_fl.tireDriveTorque < 40.0){
            vehstate->tirestate_fl.tireDriveTorque += timestep;
            vehstate->tirestate_fr.tireDriveTorque += timestep;
            vehstate->tirestate_rl.tireDriveTorque += timestep;
            vehstate->tirestate_rr.tireDriveTorque += timestep;        
        }else if(vehstate->tirestate_fl.tireDriveTorque != 0.0){
            vehstate->tirestate_fl.tireDriveTorque = 40.0;
            vehstate->tirestate_fr.tireDriveTorque = 40.0;
            vehstate->tirestate_rl.tireDriveTorque = 40.0;
            vehstate->tirestate_rr.tireDriveTorque = 40.0;        
        }
        
        if(i*param_dtm->vehicleparameters.timestep > 75.0 && i*param_dtm->vehicleparameters.timestep < 78.0){
            vehstate->steeringangle = 0.1;
        }else if(i*param_dtm->vehicleparameters.timestep > 90.0 && i*param_dtm->vehicleparameters.timestep < 93.0){
            vehstate->steeringangle = -0.1;
        }else if(i*param_dtm->vehicleparameters.timestep > 100.0){
            vehstate->steeringangle = 0.2;
        }
    }


    // if(timing == '1'){
    //     clock_gettime() is not defined on WINDOWS!!!
    //     clock_gettime(CLOCK_REALTIME, &end);
    //     long seconds = end.tv_sec - begin.tv_sec;
    //     long nanoseconds = end.tv_nsec - begin.tv_nsec;
    //     double elapsed = seconds + nanoseconds*1e-9;
        
    //     printf("Time measured: %.3f seconds.\n", elapsed);
    // }
    
    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    param_dtm_free(param_dtm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);

}


void dtm_brake(){
    printf("\n\e[1;37m\e[4;37mStart test dtm_brake\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    Parameters_dtm *param_dtm;
    param_dtm = param_dtm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct Tireparameters *tireparam_fl = &param_dtm->tirefl;

    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct Tireparameters *tireparam_fr = &param_dtm->tirefr;

    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct Tireparameters *tireparam_rl = &param_dtm->tirerl;

    struct TireState *tirestate_rr = &vehstate->tirestate_rr;
    struct Tireparameters *tireparam_rr = &param_dtm->tirerr;

    struct Vehicleparameters *vehparam = &param_dtm->vehicleparameters;


    //#########################
    //### SET initial state ###
    //#########################
    
    double torquePerWheel, brakePressurePerWheel, timestep, v_initialize, psi_initialize, dpsi_initialize, steeringangle, log_time;
    char logging, timing;
    int timecap, loop_steps, log_steps;
    struct timespec begin, end; 

    torquePerWheel          = 0.0;
    brakePressurePerWheel   = 0.0;

    timestep                = 0.0001;

    v_initialize            = 0.0;
    psi_initialize          = 0.0;
    dpsi_initialize         = 0.0;
    steeringangle           = 0.0;

    logging                 = '1';
    log_time                = 0.1;
    log_steps               = log_time/timestep;
    
    timecap                 = 200;
    loop_steps              = timecap/timestep;

    timing                  = '1';

    printf("Set Parameters\n\n");
    setParameters(param_dtm);

    printf("Set timestep to %.5f \n", timestep);
    param_dtm->vehicleparameters.timestep = timestep;

    printf("Activate(1)/ Deactivate(0) logging: %c \n", logging);

    printf("Set tireDriveTorque FL/FR to %.2f Nm\n", torquePerWheel);
    vehstate->tirestate_fl.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_fr.tireDriveTorque = torquePerWheel;
    
    printf("Set brakePressure_Pa FL/FR to %.2f bar\n", brakePressurePerWheel);
    vehstate->tirestate_fl.brakePressure_Pa = brakePressurePerWheel;

    printf("Set vx to %.2f m/s\n", v_initialize);
    vehstate->vx_veh_mps = v_initialize;
    
    printf("Set psi_ini to %.2f rad\n", psi_initialize);
    vehstate->psi_ini = psi_initialize;

    printf("Set dpsi_ini to %.2f rad/s\n", dpsi_initialize);
    vehstate->dpsi_ini = dpsi_initialize;

    printf("Set SteeringAngle to %.2f rad\n\n", steeringangle);
    vehstate->steeringangle = steeringangle;

    vehstate->xpos_ini0_m = 0.0;
    vehstate->ypos_ini0_m = 0.0;

    if(logging == '1'){
        create_logfile_dtm(param_dtm, vehstate);
        // create_logfile_dtm_runge(param_dtm, vehstate);
    }

    //#############################
    //### CALL tested functions ###
    //#############################

    // if(timing == '1'){
    //     // CLOCK_REALTIME           return Wall time 
    //     // CLOCK_PROCESS_CPUTIME_ID return CPU time 
    //     //clock_gettime() is not defined on WINDOWS!!!
    //     clock_gettime(CLOCK_REALTIME, &begin);
    // }

    for(int i=0; i<loop_steps;i++){

        calcLongForce(param_dtm, vehstate);
        calcFz(param_dtm, vehstate);

        calcWheelSpeed(param_dtm, vehstate);
        calcWheelSlips(param_dtm, vehstate);

        // magicFormula52_c(tireparam_fl, tirestate_fl, vehstate);
        // magicFormula52_c(tireparam_fr, tirestate_fr, vehstate);
        // magicFormula52_c(tireparam_rl, tirestate_rl, vehstate);
        // magicFormula52_c(tireparam_rr, tirestate_rr, vehstate);
        Pacejka5Param(param_dtm, vehstate);
  
        // calcDerivatives(param_dtm, vehparam, vehstate);
        // stepVehBody(param_dtm, vehparam, vehstate);
        // adams_bashforth(param_dtm, vehparam, vehstate);
        runge_kutta(param_dtm, vehparam, vehstate);

        if(logging == '1' && i%log_steps==0){
            write_logfile_dtm(param_dtm, vehstate, i*param_dtm->vehicleparameters.timestep);
        }

        if(i*param_dtm->vehicleparameters.timestep > 3.0 && vehstate->tirestate_fl.tireDriveTorque < 50.0){
            vehstate->tirestate_fl.tireDriveTorque += timestep*5.0;
            vehstate->tirestate_fr.tireDriveTorque += timestep*5.0;
            vehstate->tirestate_rl.tireDriveTorque += timestep*5.0;
            vehstate->tirestate_rr.tireDriveTorque += timestep*5.0;        
        }else if(vehstate->tirestate_fl.tireDriveTorque != 0.0){
            vehstate->tirestate_fl.tireDriveTorque = 50.0;
            vehstate->tirestate_fr.tireDriveTorque = 50.0;
            vehstate->tirestate_rl.tireDriveTorque = 50.0;
            vehstate->tirestate_rr.tireDriveTorque = 50.0;        
        }
        
        // if(i*param_dtm->vehicleparameters.timestep > 300.0){
        //     vehstate->tirestate_fl.tireDriveTorque = 0.0;
        //     vehstate->tirestate_fr.tireDriveTorque = 0.0;
        //     vehstate->tirestate_rl.tireDriveTorque = 0.0;
        //     vehstate->tirestate_rr.tireDriveTorque = 0.0; 

        //     vehstate->tirestate_fl.brakePressure_Pa = 10.0*1.0E5; 
        //     vehstate->tirestate_fr.brakePressure_Pa = 10.0*1.0E5; 
        //     vehstate->tirestate_rl.brakePressure_Pa = 10.0*1.0E5; 
        //     vehstate->tirestate_rr.brakePressure_Pa = 10.0*1.0E5; 
        // }
        
        if(i*param_dtm->vehicleparameters.timestep > 75.0 && i*param_dtm->vehicleparameters.timestep < 78.0){
            vehstate->steeringangle = 0.1;
        }else if(i*param_dtm->vehicleparameters.timestep > 90.0 && i*param_dtm->vehicleparameters.timestep < 93.0){
            vehstate->steeringangle = -0.1;
        }else if(i*param_dtm->vehicleparameters.timestep > 100.0){
            vehstate->steeringangle = 0.2;
        }
    }


    // if(timing == '1'){
    //     clock_gettime() is not defined on WINDOWS!!!
    //     clock_gettime(CLOCK_REALTIME, &end);
    //     long seconds = end.tv_sec - begin.tv_sec;
    //     long nanoseconds = end.tv_nsec - begin.tv_nsec;
    //     double elapsed = seconds + nanoseconds*1e-9;
        
    //     printf("Time measured: %.3f seconds.\n", elapsed);
    // }
    
    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree Param_dtm\n");
    param_dtm_free(param_dtm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);
}



void printvehstate(struct VehicleState* vehstate){
    
    //#####################
    //### VEHICLE STATE ###
    //#####################

    printf("\n\t\e[1;37mVEHSTATE\e[0m\n\n");

    printf("PosX Vehicle:\t\t%f \n", vehstate->pos_ini_0[0]);
    printf("PosY Vehicle:\t\t%f \n\n", vehstate->pos_ini_0[1]);

    printf("VX Vehicle:\t\t%f \n", vehstate->vx_veh_mps);
    printf("VY Vehicle:\t\t%f \n\n", vehstate->vy_veh_mps);
    
    printf("dPsi Vehicle:\t\t%f \n", vehstate->dpsi_veh);
    printf("dTheta Vehicle:\t\t%f \n", vehstate->dtheta_veh);
    printf("dPhi Vehicle:\t\t%f \n\n", vehstate->dphi_veh);

    printf("Psi Vehicle:\t\t%f °\n", vehstate->psi_veh*M_PI/180.0);
    printf("Theta Vehicle:\t\t%f °\n", vehstate->theta_veh*M_PI/180.0);
    printf("Phi Vehicle:\t\t%f °\n\n", vehstate->phi_veh*M_PI/180.0);


    //##################
    //### TIRE STATE ###
    //##################

    printf("\n\t\e[1;37mTIRESTATE\e[0m\n\n");
    /*
    printf("tireDriveTorque FL:\t%f \n", vehstate->tirestate_fl.tireDriveTorque);
    printf("tireBrakeTorque FL:\t%f \n\n", vehstate->tirestate_fl.tireBrakeTorque);

    printf("tireDriveTorque FR:\t%f \n", vehstate->tirestate_fr.tireDriveTorque);
    printf("tireBrakeTorque FR:\t%f \n\n", vehstate->tirestate_fr.tireBrakeTorque);
    */

    printf("Fx FL:\t\t\t%f \n", vehstate->tirestate_fl.fx);
    printf("Fy FL:\t\t\t%f \n", vehstate->tirestate_fl.fy);
    printf("Fz FL:\t\t\t%f \n\n", vehstate->tirestate_fl.fz);

    printf("Fx FR:\t\t\t%f \n", vehstate->tirestate_fr.fx);
    printf("Fy FR:\t\t\t%f \n", vehstate->tirestate_fr.fy);
    printf("Fz FR:\t\t\t%f \n\n", vehstate->tirestate_fr.fz);

    printf("WheelSpeed FL:\t\t%f \n", vehstate->tirestate_fl.omega_radps);
    printf("WheelSpeed FR:\t\t%f \n", vehstate->tirestate_fr.omega_radps);
    printf("WheelSpeed RL:\t\t%f \n", vehstate->tirestate_rl.omega_radps);
    printf("WheelSpeed RR:\t\t%f \n\n", vehstate->tirestate_rr.omega_radps);

    printf("Kappa FL:\t\t%f \n", vehstate->tirestate_fl.kappa);
    printf("Kappa FR:\t\t%f \n", vehstate->tirestate_fr.kappa);
    printf("Kappa RL:\t\t%f \n", vehstate->tirestate_rl.kappa);
    printf("Kappa RR:\t\t%f \n\n", vehstate->tirestate_rr.kappa);

    printf("Alpha FL:\t\t%f \n", vehstate->tirestate_fl.alpha);
    printf("Alpha FR:\t\t%f \n\n", vehstate->tirestate_fr.alpha);
    


}

//TODO for limitedWheelSpeed == 0 and vehstate->tirestate_fl.roh == 0 is the brake torqe = 0 !! 


void test_stm(){

    printf("\n\e[1;37m\e[4;37mStart test_stm\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    SingleTrackModel *stm;
    stm = stm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct TireState *tirestate_rr = &vehstate->tirestate_rr;


    //#########################
    //### SET initial state ###
    //#########################
    
    double torquePerWheel, brakePressurePerWheel, timestep, v_initialize, psi_initialize, omegaini, steeringangle;
    double fx_max = 0.0, i_fx_max = 0.0;
    char logging;

    torquePerWheel          = 0.0;
    brakePressurePerWheel   = 0.0;

    timestep                = 0.0001;

    v_initialize            = 0.0;
    psi_initialize          = 0.0;
    omegaini                = 0.0;
    steeringangle           = 0.0;

    logging                 = '1';

    printf("Set Parameters\n\n");
    setParameters_stm(stm);

    printf("Set timestep to %06.3f \n\n", timestep);
    stm->timestep = timestep;

    printf("Activate(1)/ Deactivate(0) logging: %c \n", logging);

    printf("Set tireDriveTorque FL/FR to %.2f Nm\n\n", torquePerWheel);
    vehstate->tirestate_fl.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_fr.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_rl.tireDriveTorque = torquePerWheel;
    vehstate->tirestate_rr.tireDriveTorque = torquePerWheel;
    
    printf("Set brakePressure_Pa FL/FR to %.2f bar\n\n", brakePressurePerWheel);
    vehstate->tirestate_fl.brakePressure_Pa = brakePressurePerWheel;

    printf("Set vx to %.2f m/s\n\n", v_initialize);
    vehstate->vx_veh_mps = v_initialize;
    
    printf("Set dpsi to %.2f rad/s\n\n", psi_initialize);
    vehstate->dpsi_veh = psi_initialize;

    vehstate->pos_ini_0[0] = 0.0;
    vehstate->pos_ini_0[1] = 0.0;

    printf("Set inital Wheelspeed to %.2f\n\n", omegaini);
    vehstate->tirestate_fl.omega_radps = omegaini;
    vehstate->tirestate_fr.omega_radps = omegaini;
    vehstate->tirestate_rl.omega_radps = omegaini;
    vehstate->tirestate_rr.omega_radps = omegaini;
    
    printf("Set SteeringAngle to %.2f rad\n\n", steeringangle);
    vehstate->steeringangle = steeringangle;

    // printf("\n\t\e[1;37m\e[4;37mInitial State\e[0m\n\n");
    // printvehstate(vehstate);

    
    if(logging == '1'){
        printf("Create Logfile\n\n");
        create_logfile_stm(stm, vehstate);
    }
    //#############################
    //### CALL tested functions ###
    //#############################

    for(int i=0; i<=1000000;i++){
            
        calcLongForce_stm(stm, vehstate);
        vehicleModel(stm, vehstate);
        integrate_update_stm(stm, vehstate);

        if(logging == '1' && i%100 == 0){
            write_logfile_stm(stm, vehstate, i*stm->timestep);
        }

        
        if(i*stm->timestep > 3.0 && vehstate->tirestate_fl.tireDriveTorque < 40.0){
            vehstate->tirestate_fl.tireDriveTorque += 0.001;
            vehstate->tirestate_fr.tireDriveTorque += 0.001;
            vehstate->tirestate_rl.tireDriveTorque += 0.001;
            vehstate->tirestate_rr.tireDriveTorque += 0.001;        
        }else if(vehstate->tirestate_fl.tireDriveTorque != 0.0){
            vehstate->tirestate_fl.tireDriveTorque = 40.0;
            vehstate->tirestate_fr.tireDriveTorque = 40.0;
            vehstate->tirestate_rl.tireDriveTorque = 40.0;
            vehstate->tirestate_rr.tireDriveTorque = 40.0;        
        }
        
       
        if(i*stm->timestep > 75.0 && i*stm->timestep < 78.0){
            vehstate->steeringangle = 0.1;
        }else if(i*stm->timestep > 78.0){
            vehstate->steeringangle = 0.0;
        }


       /*
       //save maximum fx FL 
        if(vehstate->tirestate_fl.fx > fx_max){
            fx_max = vehstate->tirestate_fl.fx;
            i_fx_max = i;
        }
        */

    }

    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree stm\n");
    stm_free(stm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);

}

void onestep_test(){


    printf("\n\e[1;37m\e[4;37mStart onestep_test\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    SingleTrackModel *stm;
    stm = stm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct TireState *tirestate_rr = &vehstate->tirestate_rr;


    //#########################
    //### SET initial state ###
    //#########################
    
    double torquePerWheel, brakePressurePerWheel, timestep, v_initialize, psi_initialize, omegaini, wheel_angle, lambda_ini, alpha_ini;

    torquePerWheel          = 20.0;
    brakePressurePerWheel   = 0.0;

    timestep                = 0.002;

    v_initialize            = 3.0;

    psi_initialize          = 0.0;
    omegaini                = 2.5;

    wheel_angle             = 0.0;

    lambda_ini              = 0.05;
    alpha_ini               = 0.0;

    printf("Set Parameters\n\n");
    setParameters_stm(stm);

    printf("Set timestep to %.2f \n\n", timestep);
    stm->timestep = timestep;

    printf("Set fx_powertrain FL/FR to %.2f Nm\n\n", torquePerWheel);
    vehstate->tirestate_fl.fx_powertrain = torquePerWheel;
    vehstate->tirestate_fr.fx_powertrain = torquePerWheel;
    vehstate->tirestate_rl.fx_powertrain = torquePerWheel;
    vehstate->tirestate_rr.fx_powertrain = torquePerWheel;
    
    printf("Set brakePressure_Pa FL/FR to %.2f bar\n\n", brakePressurePerWheel);
    vehstate->tirestate_fl.brakePressure_Pa = brakePressurePerWheel;

    printf("Set vx to %.2f m/s\n\n", v_initialize);
    vehstate->vx_veh_mps = v_initialize;
    
    printf("Set dpsi to %.2f rad/s\n\n", psi_initialize);
    vehstate->dpsi_veh = psi_initialize;

    vehstate->pos_ini_0[0] = 0.0;
    vehstate->pos_ini_0[1] = 0.0;

    printf("Set inital Wheelspeed to %.2f\n\n", omegaini);
    vehstate->tirestate_fl.roh = omegaini;
    vehstate->tirestate_fr.roh = omegaini;
    vehstate->tirestate_rl.roh = omegaini;
    vehstate->tirestate_rr.roh = omegaini;
    
    printf("Set steering angle to %.2f\n\n", wheel_angle);
    vehstate->steeringangle = wheel_angle;

    printf("Set inital slip lambda to %.2f\n\n", lambda_ini);
    vehstate->tirestate_fl.lambda_stm0 = lambda_ini;
    vehstate->tirestate_fr.lambda_stm0 = lambda_ini;
    vehstate->tirestate_rl.lambda_stm0 = lambda_ini;
    vehstate->tirestate_rr.lambda_stm0 = lambda_ini;


    printf("Set inital slip angle alpha to %.2f\n\n", alpha_ini);
    vehstate->tirestate_fl.alpha_stm0 = alpha_ini;
    vehstate->tirestate_fr.alpha_stm0 = alpha_ini;
    vehstate->tirestate_rl.alpha_stm0 = alpha_ini;
    vehstate->tirestate_rr.alpha_stm0 = alpha_ini;
    //printf("\n\t\e[1;37m\e[4;37mInitial State\e[0m\n\n");
    //printvehstate(vehstate);

    //#############################
    //### CALL tested functions ###
    //#############################
    //calcLongForce_stm(stm, vehstate);
    
    
    vehicleModel(stm, vehstate);

    printf("diffs[0] dvx : \t\t%.15f\n", stm->m_diffS[3]);
    printf("diffs[1] dvy : \t\t%.15f\n", stm->m_diffS[4]);
    printf("diffs[2] ddpsi : \t%.15f\n", stm->m_diffS[5]);
    printf("diffs[3] omega[0] : \t%.15f\n", stm->m_diffS[6]);
    printf("diffs[4] omega[1] : \t%.15f\n", stm->m_diffS[7]);
    printf("diffs[5] omega[2] : \t%.15f\n", stm->m_diffS[8]);
    printf("diffs[6] omega[3] : \t%.15f\n", stm->m_diffS[9]);
    printf("diffs[7] dlambda[0] : \t%.15f\n", stm->m_diffS[10]);
    printf("diffs[8] dlambda[1] : \t%.15f\n", stm->m_diffS[11]);
    printf("diffs[9] dlambda[2] : \t%.15f\n", stm->m_diffS[12]);
    printf("diffs[10] dlambda[3] : \t%.15f\n", stm->m_diffS[13]);
    printf("diffs[11] dalpha[0] : \t%.15f\n", stm->m_diffS[14]);
    printf("diffs[12] dalpha[1] : \t%.15f\n", stm->m_diffS[15]);
    printf("diffs[13] dalpha[2] : \t%.15f\n", stm->m_diffS[16]);
    printf("diffs[14] dalpha[3] : \t%.15f\n", stm->m_diffS[17]);

    /*
    stm->m_diffS[3] = dvx; 
    stm->m_diffS[4] = dvy;
    stm->m_diffS[5] = ddPsi;
    stm->m_diffS[6] = domega[0];
    stm->m_diffS[7] = domega[1];
    stm->m_diffS[8] = domega[2];
    stm->m_diffS[9] = domega[3];
    stm->m_diffS[10] = dlambda[0];
    stm->m_diffS[11] = dlambda[1];
    stm->m_diffS[12] = dlambda[2];
    stm->m_diffS[13] = dlambda[3];
    stm->m_diffS[14] = dalpha[0];
    stm->m_diffS[15] = dalpha[1];
    stm->m_diffS[16] = dalpha[2];
    stm->m_diffS[17] = dalpha[3];
    */

    //####################
    //### FREE Structs ###
    //####################

    printf("\nFree stm\n");
    stm_free(stm);

    printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);

}


//###############
//### LOGGING ###
//###############

void create_logfile_stm(SingleTrackModel *stm, struct VehicleState* vehstate){
    
    FILE *logfile;

    time_t rawtime;
    struct tm *timeinfo;

    char day[3], month[3], year[5];
    char hour[3], min[3], sec[5];
    char filename[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //printf ("Current local time and date: %d.%d.%d-%d:%d:%d\n", timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

    sprintf(day, "%02d", timeinfo->tm_mday);
    sprintf(month, "%02d", timeinfo->tm_mon+1);
    sprintf(year, "%4d", timeinfo->tm_year+1900);
    sprintf(hour, "%02d", timeinfo->tm_hour);
    sprintf(min, "%02d", timeinfo->tm_min);
    sprintf(sec, "%02d", timeinfo->tm_sec);

    strcpy(filename, "../log/");
    strcat(filename,day);
    strcat(filename,".");
    strcat(filename,month);
    strcat(filename,".");
    strcat(filename,year);
    strcat(filename,"-");
    strcat(filename,hour);
    strcat(filename,":");
    strcat(filename,min);
    strcat(filename,":");
    strcat(filename,sec);
    strcat(filename,"_STM.csv");

    //copy name to struct 
    strcpy(stm->logfile_name, filename);

    //write initial state to logfile    
    logfile = fopen(stm->logfile_name, "a");
    
    fprintf(logfile, "Set timestep to \t\t\t%08.5f s\n", stm->timestep);
    fprintf(logfile, "Set vx to \t\t\t\t\t%.2f m/s\n", vehstate->vx_veh_mps);
    fprintf(logfile, "Set SteeringAngle to \t\t%.2f rad\n", vehstate->steeringangle);
    fprintf(logfile, "Set tireDriveTorque to \t\t%.2f Nm\n", vehstate->tirestate_fl.tireDriveTorque);
    fprintf(logfile, "Set brakePressure_Pa FL/FR to \t%.2f bar\n\n", vehstate->tirestate_fl.brakePressure_Pa);

    fprintf(logfile, "time_s, xpos_m, ypos_m, psi_rad, vx_mps, vy_mps, dpsi_radps, ax_mps2, ay_mps2,"
        "omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        "lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        "alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        "Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        "Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        "FxPowertrain_FL_N, FxPowertrain_FR_N, FxPowertrain_RL_N, FxPowertrain_RR_N, " 
        "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        "SteeringAngle_rad, ddPsi_radps2\n");

    fclose(logfile);
}


void write_logfile_stm(SingleTrackModel *stm, struct VehicleState* vehstate, double timestep){

    FILE *logfile;

    logfile = fopen(stm->logfile_name, "a");
    //fprintf(logfile, "%07.3f vx:\t%02.2f\t FL fx:\t%f\n",timestep,vehstate->vx_veh_mps, vehstate->tirestate_fl.fx);
    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f, " 
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f\n",
        timestep, vehstate->pos_ini_0[0], vehstate->pos_ini_0[1], vehstate->psi_veh, vehstate->vx_veh_mps, vehstate->vy_veh_mps, vehstate->dpsi_veh, vehstate->ax_veh_mps2, vehstate->ay_veh_mps2,
        vehstate->tirestate_fl.omega_radps, vehstate->tirestate_fr.omega_radps, vehstate->tirestate_rl.omega_radps, vehstate->tirestate_rr.omega_radps,
        vehstate->tirestate_fl.kappa, vehstate->tirestate_fr.kappa, vehstate->tirestate_rl.kappa, vehstate->tirestate_rr.kappa,
        vehstate->tirestate_fl.alpha, vehstate->tirestate_fr.alpha, vehstate->tirestate_rl.alpha, vehstate->tirestate_rr.alpha,
        vehstate->tirestate_fl.fx, vehstate->tirestate_fr.fx, vehstate->tirestate_rl.fx, vehstate->tirestate_rr.fx,
        vehstate->tirestate_fl.fy, vehstate->tirestate_fr.fy, vehstate->tirestate_rl.fy, vehstate->tirestate_rr.fy,
        vehstate->tirestate_fl.fx_powertrain, vehstate->tirestate_fr.fx_powertrain, vehstate->tirestate_rl.fx_powertrain, vehstate->tirestate_rr.fx_powertrain,
        vehstate->tirestate_fl.brakePressure_Pa, vehstate->tirestate_fr.brakePressure_Pa, vehstate->tirestate_rl.brakePressure_Pa, vehstate->tirestate_rr.brakePressure_Pa,
        vehstate->steeringangle, stm->m_diffS[5]);
    
    fclose(logfile);

}


void create_logfile_dtm(Parameters_dtm *param_dtm, struct VehicleState* vehstate){
    
    FILE *logfile;

    time_t rawtime;
    struct tm *timeinfo;

    char day[3], month[3], year[5];
    char hour[3], min[3], sec[5];
    char filename[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    sprintf(day, "%02d", timeinfo->tm_mday);
    sprintf(month, "%02d", timeinfo->tm_mon+1);
    sprintf(year, "%4d", timeinfo->tm_year+1900);
    sprintf(hour, "%02d", timeinfo->tm_hour);
    sprintf(min, "%02d", timeinfo->tm_min);
    sprintf(sec, "%02d", timeinfo->tm_sec);

    strcpy(filename, "../log/");
    strcat(filename,year);
    strcat(filename,".");
    strcat(filename,month);
    strcat(filename,".");
    strcat(filename,day);
    strcat(filename,"-");
    strcat(filename,hour);
    strcat(filename,":");
    strcat(filename,min);
    strcat(filename,":");
    strcat(filename,sec);
    strcat(filename,"_DTM.csv");

    //copy name to struct 
    strcpy(param_dtm->logfile_name, filename);

    //write initial state to logfile    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "Set timestep to \t\t\t%08.5f s\n", param_dtm->vehicleparameters.timestep);
    fprintf(logfile, "Set vx to \t\t\t\t\t%.2f m/s\n", vehstate->vx_veh_mps);
    fprintf(logfile, "Set SteeringAngle to \t\t%.2f rad\n", vehstate->steeringangle);
    fprintf(logfile, "Set tireDriveTorque to \t\t%.2f Nm\n", vehstate->tirestate_fl.tireDriveTorque);
    fprintf(logfile, "Set brakePressure_Pa FL/FR to \t%.2f bar\n\n", vehstate->tirestate_fl.brakePressure_Pa);

    fprintf(logfile, "time_s, xpos_m, ypos_m, psi_rad, vx_mps, vy_mps, dpsi_radps, ax_mps2, ay_mps2,"
        "omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        "lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        "alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        "Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        "Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        "FxPowertrain_FL_N, FxPowertrain_FR_N, FxPowertrain_RL_N, FxPowertrain_RR_N, " 
        "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        "SteeringAngle_rad\n");

    fclose(logfile);

}


void write_logfile_dtm(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep){

    FILE *logfile;
    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f, " 
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f\n",
        timestep, vehstate->xpos_ini0_m, vehstate->ypos_ini0_m, vehstate->psi_veh, vehstate->vx_veh_mps, vehstate->vy_veh_mps, vehstate->dpsi_veh, vehstate->ax_veh_mps2, vehstate->ay_veh_mps2,
        vehstate->tirestate_fl.omega_radps, vehstate->tirestate_fr.omega_radps, vehstate->tirestate_rl.omega_radps, vehstate->tirestate_rr.omega_radps,
        vehstate->tirestate_fl.kappa, vehstate->tirestate_fr.kappa, vehstate->tirestate_rl.kappa, vehstate->tirestate_rr.kappa,
        vehstate->tirestate_fl.alpha, vehstate->tirestate_fr.alpha, vehstate->tirestate_rl.alpha, vehstate->tirestate_rr.alpha,
        vehstate->tirestate_fl.fx, vehstate->tirestate_fr.fx, vehstate->tirestate_rl.fx, vehstate->tirestate_rr.fx,
        vehstate->tirestate_fl.fy, vehstate->tirestate_fr.fy, vehstate->tirestate_rl.fy, vehstate->tirestate_rr.fy,
        vehstate->tirestate_fl.fx_powertrain, vehstate->tirestate_fr.fx_powertrain, vehstate->tirestate_rl.fx_powertrain, vehstate->tirestate_rr.fx_powertrain,
        vehstate->tirestate_fl.brakePressure_Pa, vehstate->tirestate_fr.brakePressure_Pa, vehstate->tirestate_rl.brakePressure_Pa, vehstate->tirestate_rr.brakePressure_Pa,
        vehstate->steeringangle);

    fclose(logfile);
}


void create_logfile_dtm_angles(Parameters_dtm *param_dtm, struct VehicleState* vehstate){
    FILE *logfile;

    time_t rawtime;
    struct tm *timeinfo;

    char day[3], month[3], year[5];
    char hour[3], min[3], sec[5];
    char filename[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    sprintf(day, "%02d", timeinfo->tm_mday);
    sprintf(month, "%02d", timeinfo->tm_mon+1);
    sprintf(year, "%4d", timeinfo->tm_year+1900);
    sprintf(hour, "%02d", timeinfo->tm_hour);
    sprintf(min, "%02d", timeinfo->tm_min);
    sprintf(sec, "%02d", timeinfo->tm_sec);

    strcpy(filename, "../log/");
    strcat(filename,year);
    strcat(filename,".");
    strcat(filename,month);
    strcat(filename,".");
    strcat(filename,day);
    strcat(filename,"-");
    strcat(filename,hour);
    strcat(filename,":");
    strcat(filename,min);
    strcat(filename,":");
    strcat(filename,sec);
    strcat(filename,"_DTM_angles.csv");

    //copy name to struct 
    strcpy(param_dtm->logfile_name, filename);

    //write initial state to logfile    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "Set timestep to \t\t\t%08.5f s\n", param_dtm->vehicleparameters.timestep);
    fprintf(logfile, "Set vx to \t\t\t\t\t%.2f m/s\n", vehstate->vx_veh_mps);
    fprintf(logfile, "Set SteeringAngle to \t\t%.2f rad\n", vehstate->steeringangle);
    fprintf(logfile, "Set tireDriveTorque to \t\t%.2f Nm\n", vehstate->tirestate_fl.tireDriveTorque);
    fprintf(logfile, "Set brakePressure_Pa FL/FR to \t%.2f bar\n\n", vehstate->tirestate_fl.brakePressure_Pa);

    fprintf(logfile, "time_s, xpos_ini_m, ypos_ini_m, psi_ini_rad, vx_veh_mps, vy_veh_mps, dpsi_ini_radps, ax_veh_mps2, ay_veh_mps2,"
        "omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        "lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        "alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        "Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        "Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        "theta_veh_rad, phi_veh_rad, dtheta_veh_radps, dphi_veh_radps, "
        "theta_ini_rad, phi_ini_rad, dtheta_ini_radps, dphi_ini_radps, "
        "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        "SteeringAngle_rad, ddPsi_veh_radps2 ddtheta_veh_radps2, ddphi_veh_radps2\n");

    fclose(logfile);
}


void write_logfile_dtm_angles(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep){

    FILE *logfile;
    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f, " 
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, ",
        timestep, vehstate->xpos_ini0_m, vehstate->ypos_ini0_m, vehstate->psi_ini, vehstate->vx_veh_mps, vehstate->vy_veh_mps, vehstate->dpsi_ini, vehstate->ax_veh_mps2, vehstate->ay_veh_mps2,
        vehstate->tirestate_fl.omega_radps, vehstate->tirestate_fr.omega_radps, vehstate->tirestate_rl.omega_radps, vehstate->tirestate_rr.omega_radps,
        vehstate->tirestate_fl.kappa, vehstate->tirestate_fr.kappa, vehstate->tirestate_rl.kappa, vehstate->tirestate_rr.kappa,
        vehstate->tirestate_fl.alpha, vehstate->tirestate_fr.alpha, vehstate->tirestate_rl.alpha, vehstate->tirestate_rr.alpha,
        vehstate->tirestate_fl.fx, vehstate->tirestate_fr.fx, vehstate->tirestate_rl.fx, vehstate->tirestate_rr.fx,
        vehstate->tirestate_fl.fy, vehstate->tirestate_fr.fy, vehstate->tirestate_rl.fy, vehstate->tirestate_rr.fy);

    fprintf(logfile,
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, \n",
        vehstate->theta_veh, vehstate->phi_veh, vehstate->dtheta_veh, vehstate->dphi_veh,
        vehstate->theta_ini, vehstate->phi_ini, vehstate->dtheta_ini, vehstate->dphi_ini,
        vehstate->tirestate_fl.brakePressure_Pa, vehstate->tirestate_fr.brakePressure_Pa, vehstate->tirestate_rl.brakePressure_Pa, vehstate->tirestate_rr.brakePressure_Pa,
        vehstate->steeringangle, vehstate->ddpsi_veh, vehstate->ddtheta_veh, vehstate->ddphi_veh);



    fclose(logfile);
}


void create_logfile_dtm_runge(Parameters_dtm *param_dtm, struct VehicleState* vehstate){
    FILE *logfile;

    time_t rawtime;
    struct tm *timeinfo;

    char day[3], month[3], year[5];
    char hour[3], min[3], sec[5];
    char filename[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);


    sprintf(day, "%02d", timeinfo->tm_mday);
    sprintf(month, "%02d", timeinfo->tm_mon+1);
    sprintf(year, "%4d", timeinfo->tm_year+1900);
    sprintf(hour, "%02d", timeinfo->tm_hour);
    sprintf(min, "%02d", timeinfo->tm_min);
    sprintf(sec, "%02d", timeinfo->tm_sec);

    strcpy(filename, "../log/");
    strcat(filename,year);
    strcat(filename,".");
    strcat(filename,month);
    strcat(filename,".");
    strcat(filename,day);
    strcat(filename,"-");
    strcat(filename,hour);
    strcat(filename,":");
    strcat(filename,min);
    strcat(filename,":");
    strcat(filename,sec);
    strcat(filename,"_DTM_movement.csv");

    //copy name to struct 
    strcpy(param_dtm->logfile_name, filename);

    //write initial state to logfile    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "Set timestep to \t\t\t%08.5f s\n", param_dtm->vehicleparameters.timestep);
    fprintf(logfile, "Set vx to \t\t\t\t\t%.2f m/s\n", vehstate->vx_veh_mps);
    fprintf(logfile, "Set SteeringAngle to \t\t%.2f rad\n", vehstate->steeringangle);
    fprintf(logfile, "Set tireDriveTorque to \t\t%.2f Nm\n", vehstate->tirestate_fl.tireDriveTorque);
    fprintf(logfile, "Set brakePressure_Pa FL/FR to \t%.2f bar\n\n", vehstate->tirestate_fl.brakePressure_Pa);

    fprintf(logfile, "time_s, xpos_ini_m, ypos_ini_m, psi_ini_rad, vx_veh_mps, vy_veh_mps, dpsi_ini_radps, ax_veh_mps2, ay_veh_mps2, "
        "xpos_runge_m, ypos_runge_m, vx_runge_mps, vy_runge_mps, ax_runge_mps2, ay_runge_mps2, "
        "SteeringAngle_rad\n");

    fclose(logfile);


}


void write_logfile_dtm_runge(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep){


    FILE *logfile;
    
    logfile = fopen(param_dtm->logfile_name, "a");
    
    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f, " 
        "%f, %f, %f, %f, %f, %f,"
        "%f\n",
        timestep, vehstate->xpos_ini0_m, vehstate->ypos_ini0_m, vehstate->psi_ini, vehstate->vx_veh_mps, vehstate->vy_veh_mps, vehstate->dpsi_ini, vehstate->ax_veh_mps2, vehstate->ay_veh_mps2,
        vehstate->runge_x, vehstate->runge_y, vehstate->runge_vx, vehstate->runge_vy, vehstate->runge_ax, vehstate->runge_ay,
        vehstate->steeringangle);

    fclose(logfile);

}

