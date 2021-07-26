#ifndef SINGLETRACKMODEL_H
#define SINGLETRACKMODEL_H

#include "VehicleState.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
struct wheelSlip{
    double lambda_perc[4];
    double alpha[4];
};

struct tireForce{
    double FxT[4];
    double FyT[4];
};
*/


typedef struct SingleTrackModel
{
    //calculation results 
    double m_exactMeasurements[12];
    double m_diffS[18];

    //path and logfile name 
    char cwd[200];
    char logfile_name[50];

    //Parameters
    double m_vx_min;
    double m_roh;
    double timestep;

    //VehicleData
    double m_Vehicle_kg;
    double l_WheelbaseF_m;
    double l_WheelbaseTotal_m;
    double w_GeomCenterlineToCOG_m;
    double h_AxlePlaneToCOG_m;
    double w_TrackF_m;
    double w_TrackR_m; 
    double I_K_Vehicle_kgm2[3][3];

    //Aerodynamics
    double A_LongitudinalDrag_m2;
    double cw_LongitudinalDrag;
    double cl_LongitudinalLift;
    double cpm_LongDragPitchMomentCoeff;
    double beta_wind_start_rad;
    double beta_wind_end_rad;
    double beta_wind_step_rad; 
    double Cs_LatDragCoeff_start;
    double Cs_LatDragCoeff_end;
    double Cs_LatDragCoeff_step;
    double Cym_DragYawMomentCoeff_start;
    double Cym_DragYawMomentCoeff_end;
    double Cym_DragYawMomentCoeff_step;

    //Environment
    double p_Air_Pa;
    double T_Air_K;
    double a_Gravity_mps2;

    //Tires
    double p_Tires_pa;

    //Brakes
    double mue_BrakePadsFrRe_static[2];
    double mue_BrakePadsFrRe_kinetic[2];
    double d_BrakeActuatorBoreFrRe_m[2];
    double r_BrakePadsMeanLeverFrRe_m[2];
    double n_BrakePadsNumberFrRe[2];

    //STMspecific
    double cLiftF;
    double cLiftR;
    double CoGz_m;
    double Gearratio;
    double m_pac_front_lat[5];
    double m_pac_front_long[5];
    double m_pac_rear_lat[5];
    double m_pac_rear_long[5];

    double r_tireF_m;
    double r_tireR_m;
    double Iyy_WheelF_kgm2;
    double Iyy_WheelR_kgm2;
    double cRollFriction_Npmps;
    double MaxRollFriction_N;
    double T_YawRate_s; 
    double T_LatVel_s;
    double T_Tire_s;

    double T_Steering_s;

    double switchModelBlend_mps;
    double PTLimitLowVel_N; 
    double switchModelVel_mps;

    int counter;
    int set_logging;
    int choose_solver_testcase;
    double log_rate_testcase;
    double timecap_testcase;
    char filename_testcase[301];

} SingleTrackModel;

SingleTrackModel *stm_new();
void stm_free(SingleTrackModel* stm);
void copy_stm_diffS(SingleTrackModel* stm1, SingleTrackModel* stm2);

void vehicleModel(SingleTrackModel* stm, VehicleState *vehstate);
void calcWheelSlips_stm(SingleTrackModel* stm, VehicleState *vehstate);
void tireModelPacejka(SingleTrackModel* stm, VehicleState *vehstate);
void calcLongForce_stm(SingleTrackModel* stm, VehicleState *vehstate);

void setParameters_stm(SingleTrackModel* stm);

void integrate_update_stm(SingleTrackModel* stm, VehicleState *vehstate);
void heun(SingleTrackModel* stm, VehicleState *vehstate);
void adams_bashforth_stm(SingleTrackModel* stm, SingleTrackModel* stm_tminus1, VehicleState *vehstate, VehicleState *vehstate_tminus1, int step);


void set_timestep(SingleTrackModel* stm, double timestep);
void set_logging(SingleTrackModel* stm, int value);
void set_solver_testcase(SingleTrackModel* stm, int value);
void set_lograte_testcase(SingleTrackModel* stm, double value);
void set_timecap_testcase(SingleTrackModel* stm, double value);
void set_filename_testcase(SingleTrackModel* stm, char* filename);

double get_param_vehmass_test(SingleTrackModel* stm);
double get_timestep(SingleTrackModel* stm);
int get_logging(SingleTrackModel* stm);
int get_solver_testcase(SingleTrackModel* stm);
double get_lograte_testcase(SingleTrackModel* stm);
double get_timecap_testcase(SingleTrackModel* stm);
char* get_filename_testcase(SingleTrackModel* stm);


#ifdef __cplusplus
}
#endif

#endif