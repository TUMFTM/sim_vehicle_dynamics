#include "../include/VehicleBody.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b)((a>b)?a:b)
#define MIN(a,b)((a<b)?a:b)

#ifndef M_PI_2
    #define M_PI_2      1.57079632679489661923132169163975144
#endif

//ONLY FOR CREATION MODULE VEHICLEBODY PYTHON BINDING 
char* setVehBodyPointer(){
    char* pointer; 
    pointer = (char*)malloc(sizeof(char*));
    return pointer;
}


void freeVehBodyPointer(char* pointer){
    free(pointer);
}


void calcDerivatives(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    //##########################################################
    //### ANGULAR ACCELERATIONS IN VEHICLE COORDINATE SYSTEM ###
    //##########################################################

    double RHS_x, RHS_y, RHS_z;

    RHS_x = vehparam->r_A_fl[1]*vehstate->tirestate_fl.fz - vehparam->r_A_fl[2]*vehstate->tirestate_fl.fy\
        + vehparam->r_A_fr[1]*vehstate->tirestate_fr.fz - vehparam->r_A_fr[2]*vehstate->tirestate_fr.fy\
        + vehparam->r_A_rl[1]*vehstate->tirestate_rl.fz - vehparam->r_A_rl[2]*vehstate->tirestate_rl.fy\
        + vehparam->r_A_rr[1]*vehstate->tirestate_rr.fz - vehparam->r_A_rr[2]*vehstate->tirestate_rr.fy;

    RHS_y = vehparam->r_A_fl[2]*vehstate->tirestate_fl.fx - vehparam->r_A_fl[0]*vehstate->tirestate_fl.fz\
        + vehparam->r_A_fr[2]*vehstate->tirestate_fr.fx - vehparam->r_A_fr[0]*vehstate->tirestate_fr.fz\
        + vehparam->r_A_rl[2]*vehstate->tirestate_rl.fx - vehparam->r_A_rl[0]*vehstate->tirestate_rl.fz\
        + vehparam->r_A_rr[2]*vehstate->tirestate_rr.fx - vehparam->r_A_rr[0]*vehstate->tirestate_rr.fz;

    // RHS_z = vehparam->r_A_fl[0]*vehstate->tirestate_fl.fy - vehparam->r_A_fl[1]*vehstate->tirestate_fl.fx\
    //     + vehparam->r_A_fr[0]*vehstate->tirestate_fr.fy - vehparam->r_A_fr[1]*vehstate->tirestate_fr.fx\
    //     + vehparam->r_A_rl[0]*vehstate->tirestate_rl.fy - vehparam->r_A_rl[1]*vehstate->tirestate_rl.fx\
    //     + vehparam->r_A_rr[0]*vehstate->tirestate_rr.fy - vehparam->r_A_rr[1]*vehstate->tirestate_rr.fx;

    double z1 = vehparam->r_A_fl[0]*vehstate->tirestate_fl.fy - vehparam->r_A_fl[1]*vehstate->tirestate_fl.fx;
    double z2 = vehparam->r_A_fr[0]*vehstate->tirestate_fr.fy - vehparam->r_A_fr[1]*vehstate->tirestate_fr.fx;
    double z3 = vehparam->r_A_rl[0]*vehstate->tirestate_rl.fy - vehparam->r_A_rl[1]*vehstate->tirestate_rl.fx;
    double z4 = vehparam->r_A_rr[0]*vehstate->tirestate_rr.fy - vehparam->r_A_rr[1]*vehstate->tirestate_rr.fx;
    RHS_z = z1+ z2 + z3 + z4;

    vehstate->ddphi_veh = 1.0/vehparam->I_K_Vehicle_kgm2[0][0] * (RHS_x - vehstate->dtheta_veh*vehparam->I_K_Vehicle_kgm2[2][2]*vehstate->dphi_veh\
        + vehstate->dphi_veh*vehparam->I_K_Vehicle_kgm2[1][1]*vehstate->dtheta_veh);

    vehstate->ddtheta_veh = 1.0/vehparam->I_K_Vehicle_kgm2[1][1] * (RHS_y - vehstate->dphi_veh*vehparam->I_K_Vehicle_kgm2[0][0]*vehstate->dpsi_veh\
        + vehstate->dpsi_veh*vehparam->I_K_Vehicle_kgm2[2][2]*vehstate->dphi_veh);

    vehstate->ddpsi_veh = 1.0/vehparam->I_K_Vehicle_kgm2[2][2] * (RHS_z - vehstate->dpsi_veh*vehparam->I_K_Vehicle_kgm2[1][1]*vehstate->dtheta_veh\
        + vehstate->dtheta_veh*vehparam->I_K_Vehicle_kgm2[0][0]*vehstate->dpsi_veh);

    // vehstate->ddphi_veh = 1.0/vehparam->I_K_Vehicle_kgm2[0][0] * (RHS_x - vehstate->dtheta_ini*vehparam->I_K_Vehicle_kgm2[2][2]*vehstate->dpsi_ini\
    // + vehstate->dpsi_ini*vehparam->I_K_Vehicle_kgm2[1][1]*vehstate->dtheta_ini);

    // vehstate->ddtheta_veh = 1.0/vehparam->I_K_Vehicle_kgm2[1][1] * (RHS_y - vehstate->dpsi_ini*vehparam->I_K_Vehicle_kgm2[0][0]*vehstate->dphi_ini\
    //     + vehstate->dphi_ini*vehparam->I_K_Vehicle_kgm2[2][2]*vehstate->dpsi_ini);

    // vehstate->ddpsi_veh = 1.0/vehparam->I_K_Vehicle_kgm2[2][2] * (RHS_z - vehstate->dphi_ini*vehparam->I_K_Vehicle_kgm2[1][1]*vehstate->dtheta_ini\
    //     + vehstate->dtheta_ini*vehparam->I_K_Vehicle_kgm2[0][0]*vehstate->dphi_ini);


    //#################################################################################
    //### ACCELERATION IN VEHICLE COORDINATE SYSTEM KINEMATIC AND DOUBLETRACK MODEL ###
    //#################################################################################

    //KINEMATIC MODEL for low velocities  
    double FxFriction = 0.0, ax_km=0.0, ay_km=0.0, neutralSteerBeta=0.0, dvy_km=0.0, neutralSteerYawRate=0.0, ddPsi_km=0.0;
    double w_dtm=0.0, w_km=0.0;
    double dalpha_km[4]={0, 0, 0, 0}, dlambda_perc_km[4]={0, 0, 0, 0}, omega_rolling[4]={0, 0, 0, 0}, domega_km[4]={0, 0, 0, 0};
    
    //limit friction to 200N
    FxFriction = MAX(MIN(vehparam->cRollFriction_Npmps*vehstate->vx_veh_mps, vehparam->MaxRollFriction_N), 0.0) + 0.5*vehparam->cw_LongitudinalDrag*vehparam->airDensity_kgpm3*vehparam->A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps;

    ax_km = ((vehstate->tirestate_fl.fx_powertrain+vehstate->tirestate_fr.fx_powertrain+vehstate->tirestate_rl.fx_powertrain+vehstate->tirestate_rr.fx_powertrain) - FxFriction)/vehparam->m_Vehicle_kg;

    //using the assumption that the centre of gravity is located at 50/50 the following
    //relation holds: beta = delta/2. With the small angle assumption and a first order low
    //pass dynamics, this results in: 
    neutralSteerBeta = vehstate->steeringangle*0.5;
    dvy_km = 1.0/vehparam->T_LatVel_s*(neutralSteerBeta*vehstate->vx_veh_mps-vehstate->vy_veh_mps);
    
    //set the target yaw rate via neutral steer yaw rate for small velocity and combine it
    //with a first order low pass to account for vehicle inertia
    neutralSteerYawRate = vehstate->steeringangle*vehstate->vx_veh_mps/(vehparam->l_WheelbaseTotal_m);
    ddPsi_km = 1.0/vehparam->T_YawRate_s*(neutralSteerYawRate - vehstate->dpsi_veh);

    //in case of kinematic model, target slips are zero 
    dalpha_km[0] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_fl.alpha);
    dalpha_km[1] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_fr.alpha);
    dalpha_km[2] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_rl.alpha);
    dalpha_km[3] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_rr.alpha);
    
    dlambda_perc_km[0] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_fl.kappa);
    dlambda_perc_km[1] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_fr.kappa);
    dlambda_perc_km[2] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_rl.kappa);
    dlambda_perc_km[3] = 1.0/vehparam->T_Tire_s*(0.0-vehstate->tirestate_rr.kappa);

    //set wheelspeed target speed to free rolling 
    omega_rolling[0] = (vehstate->vx_veh_mps - vehstate->dpsi_veh*vehparam->w_TrackF_m*0.5)/param_dtm->tirefl.unloaded_radius;
    omega_rolling[1] = (vehstate->vx_veh_mps + vehstate->dpsi_veh*vehparam->w_TrackF_m*0.5)/param_dtm->tirefr.unloaded_radius;
    omega_rolling[2] = (vehstate->vx_veh_mps - vehstate->dpsi_veh*vehparam->w_TrackR_m*0.5)/param_dtm->tirerl.unloaded_radius;
    omega_rolling[3] = (vehstate->vx_veh_mps + vehstate->dpsi_veh*vehparam->w_TrackR_m*0.5)/param_dtm->tirerr.unloaded_radius;

    domega_km[0] = 1.0/vehparam->T_Tire_s*(omega_rolling[0]-vehstate->tirestate_fl.omega_radps);
    domega_km[1] = 1.0/vehparam->T_Tire_s*(omega_rolling[1]-vehstate->tirestate_fr.omega_radps);
    domega_km[2] = 1.0/vehparam->T_Tire_s*(omega_rolling[2]-vehstate->tirestate_rl.omega_radps);
    domega_km[3] = 1.0/vehparam->T_Tire_s*(omega_rolling[3]-vehstate->tirestate_rr.omega_radps);

    //calculate alternative lateral acceleration for small velocities based on kinematic model
    //yaw rate 
    ay_km = vehstate->dpsi_veh*vehstate->vx_veh_mps;
    
    //overblend kinematic model and single track model 
    //calc weighting factors 
    w_dtm = 0.5*(tanh((vehstate->vx_veh_mps-vehparam->switchModelVel_mps)/vehparam->switchModelBlend_mps)+1.0);
    w_km = 1.0-w_dtm;
   

    //calculate acceleration with equation of principle of linear momentum
    vehstate->a_x_buffer = vehstate->dpsi_veh*vehstate->vy_veh_mps - vehstate->dtheta_veh*vehstate->vz_veh_mps + 1.0/vehparam->m_Vehicle_kg\
     * (vehstate->tirestate_fl.fx+vehstate->tirestate_fr.fx+vehstate->tirestate_rl.fx+vehstate->tirestate_rr.fx\
     - 0.5*vehparam->cw_LongitudinalDrag*vehparam->airDensity_kgpm3*vehparam->A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps);//+vehstate->vy_veh_mps*vehstate->vy_veh_mps)*vehstate->vx_veh_mps);
     
    vehstate->a_y_buffer = vehstate->dphi_veh*vehstate->vz_veh_mps - vehstate->dpsi_veh*vehstate->vx_veh_mps + 1.0/vehparam->m_Vehicle_kg\
     * (vehstate->tirestate_fl.fy+vehstate->tirestate_fr.fy+vehstate->tirestate_rl.fy+vehstate->tirestate_rr.fy);
    //- 0.5*vehparam->cw_LongitudinalDrag*vehparam->airDensity_kgpm3*vehparam->A_LongitudinalDrag_m2*sqrt(vehstate->vx_veh_mps*vehstate->vx_veh_mps+vehstate->vy_veh_mps*vehstate->vy_veh_mps)*vehstate->vy_veh_mps);


    //calculate acceleration 
    vehstate->ax_veh_mps2 = w_km*ax_km + w_dtm*vehstate->a_x_buffer;
    vehstate->ay_veh_mps2 = w_km*ay_km + w_dtm*vehstate->a_y_buffer;
    //vehstate->az_veh_mps2 = (vehstate->buffer_vz_veh_mps-vehstate->vz_veh_mps)/vehparam->timestep;

}


void stepVehBody(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    //TODO integrate/update the derivatives to teh veloveties! 

    //################################################
    //### UPDATE VEHCILE ANGLES IN INI COORDINATES ###
    //################################################

    vehstate->dpsi_veh = vehstate->dpsi_veh + vehstate->ddpsi_veh*vehparam->timestep;
    vehstate->dtheta_veh = vehstate->dtheta_veh + vehstate->ddtheta_veh*vehparam->timestep;
    vehstate->dphi_veh = vehstate->dphi_veh + vehstate->ddphi_veh*vehparam->timestep;
    // vehstate->psi_veh = vehstate->psi_veh + vehstate->dpsi_veh*vehparam->timestep;
    // vehstate->theta_veh = vehstate->theta_veh + vehstate->dtheta_veh*vehparam->timestep;
    // vehstate->phi_veh = vehstate->phi_veh + vehstate->dphi_veh*vehparam->timestep;
    
    
    // Winkelgeschwindigkeit des Fahrzeugaufbaus relativ zum Inertialsystem und 
    // dargestellt in Koordinaten des fahrzeugfesten Koordinatensystems
    double trafoMat_veh_ini_veh[3][3] = 
    {   
        {
        -sin(vehstate->theta_ini),
        0.0,
        1.0
        },
        {
        cos(vehstate->theta_ini)*sin(vehstate->phi_ini), 
        cos(vehstate->phi_ini),
        0.0
        },
        {
        cos(vehstate->theta_ini)*cos(vehstate->phi_ini),
        -sin(vehstate->phi_ini), 
        0.0
        },
    };

    //update angular velocity of vehicle in ini coordinate system but measured in veh coordinates
    vehstate->dphi_ini = trafoMat_veh_ini_veh[0][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[0][2]*vehstate->dphi_veh; 
    vehstate->dtheta_ini = trafoMat_veh_ini_veh[1][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[1][1]*vehstate->dtheta_veh; 
    vehstate->dpsi_ini = trafoMat_veh_ini_veh[2][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[2][1]*vehstate->dtheta_veh; 

    //update angles in ini coordinates
    vehstate->psi_ini = vehstate->psi_ini + vehstate->dpsi_ini*vehparam->timestep;
    vehstate->theta_ini = vehstate->theta_ini + vehstate->dtheta_ini*vehparam->timestep;
    vehstate->phi_ini = vehstate->phi_ini + vehstate->dphi_ini*vehparam->timestep;


    //###############################################################
    //### UPDATE VEHCILE VELOCITY AND POSTITON IN INI COORDINATES ###
    //###############################################################

    //update vehicle velocities
    vehstate->vx_veh_mps = vehstate->vx_veh_mps + vehstate->ax_veh_mps2*vehparam->timestep;
    vehstate->vy_veh_mps = vehstate->vy_veh_mps + vehstate->ay_veh_mps2*vehparam->timestep;

    //calculate distance covered in veh coordinates 
    vehstate->xpos_veh1_m = vehparam->timestep*vehstate->vx_veh_mps;
    vehstate->ypos_veh1_m = vehparam->timestep*vehstate->vy_veh_mps;
    vehstate->zpos_veh1_m = vehparam->timestep*vehstate->vz_veh_mps;

    //trafo matrix from veh coordinate system in ini coordinate system 
    double rotMat_veh_ini[3][3] = 
    {   
        {
        cos(vehstate->theta_ini)*cos(vehstate->psi_ini), 
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->psi_ini)-cos(vehstate->phi_ini)*sin(vehstate->psi_ini),
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->psi_ini)+sin(vehstate->phi_ini)*sin(vehstate->psi_ini)
        },
        {
        cos(vehstate->theta_ini)*sin(vehstate->psi_ini), 
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->psi_ini)+cos(vehstate->phi_ini)*cos(vehstate->psi_ini),
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->psi_ini)-sin(vehstate->phi_ini)*sin(vehstate->psi_ini)
        },
        {
        -sin(vehstate->theta_ini),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini), 
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
    };
    
    //transform cahnge of position veh1 into ini coordinate syetem 
    vehstate->xpos_ini1_m = vehstate->xpos_ini0_m + rotMat_veh_ini[0][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[0][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[0][2]*vehstate->zpos_veh1_m; 
    vehstate->ypos_ini1_m = vehstate->ypos_ini0_m + rotMat_veh_ini[1][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[1][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[1][2]*vehstate->zpos_veh1_m; 
    vehstate->zpos_ini1_m = vehstate->zpos_ini0_m + rotMat_veh_ini[2][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[2][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[2][2]*vehstate->zpos_veh1_m; 
    
    //calculate new velocity in ini coordinates - rotational velocity = 0 because the center of gravity positon is [0, 0, 0]
    //TODO vx and vy are not turned correctly !!! v_y stays to high for too long and v_x is way to low for steer ramp test 
    vehstate->vx_ini_mps = (vehstate->xpos_ini1_m - vehstate->xpos_ini0_m)/vehparam->timestep;
    vehstate->vy_ini_mps = (vehstate->ypos_ini1_m - vehstate->ypos_ini0_m)/vehparam->timestep;
    vehstate->vz_ini_mps = (vehstate->zpos_ini1_m - vehstate->zpos_ini0_m)/vehparam->timestep;

    //update positon in ini cooridnates
    vehstate->xpos_ini0_m = vehstate->xpos_ini1_m;
    vehstate->ypos_ini0_m = vehstate->ypos_ini1_m;
    vehstate->zpos_ini0_m = vehstate->zpos_ini1_m;

    //TODO 
    // vehstate->vx_ini_mps = vehstate->vx_ini_mps + vehstate->dtheta_veh*vehstate->zpos_veh1_m - vehstate->dpsi_veh*vehstate->ypos_veh1_m;
    // vehstate->vy_ini_mps = vehstate->vy_ini_mps + vehstate->dpsi_veh*vehstate->xpos_veh1_m - vehstate->dphi_veh*vehstate->zpos_veh1_m;
    // vehstate->vz_ini_mps = vehstate->vz_ini_mps + vehstate->dphi_veh*vehstate->ypos_veh1_m - vehstate->dtheta_veh*vehstate->xpos_veh1_m;


    // vehstate->xpos_ini0_m = vehstate->xpos_ini0_m + vehstate->vx_ini_mps*vehparam->timestep;
    // vehstate->ypos_ini0_m = vehstate->ypos_ini0_m + vehstate->vy_ini_mps*vehparam->timestep;
    // vehstate->zpos_ini0_m = vehstate->zpos_ini0_m + vehstate->vz_ini_mps*vehparam->timestep;    

    //transform velocity from veh into ini coordinate system 
    // vehstate->vx_ini_mps = rotMat_veh_ini[0][0]*vehstate->vx_veh_mps + rotMat_veh_ini[0][1]*vehstate->vy_veh_mps;// + rotMat_veh_ini[0][2]*vehstate->vz_veh_mps; 
    // vehstate->vy_ini_mps = rotMat_veh_ini[1][0]*vehstate->vx_veh_mps + rotMat_veh_ini[1][1]*vehstate->vy_veh_mps;// + rotMat_veh_ini[1][2]*vehstate->vz_veh_mps; 
    // vehstate->vz_ini_mps = rotMat_veh_ini[2][0]*vehstate->vx_veh_mps + rotMat_veh_ini[2][1]*vehstate->vy_veh_mps;// + rotMat_veh_ini[2][2]*vehstate->vz_veh_mps; 


    // vehstate->xpos_ini0_m = vehstate->xpos_ini0_m + vehstate->vx_ini_mps*vehparam->timestep;
    // vehstate->ypos_ini0_m = vehstate->ypos_ini0_m + vehstate->vy_ini_mps*vehparam->timestep;
    // vehstate->zpos_ini0_m = vehstate->zpos_ini0_m + vehstate->vz_ini_mps*vehparam->timestep;    

}


void adams_bashforth(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    double h = vehparam->timestep;

    VehicleState *k1;
    k1 = vehstate_new();

    VehicleState *k2;
    k2 = vehstate_new();

    copyVehstate(vehstate, k1);
    copyVehstate(vehstate, k2);

    // calcDerivatives(param_dtm, vehparam, k1);

    k2->ddphi_veh = k1->ddphi_veh*h;
    k2->ddtheta_veh = k1->ddtheta_veh*h;
    k2->ddpsi_veh = k1->ddpsi_veh;

    // k2->dphi_veh = k1->dphi_veh*h;
    // k2->dtheta_veh = k1->dtheta_veh*h;
    // k2->dpsi_veh = k1->dpsi_veh;

    
    // k2->dphi_ini = k1->dphi_ini*h;
    // k2->dtheta_ini = k1->dtheta_ini*h;
    // k2->dpsi_ini = k1->dpsi_ini;

    // k2->phi_ini = k1->phi_ini*h;
    // k2->theta_ini = k1->theta_ini*h;
    // k2->psi_ini = k1->psi_ini;


    k2->ax_veh_mps2 = k1->ax_veh_mps2*h;
    k2->ay_veh_mps2 = k1->ay_veh_mps2*h;

    // k2->vx_veh_mps = k1->vx_veh_mps*h;
    // k2->vy_veh_mps = k1->vy_veh_mps*h;

    // k2->xpos_veh1_m = k1->xpos_veh1_m*h;
    // k2->ypos_veh1_m = k1->ypos_veh1_m*h;
    // k2->zpos_veh1_m = k1->zpos_veh1_m*h;

    // k2->vx_ini_mps = k1->vx_ini_mps*h;
    // k2->vy_ini_mps = k1->vy_ini_mps*h;
    // k2->vz_ini_mps = k1->vz_ini_mps*h;

    // k2->xpos_ini0_m = k1->xpos_ini0_m*h;
    // k2->ypos_ini0_m = k1->ypos_ini0_m*h;
    // k2->zpos_ini0_m = k1->zpos_ini0_m*h;


    vehparam->timestep = h;

    stepVehBody(param_dtm, vehparam, k2);
    calcDerivatives(param_dtm, vehparam, k2);

    
    vehstate->ddphi_veh     = 0.5*(k1->ddphi_veh + k2->ddphi_veh);
    vehstate->ddtheta_veh   = 0.5*(k1->ddtheta_veh + k2->ddtheta_veh);
    vehstate->ddpsi_veh     = 0.5*(k1->ddpsi_veh + k2->ddpsi_veh);
    
    vehstate->dphi_veh = vehstate->dphi_veh + h*0.5*(k1->ddphi_veh + k2->ddphi_veh);
    vehstate->dtheta_veh = vehstate->dtheta_veh + h*0.5*(k1->ddtheta_veh + k2->ddtheta_veh);
    vehstate->dpsi_veh = vehstate->dpsi_veh + h*0.5*(k1->ddpsi_veh + k2->ddpsi_veh);


    vehstate->ax_veh_mps2 = 0.5*(k1->ax_veh_mps2 + k2->ax_veh_mps2);
    vehstate->ay_veh_mps2 = 0.5*(k1->ay_veh_mps2 + k2->ay_veh_mps2);
    
    vehstate->vx_veh_mps = vehstate->vx_veh_mps + h*0.5*(k1->ax_veh_mps2 + k2->ax_veh_mps2);
    vehstate->vy_veh_mps = vehstate->vy_veh_mps + h*0.5*(k1->ay_veh_mps2 + k2->ay_veh_mps2);
    
    vehstate_free(k1);
    vehstate_free(k2);

    stepVehBody_multistep(param_dtm, vehparam, vehstate);
}


void adams_bashforth2(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    
    double tbuffer = vehparam->timestep;
    
    vehparam->timestep = vehparam->timestep*0.5;
    double h = vehparam->timestep;

    VehicleState *k1;
    k1 = vehstate_new();

    VehicleState *k2;
    k2 = vehstate_new();

    copyVehstate(vehstate, k1);
    copyVehstate(vehstate, k2);

    // calcDerivatives(param_dtm, vehparam, k1);

    /*
    k2->ddphi_veh = k1->ddphi_veh*h;
    k2->ddtheta_veh = k1->ddtheta_veh*h;
    k2->ddpsi_veh = k1->ddpsi_veh;


    k2->ax_veh_mps2 = k1->ax_veh_mps2*h;
    k2->ay_veh_mps2 = k1->ay_veh_mps2*h;

    vehparam->timestep = h;
    */

    calcDerivatives(param_dtm, vehparam, k2);
    stepVehBody(param_dtm, vehparam, k2);

    
    vehstate->ddphi_veh     = 1.5*k2->ddphi_veh - h*0.5*k1->ddphi_veh;
    vehstate->ddtheta_veh   = 1.5*k2->dtheta_veh - h*0.5*k1->dtheta_veh;
    vehstate->ddpsi_veh     = 1.5*k2->dpsi_veh - h*0.5*k1->dpsi_veh;
    
    vehstate->dphi_veh = k2->dphi_veh + h*1.5*k2->ddphi_veh - h*0.5*k1->ddphi_veh;
    vehstate->dtheta_veh = k2->dtheta_veh + h*1.5*k2->dtheta_veh - h*0.5*k1->dtheta_veh;
    vehstate->dpsi_veh = k2->dpsi_veh + h*1.5*k2->dpsi_veh - h*0.5*k1->dpsi_veh;


    vehstate->ax_veh_mps2 = 1.5*k2->ax_veh_mps2 - h*0.5*k1->ax_veh_mps2;
    vehstate->ay_veh_mps2 = 1.5*k2->ay_veh_mps2 - h*0.5*k1->ay_veh_mps2;
    
    vehstate->vx_veh_mps = k2->vx_veh_mps + h*1.5*k2->ax_veh_mps2 - h*0.5*k1->ax_veh_mps2;
    vehstate->vy_veh_mps = k2->vy_veh_mps + h*1.5*k2->ay_veh_mps2 - h*0.5*k1->ay_veh_mps2;
    
    vehstate_free(k1);
    vehstate_free(k2);

    vehparam->timestep = tbuffer;

    stepVehBody_multistep(param_dtm, vehparam, vehstate);
}


void runge_kutta(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    double h = vehparam->timestep;

    VehicleState *k1;
    k1 = vehstate_new();

    VehicleState *k2;
    k2 = vehstate_new();

    VehicleState *k3;
    k3 = vehstate_new();

    VehicleState *k4;
    k4 = vehstate_new();

    copyVehstate(vehstate, k1);
    copyVehstate(vehstate, k2);
    copyVehstate(vehstate, k3);
    copyVehstate(vehstate, k4);

    //calcDerivatives(param_dtm, vehparam, k1);

    k2->ddphi_veh   = k1->ddphi_veh*h*0.5;
    k2->ddtheta_veh = k1->ddtheta_veh*h*0.5;
    k2->ddpsi_veh   = k1->ddpsi_veh*h*0.5;

    // k2->dphi_veh    = k1->dphi_veh*h*0.5;
    // k2->dtheta_veh  = k1->dtheta_veh*h*0.5;
    // k2->dpsi_veh    = k1->dpsi_veh;

    
    // k2->dphi_ini    = k1->dphi_ini*h*0.5;
    // k2->dtheta_ini  = k1->dtheta_ini*h*0.5;
    // k2->dpsi_ini    = k1->dpsi_ini;

    // k2->phi_ini     = k1->phi_ini*h*0.5;
    // k2->theta_ini   = k1->theta_ini*h*0.5;
    // k2->psi_ini     = k1->psi_ini;


    k2->ax_veh_mps2 = k1->ax_veh_mps2*h*0.5;
    k2->ay_veh_mps2 = k1->ay_veh_mps2*h*0.5;

    // k2->vx_veh_mps    = k1->vx_veh_mps*h*0.5;
    // k2->vy_veh_mps    = k1->vy_veh_mps*h*0.5;

    // k2->xpos_veh1_m = k1->xpos_veh1_m*h*0.5;
    // k2->ypos_veh1_m = k1->ypos_veh1_m*h*0.5;
    // k2->zpos_veh1_m = k1->zpos_veh1_m*h*0.5;

    // k2->vx_ini_mps  = k1->vx_ini_mps*h*0.5;
    // k2->vy_ini_mps  = k1->vy_ini_mps*h*0.5;
    // k2->vz_ini_mps  = k1->vz_ini_mps*h*0.5;

    // k2->xpos_ini0_m = k1->xpos_ini0_m*h*0.5;
    // k2->ypos_ini0_m = k1->ypos_ini0_m*h*0.5;
    // k2->zpos_ini0_m = k1->zpos_ini0_m*h*0.5;


    vehparam->timestep = h*0.5;
    stepVehBody_multistep(param_dtm, vehparam, k2);
    calcDerivatives(param_dtm, vehparam, k2);

    k3->ddphi_veh = k2->ddphi_veh*h*0.5;
    k3->ddtheta_veh = k2->ddtheta_veh*h*0.5;
    k3->ddpsi_veh = k2->ddpsi_veh*h*0.5;

    // k3->dphi_veh = k2->dphi_veh*h*0.5;
    // k3->dtheta_veh = k2->dtheta_veh*h*0.5;
    // k3->dpsi_veh = k2->dpsi_veh;

    
    // k3->dphi_ini = k2->dphi_ini*h*0.5;
    // k3->dtheta_ini = k2->dtheta_ini*h*0.5;
    // k3->dpsi_ini = k2->dpsi_ini;

    // k3->phi_ini = k2->phi_ini*h*0.5;
    // k3->theta_ini = k2->theta_ini*h*0.5;
    // k3->psi_ini = k2->psi_ini;


    k3->ax_veh_mps2 = k2->ax_veh_mps2*h*0.5;
    k3->ay_veh_mps2 = k2->ay_veh_mps2*h*0.5;

    // k3->vx_veh_mps = k2->vx_veh_mps*h*0.5;
    // k3->vy_veh_mps = k2->vy_veh_mps*h*0.5;

    // k3->xpos_veh1_m = k2->xpos_veh1_m*h*0.5;
    // k3->ypos_veh1_m = k2->ypos_veh1_m*h*0.5;
    // k3->zpos_veh1_m = k2->zpos_veh1_m*h*0.5;

    // k3->vx_ini_mps = k2->vx_ini_mps*h*0.5;
    // k3->vy_ini_mps = k2->vy_ini_mps*h*0.5;
    // k3->vz_ini_mps = k2->vz_ini_mps*h*0.5;

    // k3->xpos_ini0_m = k2->xpos_ini0_m*h*0.5;
    // k3->ypos_ini0_m = k2->ypos_ini0_m*h*0.5;
    // k3->zpos_ini0_m = k2->zpos_ini0_m*h*0.5;

    stepVehBody_multistep(param_dtm, vehparam, k3);
    calcDerivatives(param_dtm, vehparam, k3);

    k4->ddphi_veh = k3->ddphi_veh*h;
    k4->ddtheta_veh = k3->ddtheta_veh*h;
    k4->ddpsi_veh = k3->ddpsi_veh*h;

    // k4->dphi_veh = k3->dphi_veh*h;
    // k4->dtheta_veh = k3->dtheta_veh*h;
    // k4->dpsi_veh = k3->dpsi_veh;

    
    // k4->dphi_ini = k3->dphi_ini*h;
    // k4->dtheta_ini = k3->dtheta_ini*h;
    // k4->dpsi_ini = k3->dpsi_ini;

    // k4->phi_ini = k3->phi_ini*h;
    // k4->theta_ini = k3->theta_ini*h;
    // k4->psi_ini = k3->psi_ini;


    k4->ax_veh_mps2 = k3->ax_veh_mps2*h;
    k4->ay_veh_mps2 = k3->ay_veh_mps2*h;

    // k4->vx_veh_mps = k3->vx_veh_mps*h;
    // k4->vy_veh_mps = k3->vy_veh_mps*h;

    // k4->xpos_veh1_m = k3->xpos_veh1_m*h;
    // k4->ypos_veh1_m = k3->ypos_veh1_m*h;
    // k4->zpos_veh1_m = k3->zpos_veh1_m*h;

    // k4->vx_ini_mps = k3->vx_ini_mps*h;
    // k4->vy_ini_mps = k3->vy_ini_mps*h;
    // k4->vz_ini_mps = k3->vz_ini_mps*h;

    // k4->xpos_ini0_m = k3->xpos_ini0_m*h;
    // k4->ypos_ini0_m = k3->ypos_ini0_m*h;
    // k4->zpos_ini0_m = k3->zpos_ini0_m*h;

    vehparam->timestep = h;
    stepVehBody_multistep(param_dtm, vehparam, k4);
    calcDerivatives(param_dtm, vehparam, k4);


    vehstate->ddphi_veh     = 1.0/6.0*(k1->ddphi_veh + 2.0*k2->ddphi_veh + 2.0*k3->ddphi_veh + k4->ddphi_veh);
    vehstate->ddtheta_veh   = 1.0/6.0*(k1->ddtheta_veh + 2.0*k2->ddtheta_veh + 2.0*k3->ddtheta_veh + k4->ddtheta_veh);
    vehstate->ddpsi_veh     = 1.0/6.0*(k1->ddpsi_veh + 2.0*k2->ddpsi_veh + 2.0*k3->ddpsi_veh + k4->ddpsi_veh);
  
    vehstate->dphi_veh      = vehstate->dphi_veh + h/6.0*(k1->ddphi_veh + 2.0*k2->ddphi_veh + 2.0*k3->ddphi_veh + k4->ddphi_veh);
    vehstate->dtheta_veh    = vehstate->dtheta_veh + h/6.0*(k1->ddtheta_veh + 2.0*k2->ddtheta_veh + 2.0*k3->ddtheta_veh + k4->ddtheta_veh);
    vehstate->dpsi_veh      = vehstate->dpsi_veh + h/6.0*(k1->ddpsi_veh + 2.0*k2->ddpsi_veh + 2.0*k3->ddpsi_veh + k4->ddpsi_veh);


    vehstate->ax_veh_mps2   = 1.0/6.0*(k1->ax_veh_mps2 + 2.0*k2->ax_veh_mps2 + 2.0*k3->ax_veh_mps2 + k4->ax_veh_mps2);
    vehstate->ay_veh_mps2   = 1.0/6.0*(k1->ay_veh_mps2 + 2.0*k2->ay_veh_mps2 + 2.0*k3->ay_veh_mps2 + k4->ay_veh_mps2);
 
    vehstate->vx_veh_mps      = vehstate->vx_veh_mps + h/6.0*(k1->ax_veh_mps2 + 2.0*k2->ax_veh_mps2 + 2.0*k3->ax_veh_mps2 + k4->ax_veh_mps2);
    vehstate->vy_veh_mps      = vehstate->vy_veh_mps + h/6.0*(k1->ay_veh_mps2 + 2.0*k2->ay_veh_mps2 + 2.0*k3->ay_veh_mps2 + k4->ay_veh_mps2);
 
    vehstate_free(k1);
    vehstate_free(k2);
    vehstate_free(k3);
    vehstate_free(k4);
    
    stepVehBody_multistep(param_dtm, vehparam, vehstate);
}


void stepVehBody_multistep(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate){

    //TODO integrate/update the derivatives to teh veloveties! 

    //################################################
    //### UPDATE VEHCILE ANGLES IN INI COORDINATES ###
    //################################################    
    
    // Winkelgeschwindigkeit des Fahrzeugaufbaus relativ zum Inertialsystem und 
    // dargestellt in Koordinaten des fahrzeugfesten Koordinatensystems
    double trafoMat_veh_ini_veh[3][3] = 
    {   
        {
        -sin(vehstate->theta_ini),
        0.0,
        1.0
        },
        {
        cos(vehstate->theta_ini)*sin(vehstate->phi_ini), 
        cos(vehstate->phi_ini),
        0.0
        },
        {
        cos(vehstate->theta_ini)*cos(vehstate->phi_ini),
        -sin(vehstate->phi_ini), 
        0.0
        },
    };

    //update angular velocity of vehicle in ini coordinate system but measured in veh coordinates
    vehstate->dphi_ini = trafoMat_veh_ini_veh[0][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[0][2]*vehstate->dphi_veh; 
    vehstate->dtheta_ini = trafoMat_veh_ini_veh[1][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[1][1]*vehstate->dtheta_veh; 
    vehstate->dpsi_ini = trafoMat_veh_ini_veh[2][0]*vehstate->dpsi_veh + trafoMat_veh_ini_veh[2][1]*vehstate->dtheta_veh; 

    //update angles in ini coordinates
    vehstate->psi_ini = vehstate->psi_ini + vehstate->dpsi_ini*vehparam->timestep;
    vehstate->theta_ini = vehstate->theta_ini + vehstate->dtheta_ini*vehparam->timestep;
    vehstate->phi_ini = vehstate->phi_ini + vehstate->dphi_ini*vehparam->timestep;


    //###############################################################
    //### UPDATE VEHCILE VELOCITY AND POSTITON IN INI COORDINATES ###
    //###############################################################

    //calculate distance covered in veh coordinates 
    vehstate->xpos_veh1_m = vehparam->timestep*vehstate->vx_veh_mps;
    vehstate->ypos_veh1_m = vehparam->timestep*vehstate->vy_veh_mps;
    vehstate->zpos_veh1_m = vehparam->timestep*vehstate->vz_veh_mps;

    //trafo matrix from veh coordinate system in ini coordinate system 
    double rotMat_veh_ini[3][3] = 
    {   
        {
        cos(vehstate->theta_ini)*cos(vehstate->psi_ini), 
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->psi_ini)-cos(vehstate->phi_ini)*sin(vehstate->psi_ini),
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->psi_ini)+sin(vehstate->phi_ini)*sin(vehstate->psi_ini)
        },
        {
        cos(vehstate->theta_ini)*sin(vehstate->psi_ini), 
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->psi_ini)+cos(vehstate->phi_ini)*cos(vehstate->psi_ini),
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->psi_ini)-sin(vehstate->phi_ini)*sin(vehstate->psi_ini)
        },
        {
        -sin(vehstate->theta_ini),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini), 
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
    };
    
    //transform cahnge of position veh1 into ini coordinate syetem 
    vehstate->xpos_ini1_m = vehstate->xpos_ini0_m + rotMat_veh_ini[0][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[0][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[0][2]*vehstate->zpos_veh1_m; 
    vehstate->ypos_ini1_m = vehstate->ypos_ini0_m + rotMat_veh_ini[1][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[1][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[1][2]*vehstate->zpos_veh1_m; 
    vehstate->zpos_ini1_m = vehstate->zpos_ini0_m + rotMat_veh_ini[2][0]*vehstate->xpos_veh1_m + rotMat_veh_ini[2][1]*vehstate->ypos_veh1_m + rotMat_veh_ini[2][2]*vehstate->zpos_veh1_m; 
    
    //calculate new velocity in ini coordinates - rotational velocity = 0 because the center of gravity positon is [0, 0, 0]
    vehstate->vx_ini_mps = (vehstate->xpos_ini1_m - vehstate->xpos_ini0_m)/vehparam->timestep;
    vehstate->vy_ini_mps = (vehstate->ypos_ini1_m - vehstate->ypos_ini0_m)/vehparam->timestep;
    vehstate->vz_ini_mps = (vehstate->zpos_ini1_m - vehstate->zpos_ini0_m)/vehparam->timestep;

    //update positon in ini cooridnates
    vehstate->xpos_ini0_m = vehstate->xpos_ini1_m;
    vehstate->ypos_ini0_m = vehstate->ypos_ini1_m;
    vehstate->zpos_ini0_m = vehstate->zpos_ini1_m;

}

