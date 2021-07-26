#include "../include/execute_testcase.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef M_PI
    #define M_PI      3.14159265358979323846
#endif

#ifdef _WIN32
    char *filepath="..\\test_scenarios\\";
    char* path_to_log = "..\\log\\";

#else 
    char* filepath = "../test_scenarios/";
    char* path_to_log = "../log/";

#endif

double separate_data(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!num--)
            return atof(tok);
    }
    return -1.111111;
}


void initialize_input_data(FILE* datafile, struct VehicleState* vehstate){

    char output[500];
    char buffer[500];

    fgets(output, sizeof(output), datafile);
    
    strcpy(buffer, output);

    vehstate->xpos_ini0_m   = separate_data(output, 1);
    strcpy(output, buffer);
    vehstate->ypos_ini0_m   = separate_data(output, 2);
    strcpy(output, buffer);
    vehstate->psi_ini       = separate_data(output, 3);// + M_PI*0.5;
    strcpy(output, buffer);


    vehstate->dpsi_ini      = separate_data(output, 4);
    strcpy(output, buffer);
    vehstate->vx_veh_mps      = separate_data(output, 5);
    strcpy(output, buffer);
    vehstate->vy_veh_mps      = separate_data(output, 6);
    strcpy(output, buffer);


    vehstate->ax_veh_mps2   = separate_data(output, 7);
    strcpy(output, buffer);
    vehstate->ay_veh_mps2   = separate_data(output, 8);
    strcpy(output, buffer);

    vehstate->tirestate_fl.kappa = separate_data(output, 9)/100.0;
    strcpy(output, buffer);
    vehstate->tirestate_fr.kappa = separate_data(output, 10)/100.0;
    strcpy(output, buffer);
    vehstate->tirestate_rl.kappa = separate_data(output, 11)/100.0;
    strcpy(output, buffer);
    vehstate->tirestate_rr.kappa = separate_data(output, 12)/100.0;
    strcpy(output, buffer);

    vehstate->tirestate_fl.alpha = separate_data(output, 13);
    strcpy(output, buffer);
    vehstate->tirestate_fr.alpha = separate_data(output, 14);
    strcpy(output, buffer);
    vehstate->tirestate_rl.alpha = separate_data(output, 15);
    strcpy(output, buffer);
    vehstate->tirestate_rr.alpha = separate_data(output, 16);
    strcpy(output, buffer);

    vehstate->tirestate_fl.tireDriveTorque = separate_data(output, 17);
    strcpy(output, buffer);
    vehstate->tirestate_fr.tireDriveTorque = separate_data(output, 18);
    strcpy(output, buffer);
    vehstate->tirestate_rl.tireDriveTorque = separate_data(output, 19);
    strcpy(output, buffer);
    vehstate->tirestate_rr.tireDriveTorque = separate_data(output, 20);
    strcpy(output, buffer);

    vehstate->tirestate_fl.omega_radps = separate_data(output, 21);
    strcpy(output, buffer);
    vehstate->tirestate_fr.omega_radps = separate_data(output, 22);
    strcpy(output, buffer);
    vehstate->tirestate_rl.omega_radps = separate_data(output, 23);
    strcpy(output, buffer);
    vehstate->tirestate_rr.omega_radps = separate_data(output, 24);
    strcpy(output, buffer);

    vehstate->tirestate_fl.brakePressure_Pa = separate_data(output, 25)*1E5;
    strcpy(output, buffer);
    vehstate->tirestate_fr.brakePressure_Pa = vehstate->tirestate_fl.brakePressure_Pa;
    strcpy(output, buffer);
    vehstate->tirestate_rl.brakePressure_Pa = separate_data(output, 26)*1E5;
    strcpy(output, buffer);
    vehstate->tirestate_rr.brakePressure_Pa = vehstate->tirestate_rl.brakePressure_Pa;
    strcpy(output, buffer);

    vehstate->steeringangle = separate_data(output, 27);


}


void update_input_data(FILE* datafile,struct VehicleState* vehstate){

    char output[500];
    char buffer[500];

    fgets(output, sizeof(output), datafile);

    strcpy(buffer, output);

    vehstate->tirestate_fl.tireDriveTorque = separate_data(output, 17);
    strcpy(output, buffer);
    vehstate->tirestate_fr.tireDriveTorque = separate_data(output, 18);
    strcpy(output, buffer);
    vehstate->tirestate_rl.tireDriveTorque = separate_data(output, 19);
    strcpy(output, buffer);
    vehstate->tirestate_rr.tireDriveTorque = separate_data(output, 20);
    strcpy(output, buffer);

    vehstate->tirestate_fl.brakePressure_Pa = separate_data(output, 25)*1.0E5;
    strcpy(output, buffer);
    vehstate->tirestate_fr.brakePressure_Pa = vehstate->tirestate_fl.brakePressure_Pa;
    strcpy(output, buffer);
    vehstate->tirestate_rl.brakePressure_Pa = separate_data(output, 26)*1.0E5;
    strcpy(output, buffer);
    vehstate->tirestate_rr.brakePressure_Pa = vehstate->tirestate_rl.brakePressure_Pa;
    strcpy(output, buffer);

    vehstate->steeringangle = separate_data(output, 27);

    //test force phi to real data 
    // strcpy(output, buffer);
    // vehstate->phi_ini =  separate_data(output, 3) + M_PI*0.5;
}

//#####################################################################
//####################### TEST SingleTrackModel #######################
//#####################################################################


void testcase_stm(){

    // printf("\n\e[1;37m\e[4;37mStart realdata_test_stm\e[0m\n\n");

    //######################
    //### CREATE Structs ###
    //######################

    SingleTrackModel *stm;
    stm = stm_new();
    
    VehicleState *vehstate;
    vehstate = vehstate_new();

    SingleTrackModel *stm_tminus1;
    stm_tminus1 = stm_new();    
    VehicleState *vehstate_tminus1;
    vehstate_tminus1 = vehstate_new();


    struct TireState *tirestate_fl = &vehstate->tirestate_fl;
    struct TireState *tirestate_fr = &vehstate->tirestate_fr;
    struct TireState *tirestate_rl = &vehstate->tirestate_rl;
    struct TireState *tirestate_rr = &vehstate->tirestate_rr;


    //#########################
    //### SET initial state ###
    //#########################
    
    double timestep, log_time, timecap;
    char logging;
    int loop_steps, log_steps;


    timestep                = 0.002;

    log_time                = 0.004;
    log_steps               = log_time/timestep;
    
    timecap                 = 65.0;             //duration test1: 10      test2: 06         test3: 12
    loop_steps              = timecap/timestep;

    logging                 = '1';

    // printf("Set Parameters\n\n");
    setParameters_stm(stm);

    // printf("Set timestep to %06.3f \n\n", timestep);
    stm->timestep = timestep;

    printf("Activate(1)/ Deactivate(0) logging: %c \n", logging);

    // printf("Initalize vehstate to real data points\n");
    
    FILE *datafile;
    char* filepath = "../test_scenarios/acc_250Nmps.csv";
    char line1[2000]; 
    char output[500];

    datafile = fopen(filepath, "r");

    if(datafile == NULL) {
        perror("Error opening file");
    }

    //step over first line with text
    fgets(line1, sizeof(line1), datafile);

    //skip j lines of file 
    // for(int j=0; j<170;j++){
    //     fgets(line1, sizeof(line1), datafile);
    // }

    initialize_input_data(datafile, vehstate);


    //test setting:
    // printf("xpos: %f\n", vehstate->xpos_ini0_m);
    // printf("ypos: %f\n", vehstate->ypos_ini0_m);
    // printf("vx: %f\n", vehstate->vx_veh_mps);
    // printf("torque RL: %f\n", vehstate->tirestate_rl.tireDriveTorque);
    // printf("steeringangle: %f\n", vehstate->steeringangle);

    
    if(logging == '1'){
        // printf("Create Logfile stm\n\n");
        create_logfile_stm_realdata(stm, vehstate);
    }
    //#############################
    //### CALL tested functions ###
    //#############################

    for(int i=0; i<loop_steps;i++){

        if(logging == '1' && i%log_steps == 0){
            write_logfile_stm_realdata(stm, vehstate, i*stm->timestep);
        }
        
        
        //EULER  
        calcLongForce_stm(stm, vehstate);
        vehicleModel(stm, vehstate);
        integrate_update_stm(stm, vehstate);
    
        
        // //HEUN
        // heun(stm, vehstate);

    
        // //ADAMS2
        // adams_bashforth_stm(stm, stm_tminus1, vehstate, vehstate_tminus1, i);


        //update input from data file 
        update_input_data(datafile, vehstate);
    }

    //####################
    //### FREE Structs ###
    //####################

    // printf("\nFree stm\n");
    stm_free(stm);
    stm_free(stm_tminus1);


    // printf("Free VehicleSatte\n\n");
    vehstate_free(vehstate);
    vehstate_free(vehstate_tminus1);

}


void testcase_euler_heun_stm_py(SingleTrackModel *stm, struct VehicleState* vehstate){

    //#########################
    //### SET initial state ###
    //#########################
    
    int loop_steps, log_steps;

    log_steps               = stm->log_rate_testcase/stm->timestep;
    loop_steps              = stm->timecap_testcase/stm->timestep;

    
    FILE *datafile;
    char filepath_and_name[320];
    char line1[2000]; 
    char output[500];

    strcpy(filepath_and_name, filepath);
    strcat(filepath_and_name, stm->filename_testcase);

    datafile = fopen(filepath_and_name, "r");

    if(datafile == NULL) {
        perror("Error opening file");
    }

    //step over first line with text
    fgets(line1, sizeof(line1), datafile);

    initialize_input_data(datafile, vehstate);


    if(stm->set_logging == 1){
        // printf("Create Logfile stm\n\n");
        create_logfile_stm_realdata(stm, vehstate);
    }
    //#############################
    //### CALL tested functions ###
    //#############################

    if(stm->choose_solver_testcase == 2){
        //ERROR
        printf("### ERROR ###\n");
        printf("tried to run testcase euler_heuns with adams solver\n");
        printf("reset choose_solver_testcase to 0 or 1 to use this testcase\n");
    } else{
        for(int i=0; i<loop_steps;i++){

            if(stm->set_logging == 1 && i%log_steps == 0){
                write_logfile_stm_realdata(stm, vehstate, i*stm->timestep);
            }
            
            if(stm->choose_solver_testcase == 0){
                //EULER  
                calcLongForce_stm(stm, vehstate);
                vehicleModel(stm, vehstate);
                integrate_update_stm(stm, vehstate);
            }
            
            if(stm->choose_solver_testcase == 1){
                //HEUN
                heun(stm, vehstate);
            }

            //update input from data file 
            update_input_data(datafile, vehstate);

        }

    }


}


void testcase_adams_stm_py(SingleTrackModel *stm, SingleTrackModel *stm_tminus1, struct VehicleState* vehstate, struct VehicleState* vehstate_tminus1){
    //#########################
    //### SET initial state ###
    //#########################
    
    int loop_steps, log_steps;

    log_steps               = stm->log_rate_testcase/stm->timestep;
    loop_steps              = stm->timecap_testcase/stm->timestep;

    
    FILE *datafile;
    char filepath_and_name[320];
    char line1[2000]; 
    char output[500];

    strcpy(filepath_and_name, filepath);
    strcat(filepath_and_name, stm->filename_testcase);

    datafile = fopen(filepath_and_name, "r");

    if(datafile == NULL) {
        perror("Error opening file");
    }

    //step over first line with text
    fgets(line1, sizeof(line1), datafile);

    initialize_input_data(datafile, vehstate);


    if(stm->set_logging == 1){
        // printf("Create Logfile stm\n\n");
        create_logfile_stm_realdata(stm, vehstate);
    }
    //#############################
    //### CALL tested functions ###
    //#############################

    for(int i=0; i<loop_steps;i++){

        if(stm->set_logging == 1 && i%log_steps == 0){
            write_logfile_stm_realdata(stm, vehstate, i*stm->timestep);
        }
        
        if(stm->choose_solver_testcase == 2){
            //ADAMS2
            adams_bashforth_stm(stm, stm_tminus1, vehstate, vehstate_tminus1, i);
        }

        //update input from data file 
        update_input_data(datafile, vehstate);

    }

}

//###################################################################################
//##################################### LOGGING #####################################
//###################################################################################


void create_logfile_stm_realdata(SingleTrackModel *stm, struct VehicleState* vehstate){
    
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

    strcpy(filename, path_to_log);
    strcat(filename,year);
    strcat(filename,".");
    strcat(filename,month);
    strcat(filename,".");
    strcat(filename,day);
    strcat(filename,"_");
    strcat(filename,hour);
    strcat(filename,"-");
    strcat(filename,min);
    strcat(filename,"-");
    strcat(filename,sec);
    strcat(filename,"_comp_STM_real.csv");

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
        "tireDriveTorque_FL_N, tireDriveTorque_FR_N, tireDriveTorque_RL_N, tireDriveTorque_RR_N, " 
        "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        "SteeringAngle_rad, ddPsi_radps2\n");

    fclose(logfile);
}


void write_logfile_stm_realdata(SingleTrackModel *stm, struct VehicleState* vehstate, double timestep){

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
        timestep, vehstate->xpos_ini0_m, vehstate->ypos_ini0_m, vehstate->psi_ini, vehstate->vx_veh_mps, vehstate->vy_veh_mps, vehstate->dpsi_ini, vehstate->ax_veh_mps2, vehstate->ay_veh_mps2,
        vehstate->tirestate_fl.omega_radps, vehstate->tirestate_fr.omega_radps, vehstate->tirestate_rl.omega_radps, vehstate->tirestate_rr.omega_radps,
        vehstate->tirestate_fl.kappa, vehstate->tirestate_fr.kappa, vehstate->tirestate_rl.kappa, vehstate->tirestate_rr.kappa,
        vehstate->tirestate_fl.alpha, vehstate->tirestate_fr.alpha, vehstate->tirestate_rl.alpha, vehstate->tirestate_rr.alpha,
        vehstate->tirestate_fl.fx, vehstate->tirestate_fr.fx, vehstate->tirestate_rl.fx, vehstate->tirestate_rr.fx,
        vehstate->tirestate_fl.fy, vehstate->tirestate_fr.fy, vehstate->tirestate_rl.fy, vehstate->tirestate_rr.fy,
        vehstate->tirestate_fl.tireDriveTorque, vehstate->tirestate_fr.tireDriveTorque, vehstate->tirestate_rl.tireDriveTorque, vehstate->tirestate_rr.tireDriveTorque,
        vehstate->tirestate_fl.brakePressure_Pa, vehstate->tirestate_fr.brakePressure_Pa, vehstate->tirestate_rl.brakePressure_Pa, vehstate->tirestate_rr.brakePressure_Pa,
        vehstate->steeringangle, stm->m_diffS[5]);
    
    fclose(logfile);

}

