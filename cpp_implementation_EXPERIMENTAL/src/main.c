#include "../include/VehicleState.h"
#include "../include/execute_testcase.h"
#include "../include/create_csv_testcases.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    //#############################
    //### TEST SingleTrackModel ###
    //#############################

    int set_log = 1;
    int set_solver = 2;
    double lograte = 1;
    char* name_testcase = "braking_100.csv";

    SingleTrackModel *stm;
    stm = stm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    SingleTrackModel *stm_tminus1;
    stm_tminus1 = stm_new();    

    VehicleState *vehstate_tminus1;
    vehstate_tminus1 = vehstate_new();

    printf("\nset parameters stm\n");
    setParameters_stm(stm);
    
    printf("\ndeactivate (0) activate(1) - logging: %d\n", set_log);
    set_logging(stm, set_log);

    set_lograte_testcase(stm, lograte);

    //set solver 0 - euler 1 - heuns 2 - adams 
    //CAUTION testcase will only execute correctly if the corresponding solver is set 
    printf("\nset solver euler (0) heuns (1) adams(2) - solver: %d\n", set_solver);
    set_solver_testcase(stm, set_solver);

    //choose testcase from test_scenarios folder 
    printf("\nname of testcase: %s\n", name_testcase);
    set_filename_testcase(stm, name_testcase);

    //use corresponding testcase for the selected solver 
    // testcase_euler_heun_stm_py(stm, vehstate);
    testcase_adams_stm_py(stm, stm_tminus1, vehstate, vehstate_tminus1);


    printf("\nfinished testcase - free memory\n");
    //printf("\nFree stm\n");
    stm_free(stm);
    stm_free(stm_tminus1);


    //printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);
    vehstate_free(vehstate_tminus1);


    //########################
    //### CREATE TESTCASES ###
    //########################

    //these functions will create the testcase .csv files 
    // acceleration_1min();
    // braking_100();
    // rolling_100();
    // steering_ramp();
    // steering_and_acc();
    // sinus_steering();
    // steer_acc_fast();
    // acc_250Nmps();
    // sinus_steering_dt002();
    // steer_ramp_dt002();
    // rolling_100_t002();
    // steer_acc_t002();


    return 0;
}