#include "../include/SingleTrackModel.h"
#include "../include/ini.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b)((a>b)?a:b)
#define MIN(a,b)((a<b)?a:b)

#ifndef M_PI
    #define M_PI      3.14159265358979323846
#endif

//these macros are used to find the location of the parameters on windows and linux/mac OS
#ifdef _WIN32
    #include <direct.h>
    char *file_vehicleparameters_stm="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_vehicleparameters.ini";
    
    #define getIniPath()  \
    char cwd[200]; \
    char *ptr; \
    _getcwd(cwd,sizeof(cwd)); \
    char mod[] = "\\mod_control"; \
    char sim[] = "\\sim_vehicle_dynamics";\
    ptr = strrchr(cwd, '\\'); \
    while(strcmp(mod, ptr)!=0 && strcmp(sim, ptr)!=0){ \
        ptr = strrchr(cwd, '\\'); \
        *ptr = '\0'; \
        ptr = strrchr(cwd, '\\'); \
    } 

#else 
    #include <unistd.h>
    char *file_vehicleparameters_stm="/cpp_implementation_EXPERIMENTAL/parameters/sim_vehicleparameters.ini";
    #define getIniPath() \
    char cwd[200]; \
    char *ptr; \
    char mod[] = "/mod_control"; \
    char sim[] = "/sim_vehicle_dynamics"; \
    getcwd(cwd,sizeof(cwd)); \
    ptr = strrchr(cwd, '/'); \
    while(strcmp(mod, ptr)!=0 && strcmp(sim, ptr)!=0){ \
        ptr = strrchr(cwd, '/');    \
        *ptr = '\0';                \
        ptr = strrchr(cwd, '/');    \
    }

#endif

SingleTrackModel *stm_new(){
//this function allocates the memory for a pointer to a SingleTrackModel struct  
    SingleTrackModel *stm, buffer = {0};
    stm = (SingleTrackModel*)malloc(sizeof(SingleTrackModel));
    *stm = buffer;
    return stm;
}


void stm_free(SingleTrackModel* stm){    
    free(stm);
}


void vehicleModel(SingleTrackModel* stm, VehicleState *vehstate){
//The vehicleModel function implements a single track model 
//at for small velocities (< parameter switchModelVel_mps) a kinematic model is used  
    double FxFriction=0.0, FxF=0.0, FxR=0.0, FyF=0.0, FyR=0.0; 
    double ax_stm=0.0, ay_stm=0.0, dvx_stm=0.0, dvy_stm=0.0, ddPsi_stm=0.0;
    double ax_km=0.0, ay_km=0.0, dvx_km=0.0, neutralSteerBeta=0.0, dvy_km=0.0, neutralSteerYawRate=0.0, ddPsi_km=0.0;
    double w_stm=0.0, w_km=0.0, dvx=0.0, dvy=0.0, ddPsi=0.0;
    double ax=0.0, ay=0.0;
    double dalpha_stm[4]={0, 0, 0, 0}, dlambda_perc_stm[4]={0, 0, 0, 0}, dalpha_km[4]={0, 0, 0, 0}, dlambda_perc_km[4]={0, 0, 0, 0}, omega_rolling[4]={0, 0, 0, 0}, domega_km[4]={0, 0, 0, 0};
    double domega[4]={0, 0, 0, 0}, dalpha[4]={0, 0, 0, 0}, dlambda[4]={0, 0, 0, 0};
    double FxPT[4] = {0, 0, 0, 0};
    double wheelInertia_factors[4]={0, 0, 0, 0}, Fz[4]={0, 0, 0, 0}, domega_stm[4]={0, 0, 0, 0};


    const double powertrainTotalForce = vehstate->tirestate_fl.fx_powertrain+vehstate->tirestate_fr.fx_powertrain+vehstate->tirestate_rl.fx_powertrain+vehstate->tirestate_rr.fx_powertrain;

    FxPT[0] = vehstate->tirestate_fl.fx_powertrain;
    FxPT[1] = vehstate->tirestate_fr.fx_powertrain;
    FxPT[2] = vehstate->tirestate_rl.fx_powertrain;
    FxPT[3] = vehstate->tirestate_rr.fx_powertrain;

    //handle negative force requests for low velocities (brake in standstill) 
    if(powertrainTotalForce < 0.0 && vehstate->vx_veh_mps < stm->m_vx_min){
        //limit the powertrain forces for slow velocities
        for(int i = 0;i<4;i++){
            FxPT[i] = MAX(FxPT[i], stm->PTLimitLowVel_N);
        }
        //in case the powertrain forces are small or negative, no powertrain forces should be
        //given to the powertrain (this is necessary for proper standstill) 

        const double negativeForceFactor = MAX(vehstate->vx_veh_mps/stm->m_vx_min, 0.0);
        FxPT[0] = FxPT[0]*negativeForceFactor;
        FxPT[1] = FxPT[1]*negativeForceFactor;
        FxPT[2] = FxPT[2]*negativeForceFactor;
        FxPT[3] = FxPT[3]*negativeForceFactor;
    }

    //wheel inertia factor matrix 
    wheelInertia_factors[0] = stm->r_tireF_m/stm->Iyy_WheelF_kgm2;
    wheelInertia_factors[1] = stm->r_tireF_m/stm->Iyy_WheelF_kgm2;
    wheelInertia_factors[2] = stm->r_tireR_m/stm->Iyy_WheelR_kgm2;
    wheelInertia_factors[3] = stm->r_tireR_m/stm->Iyy_WheelR_kgm2;

    //calculate friction, aero and tire forces 

    //limit friction to 200N
    FxFriction = MAX(MIN(stm->cRollFriction_Npmps*vehstate->vx_veh_mps, stm->MaxRollFriction_N), 0.0) + 0.5*stm->cw_LongitudinalDrag*stm->m_roh*stm->A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps;
    //Fz 
    //TODO check changes f_g*0.5 to f_g*0.25!! 
    vehstate->tirestate_fl.fz = (stm->m_Vehicle_kg*9.81+vehstate->fz_ext_N)*(stm->l_WheelbaseTotal_m-stm->l_WheelbaseF_m)/(stm->l_WheelbaseTotal_m)*0.5 + 0.5*0.5*stm->m_roh*stm->cLiftF*stm->A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps; 
    vehstate->tirestate_fr.fz = vehstate->tirestate_fl.fz;
    vehstate->tirestate_rl.fz = (stm->m_Vehicle_kg*9.81+vehstate->fz_ext_N)*stm->l_WheelbaseF_m/(stm->l_WheelbaseTotal_m)*0.5 + 0.5*0.5*stm->m_roh*stm->cLiftR*stm->A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps; 
    vehstate->tirestate_rr.fz = vehstate->tirestate_rl.fz;
    

    tireModelPacejka(stm, vehstate);

    //calculate single track model 
    //calculate equivalent single track accelerations
    FxF = vehstate->tirestate_fl.fx + vehstate->tirestate_fr.fx;
    FxR = vehstate->tirestate_rl.fx + vehstate->tirestate_rr.fx;
    FyF = vehstate->tirestate_fl.fy + vehstate->tirestate_fr.fy;
    FyR = vehstate->tirestate_rl.fy + vehstate->tirestate_rr.fy;
    
    //calculate single track model
    //calculate accelerations
    ax_stm = (FxF*cos(vehstate->steeringangle) - FyF*sin(vehstate->steeringangle) + FxR - FxFriction + vehstate->fx_ext_N)/stm->m_Vehicle_kg;
    ay_stm = (FyF*cos(vehstate->steeringangle) + FxF*sin(vehstate->steeringangle) + FyR + vehstate->fy_ext_N)/stm->m_Vehicle_kg;
    dvx_stm = ax_stm + vehstate->dpsi_ini*vehstate->vy_veh_mps;
    dvy_stm = ay_stm - vehstate->dpsi_ini*vehstate->vx_veh_mps;
    ddPsi_stm = ((FyF*cos(vehstate->steeringangle) + FxF*sin(vehstate->steeringangle))*stm->l_WheelbaseF_m - FyR*(stm->l_WheelbaseTotal_m-stm->l_WheelbaseF_m) + vehstate->mz_ext_Nm)/stm->I_K_Vehicle_kgm2[2][2]; 

    domega_stm[0] = (FxPT[0] - vehstate->tirestate_fl.fx)*wheelInertia_factors[0];  
    domega_stm[1] = (FxPT[1] - vehstate->tirestate_fr.fx)*wheelInertia_factors[1];  
    domega_stm[2] = (FxPT[2] - vehstate->tirestate_rl.fx)*wheelInertia_factors[2];  
    domega_stm[3] = (FxPT[3] - vehstate->tirestate_rr.fx)*wheelInertia_factors[3];  

    //calculate kinematic model 
    //same for longitudinal dynamics as they are not affected by small slip angle problems
    ax_km = ((FxPT[0]+FxPT[1]+FxPT[2]+FxPT[3]) - FxFriction)/stm->m_Vehicle_kg;
    dvx_km = ax_km;

    //using the assumption that the centre of gravity is located at 50/50 the following
    //relation holds: beta = delta/2. With the small angle assumption and a first order low
    //pass dynamics, this results in: 
    neutralSteerBeta = vehstate->steeringangle*0.5;
    dvy_km = 1.0/stm->T_LatVel_s*(neutralSteerBeta*vehstate->vx_veh_mps-vehstate->vy_veh_mps);

    //set the target yaw rate via neutral steer yaw rate for small velocity and combine it
    //with a first order low pass to account for vehicle inertia
    neutralSteerYawRate = vehstate->steeringangle*vehstate->vx_veh_mps/(stm->l_WheelbaseTotal_m);
    ddPsi_km = 1.0/stm->T_YawRate_s*(neutralSteerYawRate - vehstate->dpsi_ini);

    //calculate slip updates
    calcWheelSlips_stm(stm, vehstate);

    dalpha_stm[0] = 1.0/stm->T_Tire_s*(vehstate->tirestate_fl.alpha_stm1-vehstate->tirestate_fl.alpha);
    dalpha_stm[1] = 1.0/stm->T_Tire_s*(vehstate->tirestate_fr.alpha_stm1-vehstate->tirestate_fr.alpha);
    dalpha_stm[2] = 1.0/stm->T_Tire_s*(vehstate->tirestate_rl.alpha_stm1-vehstate->tirestate_rl.alpha);
    dalpha_stm[3] = 1.0/stm->T_Tire_s*(vehstate->tirestate_rr.alpha_stm1-vehstate->tirestate_rr.alpha);

    //TODO this is no longer perc because kappa is not! 
    dlambda_perc_stm[0] = 1.0/stm->T_Tire_s*(vehstate->tirestate_fl.lambda_stm1-vehstate->tirestate_fl.kappa);
    dlambda_perc_stm[1] = 1.0/stm->T_Tire_s*(vehstate->tirestate_fr.lambda_stm1-vehstate->tirestate_fr.kappa);
    dlambda_perc_stm[2] = 1.0/stm->T_Tire_s*(vehstate->tirestate_rl.lambda_stm1-vehstate->tirestate_rl.kappa);
    dlambda_perc_stm[3] = 1.0/stm->T_Tire_s*(vehstate->tirestate_rr.lambda_stm1-vehstate->tirestate_rr.kappa);

    //in case of kinematic model, target slips are zero 
    dalpha_km[0] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_fl.alpha);
    dalpha_km[1] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_fr.alpha);
    dalpha_km[2] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_rl.alpha);
    dalpha_km[3] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_rr.alpha);
    
    dlambda_perc_km[0] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_fl.kappa);
    dlambda_perc_km[1] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_fr.kappa);
    dlambda_perc_km[2] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_rl.kappa);
    dlambda_perc_km[3] = 1.0/stm->T_Tire_s*(0.0-vehstate->tirestate_rr.kappa);


    //set wheelspeed target speed to free rolling 
    omega_rolling[0] = (vehstate->vx_veh_mps - vehstate->dpsi_ini*stm->w_TrackF_m*0.5)/stm->r_tireF_m;
    omega_rolling[1] = (vehstate->vx_veh_mps + vehstate->dpsi_ini*stm->w_TrackF_m*0.5)/stm->r_tireF_m;
    omega_rolling[2] = (vehstate->vx_veh_mps - vehstate->dpsi_ini*stm->w_TrackR_m*0.5)/stm->r_tireR_m;
    omega_rolling[3] = (vehstate->vx_veh_mps + vehstate->dpsi_ini*stm->w_TrackR_m*0.5)/stm->r_tireR_m;

    domega_km[0] = 1.0/stm->T_Tire_s*(omega_rolling[0]-vehstate->tirestate_fl.omega_radps);
    domega_km[1] = 1.0/stm->T_Tire_s*(omega_rolling[1]-vehstate->tirestate_fr.omega_radps);
    domega_km[2] = 1.0/stm->T_Tire_s*(omega_rolling[2]-vehstate->tirestate_rl.omega_radps);
    domega_km[3] = 1.0/stm->T_Tire_s*(omega_rolling[3]-vehstate->tirestate_rr.omega_radps);
    
    //calculate alternative lateral acceleration for small velocities based on kinematic model
    //yaw rate 
    ay_km = vehstate->dpsi_ini*vehstate->vx_veh_mps;
    
    //overblend kinematic model and single track model 
    //calc weighting factors 
    w_stm = 0.5*(tanh((vehstate->vx_veh_mps-stm->switchModelVel_mps)/stm->switchModelBlend_mps)+1.0);
    w_km = 1.0-w_stm;
    

    //blend process 
    dvx = dvx_km*w_km + dvx_stm*w_stm;
    dvy = dvy_km*w_km + dvy_stm*w_stm;
    ddPsi = ddPsi_km*w_km + ddPsi_stm*w_stm;
    ax = ax_km*w_km + ax_stm*w_stm;
    ay = ay_km*w_km + ay_stm*w_stm;

    for(int l=0;l<4;l++){
        domega[l] = domega_km[l]*w_km + domega_stm[l]*w_stm;
        dalpha[l] = dalpha_km[l]*w_km + dalpha_stm[l]*w_stm;
        dlambda[l] = dlambda_perc_km[l]*w_km + dlambda_perc_stm[l]*w_stm;
    }

    
    stm->m_exactMeasurements[3] = vehstate->vx_veh_mps;
    stm->m_exactMeasurements[4] = vehstate->vy_veh_mps;
    stm->m_exactMeasurements[5] = vehstate->dpsi_ini;
    stm->m_exactMeasurements[6] = ax;
    stm->m_exactMeasurements[7] = ay;
    stm->m_exactMeasurements[8] = vehstate->tirestate_fl.omega_radps;
    stm->m_exactMeasurements[9] = vehstate->tirestate_fr.omega_radps;
    stm->m_exactMeasurements[10] = vehstate->tirestate_rl.omega_radps;
    stm->m_exactMeasurements[11] = vehstate->tirestate_rl.omega_radps;

    stm->m_diffS[0] = cos(vehstate->psi_ini)*vehstate->vx_veh_mps - sin(vehstate->psi_ini)*vehstate->vy_veh_mps;
    stm->m_diffS[1] = sin(vehstate->psi_ini)*vehstate->vx_veh_mps + cos(vehstate->psi_ini)*vehstate->vy_veh_mps;
    stm->m_diffS[2] = vehstate->dpsi_ini;
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

    //set vehstate acceleration
    vehstate->ax_veh_mps2 = ax;
    vehstate->ay_veh_mps2 = ay;

}


void calcWheelSlips_stm(SingleTrackModel* stm, VehicleState *vehstate){
//calculate longitudinal wheel slip and lateral side slip of each individual tire 

    //initalize variables    
    //double vxCG, vyCG, dPsi;
    double v_ref[4] ={0, 0, 0, 0}, v_wheel[4]={0, 0, 0, 0};
    double vx_fr=0.0, vx_fl=0.0,vx_rr=0.0, vx_rl=0.0, vy_fr=0.0, vy_fl=0.0, vy_rr=0.0, vy_rl=0.0;
    double rotationMatrixFront[2][2]= {{0,0}, {0,0}};
    double vxT_fl=0.0, vxT_fr=0.0, vyT_fl=0.0, vyT_fr=0.0;
    
    //calculate chassis velocities at wheel centers projected to the ground
    vx_fr = vehstate->vx_veh_mps + (vehstate->dpsi_ini*stm->w_TrackF_m*0.5);
    vx_fl = vehstate->vx_veh_mps - (vehstate->dpsi_ini*stm->w_TrackF_m*0.5);
    vx_rr = vehstate->vx_veh_mps + (vehstate->dpsi_ini*stm->w_TrackR_m*0.5);
    vx_rl = vehstate->vx_veh_mps - (vehstate->dpsi_ini*stm->w_TrackR_m*0.5);
    vy_fr = vehstate->vy_veh_mps + (vehstate->dpsi_ini*stm->l_WheelbaseF_m);
    vy_fl = vehstate->vy_veh_mps + (vehstate->dpsi_ini*stm->l_WheelbaseF_m);
    vy_rr = vehstate->vy_veh_mps - (vehstate->dpsi_ini*(stm->l_WheelbaseTotal_m-stm->l_WheelbaseF_m));
    vy_rl = vehstate->vy_veh_mps - (vehstate->dpsi_ini*(stm->l_WheelbaseTotal_m-stm->l_WheelbaseF_m));

    //calculate rotationMatrixFront for front tires to transform to tire coordinates
    rotationMatrixFront[0][0] = cos(-vehstate->steeringangle);
    rotationMatrixFront[0][1] = -sin(-vehstate->steeringangle);
    rotationMatrixFront[1][0] = sin(-vehstate->steeringangle);
    rotationMatrixFront[1][1] = cos(-vehstate->steeringangle);

    //transform to tire coordinates
    vxT_fl = rotationMatrixFront[0][0]*vx_fl + rotationMatrixFront[0][1]*vy_fl;
    vyT_fl = rotationMatrixFront[1][0]*vx_fl + rotationMatrixFront[1][1]*vy_fl;
    vxT_fr = rotationMatrixFront[0][0]*vx_fr + rotationMatrixFront[0][1]*vy_fr;
    vyT_fr = rotationMatrixFront[1][0]*vx_fr + rotationMatrixFront[1][1]*vy_fr;

    //calculate tire slip angles 
    if(vehstate->vx_veh_mps > stm->m_vx_min){
        vehstate->tirestate_fl.alpha_stm1 = atan2(-vyT_fl, vxT_fl);
        vehstate->tirestate_fr.alpha_stm1 = atan2(-vyT_fr, vxT_fr);
        vehstate->tirestate_rl.alpha_stm1 = atan2(-vy_rl, vx_rl);
        vehstate->tirestate_rr.alpha_stm1 = atan2(-vy_rr, vx_rr);
    } else {
        vehstate->tirestate_fl.alpha_stm1 = 0.0;
        vehstate->tirestate_fr.alpha_stm1 = 0.0;
        vehstate->tirestate_rl.alpha_stm1 = 0.0;
        vehstate->tirestate_rr.alpha_stm1 = 0.0;
    }

    //calculate absolute reference velocities of tire
    v_ref[0] = vxT_fl;
    v_ref[1] = vxT_fr;
    v_ref[2] = vx_rl;
    v_ref[3] = vx_rr;

    //calculate wheel over ground velocities 
    v_wheel[0] = stm->r_tireF_m*vehstate->tirestate_fl.omega_radps;
    v_wheel[1] = stm->r_tireF_m*vehstate->tirestate_fr.omega_radps;
    v_wheel[2] = stm->r_tireR_m*vehstate->tirestate_rl.omega_radps;
    v_wheel[3] = stm->r_tireR_m*vehstate->tirestate_rr.omega_radps;

    //calculate tireslips    
    vehstate->tirestate_fl.lambda_stm1 = (v_wheel[0]-v_ref[0])/MAX(stm->m_vx_min, v_ref[0]);
    vehstate->tirestate_fr.lambda_stm1 = (v_wheel[1]-v_ref[1])/MAX(stm->m_vx_min, v_ref[1]);
    vehstate->tirestate_rl.lambda_stm1 = (v_wheel[2]-v_ref[2])/MAX(stm->m_vx_min, v_ref[2]);
    vehstate->tirestate_rr.lambda_stm1 = (v_wheel[3]-v_ref[3])/MAX(stm->m_vx_min, v_ref[3]);

}


void tireModelPacejka(SingleTrackModel* stm, VehicleState *vehstate){
//Pacjeka tire model based on a four coefficient approach
//evaluates the lateral and longitudinal tire forces using the specified 
//pacjeka models for front and rear

    vehstate->tirestate_fl.fx = vehstate->tirestate_fl.fz*stm->m_pac_front_long[2]      * sin(stm->m_pac_front_long[1]*atan(stm->m_pac_front_long[0]*vehstate->tirestate_fl.kappa-stm->m_pac_front_long[3]*(stm->m_pac_front_long[0]*vehstate->tirestate_fl.kappa-atan(stm->m_pac_front_long[0]*vehstate->tirestate_fl.kappa))));
    vehstate->tirestate_fr.fx = vehstate->tirestate_fr.fz*stm->m_pac_front_long[2]      * sin(stm->m_pac_front_long[1]*atan(stm->m_pac_front_long[0]*vehstate->tirestate_fr.kappa-stm->m_pac_front_long[3]*(stm->m_pac_front_long[0]*vehstate->tirestate_fr.kappa-atan(stm->m_pac_front_long[0]*vehstate->tirestate_fr.kappa))));
    vehstate->tirestate_rl.fx = vehstate->tirestate_rl.fz*stm->m_pac_rear_long[2]       * sin(stm->m_pac_rear_long[1]*atan(stm->m_pac_rear_long[0]*vehstate->tirestate_rl.kappa-stm->m_pac_rear_long[3]*(stm->m_pac_rear_long[0]*vehstate->tirestate_rl.kappa-atan(stm->m_pac_rear_long[0]*vehstate->tirestate_rl.kappa))));
    vehstate->tirestate_rr.fx = vehstate->tirestate_rr.fz*stm->m_pac_rear_long[2]       * sin(stm->m_pac_rear_long[1]*atan(stm->m_pac_rear_long[0]*vehstate->tirestate_rr.kappa-stm->m_pac_rear_long[3]*(stm->m_pac_rear_long[0]*vehstate->tirestate_rr.kappa-atan(stm->m_pac_rear_long[0]*vehstate->tirestate_rr.kappa))));

    vehstate->tirestate_fl.fy = vehstate->tirestate_fl.fz*stm->m_pac_front_lat[2]       *sin(stm->m_pac_front_lat[1]*atan(stm->m_pac_front_lat[0]*vehstate->tirestate_fl.alpha-stm->m_pac_front_lat[3]*(stm->m_pac_front_lat[0]*vehstate->tirestate_fl.alpha-atan(stm->m_pac_front_lat[0]*vehstate->tirestate_fl.alpha))));
    vehstate->tirestate_fr.fy = vehstate->tirestate_fr.fz*stm->m_pac_front_lat[2]       *sin(stm->m_pac_front_lat[1]*atan(stm->m_pac_front_lat[0]*vehstate->tirestate_fr.alpha-stm->m_pac_front_lat[3]*(stm->m_pac_front_lat[0]*vehstate->tirestate_fr.alpha-atan(stm->m_pac_front_lat[0]*vehstate->tirestate_fr.alpha))));
    vehstate->tirestate_rl.fy = vehstate->tirestate_rl.fz*stm->m_pac_rear_lat[2]        *sin(stm->m_pac_rear_lat[1]*atan(stm->m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha-stm->m_pac_rear_lat[3]*(stm->m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha-atan(stm->m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha))));
    vehstate->tirestate_rr.fy = vehstate->tirestate_rr.fz*stm->m_pac_rear_lat[2]        *sin(stm->m_pac_rear_lat[1]*atan(stm->m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha-stm->m_pac_rear_lat[3]*(stm->m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha-atan(stm->m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha))));    
}


void calcLongForce_stm(SingleTrackModel* stm, VehicleState *vehstate){
//The function calculates the force of the powertrain in dependence of the input tire torque und brake pressure 
//the wheel speed is limited to enforce proper standstill 
    double limitedWheelSpeed[4]; 

    limitedWheelSpeed[0] = (vehstate->tirestate_fl.omega_radps < 0) ? 0 : (stm->switchModelVel_mps/stm->r_tireF_m < vehstate->tirestate_fl.omega_radps) ? stm->switchModelVel_mps/stm->r_tireF_m : vehstate->tirestate_fl.omega_radps;
    limitedWheelSpeed[1] = (vehstate->tirestate_fr.omega_radps < 0) ? 0 : (stm->switchModelVel_mps/stm->r_tireF_m < vehstate->tirestate_fr.omega_radps) ? stm->switchModelVel_mps/stm->r_tireF_m : vehstate->tirestate_fr.omega_radps;
    limitedWheelSpeed[2] = (vehstate->tirestate_rl.omega_radps < 0) ? 0 : (stm->switchModelVel_mps/stm->r_tireR_m < vehstate->tirestate_rl.omega_radps) ? stm->switchModelVel_mps/stm->r_tireR_m : vehstate->tirestate_rl.omega_radps;
    limitedWheelSpeed[3] = (vehstate->tirestate_rl.omega_radps < 0) ? 0 : (stm->switchModelVel_mps/stm->r_tireR_m < vehstate->tirestate_rl.omega_radps) ? stm->switchModelVel_mps/stm->r_tireR_m : vehstate->tirestate_rl.omega_radps;

    vehstate->tirestate_fl.fx_powertrain = vehstate->tirestate_fl.tireDriveTorque*1/stm->r_tireF_m - (vehstate->tirestate_fl.brakePressure_Pa*(stm->r_BrakePadsMeanLeverFrRe_m[0]/stm->r_tireF_m)*stm->mue_BrakePadsFrRe_kinetic[0]*M_PI*(stm->d_BrakeActuatorBoreFrRe_m[0]*0.5)*(stm->d_BrakeActuatorBoreFrRe_m[0]*0.5)*stm->n_BrakePadsNumberFrRe[0]*limitedWheelSpeed[0]*stm->r_tireF_m/stm->switchModelVel_mps);
    vehstate->tirestate_fr.fx_powertrain = vehstate->tirestate_fr.tireDriveTorque*1/stm->r_tireF_m - (vehstate->tirestate_fr.brakePressure_Pa*(stm->r_BrakePadsMeanLeverFrRe_m[0]/stm->r_tireF_m)*stm->mue_BrakePadsFrRe_kinetic[0]*M_PI*(stm->d_BrakeActuatorBoreFrRe_m[0]*0.5)*(stm->d_BrakeActuatorBoreFrRe_m[0]*0.5)*stm->n_BrakePadsNumberFrRe[0]*limitedWheelSpeed[1]*stm->r_tireF_m/stm->switchModelVel_mps);
    vehstate->tirestate_rl.fx_powertrain = vehstate->tirestate_rl.tireDriveTorque*1/stm->r_tireR_m - (vehstate->tirestate_rl.brakePressure_Pa*(stm->r_BrakePadsMeanLeverFrRe_m[1]/stm->r_tireR_m)*stm->mue_BrakePadsFrRe_kinetic[1]*M_PI*(stm->d_BrakeActuatorBoreFrRe_m[1]*0.5)*(stm->d_BrakeActuatorBoreFrRe_m[1]*0.5)*stm->n_BrakePadsNumberFrRe[1]*limitedWheelSpeed[2]*stm->r_tireR_m/stm->switchModelVel_mps);
    vehstate->tirestate_rr.fx_powertrain = vehstate->tirestate_rr.tireDriveTorque*1/stm->r_tireR_m - (vehstate->tirestate_rr.brakePressure_Pa*(stm->r_BrakePadsMeanLeverFrRe_m[1]/stm->r_tireR_m)*stm->mue_BrakePadsFrRe_kinetic[1]*M_PI*(stm->d_BrakeActuatorBoreFrRe_m[1]*0.5)*(stm->d_BrakeActuatorBoreFrRe_m[1]*0.5)*stm->n_BrakePadsNumberFrRe[1]*limitedWheelSpeed[3]*stm->r_tireR_m/stm->switchModelVel_mps);

}


static int handler(void* user, const char* section, const char* name, const char* value){
//The handler function is needed to get the paramteres from the .ini files
//every Parameter is explicitly named with the corresponding [block_name] from the .ini file 
//the parameters are stored inside the SingleTrackModel structure  
    SingleTrackModel* stm = (SingleTrackModel*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
 
    //VEHICLE Parameter
    if(MATCH("VehicleData", "m_Vehicle_kg")){
        stm->m_Vehicle_kg = atof(value);
    } else if(MATCH("VehicleData","l_WheelbaseF_m")){
        stm->l_WheelbaseF_m = atof(value);
    }else if(MATCH("VehicleData","l_WheelbaseTotal_m")){
        stm->l_WheelbaseTotal_m = atof(value);
    }else if(MATCH("VehicleData","w_GeomCenterlineToCOG_m")){
        stm->w_GeomCenterlineToCOG_m = atof(value);
    }else if(MATCH("VehicleData","h_AxlePlaneToCOG_m")){
        stm->h_AxlePlaneToCOG_m = atof(value);
    }else if(MATCH("VehicleData","w_TrackF_m")){
        stm->w_TrackF_m = atof(value);
    }else if(MATCH("VehicleData","w_TrackR_m")){
        stm->w_TrackR_m = atof(value);
    }else if(MATCH("VehicleData","I_K_Vehicle_kgm2")){    
        char* token;
        int i=0, j=0;

        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            if(i==2){
                stm->I_K_Vehicle_kgm2[j][i] = atof(token);
                token = strtok(NULL," ");
                i=0;
                j++;
            }else{
                stm->I_K_Vehicle_kgm2[j][i] = atof(token);
                token = strtok(NULL," ");
                i++;
            } 
        }
    }
    //Aerodynamics
    else if(MATCH("Aerodynamics","A_LongitudinalDrag_m2")){
        stm->A_LongitudinalDrag_m2 = atof(value);
    }else if(MATCH("Aerodynamics","cw_LongitudinalDrag")){
        stm->cw_LongitudinalDrag = atof(value);
    }else if(MATCH("Aerodynamics","cl_LongitudinalLift")){
        stm->cl_LongitudinalLift = atof(value);
    }else if(MATCH("Aerodynamics","cpm_LongDragPitchMomentCoeff")){
        stm->cpm_LongDragPitchMomentCoeff = atof(value);
    }else if(MATCH("Aerodynamics","beta_wind_start_rad")){
        stm->beta_wind_start_rad = atof(value);
    }else if(MATCH("Aerodynamics","beta_wind_end_rad")){
        stm->beta_wind_end_rad = atof(value);
    }else if(MATCH("Aerodynamics","beta_wind_step_rad")){
        stm->beta_wind_step_rad = atof(value);
    }else if(MATCH("Aerodynamics","Cs_LatDragCoeff_start")){
        stm->Cs_LatDragCoeff_start = atof(value);
    }else if(MATCH("Aerodynamics","Cs_LatDragCoeff_end")){
        stm->Cs_LatDragCoeff_end = atof(value);
    }else if(MATCH("Aerodynamics","Cs_LatDragCoeff_step")){
        stm->Cs_LatDragCoeff_step = atof(value);
    }else if(MATCH("Aerodynamics","Cym_DragYawMomentCoeff_start")){
        stm->Cym_DragYawMomentCoeff_start = atof(value);
    }else if(MATCH("Aerodynamics","Cym_DragYawMomentCoeff_end")){
        stm->Cym_DragYawMomentCoeff_end = atof(value);
    }else if(MATCH("Aerodynamics","Cym_DragYawMomentCoeff_step")){
        stm->Cym_DragYawMomentCoeff_step = atof(value);
    }
    //Environment
    else if(MATCH("Environment","p_Air_Pa")){
        stm->p_Air_Pa = atof(value);
    }else if(MATCH("Environment","T_Air_K")){
        stm->T_Air_K = atof(value);
    }else if(MATCH("Environment","a_Gravity_mps2")){
        stm->a_Gravity_mps2 = atof(value);
    }
    //Tires
    else if(MATCH("Tires","p_Tires_pa")){
        stm->p_Tires_pa = atof(value);
    }
    //BRAKE Parameter
    //Brakes
    if(MATCH("Brakes", "mue_BrakePadsFrRe_static")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->mue_BrakePadsFrRe_static[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else if(MATCH("Brakes","mue_BrakePadsFrRe_kinetic")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->mue_BrakePadsFrRe_kinetic[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else if(MATCH("Brakes","d_BrakeActuatorBoreFrRe_m")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->d_BrakeActuatorBoreFrRe_m[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else if(MATCH("Brakes","r_BrakePadsMeanLeverFrRe_m")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->r_BrakePadsMeanLeverFrRe_m[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else if(MATCH("Brakes","n_BrakePadsNumberFrRe")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->n_BrakePadsNumberFrRe[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }
    //STMspecific
    else if(MATCH("STMspecific","cLiftF")){
        stm->cLiftF = atof(value);
    }else if(MATCH("STMspecific","cLiftR")){
        stm->cLiftR = atof(value);
    }else if(MATCH("STMspecific","CoGz_m")){
        stm->CoGz_m = atof(value);
    }else if(MATCH("STMspecific","Gearratio")){
        stm->Gearratio = atof(value);
    }else if(MATCH("STMspecific","r_tireF_m")){
        stm->r_tireF_m = atof(value);
    }else if(MATCH("STMspecific","r_tireR_m")){
        stm->r_tireR_m = atof(value);
    }else if(MATCH("STMspecific","Iyy_WheelF_kgm2")){
        stm->Iyy_WheelF_kgm2 = atof(value);
    }else if(MATCH("STMspecific","Iyy_WheelR_kgm2")){
        stm->Iyy_WheelR_kgm2 = atof(value);
    }else if(MATCH("STMspecific","cRollFriction_Npmps")){
        stm->cRollFriction_Npmps = atof(value);
    }else if(MATCH("STMspecific","MaxRollFriction_N")){
        stm->MaxRollFriction_N = atof(value);
    }else if(MATCH("STMspecific","T_YawRate_s")){
        stm->T_YawRate_s = atof(value);
    }else if(MATCH("STMspecific","T_LatVel_s")){
        stm->T_LatVel_s = atof(value);
    }else if(MATCH("STMspecific","T_Tire_s")){
        stm->T_Tire_s = atof(value);
    }else if(MATCH("STMspecific","T_Steering_s")){
        stm->T_Steering_s = atof(value);
    }else if(MATCH("STMspecific","PTLimitLowVel_N")){
        stm->PTLimitLowVel_N = atof(value);
    }else if(MATCH("STMspecific","switchModelVel_mps")){
        stm->switchModelVel_mps = atof(value);
    }else if(MATCH("STMspecific","switchModelBlend_mps")){
        stm->switchModelBlend_mps = atof(value);
    }
    //PAJEKA Parameter
    else if(MATCH("STMspecific","PacLatF")){    
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->m_pac_front_lat[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        } 
    }else if(MATCH("STMspecific","PacLongF")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->m_pac_front_long[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        } 
    }else if(MATCH("STMspecific","PacLatR")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->m_pac_rear_lat[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else if(MATCH("STMspecific","PacLongR")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            stm->m_pac_rear_long[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        } 

    }
    else {
        return 0; //unknown section/ name error
    }



/*
    MISSING

    [veh_param]

    CoGy_m
    CoGz_m
    Gearratio

    [brake_param]

    n_BrakePadsB
    n_BrakePadsF

    [steering_param]
    T_Steering_s

*/
    return 1;
}


void setParameters_stm(SingleTrackModel* stm){

    char path_vehicle[200];

    // GETINIPATH MACRO
    getIniPath();
    
    strcpy(path_vehicle, cwd);
    strcat(path_vehicle, file_vehicleparameters_stm);
    ini_parse(path_vehicle, handler, stm);

    strcpy(stm->cwd, cwd);

    stm->m_vx_min = 0.5 * stm->switchModelVel_mps;
    stm->m_roh = 1.22;
    stm->timestep = 0.004;

    stm->set_logging = 0;
    stm->timecap_testcase = 65.0;
    stm->log_rate_testcase = 0.004;

    //reset sign of cLiftF/ cLiftR
    stm->cLiftF *= -1.0; 
    stm->cLiftR *= -1.0; 


    stm->m_exactMeasurements[0] = 0.0;
    stm->m_exactMeasurements[1] = 0.0;
    stm->m_exactMeasurements[2] = 0.0;
    stm->m_exactMeasurements[3] = 0.0;
    stm->m_exactMeasurements[4] = 0.0;
    stm->m_exactMeasurements[5] = 0.0;
    stm->m_exactMeasurements[6] = 0.0;
    stm->m_exactMeasurements[7] = 0.0;
    stm->m_exactMeasurements[8] = 0.0;
    stm->m_exactMeasurements[9] = 0.0;
    stm->m_exactMeasurements[10] = 0.0;
    stm->m_exactMeasurements[11] = 0.0;


    stm->m_diffS[0] = 0.0;
    stm->m_diffS[1] = 0.0;
    stm->m_diffS[2] = 0.0;
    stm->m_diffS[3] = 0.0;
    stm->m_diffS[4] = 0.0;
    stm->m_diffS[5] = 0.0;
    stm->m_diffS[6] = 0.0;
    stm->m_diffS[7] = 0.0;
    stm->m_diffS[8] = 0.0;
    stm->m_diffS[9] = 0.0;
    stm->m_diffS[10] = 0.0;
    stm->m_diffS[11] = 0.0;
    stm->m_diffS[12] = 0.0;
    stm->m_diffS[13] = 0.0;
    stm->m_diffS[14] = 0.0;
    stm->m_diffS[15] = 0.0;
    stm->m_diffS[16] = 0.0;
    stm->m_diffS[17] = 0.0;
}


void integrate_update_stm(SingleTrackModel* stm, VehicleState *vehstate){
//This function integrates the vehiclestate with a forward euler 
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

    //integrate posiion
    vehstate->xpos_ini0_m = vehstate->xpos_ini0_m + stm->m_diffS[0]*stm->timestep;
    vehstate->ypos_ini0_m = vehstate->ypos_ini0_m + stm->m_diffS[1]*stm->timestep;
    vehstate->psi_ini = vehstate->psi_ini + stm->m_diffS[2]*stm->timestep;

    //integrate velocity
    vehstate->vx_veh_mps = vehstate->vx_veh_mps + stm->m_diffS[3]*stm->timestep;
    vehstate->vy_veh_mps = vehstate->vy_veh_mps + stm->m_diffS[4]*stm->timestep;
    vehstate->dpsi_ini = vehstate->dpsi_ini + stm->m_diffS[5]*stm->timestep; 

    //integrate tire velocity 
    vehstate->tirestate_fl.omega_radps = vehstate->tirestate_fl.omega_radps + stm->m_diffS[6]*stm->timestep;
    vehstate->tirestate_fr.omega_radps = vehstate->tirestate_fr.omega_radps + stm->m_diffS[7]*stm->timestep;
    vehstate->tirestate_rl.omega_radps = vehstate->tirestate_rl.omega_radps + stm->m_diffS[8]*stm->timestep;
    vehstate->tirestate_rr.omega_radps = vehstate->tirestate_rr.omega_radps + stm->m_diffS[9]*stm->timestep;
 
    //integrate tire slip
    vehstate->tirestate_fl.kappa = vehstate->tirestate_fl.kappa + stm->timestep*stm->m_diffS[10];
    vehstate->tirestate_fr.kappa = vehstate->tirestate_fr.kappa + stm->timestep*stm->m_diffS[11];
    vehstate->tirestate_rl.kappa = vehstate->tirestate_rl.kappa + stm->timestep*stm->m_diffS[12];
    vehstate->tirestate_rr.kappa = vehstate->tirestate_rr.kappa + stm->timestep*stm->m_diffS[13];

    vehstate->tirestate_fl.alpha = vehstate->tirestate_fl.alpha + stm->timestep*stm->m_diffS[14];
    vehstate->tirestate_fr.alpha = vehstate->tirestate_fr.alpha + stm->timestep*stm->m_diffS[15];
    vehstate->tirestate_rl.alpha = vehstate->tirestate_rl.alpha + stm->timestep*stm->m_diffS[16];
    vehstate->tirestate_rr.alpha = vehstate->tirestate_rr.alpha + stm->timestep*stm->m_diffS[17];

}


void adams_bashforth_stm(SingleTrackModel* stm, SingleTrackModel* stm_tminus1, VehicleState *vehstate, VehicleState *vehstate_tminus1, int step){
//This Funvtion integrates the vehiclestate with a two step adams-bashforth-method
    SingleTrackModel *stm_buffer;
    stm_buffer = stm_new();

    VehicleState *vehstate_buffer;
    vehstate_buffer = vehstate_new();

    setParameters_stm(stm_buffer);

    stm_buffer->timestep = stm->timestep;

    copy_stm_diffS(stm, stm_buffer);
    copyVehstate(vehstate, vehstate_buffer);

    if(step ==0){
        copy_stm_diffS(stm, stm_tminus1);
        copyVehstate(vehstate, vehstate_tminus1);

        //euler integration
        calcLongForce_stm(stm, vehstate);
        vehicleModel(stm, vehstate);
        integrate_update_stm(stm, vehstate);
    }else {
        //y_n+1 = y_n + h*(3/2f(y_n)-1/2f(y_n-1))
        calcLongForce_stm(stm, vehstate);
        vehicleModel(stm, vehstate);

        stm_buffer->m_diffS[0]  =   0.5*(3*stm->m_diffS[0]  - stm_tminus1->m_diffS[0] );
        stm_buffer->m_diffS[1]  =   0.5*(3*stm->m_diffS[1]  - stm_tminus1->m_diffS[1] );
        stm_buffer->m_diffS[2]  =   0.5*(3*stm->m_diffS[2]  - stm_tminus1->m_diffS[2] );
        stm_buffer->m_diffS[3]  =   0.5*(3*stm->m_diffS[3]  - stm_tminus1->m_diffS[3] );
        stm_buffer->m_diffS[4]  =   0.5*(3*stm->m_diffS[4]  - stm_tminus1->m_diffS[4] );
        stm_buffer->m_diffS[5]  =   0.5*(3*stm->m_diffS[5]  - stm_tminus1->m_diffS[5] );
        stm_buffer->m_diffS[6]  =   0.5*(3*stm->m_diffS[6]  - stm_tminus1->m_diffS[6] );
        stm_buffer->m_diffS[7]  =   0.5*(3*stm->m_diffS[7]  - stm_tminus1->m_diffS[7] );
        stm_buffer->m_diffS[8]  =   0.5*(3*stm->m_diffS[8]  - stm_tminus1->m_diffS[8] );
        stm_buffer->m_diffS[9]  =   0.5*(3*stm->m_diffS[9]  - stm_tminus1->m_diffS[9] );
        stm_buffer->m_diffS[10] =   0.5*(3*stm->m_diffS[10] - stm_tminus1->m_diffS[10]);
        stm_buffer->m_diffS[11] =   0.5*(3*stm->m_diffS[11] - stm_tminus1->m_diffS[11]);
        stm_buffer->m_diffS[12] =   0.5*(3*stm->m_diffS[12] - stm_tminus1->m_diffS[12]);
        stm_buffer->m_diffS[13] =   0.5*(3*stm->m_diffS[13] - stm_tminus1->m_diffS[13]);
        stm_buffer->m_diffS[14] =   0.5*(3*stm->m_diffS[14] - stm_tminus1->m_diffS[14]);
        stm_buffer->m_diffS[15] =   0.5*(3*stm->m_diffS[15] - stm_tminus1->m_diffS[15]);
        stm_buffer->m_diffS[16] =   0.5*(3*stm->m_diffS[16] - stm_tminus1->m_diffS[16]);
        stm_buffer->m_diffS[17] =   0.5*(3*stm->m_diffS[17] - stm_tminus1->m_diffS[17]);


        vehstate_buffer->ax_veh_mps2 = vehstate->ax_veh_mps2 + 0.5*stm->timestep*(3*vehstate->ax_veh_mps2 - vehstate_tminus1->ax_veh_mps2);
        vehstate_buffer->ay_veh_mps2 = vehstate->ay_veh_mps2 + 0.5*stm->timestep*(3*vehstate->ay_veh_mps2 - vehstate_tminus1->ay_veh_mps2);


        integrate_update_stm(stm_buffer, vehstate_buffer);
 

        copy_stm_diffS(stm, stm_tminus1);
        copyVehstate(vehstate, vehstate_tminus1);

        copy_stm_diffS(stm_buffer, stm);
        copyVehstate(vehstate_buffer, vehstate);

    }


}


void heun(SingleTrackModel* stm, VehicleState *vehstate){
//This Funvtion integrates the vehiclestate with heuns-method
    SingleTrackModel *stm_buffer;
    stm_buffer = stm_new();

    VehicleState *vehstate_buffer;
    vehstate_buffer = vehstate_new();

    setParameters_stm(stm_buffer);

    copy_stm_diffS(stm, stm_buffer);
    copyVehstate(vehstate, vehstate_buffer);


    //~y = y_i + h*f'
    //y_i+1 = y_i + h*0.5*(f'_i + f'_~y)
    integrate_update_stm(stm_buffer, vehstate_buffer);
    calcLongForce_stm(stm_buffer, vehstate_buffer);
    vehicleModel(stm_buffer, vehstate_buffer);
 

    stm->m_diffS[0]  =   0.5*(stm->m_diffS[0]  + stm_buffer->m_diffS[0] );
    stm->m_diffS[1]  =   0.5*(stm->m_diffS[1]  + stm_buffer->m_diffS[1] );
    stm->m_diffS[2]  =   0.5*(stm->m_diffS[2]  + stm_buffer->m_diffS[2] );
    stm->m_diffS[3]  =   0.5*(stm->m_diffS[3]  + stm_buffer->m_diffS[3] );
    stm->m_diffS[4]  =   0.5*(stm->m_diffS[4]  + stm_buffer->m_diffS[4] );
    stm->m_diffS[5]  =   0.5*(stm->m_diffS[5]  + stm_buffer->m_diffS[5] );
    stm->m_diffS[6]  =   0.5*(stm->m_diffS[6]  + stm_buffer->m_diffS[6] );
    stm->m_diffS[7]  =   0.5*(stm->m_diffS[7]  + stm_buffer->m_diffS[7] );
    stm->m_diffS[8]  =   0.5*(stm->m_diffS[8]  + stm_buffer->m_diffS[8] );
    stm->m_diffS[9]  =   0.5*(stm->m_diffS[9]  + stm_buffer->m_diffS[9] );
    stm->m_diffS[10] =   0.5*(stm->m_diffS[10] + stm_buffer->m_diffS[10]);
    stm->m_diffS[11] =   0.5*(stm->m_diffS[11] + stm_buffer->m_diffS[11]);
    stm->m_diffS[12] =   0.5*(stm->m_diffS[12] + stm_buffer->m_diffS[12]);
    stm->m_diffS[13] =   0.5*(stm->m_diffS[13] + stm_buffer->m_diffS[13]);
    stm->m_diffS[14] =   0.5*(stm->m_diffS[14] + stm_buffer->m_diffS[14]);
    stm->m_diffS[15] =   0.5*(stm->m_diffS[15] + stm_buffer->m_diffS[15]);
    stm->m_diffS[16] =   0.5*(stm->m_diffS[16] + stm_buffer->m_diffS[16]);
    stm->m_diffS[17] =   0.5*(stm->m_diffS[17] + stm_buffer->m_diffS[17]);

    vehstate->ax_veh_mps2 = 0.5*(vehstate->ax_veh_mps2 + vehstate_buffer->ax_veh_mps2);
    vehstate->ay_veh_mps2 = 0.5*(vehstate->ay_veh_mps2 + vehstate_buffer->ay_veh_mps2);
    

    integrate_update_stm(stm, vehstate);
}


void copy_stm_diffS(SingleTrackModel* stm1, SingleTrackModel* stm2){

    stm2->m_diffS[0]  =   stm1->m_diffS[0];
    stm2->m_diffS[1]  =   stm1->m_diffS[1];
    stm2->m_diffS[2]  =   stm1->m_diffS[2];
    stm2->m_diffS[3]  =   stm1->m_diffS[3];
    stm2->m_diffS[4]  =   stm1->m_diffS[4];
    stm2->m_diffS[5]  =   stm1->m_diffS[5];
    stm2->m_diffS[6]  =   stm1->m_diffS[6];
    stm2->m_diffS[7]  =   stm1->m_diffS[7];
    stm2->m_diffS[8]  =   stm1->m_diffS[8];
    stm2->m_diffS[9]  =   stm1->m_diffS[9];
    stm2->m_diffS[10] =   stm1->m_diffS[10];
    stm2->m_diffS[11] =   stm1->m_diffS[11];
    stm2->m_diffS[12] =   stm1->m_diffS[12];
    stm2->m_diffS[13] =   stm1->m_diffS[13];
    stm2->m_diffS[14] =   stm1->m_diffS[14];
    stm2->m_diffS[15] =   stm1->m_diffS[15];
    stm2->m_diffS[16] =   stm1->m_diffS[16];
    stm2->m_diffS[17] =   stm1->m_diffS[17];
 
}


void set_timestep(SingleTrackModel* stm, double timestep){
    stm->timestep = timestep;
}

void set_logging(SingleTrackModel* stm, int value){
    stm->set_logging = value;
}

void set_solver_testcase(SingleTrackModel* stm, int value){
    stm->choose_solver_testcase = value;
}

void set_lograte_testcase(SingleTrackModel* stm, double value){
    stm->log_rate_testcase = value;
}

void set_timecap_testcase(SingleTrackModel* stm, double value){
    stm->timecap_testcase = value;
}

void set_filename_testcase(SingleTrackModel* stm, char* filename){
    //CAUTION filename must not exceed 300 characters 
    //otherwise an this will lead to an undefined behavior 
    //filename must end with the ".csv" 
    strcpy(stm->filename_testcase, filename);
}


double get_param_vehmass_test(SingleTrackModel* stm){
    return stm->m_Vehicle_kg;
}

int get_solver_testcase(SingleTrackModel* stm){
    return stm->choose_solver_testcase;
}

double get_timestep(SingleTrackModel* stm){
    return stm->timestep;
}

int get_logging(SingleTrackModel* stm){
    return stm->set_logging;
}

double get_lograte_testcase(SingleTrackModel* stm){
    return stm->log_rate_testcase;
}

double get_timecap_testcase(SingleTrackModel* stm){
    return stm->timecap_testcase;
}

char* get_filename_testcase(SingleTrackModel* stm){
    return stm->filename_testcase;
}

