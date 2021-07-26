#include "../include/TireModel.h"

#include <math.h>
#include <string.h>

#define SIGNUM(x)((x>0)?1:((x<0)?-1:0))
#define MAX(a,b)((a>b)?a:b)
#define MIN(a,b)((a<b)?a:b)

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif


void testinput(struct TireState* tirestate, const double *fz, const double *kappa, const double *alpha){
    /*
    This testinput was used to debug the magicFormula52 function via matlab and compare it
    */
    tirestate->fz = *fz;
    tirestate->kappa = *kappa;
    tirestate->alpha = *alpha;

}


//void calcTirestatus(Parameters_dtm* param_dtm, struct TireState* tirestate, const double *vx, const double *vy, const double *psidot){
void calcFz(Parameters_dtm* param_dtm, VehicleState *vehstate){

    //fz
    //TODO take influence of pitch and roll angle into account ?!!

    double fz_static_fl_N = 0.0, fz_static_fr_N = 0.0, fz_static_rl_N = 0.0, fz_static_rr_N = 0.0;
    double fz_aero_fl_N = 0.0, fz_aero_fr_N = 0.0, fz_aero_rl_N = 0.0, fz_aero_rr_N = 0.0;
    double fz_pitch_fl_N = 0.0, fz_pitch_fr_N = 0.0, fz_pitch_rl_N = 0.0, fz_pitch_rr_N = 0.0;
    double fz_roll_fl_N = 0.0, fz_roll_fr_N = 0.0, fz_roll_rl_N = 0.0, fz_roll_rr_N = 0.0;


    fz_static_fl_N = param_dtm->vehicleparameters.m_Vehicle_kg*param_dtm->vehicleparameters.a_Gravity_mps2*(param_dtm->vehicleparameters.l_WheelbaseTotal_m-param_dtm->vehicleparameters.l_WheelbaseF_m)/ \
        param_dtm->vehicleparameters.l_WheelbaseTotal_m*0.5;
    
    fz_static_fr_N = fz_static_fl_N;

    fz_static_rl_N = param_dtm->vehicleparameters.m_Vehicle_kg*param_dtm->vehicleparameters.a_Gravity_mps2*param_dtm->vehicleparameters.l_WheelbaseF_m/ \
        param_dtm->vehicleparameters.l_WheelbaseTotal_m*0.5;

    fz_static_rr_N = fz_static_rl_N;


    fz_aero_fl_N = (0.5*param_dtm->vehicleparameters.airDensity_kgpm3* \
        param_dtm->vehicleparameters.cl_LongitudinalLift*param_dtm->vehicleparameters.A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps)\
        *(param_dtm->vehicleparameters.l_WheelbaseTotal_m-param_dtm->vehicleparameters.l_WheelbaseF_m)/param_dtm->vehicleparameters.l_WheelbaseTotal_m;

    fz_aero_fr_N = fz_aero_fl_N;
    
    fz_aero_rl_N = (0.5*param_dtm->vehicleparameters.airDensity_kgpm3* \
        param_dtm->vehicleparameters.cl_LongitudinalLift*param_dtm->vehicleparameters.A_LongitudinalDrag_m2*vehstate->vx_veh_mps*vehstate->vx_veh_mps)\
        *param_dtm->vehicleparameters.l_WheelbaseF_m/param_dtm->vehicleparameters.l_WheelbaseTotal_m;
    
    fz_aero_rr_N = fz_aero_rl_N;

    //TODO check calculation 
    /*
    fz_pitch_fl_N = 0.5*((vehstate->tirestate_rl.fz+vehstate->tirestate_rr.fz)*(param_dtm->vehicleparameters.l_WheelbaseTotal_m-param_dtm->vehicleparameters.l_WheelbaseF_m)\
        - (vehstate->tirestate_fl.fz+vehstate->tirestate_fr.fz)*param_dtm->vehicleparameters.l_WheelbaseF_m);
    
    fz_pitch_fr_N = fz_pitch_fl_N;
    */
    
    //update fz
    vehstate->tirestate_fl.fz = fz_static_fl_N + fz_aero_fl_N + fz_pitch_fl_N + fz_roll_fl_N;
    vehstate->tirestate_fr.fz = fz_static_fr_N + fz_aero_fr_N + fz_pitch_fr_N + fz_roll_fr_N;
    vehstate->tirestate_rl.fz = fz_static_rl_N + fz_aero_rl_N + fz_pitch_rl_N + fz_roll_rl_N;
    vehstate->tirestate_rr.fz = fz_static_rr_N + fz_aero_rr_N + fz_pitch_rr_N + fz_roll_rr_N;


}


void calcLongForce(Parameters_dtm *param_dtm, VehicleState *vehstate){

    double limitedWheelSpeed[4]; 

    limitedWheelSpeed[0] = (vehstate->tirestate_fl.omega_radps < 0) ? 0 : (param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirefl.unloaded_radius < vehstate->tirestate_fl.omega_radps) ? param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirefl.unloaded_radius : vehstate->tirestate_fl.omega_radps;
    limitedWheelSpeed[1] = (vehstate->tirestate_fr.omega_radps < 0) ? 0 : (param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirefr.unloaded_radius < vehstate->tirestate_fr.omega_radps) ? param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirefr.unloaded_radius : vehstate->tirestate_fr.omega_radps;
    limitedWheelSpeed[2] = (vehstate->tirestate_rl.omega_radps < 0) ? 0 : (param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirerl.unloaded_radius < vehstate->tirestate_rl.omega_radps) ? param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirerl.unloaded_radius : vehstate->tirestate_rl.omega_radps;
    limitedWheelSpeed[3] = (vehstate->tirestate_rr.omega_radps < 0) ? 0 : (param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirerr.unloaded_radius < vehstate->tirestate_rr.omega_radps) ? param_dtm->vehicleparameters.switchModelVel_mps/param_dtm->tirerr.unloaded_radius : vehstate->tirestate_rr.omega_radps;
    

    vehstate->tirestate_fl.tireBrakeTorque = vehstate->tirestate_fl.brakePressure_Pa*param_dtm->vehicleparameters.r_BrakePadsMeanLeverFrRe_m[0]*param_dtm->vehicleparameters.mue_BrakePadsFrRe_kinetic[0]*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[0]*0.5)*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[0]*0.5)*M_PI*0.25*param_dtm->vehicleparameters.n_BrakePadsNumberFrRe[0]*limitedWheelSpeed[0]*param_dtm->tirefl.unloaded_radius/param_dtm->vehicleparameters.switchModelVel_mps;
    vehstate->tirestate_fr.tireBrakeTorque = vehstate->tirestate_fr.brakePressure_Pa*param_dtm->vehicleparameters.r_BrakePadsMeanLeverFrRe_m[0]*param_dtm->vehicleparameters.mue_BrakePadsFrRe_kinetic[0]*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[0]*0.5)*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[0]*0.5)*M_PI*0.25*param_dtm->vehicleparameters.n_BrakePadsNumberFrRe[0]*limitedWheelSpeed[1]*param_dtm->tirefr.unloaded_radius/param_dtm->vehicleparameters.switchModelVel_mps;
    vehstate->tirestate_rl.tireBrakeTorque = vehstate->tirestate_rl.brakePressure_Pa*param_dtm->vehicleparameters.r_BrakePadsMeanLeverFrRe_m[1]*param_dtm->vehicleparameters.mue_BrakePadsFrRe_kinetic[1]*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[1]*0.5)*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[1]*0.5)*M_PI*0.25*param_dtm->vehicleparameters.n_BrakePadsNumberFrRe[1]*limitedWheelSpeed[2]*param_dtm->tirerl.unloaded_radius/param_dtm->vehicleparameters.switchModelVel_mps;
    vehstate->tirestate_rr.tireBrakeTorque = vehstate->tirestate_rr.brakePressure_Pa*param_dtm->vehicleparameters.r_BrakePadsMeanLeverFrRe_m[1]*param_dtm->vehicleparameters.mue_BrakePadsFrRe_kinetic[1]*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[1]*0.5)*(param_dtm->vehicleparameters.d_BrakeActuatorBoreFrRe_m[1]*0.5)*M_PI*0.25*param_dtm->vehicleparameters.n_BrakePadsNumberFrRe[1]*limitedWheelSpeed[3]*param_dtm->tirerr.unloaded_radius/param_dtm->vehicleparameters.switchModelVel_mps;


    vehstate->tirestate_fl.fx_powertrain = vehstate->tirestate_fl.tireDriveTorque/param_dtm->tirefl.unloaded_radius - vehstate->tirestate_fl.tireBrakeTorque/param_dtm->tirefl.unloaded_radius;
    vehstate->tirestate_fr.fx_powertrain = vehstate->tirestate_fr.tireDriveTorque/param_dtm->tirefr.unloaded_radius - vehstate->tirestate_fr.tireBrakeTorque/param_dtm->tirefl.unloaded_radius;
    vehstate->tirestate_rl.fx_powertrain = vehstate->tirestate_rl.tireDriveTorque/param_dtm->tirerl.unloaded_radius - vehstate->tirestate_rl.tireBrakeTorque/param_dtm->tirefl.unloaded_radius;
    vehstate->tirestate_rr.fx_powertrain = vehstate->tirestate_rr.tireDriveTorque/param_dtm->tirerr.unloaded_radius - vehstate->tirestate_rr.tireBrakeTorque/param_dtm->tirefl.unloaded_radius;
}


void calcWheelSlips(Parameters_dtm *param_dtm, VehicleState *vehstate){
//calculate longitudinal wheel sleep and lateral side slip of each individual tire 

    //initalize variables    
    //double vxCG, vyCG, dPsi;
    double v_ref[4]={0, 0, 0, 0}, v_wheel[4]={0, 0, 0, 0};
    double v_wheel_fl=0.0, v_wheel_fr=0.0, v_wheel_rl=0.0,v_wheel_rr=0.0;
    double vx_fr=0.0, vx_fl=0.0,vx_rr=0.0, vx_rl=0.0, vy_fr=0.0, vy_fl=0.0, vy_rr=0.0, vy_rl=0.0;
    double rotationMatrixFront[2][2]= {{0,0}, {0,0}};
    double vxT_fl=0.0, vxT_fr=0.0, vyT_fl=0.0, vyT_fr=0.0;
    
    //calculate chassis velocities at wheel centers projected to the ground   
    vx_fr = vehstate->vx_veh_mps + (vehstate->dpsi_veh*param_dtm->vehicleparameters.w_TrackF_m*0.5);
    vx_fl = vehstate->vx_veh_mps - (vehstate->dpsi_veh*param_dtm->vehicleparameters.w_TrackF_m*0.5);
    vx_rr = vehstate->vx_veh_mps + (vehstate->dpsi_veh*param_dtm->vehicleparameters.w_TrackR_m*0.5);
    vx_rl = vehstate->vx_veh_mps - (vehstate->dpsi_veh*param_dtm->vehicleparameters.w_TrackR_m*0.5);
    vy_fr = vehstate->vy_veh_mps + (vehstate->dpsi_veh*param_dtm->vehicleparameters.l_WheelbaseF_m);
    vy_fl = vehstate->vy_veh_mps + (vehstate->dpsi_veh*param_dtm->vehicleparameters.l_WheelbaseF_m);
    vy_rr = vehstate->vy_veh_mps - (vehstate->dpsi_veh*(param_dtm->vehicleparameters.l_WheelbaseTotal_m-param_dtm->vehicleparameters.l_WheelbaseF_m));
    vy_rl = vehstate->vy_veh_mps - (vehstate->dpsi_veh*(param_dtm->vehicleparameters.l_WheelbaseTotal_m-param_dtm->vehicleparameters.l_WheelbaseF_m));

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
    if(vehstate->vx_veh_mps > param_dtm->vehicleparameters.vx_min_mps){
        vehstate->tirestate_fl.alpha = atan2(-vyT_fl, vxT_fl);
        vehstate->tirestate_fr.alpha = atan2(-vyT_fr, vxT_fr);
        vehstate->tirestate_rl.alpha = atan2(-vy_rl, vx_rl);
        vehstate->tirestate_rr.alpha = atan2(-vy_rr, vx_rr);
    } else {
        vehstate->tirestate_fl.alpha = 0.0;
        vehstate->tirestate_fr.alpha = 0.0;
        vehstate->tirestate_rl.alpha = 0.0;
        vehstate->tirestate_rr.alpha = 0.0;
    }


    //calculate wheel over ground velocities
    v_wheel_fl = param_dtm->tirefl.unloaded_radius*vehstate->tirestate_fl.omega_radps;
    v_wheel_fr = param_dtm->tirefr.unloaded_radius*vehstate->tirestate_fr.omega_radps;
    v_wheel_rl = param_dtm->tirerl.unloaded_radius*vehstate->tirestate_rl.omega_radps;
    v_wheel_rr = param_dtm->tirerr.unloaded_radius*vehstate->tirestate_rr.omega_radps;

   vehstate->tirestate_fl.kappa = (v_wheel_fl-vxT_fl)/MAX(param_dtm->vehicleparameters.vx_min_mps, vxT_fl);
   vehstate->tirestate_fr.kappa = (v_wheel_fr-vxT_fr)/MAX(param_dtm->vehicleparameters.vx_min_mps,vxT_fr);
   vehstate->tirestate_rl.kappa = (v_wheel_rl-vx_rl)/MAX(param_dtm->vehicleparameters.vx_min_mps,vx_rl);
   vehstate->tirestate_rr.kappa = (v_wheel_rr-vx_rr)/MAX(param_dtm->vehicleparameters.vx_min_mps,vx_rr);
}


void calcWheelSpeed(Parameters_dtm *param_dtm, VehicleState *vehstate){

    vehstate->tirestate_fl.omega_radps = param_dtm->vehicleparameters.timestep/param_dtm->tirefl.Iyy_Wheel_kgm2*(vehstate->tirestate_fl.tireDriveTorque - vehstate->tirestate_fl.tireBrakeTorque*SIGNUM(vehstate->tirestate_fl.omega_radps) - param_dtm->tirefl.unloaded_radius * vehstate->tirestate_fl.fx) + vehstate->tirestate_fl.omega_radps;
    vehstate->tirestate_fr.omega_radps = param_dtm->vehicleparameters.timestep/param_dtm->tirefr.Iyy_Wheel_kgm2*(vehstate->tirestate_fr.tireDriveTorque - vehstate->tirestate_fr.tireBrakeTorque*SIGNUM(vehstate->tirestate_fr.omega_radps) - param_dtm->tirefr.unloaded_radius * vehstate->tirestate_fr.fx) + vehstate->tirestate_fr.omega_radps;
    vehstate->tirestate_rl.omega_radps = param_dtm->vehicleparameters.timestep/param_dtm->tirerl.Iyy_Wheel_kgm2*(vehstate->tirestate_rl.tireDriveTorque - vehstate->tirestate_rl.tireBrakeTorque*SIGNUM(vehstate->tirestate_rl.omega_radps) - param_dtm->tirerl.unloaded_radius * vehstate->tirestate_rl.fx) + vehstate->tirestate_rl.omega_radps;
    vehstate->tirestate_rr.omega_radps = param_dtm->vehicleparameters.timestep/param_dtm->tirerr.Iyy_Wheel_kgm2*(vehstate->tirestate_rr.tireDriveTorque - vehstate->tirestate_rr.tireBrakeTorque*SIGNUM(vehstate->tirestate_rr.omega_radps) - param_dtm->tirerr.unloaded_radius * vehstate->tirestate_rr.fx) + vehstate->tirestate_rr.omega_radps;

    //TODO check if runge kutta works better here for the integration! 
    vehstate->tirestate_fl.roh = vehstate->tirestate_fl.roh + vehstate->tirestate_fl.omega_radps * param_dtm->vehicleparameters.timestep;
    vehstate->tirestate_fr.roh = vehstate->tirestate_fr.roh + vehstate->tirestate_fr.omega_radps * param_dtm->vehicleparameters.timestep;
    vehstate->tirestate_rl.roh = vehstate->tirestate_rl.roh + vehstate->tirestate_rl.omega_radps * param_dtm->vehicleparameters.timestep;
    vehstate->tirestate_rr.roh = vehstate->tirestate_rr.roh + vehstate->tirestate_rr.omega_radps * param_dtm->vehicleparameters.timestep;
}

void magicFormula52_c(struct Tireparameters *tire_param, struct TireState* tirestate,  VehicleState *vehstate){

    //varsign 
    int varsign;
    if(strcmp(tire_param->tyreside, "'RIGHT'")==0){
        varsign = 1;
    }else{
        varsign = -1;
    };

    tirestate->alpha = tirestate->alpha*varsign;
    tirestate->gamma = tirestate->gamma*varsign;

    //Referenzgeschwindigkeit auf diejenige aus dem Reifenfile festlegen
    double vref = tire_param->longvl;
    
    double fnomin_ = tire_param->fnomin*tire_param->lfzo;
    double dfz = (tirestate->fz-fnomin_)/fnomin_;

    //LONGITUDINAL

    //pure slip
    double gammax = tirestate->gamma*tire_param->lgax;
    double shx = (tire_param->phx1+tire_param->phx2*dfz)*tire_param->lvx*tire_param->lmux;
    double svx = tirestate->fz*(tire_param->pvx1+tire_param->pvx2*dfz)*tire_param->lvx*tire_param->lmux;
    double kappax = tirestate->kappa+shx;
    double mux = (tire_param->pdx1+tire_param->pdx2*dfz)*(1-tire_param->pdx3*gammax*gammax)*tire_param->lmux;
    double cx = tire_param->pcx1*tire_param->lcx;
    double dx = mux*tirestate->fz;
    double ex = (tire_param->pex1+tire_param->pex2*dfz+tire_param->pex3*dfz*dfz)*(1-tire_param->pex4*SIGNUM(kappax))*tire_param->lex;
    ex = (ex>1.0)?1:ex;
    double kx = tirestate->fz*(tire_param->pkx1+tire_param->pkx2*dfz)*exp(tire_param->pkx3*dfz)*tire_param->lkx;
    double bx = kx/(cx*dx);
    double fx0 = dx*sin(cx*atan(bx*kappax-ex*(bx*kappax-atan(bx*kappax))))+svx;

    //combined slip 
    double shxa = tire_param->rhx1;
    double alphas = tirestate->alpha+shxa;
    double bxa = tire_param->rbx1*cos(atan(tire_param->rbx2*tirestate->kappa))*tire_param->lxal;
    double cxa = tire_param->rcx1;
    double exa = tire_param->rex1+tire_param->rex2*dfz;
    double gxa0 = cos(cxa*atan(bxa*shxa-exa*(bxa*shxa-atan(bxa*shxa))));
    double gxa = cos(cxa*atan(bxa*alphas-exa*(bxa*alphas-atan(bxa*alphas))))/gxa0;
    tirestate->fx_tire = gxa*fx0;

    //LATERAL 

    //pure slip
    double gammay = tirestate->gamma*tire_param->lgay;
    double shy = (tire_param->phy1+tire_param->phy2*dfz)*tire_param->lhy+tire_param->phy3*gammay;
    double alphay = tirestate->alpha + shy;
    double muy = (tire_param->pdy1+tire_param->pdy2*dfz)*(1.0-tire_param->pdy3*gammay*gammay)*tire_param->lmuy;
    double svy = tirestate->fz*((tire_param->pvy1+tire_param->pvy2*dfz)*tire_param->lvy+(tire_param->pvy3+tire_param->pvy4*dfz)*gammay)*tire_param->lmuy;
    double dy = muy*tirestate->fz;
    double cy = tire_param->pcy1*tire_param->lcy;
    double ey = (tire_param->pey1+tire_param->pey2*dfz)*(1.0-(tire_param->pey3+tire_param->pey4*gammay)*SIGNUM(alphay))*tire_param->ley;
    ey = (ey>1.0)?1:ey;
    double ky = tire_param->pky1*tire_param->fnomin*sin(2.0*atan(tirestate->fz/(tire_param->pky2*tire_param->fnomin*tire_param->lfzo)))*(1-tire_param->pky3*fabs(gammay))*tire_param->lfzo*tire_param->lky;
    double by = ky/(cy*dy);
    double fy0 = dy*sin(cy*atan(by*alphay-ey*(by*alphay-atan(by*alphay))))+svy;

    //combined slip
    double shyk = tire_param->rhy1+tire_param->rhy2*dfz;
    double kappas = tirestate->kappa+shyk;
    double byk = tire_param->rby1*cos(atan(tire_param->rby2*(tirestate->alpha-tire_param->rby3)))*tire_param->lyka;
    double cyk = tire_param->rcy1; 
    double eyk = tire_param->rey1+tire_param->rey2*dfz;
    double dvyk = muy*tirestate->fz*(tire_param->rvy1+tire_param->rvy2*dfz+tire_param->rvy3*tirestate->gamma)*cos(atan(tire_param->rvy4*tirestate->alpha));
    double svyk = dvyk*sin(tire_param->rvy5*atan(tire_param->rvy6*tirestate->kappa))*tire_param->lvyka;
    double gyk0 = cos(cyk*atan(byk*shyk-eyk*(byk*shyk-atan(byk*shyk))));
    double gyk = cos(cyk*atan(byk*kappas-eyk*(byk*kappas-atan(byk*kappas))))/gyk0;
    tirestate->fy_tire = gyk*fy0+svyk;

    //ALIGNING TORQUE 

    //pure slip 
    double gammaz = tirestate->gamma*tire_param->lgaz;
    double sht = tire_param->qhz1+tire_param->qhz2*dfz+(tire_param->qhz3*tire_param->qhz4*dfz)*gammaz;
    double alphat = tirestate->alpha+sht;
    double bt = (tire_param->qbz1+tire_param->qbz2*dfz+tire_param->qbz3*dfz*dfz)*(1+tire_param->qbz4*gammaz+tire_param->qbz5*fabs(gammaz))*tire_param->lky/tire_param->lmuy;
    double ct = tire_param->qcz1;
    double dt = tirestate->fz*(tire_param->qdz1+tire_param->qdz2*dfz)*(1+tire_param->qdz3*gammaz+tire_param->qdz4*gammaz*gammaz)*(tire_param->unloaded_radius/tire_param->fnomin)*tire_param->ltr;
    double et = (tire_param->qez1+tire_param->qez2*dfz+tire_param->qez3*dfz*dfz);//*(1+(tire_param->qez4+tire_param->qez5*gammaz)*2.0/M_PI*atan(bt*ct*alphat));
    et = (et>1.0)?1.0:et;
    double shr = shy+svy/ky;
    double alphar = tirestate->alpha+shr;
    double dr = tirestate->fz*((tire_param->qdz6+tire_param->qdz7*dfz)*tire_param->lres+(tire_param->qdz8+tire_param->qdz9*dfz)*gammaz)*tire_param->unloaded_radius*tire_param->lmuy;
    double br = tire_param->qbz9*tire_param->lky/tire_param->lmuy+tire_param->qbz10*by*cy;

    //combine slip
    double alphateq = atan(sqrt((tan(alphat)*tan(alphat))+(kx/ky)*(kx/ky)*tirestate->kappa*tirestate->kappa))*SIGNUM(alphat);
    double alphareq = atan(sqrt((tan(alphar)*tan(alphar))+(kx/ky)*(kx/ky)*tirestate->kappa*tirestate->kappa))*SIGNUM(alphar);
    double t = dt*cos(ct*atan(bt*alphateq-et*(bt*alphateq-atan(bt*alphateq))))*cos(tirestate->alpha);
    double fy_ = tirestate->fy-svyk;
    double mzr = dr*cos(atan(br*alphareq))*cos(tirestate->alpha);
    double s = (tire_param->ssz1+tire_param->ssz2*(tirestate->fy/tire_param->fnomin)+(tire_param->ssz3+tire_param->ssz4*dfz)*tirestate->gamma)*tire_param->unloaded_radius*tire_param->ls;
    tirestate->mz = -t*fy_+mzr+s*tirestate->fx;

    //OVERTRUNING MOMENT

    tirestate->mx= tire_param->unloaded_radius*tirestate->fz*(tire_param->qsx1*tire_param->lvmx+(-tire_param->qsx2*tirestate->gamma+tire_param->qsx3*tirestate->fy/tire_param->fnomin)*tire_param->lmx);

    //ROLLING RESTINTANCE TORQUW 

    if(tire_param->qsy1==0 && tire_param->qsy2==0){
        tirestate->my = tire_param->unloaded_radius*(svx+kx*shx)*SIGNUM(vehstate->vx_veh_mps);
    }else {
        tirestate->my = -tire_param->unloaded_radius*tirestate->fz*(tire_param->qsy1+tire_param->qsy2*tirestate->fx/tire_param->fnomin+tire_param->qsy3*fabs(vehstate->vx_veh_mps/vref)+tire_param->qsy4*pow((vehstate->vx_veh_mps/vref),4))*SIGNUM(vehstate->vx_veh_mps)*tire_param->lmy;
    }

    // Spiegelung der Reifencharakteristik 
    //TODO check SPIEGELUNG!!!
    tirestate->fy_tire = varsign*tirestate->fy;
    tirestate->mx = varsign*tirestate->mx;
    tirestate->mz = varsign*tirestate->mz;


    //transform tire forces from tire coordinate system in vehicle coordinate system 
    double rotMat_tire_veh_front[3][3] = 
    {
        {
        cos(vehstate->steeringangle)*cos(vehstate->theta_ini),
        -sin(vehstate->steeringangle)*cos(vehstate->theta_ini),
        -sin(vehstate->theta_ini)
        },
        {
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->steeringangle) + cos(vehstate->phi_ini)*sin(vehstate->steeringangle),
        -sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->steeringangle) + cos(vehstate->phi_ini)*cos(vehstate->steeringangle),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
        {
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->steeringangle) - sin(vehstate->phi_ini)*sin(vehstate->steeringangle),
        -cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->steeringangle) - sin(vehstate->phi_ini)*cos(vehstate->steeringangle),
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        }
    };


    double rotMat_tire_veh_rear[3][3] = 
    {
        {
        cos(vehstate->theta_ini),
        0.0,
        -sin(vehstate->theta_ini)
        },
        {
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini),
        cos(vehstate->phi_ini),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
        {
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini),
        -sin(vehstate->phi_ini),
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        }
    };

    //transform fx_tire to fx 'veh'
    tirestate->fx = rotMat_tire_veh_front[0][0]*tirestate->fx_tire + rotMat_tire_veh_front[0][1]*tirestate->fy_tire + rotMat_tire_veh_front[0][2]*tirestate->fz;
    
    //transform fy_tire to fy 'veh'
    tirestate->fy = rotMat_tire_veh_front[1][0]*tirestate->fx_tire + rotMat_tire_veh_front[1][1]*tirestate->fy_tire + rotMat_tire_veh_front[1][2]*tirestate->fz;


}


void magicFormula52(struct Tireparameters *tire_param, struct TireState* tirestate, const double *gamma, const double *vx)
{  

    //double *fz, double *kappa, double *alpha,
    
    //Referenzgeschwindigkeit auf diejenige aus dem Reifenfile festlegen
    double vref = tire_param->longvl;
    
    double fnomin_ = tire_param->fnomin*tire_param->lfzo;
    double dfz = (tirestate->fz-fnomin_)/fnomin_;

    //LONGITUDINAL

    //pure slip
    double gammax = (*gamma)*tire_param->lgax;
    double shx = (tire_param->phx1+tire_param->phx2*dfz)*tire_param->lvx*tire_param->lmux;
    double svx = tirestate->fz*(tire_param->pvx1+tire_param->pvx2*dfz)*tire_param->lvx*tire_param->lmux;
    double kappax = tirestate->kappa+shx;
    double mux = (tire_param->pdx1+tire_param->pdx2*dfz)*(1-tire_param->pdx3*gammax*gammax)*tire_param->lmux;
    double cx = tire_param->pcx1*tire_param->lcx;
    double dx = mux*tirestate->fz;
    double ex = (tire_param->pex1+tire_param->pex2*dfz+tire_param->pex3*dfz*dfz)*(1-tire_param->pex4*SIGNUM(kappax))*tire_param->lex;
    ex = (ex>1.0)?1:ex;
    double kx = tirestate->fz*(tire_param->pkx1+tire_param->pkx2*dfz)*exp(tire_param->pkx3*dfz)*tire_param->lkx;
    double bx = kx/(cx*dx);
    double fx0 = dx*sin(cx*atan(bx*kappax-ex*(bx*kappax-atan(bx*kappax))))+svx;

    //combined slip 
    double shxa = tire_param->rhx1;
    double alphas = tirestate->alpha+shxa;
    double bxa = tire_param->rbx1*cos(atan(tire_param->rbx2*tirestate->kappa))*tire_param->lxal;
    double cxa = tire_param->rcx1;
    double exa = tire_param->rex1+tire_param->rex2*dfz;
    double gxa0 = cos(cxa*atan(bxa*shxa-exa*(bxa*shxa-atan(bxa*shxa))));
    double gxa = cos(cxa*atan(bxa*alphas-exa*(bxa*alphas-atan(bxa*alphas))))/gxa0;
    tirestate->fx = gxa*fx0;

    //LATERAL 

    //pure slip
    double gammay = (*gamma)*tire_param->lgay;
    double shy = (tire_param->phy1+tire_param->phy2*dfz)*tire_param->lhy+tire_param->phy3*gammay;
    double alphay = tirestate->alpha + shy;
    double muy = (tire_param->pdy1+tire_param->pdy2*dfz)*(1.0-tire_param->pdy3*gammay*gammay)*tire_param->lmuy;
    double svy = tirestate->fz*((tire_param->pvy1+tire_param->pvy2*dfz)*tire_param->lvy+(tire_param->pvy3+tire_param->pvy4*dfz)*gammay)*tire_param->lmuy;
    double dy = muy*tirestate->fz;
    double cy = tire_param->pcy1*tire_param->lcy;
    double ey = (tire_param->pey1+tire_param->pey2*dfz)*(1.0-(tire_param->pey3+tire_param->pey4*gammay)*SIGNUM(alphay))*tire_param->ley;
    ey = (ey>1.0)?1:ey;
    double ky = tire_param->pky1*tire_param->fnomin*sin(2.0*atan(tirestate->fz/(tire_param->pky2*tire_param->fnomin*tire_param->lfzo)))*(1-tire_param->pky3*fabs(gammay))*tire_param->lfzo*tire_param->lky;
    double by = ky/(cy*dy);
    double fy0 = dy*sin(cy*atan(by*alphay-ey*(by*alphay-atan(by*alphay))))+svy;

    //combined slip
    double shyk = tire_param->rhy1+tire_param->rhy2*dfz;
    double kappas = tirestate->kappa+shyk;
    double byk = tire_param->rby1*cos(atan(tire_param->rby2*(tirestate->alpha-tire_param->rby3)))*tire_param->lyka;
    double cyk = tire_param->rcy1; 
    double eyk = tire_param->rey1+tire_param->rey2*dfz;
    double dvyk = muy*tirestate->fz*(tire_param->rvy1+tire_param->rvy2*dfz+tire_param->rvy3*(*gamma))*cos(atan(tire_param->rvy4*tirestate->alpha));
    double svyk = dvyk*sin(tire_param->rvy5*atan(tire_param->rvy6*tirestate->kappa))*tire_param->lvyka;
    double gyk0 = cos(cyk*atan(byk*shyk-eyk*(byk*shyk-atan(byk*shyk))));
    double gyk = cos(cyk*atan(byk*kappas-eyk*(byk*kappas-atan(byk*kappas))))/gyk0;
    tirestate->fy = gyk*fy0+svyk;

    //ALIGNING TORQUE 

    //pure slip 
    double gammaz = (*gamma)*tire_param->lgaz;
    double sht = tire_param->qhz1+tire_param->qhz2*dfz+(tire_param->qhz3*tire_param->qhz4*dfz)*gammaz;
    double alphat = tirestate->alpha+sht;
    double bt = (tire_param->qbz1+tire_param->qbz2*dfz+tire_param->qbz3*dfz*dfz)*(1+tire_param->qbz4*gammaz+tire_param->qbz5*fabs(gammaz))*tire_param->lky/tire_param->lmuy;
    double ct = tire_param->qcz1;
    double dt = tirestate->fz*(tire_param->qdz1+tire_param->qdz2*dfz)*(1+tire_param->qdz3*gammaz+tire_param->qdz4*gammaz*gammaz)*(tire_param->unloaded_radius/tire_param->fnomin)*tire_param->ltr;
    double et = (tire_param->qez1+tire_param->qez2*dfz+tire_param->qez3*dfz*dfz);//*(1+(tire_param->qez4+tire_param->qez5*gammaz)*2.0/M_PI*atan(bt*ct*alphat));
    et = (et>1.0)?1.0:et;
    double shr = shy+svy/ky;
    double alphar = tirestate->alpha+shr;
    double dr = tirestate->fz*((tire_param->qdz6+tire_param->qdz7*dfz)*tire_param->lres+(tire_param->qdz8+tire_param->qdz9*dfz)*gammaz)*tire_param->unloaded_radius*tire_param->lmuy;
    double br = tire_param->qbz9*tire_param->lky/tire_param->lmuy+tire_param->qbz10*by*cy;

    //combine slip
    double alphateq = atan(sqrt((tan(alphat)*tan(alphat))+(kx/ky)*(kx/ky)*tirestate->kappa*tirestate->kappa))*SIGNUM(alphat);
    double alphareq = atan(sqrt((tan(alphar)*tan(alphar))+(kx/ky)*(kx/ky)*tirestate->kappa*tirestate->kappa))*SIGNUM(alphar);
    double t = dt*cos(ct*atan(bt*alphateq-et*(bt*alphateq-atan(bt*alphateq))))*cos(tirestate->alpha);
    double fy_ = tirestate->fy-svyk;
    double mzr = dr*cos(atan(br*alphareq))*cos(tirestate->alpha);
    double s = (tire_param->ssz1+tire_param->ssz2*(tirestate->fy/tire_param->fnomin)+(tire_param->ssz3+tire_param->ssz4*dfz)*(*gamma))*tire_param->unloaded_radius*tire_param->ls;
    tirestate->mz = -t*fy_+mzr+s*tirestate->fx;

    //OVERTRUNING MOMENT

    tirestate->mx= tire_param->unloaded_radius*tirestate->fz*(tire_param->qsx1*tire_param->lvmx+(-tire_param->qsx2*(*gamma)+tire_param->qsx3*tirestate->fy/tire_param->fnomin)*tire_param->lmx);

    //ROLLING RESTINTANCE TORQUW 

    if(tire_param->qsy1==0 && tire_param->qsy2==0){
        tirestate->my = tire_param->unloaded_radius*(svx+kx*shx)*SIGNUM(vx);
    }else {
        tirestate->my = -tire_param->unloaded_radius*tirestate->fz*(tire_param->qsy1+tire_param->qsy2*tirestate->fx/tire_param->fnomin+tire_param->qsy3*fabs((*vx)/vref)+tire_param->qsy4*pow((*vx/vref),4))*SIGNUM(*vx)*tire_param->lmy;
    }

// Spiegelung der Reifencharakteristik 
    //tirestate->debug = tirestate->fx;
}


void Pacejka5Param(Parameters_dtm *param_dtm, VehicleState *vehstate){
    //Pacjeka tire model based on a four coefficient approach
    //evaluates the lateral and longitudinal tire forces using the specified 
    //pacjeka models for front and rear
        
    vehstate->tirestate_fl.fx_tire = vehstate->tirestate_fl.fz/param_dtm->vehicleparameters.m_pac_front_long[4]*param_dtm->vehicleparameters.m_pac_front_long[2]\
        *sin(param_dtm->vehicleparameters.m_pac_front_long[1]*atan(param_dtm->vehicleparameters.m_pac_front_long[0]*vehstate->tirestate_fl.kappa\
        -param_dtm->vehicleparameters.m_pac_front_long[3]*(param_dtm->vehicleparameters.m_pac_front_long[0]*(vehstate->tirestate_fl.kappa)\
        -atan(param_dtm->vehicleparameters.m_pac_front_long[0]*(vehstate->tirestate_fl.kappa)))));
    
    vehstate->tirestate_fr.fx_tire = vehstate->tirestate_fr.fz/param_dtm->vehicleparameters.m_pac_front_long[4]*param_dtm->vehicleparameters.m_pac_front_long[2]\
        *sin(param_dtm->vehicleparameters.m_pac_front_long[1]*atan(param_dtm->vehicleparameters.m_pac_front_long[0]*vehstate->tirestate_fr.kappa\
        -param_dtm->vehicleparameters.m_pac_front_long[3]*(param_dtm->vehicleparameters.m_pac_front_long[0]*vehstate->tirestate_fr.kappa\
        -atan(param_dtm->vehicleparameters.m_pac_front_long[0]*vehstate->tirestate_fr.kappa))));
    
    vehstate->tirestate_rl.fx_tire = vehstate->tirestate_rl.fz/param_dtm->vehicleparameters.m_pac_rear_long[4]*param_dtm->vehicleparameters.m_pac_rear_long[2]\
        *sin(param_dtm->vehicleparameters.m_pac_rear_long[1]*atan(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rl.kappa\
        -param_dtm->vehicleparameters.m_pac_rear_long[3]*(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rl.kappa\
        -atan(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rl.kappa))));
    
    vehstate->tirestate_rr.fx_tire = vehstate->tirestate_rr.fz/param_dtm->vehicleparameters.m_pac_rear_long[4]*param_dtm->vehicleparameters.m_pac_rear_long[2]\
        *sin(param_dtm->vehicleparameters.m_pac_rear_long[1]*atan(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rr.kappa\
        -param_dtm->vehicleparameters.m_pac_rear_long[3]*(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rr.kappa\
        -atan(param_dtm->vehicleparameters.m_pac_rear_long[0]*vehstate->tirestate_rr.kappa))));


    vehstate->tirestate_fl.fy_tire = vehstate->tirestate_fl.fz/param_dtm->vehicleparameters.m_pac_front_lat[4]*param_dtm->vehicleparameters.m_pac_front_lat[2]\
        *sin(param_dtm->vehicleparameters.m_pac_front_lat[1]*atan(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fl.alpha\
        -param_dtm->vehicleparameters.m_pac_front_lat[3]*(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fl.alpha\
        -atan(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fl.alpha))));
    
    vehstate->tirestate_fr.fy_tire = vehstate->tirestate_fr.fz/param_dtm->vehicleparameters.m_pac_front_lat[4]*param_dtm->vehicleparameters.m_pac_front_lat[2]\
        *sin(param_dtm->vehicleparameters.m_pac_front_lat[1]*atan(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fr.alpha\
        -param_dtm->vehicleparameters.m_pac_front_lat[3]*(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fr.alpha\
        -atan(param_dtm->vehicleparameters.m_pac_front_lat[0]*vehstate->tirestate_fr.alpha))));
    
    vehstate->tirestate_rl.fy_tire = vehstate->tirestate_rl.fz/param_dtm->vehicleparameters.m_pac_rear_lat[4]*param_dtm->vehicleparameters.m_pac_rear_lat[2]\
        *sin(param_dtm->vehicleparameters.m_pac_rear_lat[1]*atan(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha\
        -param_dtm->vehicleparameters.m_pac_rear_lat[3]*(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha\
        -atan(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rl.alpha))));
    
    vehstate->tirestate_rr.fy_tire = vehstate->tirestate_rr.fz/param_dtm->vehicleparameters.m_pac_rear_lat[4]*param_dtm->vehicleparameters.m_pac_rear_lat[2]\
        *sin(param_dtm->vehicleparameters.m_pac_rear_lat[1]*atan(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha\
        -param_dtm->vehicleparameters.m_pac_rear_lat[3]*(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha\
        -atan(param_dtm->vehicleparameters.m_pac_rear_lat[0]*vehstate->tirestate_rr.alpha))));


    //TODO transform tire forces to veh coordinate system 
    double rotMat_tire_veh_front[3][3] = 
    {
        {
        cos(vehstate->steeringangle)*cos(vehstate->theta_ini),
        -sin(vehstate->steeringangle)*cos(vehstate->theta_ini),
        -sin(vehstate->theta_ini)
        },
        {
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->steeringangle) + cos(vehstate->phi_ini)*sin(vehstate->steeringangle),
        -sin(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->steeringangle) + cos(vehstate->phi_ini)*cos(vehstate->steeringangle),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
        {
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*cos(vehstate->steeringangle) - sin(vehstate->phi_ini)*sin(vehstate->steeringangle),
        -cos(vehstate->phi_ini)*sin(vehstate->theta_ini)*sin(vehstate->steeringangle) - sin(vehstate->phi_ini)*cos(vehstate->steeringangle),
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        }
    };


    double rotMat_tire_veh_rear[3][3] = 
    {
        {
        cos(vehstate->theta_ini),
        0.0,
        -sin(vehstate->theta_ini)
        },
        {
        sin(vehstate->phi_ini)*sin(vehstate->theta_ini),
        cos(vehstate->phi_ini),
        sin(vehstate->phi_ini)*cos(vehstate->theta_ini)
        },
        {
        cos(vehstate->phi_ini)*sin(vehstate->theta_ini),
        -sin(vehstate->phi_ini),
        cos(vehstate->phi_ini)*cos(vehstate->theta_ini)
        }
    };

    //transform fx_tire to fx 'veh'
    vehstate->tirestate_fl.fx = rotMat_tire_veh_front[0][0]*vehstate->tirestate_fl.fx_tire + rotMat_tire_veh_front[0][1]*vehstate->tirestate_fl.fy_tire + rotMat_tire_veh_front[0][2]*vehstate->tirestate_fl.fz;
    vehstate->tirestate_fr.fx = rotMat_tire_veh_front[0][0]*vehstate->tirestate_fr.fx_tire + rotMat_tire_veh_front[0][1]*vehstate->tirestate_fr.fy_tire + rotMat_tire_veh_front[0][2]*vehstate->tirestate_fr.fz;
    vehstate->tirestate_rl.fx = rotMat_tire_veh_rear[0][0]*vehstate->tirestate_rl.fx_tire + rotMat_tire_veh_rear[0][1]*vehstate->tirestate_rl.fy_tire + rotMat_tire_veh_rear[0][2]*vehstate->tirestate_rl.fz;
    vehstate->tirestate_rr.fx = rotMat_tire_veh_rear[0][0]*vehstate->tirestate_rr.fx_tire + rotMat_tire_veh_rear[0][1]*vehstate->tirestate_rr.fy_tire + rotMat_tire_veh_rear[0][2]*vehstate->tirestate_rr.fz;
    
    //transform fy_tire to fy 'veh'
    vehstate->tirestate_fl.fy = rotMat_tire_veh_front[1][0]*vehstate->tirestate_fl.fx_tire + rotMat_tire_veh_front[1][1]*vehstate->tirestate_fl.fy_tire + rotMat_tire_veh_front[1][2]*vehstate->tirestate_fl.fz;
    vehstate->tirestate_fr.fy = rotMat_tire_veh_front[1][0]*vehstate->tirestate_fr.fx_tire + rotMat_tire_veh_front[1][1]*vehstate->tirestate_fr.fy_tire + rotMat_tire_veh_front[1][2]*vehstate->tirestate_fr.fz;
    vehstate->tirestate_rl.fy = rotMat_tire_veh_rear[1][0]*vehstate->tirestate_rl.fx_tire + rotMat_tire_veh_rear[1][1]*vehstate->tirestate_rl.fy_tire + rotMat_tire_veh_rear[1][2]*vehstate->tirestate_rl.fz;
    vehstate->tirestate_rr.fy = rotMat_tire_veh_rear[1][0]*vehstate->tirestate_rr.fx_tire + rotMat_tire_veh_rear[1][1]*vehstate->tirestate_rr.fy_tire + rotMat_tire_veh_rear[1][2]*vehstate->tirestate_rr.fz;

}

