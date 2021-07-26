#ifndef TEST_H
#define TEST_H

#include "../include/VehicleState.h"
#include "../include/SingleTrackModel.h"
#include "../include/Param_dtm.h"

#ifdef __cplusplus
extern "C" {
#endif

//###########
//### STM ###
//###########

void test_paramsetting_stm();

void test_calctirestatus();

void test_vehbody();

void test_stm();

void onestep_test();


//###########
//### DTM ###
//###########

void test_paramsetting_dtm();

void test_loop_vehstate();

void dtm_brake();

//###############
//### LOGGING ###
//###############

void printvehstate(struct VehicleState* vehstate);

void create_logfile_stm(SingleTrackModel *stm, struct VehicleState* vehstate);
void write_logfile_stm(SingleTrackModel *stm, struct VehicleState* vehstate, double timestep);

void create_logfile_dtm(Parameters_dtm *param_dtm, struct VehicleState* vehstate);
void write_logfile_dtm(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep);
void create_logfile_dtm_angles(Parameters_dtm *param_dtm, struct VehicleState* vehstate);
void write_logfile_dtm_angles(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep);

void create_logfile_dtm_runge(Parameters_dtm *param_dtm, struct VehicleState* vehstate);
void write_logfile_dtm_runge(Parameters_dtm *param_dtm, struct VehicleState* vehstate, double timestep);

#ifdef __cplusplus
}
#endif

#endif