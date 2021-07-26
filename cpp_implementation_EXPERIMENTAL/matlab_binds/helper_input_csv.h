#ifndef HELPER_INPUT_CSV_H
#define HELPER_INPUT_CSV_H

#include "../include/VehicleState.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef M_PI
    #define M_PI      3.14159265358979323846
#endif


#ifdef __cplusplus
extern "C" {
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
};

double reading_test(){
    FILE *datafile;

    char* filepath = "/Users/jens/Desktop/Masterthesis/400_Data/monte_day4_run5_curve1.csv";
    
    char line1[350];
    char output[250];

    datafile = fopen(filepath, "r");

    if(datafile == NULL) {
        perror("Error opening file");
    }

    fgets(line1, sizeof(line1), datafile);
    // printf("%s \n", line1);

    fgets(output, sizeof(output), datafile);
    // printf("%s \n", output);

    strcpy(line1, output);
    //test seperating data 
    int num = 2;
    double value, value2;

    value = separate_data(output, num);
    // printf("%f\n", value);

    strcpy(output, line1);

    value2 = separate_data(output, 1);

    // printf("%f\n", value2);

    fclose(datafile);

    return value;
};


double reading_test2(FILE* datafile){
   
    char line1[350];
    char output[250];

    if(datafile == NULL) {
        perror("Error opening file");
    }

    fgets(line1, sizeof(line1), datafile);
    // printf("%s \n", line1);

    fgets(output, sizeof(output), datafile);
    // printf("%s \n", output);

    strcpy(line1, output);
    //test seperating data 
    int num = 2;
    double value, value2;

    value = separate_data(output, num);
    // printf("%f\n", value);

    strcpy(output, line1);

    value2 = separate_data(output, 1);

    // printf("%f\n", value2);

    fclose(datafile);

    return value;
};

void initialize_input_data(FILE* datafile, struct VehicleState* vehstate){

    char output[250];
    char buffer[250];

    fgets(output, sizeof(output), datafile);
    
    strcpy(buffer, output);

    vehstate->xpos_ini0_m   = separate_data(output, 1);
    strcpy(output, buffer);
    vehstate->ypos_ini0_m   = separate_data(output, 2);
    strcpy(output, buffer);
    vehstate->psi_ini       = separate_data(output, 3) + M_PI*0.5;
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


};



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

};


#ifdef __cplusplus
}
#endif

#endif