#include "../include/VehicleState.h"
#include <stdlib.h>

VehicleState *vehstate_new(){
    VehicleState *vehstate, buffer = {0};
    vehstate = (VehicleState*)malloc(sizeof(VehicleState));
    *vehstate = buffer;
    return vehstate;
}

void vehstate_free(VehicleState* vehstate){
    free(vehstate);
}

void testSetPos(VehicleState* vehstate, double pos){
    vehstate->pos_ini_1[0] = pos;
}

double getPosIni(VehicleState* vehstate){
    return vehstate->pos_ini_1[0];
}

void copyVehstate(VehicleState *v1, VehicleState *v2){
    
    v2->ddphi_veh = v1->ddphi_veh;
    v2->ddtheta_veh = v1->ddtheta_veh;
    v2->ddpsi_veh = v1->ddpsi_veh;

    
    v2->dphi_veh = v1->dphi_veh;
    v2->dtheta_veh = v1->dtheta_veh;
    v2->dpsi_veh = v1->dpsi_veh;

    
    v2->dphi_ini = v1->dphi_ini;
    v2->dtheta_ini = v1->dtheta_ini;
    v2->dpsi_ini = v1->dpsi_ini;

    v2->phi_ini = v1->phi_ini;
    v2->theta_ini = v1->theta_ini;
    v2->psi_ini = v1->psi_ini;
    
    v2->ax_veh_mps2 = v1->ax_veh_mps2;
    v2->ay_veh_mps2 = v1->ay_veh_mps2;

    
    v2->vx_veh_mps = v1->vx_veh_mps;
    v2->vy_veh_mps = v1->vy_veh_mps;

    v2->xpos_veh1_m = v1->xpos_veh1_m;
    v2->ypos_veh1_m = v1->ypos_veh1_m;
    v2->zpos_veh1_m = v1->zpos_veh1_m;

    v2->vx_ini_mps = v1->vx_ini_mps;
    v2->vy_ini_mps = v1->vy_ini_mps;
    v2->vz_ini_mps = v1->vz_ini_mps;

    v2->xpos_ini0_m = v1->xpos_ini0_m;
    v2->ypos_ini0_m = v1->ypos_ini0_m;
    v2->zpos_ini0_m = v1->zpos_ini0_m;

    v2->tirestate_fl.tireDriveTorque = v1->tirestate_fl.tireDriveTorque;
    v2->tirestate_fr.tireDriveTorque = v1->tirestate_fr.tireDriveTorque;
    v2->tirestate_rl.tireDriveTorque = v1->tirestate_rl.tireDriveTorque;
    v2->tirestate_rr.tireDriveTorque = v1->tirestate_rr.tireDriveTorque;

    v2->tirestate_fl.brakePressure_Pa = v1->tirestate_fl.brakePressure_Pa;
    v2->tirestate_fr.brakePressure_Pa = v1->tirestate_fr.brakePressure_Pa;
    v2->tirestate_rl.brakePressure_Pa = v1->tirestate_rl.brakePressure_Pa;
    v2->tirestate_rr.brakePressure_Pa = v1->tirestate_rr.brakePressure_Pa;

    v2->tirestate_fl.fx = v1->tirestate_fl.fx;
    v2->tirestate_fr.fx = v1->tirestate_fr.fx;
    v2->tirestate_rl.fx = v1->tirestate_rl.fx;
    v2->tirestate_rr.fx = v1->tirestate_rr.fx;

    v2->tirestate_fl.fy = v1->tirestate_fl.fy;
    v2->tirestate_fr.fy = v1->tirestate_fr.fy;
    v2->tirestate_rl.fy = v1->tirestate_rl.fy;
    v2->tirestate_rr.fy = v1->tirestate_rr.fy;

    v2->tirestate_fl.fz = v1->tirestate_fl.fz;
    v2->tirestate_fr.fz = v1->tirestate_fr.fz;
    v2->tirestate_rl.fz = v1->tirestate_rl.fz;
    v2->tirestate_rr.fz = v1->tirestate_rr.fz;

    v2->tirestate_fl.fx_powertrain = v1->tirestate_fl.fx_powertrain;
    v2->tirestate_fr.fx_powertrain = v1->tirestate_fr.fx_powertrain;
    v2->tirestate_rl.fx_powertrain = v1->tirestate_rl.fx_powertrain;
    v2->tirestate_rr.fx_powertrain = v1->tirestate_rr.fx_powertrain;

    v2->tirestate_fl.alpha = v1->tirestate_fl.alpha;
    v2->tirestate_fr.alpha = v1->tirestate_fr.alpha;
    v2->tirestate_rl.alpha = v1->tirestate_rl.alpha;
    v2->tirestate_rr.alpha = v1->tirestate_rr.alpha;

    v2->tirestate_fl.kappa = v1->tirestate_fl.kappa;
    v2->tirestate_fr.kappa = v1->tirestate_fr.kappa;
    v2->tirestate_rl.kappa = v1->tirestate_rl.kappa;
    v2->tirestate_rr.kappa = v1->tirestate_rr.kappa;

    v2->tirestate_fl.omega_radps = v1->tirestate_fl.omega_radps;
    v2->tirestate_fr.omega_radps = v1->tirestate_fr.omega_radps;
    v2->tirestate_rl.omega_radps = v1->tirestate_rl.omega_radps;
    v2->tirestate_rr.omega_radps = v1->tirestate_rr.omega_radps;

    v2->steeringangle = v1->steeringangle;

    v2->fx_ext_N = v1->fx_ext_N;
    v2->fy_ext_N = v1->fy_ext_N;
    v2->fz_ext_N = v1->fz_ext_N;

    v2->mx_ext_Nm = v1->mx_ext_Nm;
    v2->my_ext_Nm = v1->my_ext_Nm;
    v2->mz_ext_Nm = v1->mz_ext_Nm;
}

//########################
//### GETTER FUNCTIONS ###
//########################
double get_posx_ini(VehicleState* vehstate){
    return vehstate->xpos_ini0_m;
}
double get_posy_ini(VehicleState* vehstate){
    return vehstate->ypos_ini0_m;
}
double get_psi_ini(VehicleState* vehstate){
    return vehstate->psi_ini;
}

double get_vx_veh(VehicleState* vehstate){
    return vehstate->vx_veh_mps;
}
double get_vy_veh(VehicleState* vehstate){
    return vehstate->vy_veh_mps;
}
double get_dpsi_ini(VehicleState* vehstate){
    return vehstate->dpsi_ini;
}

double get_ax_veh(VehicleState* vehstate){
    return vehstate->ax_veh_mps2;
}
double get_ay_veh(VehicleState* vehstate){
    return vehstate->ay_veh_mps2;
}
double get_ddpsi_ini(VehicleState* vehstate){
    return vehstate->ddpsi_veh;
}

double get_omega_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.omega_radps;
}
double get_omega_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.omega_radps;
}
double get_omega_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.omega_radps;
}
double get_omega_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.omega_radps;
}

double get_lambda_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.kappa;
}
double get_lambda_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.kappa;
}
double get_lambda_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.kappa;
}
double get_lambda_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.kappa;
}

double get_alpha_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.alpha;
}
double get_alpha_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.alpha;
}
double get_alpha_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.alpha;
}
double get_alpha_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.alpha;
}

double get_domega_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.domega_radps2;
}
double get_domega_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.domega_radps2;
}
double get_domega_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.domega_radps2;
}
double get_domega_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.domega_radps2;
}


double get_fx_tire_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.fx;
}
double get_fx_tire_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.fx;
}
double get_fx_tire_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.fx;
}
double get_fx_tire_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.fx;
}

double get_fy_tire_fl(VehicleState* vehstate){
    return vehstate->tirestate_fl.fy;
}
double get_fy_tire_fr(VehicleState* vehstate){
    return vehstate->tirestate_fr.fy;
}
double get_fy_tire_rl(VehicleState* vehstate){
    return vehstate->tirestate_rl.fy;
}
double get_fy_tire_rr(VehicleState* vehstate){
    return vehstate->tirestate_rr.fy;
}

double get_steeringangle(VehicleState* vehstate){
    return vehstate->steeringangle;
}

double get_torque_fl_Nm(VehicleState* vehstate){
    return vehstate->tirestate_fl.tireDriveTorque;
}
double get_torque_fr_Nm(VehicleState* vehstate){
    return vehstate->tirestate_fr.tireDriveTorque;
}
double get_torque_rl_Nm(VehicleState* vehstate){
    return vehstate->tirestate_rl.tireDriveTorque;
}
double get_torque_rr_Nm(VehicleState* vehstate){
    return vehstate->tirestate_rr.tireDriveTorque;
}

double get_brakepressure_fl_Pa(VehicleState* vehstate){
    return vehstate->tirestate_fl.brakePressure_Pa;
}
double get_brakepressure_fr_Pa(VehicleState* vehstate){
    return vehstate->tirestate_fr.brakePressure_Pa;
}
double get_brakepressure_rl_Pa(VehicleState* vehstate){
    return vehstate->tirestate_rl.brakePressure_Pa;
}
double get_brakepressure_rr_Pa(VehicleState* vehstate){
    return vehstate->tirestate_rr.brakePressure_Pa;
}


//########################
//### SETTER FUNCTIONS ###
//########################
void set_steeringangle(VehicleState* vehstate, double angle_rad){
    vehstate->steeringangle = angle_rad;
}

void set_torque_fl_Nm(VehicleState* vehstate, double torque_Nm){
    vehstate->tirestate_fl.tireDriveTorque = torque_Nm;
}
void set_torque_fr_Nm(VehicleState* vehstate, double torque_Nm){
    vehstate->tirestate_fr.tireDriveTorque = torque_Nm;
}
void set_torque_rl_Nm(VehicleState* vehstate, double torque_Nm){
    vehstate->tirestate_rl.tireDriveTorque = torque_Nm;
}
void set_torque_rr_Nm(VehicleState* vehstate, double torque_Nm){
    vehstate->tirestate_rr.tireDriveTorque = torque_Nm;
}

void set_brakepressure_fl_Pa(VehicleState* vehstate, double pressure_Pa){
    vehstate->tirestate_fl.brakePressure_Pa = pressure_Pa;
}
void set_brakepressure_fr_Pa(VehicleState* vehstate, double pressure_Pa){
    vehstate->tirestate_fr.brakePressure_Pa = pressure_Pa;
}
void set_brakepressure_rl_Pa(VehicleState* vehstate, double pressure_Pa){
    vehstate->tirestate_rl.brakePressure_Pa = pressure_Pa;
}
void set_brakepressure_rr_Pa(VehicleState* vehstate, double pressure_Pa){
    vehstate->tirestate_rr.brakePressure_Pa = pressure_Pa;
}

void set_posx_ini(VehicleState* vehstate, double posx){
    vehstate->xpos_ini0_m = posx;
}
void set_posy_ini(VehicleState* vehstate, double posy){
    vehstate->ypos_ini0_m = posy;
}
void set_psi_ini(VehicleState* vehstate, double psi){
    vehstate->dpsi_ini = psi;
}

void set_vx_veh(VehicleState* vehstate, double vx){
    vehstate->vx_veh_mps = vx;
}
void set_vy_veh(VehicleState* vehstate, double vy){
    vehstate->vy_veh_mps = vy;
}
void set_dpsi_ini(VehicleState* vehstate, double dpsi){
    vehstate->dpsi_ini = dpsi;
}

void set_ax_veh(VehicleState* vehstate, double ax){
    vehstate->ax_veh_mps2 = ax;
}
void set_ay_veh(VehicleState* vehstate, double ay){
    vehstate->ay_veh_mps2 = ay;
}
void set_ddpsi_ini(VehicleState* vehstate, double ddpsi){
    vehstate->ddpsi_veh = ddpsi;
}

void set_omega_fl(VehicleState* vehstate, double omega){
    vehstate->tirestate_fl.omega_radps = omega;
}
void set_omega_fr(VehicleState* vehstate, double omega){
    vehstate->tirestate_fr.omega_radps = omega;
}
void set_omega_rl(VehicleState* vehstate, double omega){
    vehstate->tirestate_rl.omega_radps = omega;
}
void set_omega_rr(VehicleState* vehstate, double omega){
    vehstate->tirestate_rr.omega_radps = omega;
}

void set_lambda_fl(VehicleState* vehstate, double lambda_0){
    vehstate->tirestate_fl.kappa = lambda_0;
}
void set_lambda_fr(VehicleState* vehstate, double lambda_0){
    vehstate->tirestate_fr.kappa = lambda_0;
}
void set_lambda_rl(VehicleState* vehstate, double lambda_0){
    vehstate->tirestate_rl.kappa = lambda_0;
}
void set_lambda_rr(VehicleState* vehstate, double lambda_0){
    vehstate->tirestate_rr.kappa = lambda_0;
}

void set_alpha_fl(VehicleState* vehstate, double alpha){
    vehstate->tirestate_fl.alpha = alpha;
}
void set_alpha_fr(VehicleState* vehstate, double alpha){
    vehstate->tirestate_fr.alpha = alpha;
}
void set_alpha_rl(VehicleState* vehstate, double alpha){
    vehstate->tirestate_rl.alpha = alpha;
}
void set_alpha_rr(VehicleState* vehstate, double alpha){
    vehstate->tirestate_rr.alpha = alpha;
}
