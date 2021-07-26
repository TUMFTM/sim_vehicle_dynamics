#ifndef EXECUTE_TESTCASE_H
#define EXECUTE_TESTCASE_H

#include "../include/VehicleState.h"
#include "../include/SingleTrackModel.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


//###########
//### STM ###
//###########

void testcase_stm();

void testcase_euler_heun_stm_py(SingleTrackModel *stm, struct VehicleState* vehstate);
void testcase_adams_stm_py(SingleTrackModel *stm, SingleTrackModel *stm_tminus1, struct VehicleState* vehstate, struct VehicleState* vehstate_tminus1);

void create_logfile_stm_realdata(SingleTrackModel *stm, struct VehicleState* vehstate);
void write_logfile_stm_realdata(SingleTrackModel *stm, struct VehicleState* vehstate, double timestep);


void initialize_input_data(FILE* datafile, struct VehicleState* vehstate);
void update_input_data(FILE* datafile, struct VehicleState* vehstate);



#ifdef __cplusplus
}
#endif

#endif