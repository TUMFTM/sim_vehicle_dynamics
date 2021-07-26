#include "../include/create_csv_testcases.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/*
Test szenarios 

    1)  5s Standstill 60 s acceleration 

    2)  100 km/h initial velocity - braking to standstill 15 bar 

    3)  100 km/h initial velocity - roll to zero 

    4)  ramp steering angle after 5 s constant velocity 

    5)  constant steeringangle and accelerate 

    6)  constant velority sinus steering angle 

*/


/*

    Format real_data 

    0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,
    9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,
    13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, 
    17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,
    21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,
    25 p_BrakeF_bar,    26 p_BrakeR_bar,
    27 Delta_Wheel_rad

*/


void acceleration_1min(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"acc_60s.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<5.0){        
            T_fl = 0.0; 
            T_fr = 0.0;
            T_rl = 0.0;
            T_rr = 0.0;
            
            p_BrakeF_bar = 0.0;
            p_Brake_R_bar = 0.0;

            steeringangle = 0.0;

        }else {
            T_fl += 0.05; 
            T_fr += 0.05;
            T_rl += 0.05;
            T_rr += 0.05;
            
            p_BrakeF_bar = 0.0;
            p_Brake_R_bar = 0.0;

            steeringangle = 0.0;
        }

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void braking_100(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"braking_100.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################
    
    vx_ini = 100/3.6;    

    T_fl = 0.0; 
    T_fr = 0.0;
    T_rl = 0.0;
    T_rr = 0.0;
    p_BrakeF_bar = 0.0;
    p_Brake_R_bar = 0.0;
    steeringangle = 0.0;

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<0.008){        
            
            p_BrakeF_bar = 0.0;
            p_Brake_R_bar = 0.0;

        }else {
            
            p_BrakeF_bar    = 15.0;
            p_Brake_R_bar   = 15.0;

        }

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void rolling_100(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"rolling_100.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################
    
    vx_ini = 100/3.6;    

    T_fl = 0.0; 
    T_fr = 0.0;
    T_rl = 0.0;
    T_rr = 0.0;
    p_BrakeF_bar = 0.0;
    p_Brake_R_bar = 0.0;
    steeringangle = 0.0;

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void steering_ramp(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steering_ramp.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<5.0){        
            //do nothing

        }else if(i<29.004){
            //increase torque
            T_fl += 0.05; 
            T_fr += 0.05;
            T_rl += 0.05;
            T_rr += 0.05;
            
        }else if(i>50){
            //ramp steeringangle
            steeringangle = 0.1;
        }

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void steering_and_acc(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steering_and_accellerating.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<5.0){        
            //do nothing

        }else{
            //increase torque
            T_fl += 0.01; 
            T_fr += 0.01;
            T_rl += 0.01;
            T_rr += 0.01;

            steeringangle = 0.05;   
        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void sinus_steering(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"sinus_steering.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<5.0){        
            //do nothing

        }else if(i<18){
            //increase torque
            T_fl += 0.05; 
            T_fr += 0.05;
            T_rl += 0.05;
            T_rr += 0.05;

        }else if(i>31.5){
            steeringangle = sin(i*0.5)*0.1;
        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void steer_acc_fast(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steer_acc_fast.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<5.0){        
            //do nothing

        }else if(T_fl<1000){
            //increase torque
            T_fl += 1.0; 
            T_fr += 1.0;
            T_rl += 1.0;
            T_rr += 1.0;

            steeringangle = 0.03;   
        }else {
            T_fl = 1000; 
            T_fr = 1000;
            T_rl = 1000;
            T_rr = 1000;

            steeringangle = 0.03;   

        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void acc_250Nmps(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"acc_250Nmps.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.004; i<65.0;i+=0.004){

        if(i<2.0){        
            //do nothing

        }else if(T_fl<1000){
            //increase torque
            T_fl += 1.0; 
            T_fr += 1.0;
            T_rl += 1.0;
            T_rr += 1.0;

 
        }else {
            T_fl = 1200; 
            T_fr = 1200;
            T_rl = 1200;
            T_rr = 1200; 

        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void sinus_steering_dt002(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steer_sinus_dt002.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.002; i<65.0;i+=0.002){

        if(i<5.0){        
            //do nothing

        }else if(i<18){
            //increase torque
            T_fl += 0.025; 
            T_fr += 0.025;
            T_rl += 0.025;
            T_rr += 0.025;

        }else if(i>37.7){
            steeringangle = sin(i*0.25)*0.035;
        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}



void steer_ramp_dt002(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steer_ramp_dt002.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.002; i<65.0;i+=0.002){

        if(i<5.0){        
            //do nothing

        }else if(i<29.004){
            //increase torque
            T_fl += 0.025; 
            T_fr += 0.025;
            T_rl += 0.025;
            T_rr += 0.025;
            
        }else if(i>50){
            //ramp steeringangle
            steeringangle = 0.1;
        }

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void rolling_100_t002(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"rolling_100_t002.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################
    
    vx_ini = 100/3.6;    

    T_fl = 0.0; 
    T_fr = 0.0;
    T_rl = 0.0;
    T_rr = 0.0;
    p_BrakeF_bar = 0.0;
    p_Brake_R_bar = 0.0;
    steeringangle = 0.0;

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.002; i<80.0;i+=0.002){

        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}


void steer_acc_t002(){

    FILE *logfile;
    char filename[50];

    double x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini;
    double T_fl, T_fr, T_rl, T_rr;
    double p_BrakeF_bar, p_Brake_R_bar;
    double steeringangle;

    double time;

    strcpy(filename, "../test_scenarios/");
    strcat(filename,"steer_acc_t002.csv");

    //write initial state to logfile    
    logfile = fopen(filename, "w");

    fprintf(logfile,     "0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,"
    "9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,"
    "13 alphaFL_rad,     14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, "
    "17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,"
    "21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,"
    "25 p_BrakeF_bar,    26 p_BrakeR_bar,"
    "27 Delta_Wheel_rad\n"
    );

    //#################
    //### INITALIZE ### 
    //#################

    fprintf(logfile, "%09.5f, %f, %f, %f, %f, %f, %f, %f, %f,"
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, %f, %f, "
        "%f, %f, "
        "%f,\n",
        time, x_ini, y_ini, psi_ini, dpsi_ini, vx_ini, vy_ini, ax_ini, ay_ini,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        T_fl, T_fr, T_rl, T_rr,
        0.0, 0.0, 0.0, 0.0,
        p_BrakeF_bar, p_Brake_R_bar,
        steeringangle);


    //############
    //### LOOP ### 
    //############
    
    for(double i = 0.002; i<65.002;i+=0.002){

        if(i<5.0){        
            //do nothing

        }else{
            //increase torque
            T_fl += 0.005; 
            T_fr += 0.005;
            T_rl += 0.005;
            T_rr += 0.005;

            steeringangle = 0.05;   
        }
        fprintf(logfile, "%07.3f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, %f, %f, "
            "%1.0f, %1.0f, %1.0f, %1.0f, "
            "%f, %f, "
            "%f,\n",
            i, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0,
            T_fl, T_fr, T_rl, T_rr,
            0.0, 0.0, 0.0, 0.0,
            p_BrakeF_bar, p_Brake_R_bar,
            steeringangle);
    }

    fclose(logfile);
}
