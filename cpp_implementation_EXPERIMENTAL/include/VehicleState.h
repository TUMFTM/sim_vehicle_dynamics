#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#ifdef __cplusplus
extern "C" {
#endif

struct TireState
{
    //input 
    double tireDriveTorque;
    double brakePressure_Pa;

    //interim results
    double fz;
    double kappa;
    double alpha;
    //TODO rename roh -> its actually droh!!! 
    double roh; //nWheel
    double omega_radps;
    double droh; //diff nWheel
    double domega_radps2;
    double tireBrakeTorque;
    double gamma;

    //results - outputs
    double fx;
    double fy;
    double mx;
    double my;
    double mz;

    double fx_tire;
    double fy_tire;

    //STM ONLY
    double fx_powertrain; 
    
    double alpha_stm0;
    double alpha_stm1;
    //double alpha_km0;
    //double alpha_km1;

    double lambda_stm0;
    double lambda_stm1;
    double lambda_km0;
    //double lambda_km1;
};


typedef struct VehicleState
{
    double pos_ini_0[3];
    double pos_ini_1[3];

    double xpos_ini0_m;
    double xpos_ini1_m;
    double ypos_ini0_m;
    double ypos_ini1_m;
    double zpos_ini0_m;
    double zpos_ini1_m;

    double xpos_veh1_m;
    double ypos_veh1_m;
    double zpos_veh1_m;
    
    double vx_ini_mps;
    double vy_ini_mps;
    double vz_ini_mps;

    double vx_veh_mps;
    double vy_veh_mps;
    double vz_veh_mps;

    double v_veh[3];
    double buffer_v_veh[3];
    double v_ini[3];
    double v_trans_ini[3];
    
    //double acc_veh[3];
    double ax_veh_mps2;
    double ay_veh_mps2;
    double az_veh_mps2;
    double a_x_buffer;
    double a_y_buffer;
    double a_z_buffer;

    double ax_ini_mps2;
    double ay_ini_mps2;
    double az_ini_mps2;

    double psi_veh;
    double theta_veh;
    double phi_veh;

    double psi_ini;
    double theta_ini;
    double phi_ini;
    
    double dpsi_veh;
    double dtheta_veh;
    double dphi_veh;

    double dpsi_ini;
    double dtheta_ini;
    double dphi_ini;
    
    double buffer_dpsi_veh;
    double buffer_dtheta_veh;
    double buffer_dphi_veh;

    double ddpsi_veh;
    double ddtheta_veh;
    double ddphi_veh;

    double buffer_v_angular[3]; //omega at time n  
    double v_angular_veh[3]; //omega at time n+1  
    
    double steeringangle;

    double fx_ext_N;
    double fy_ext_N;
    double fz_ext_N;

    double mx_ext_Nm;
    double my_ext_Nm;
    double mz_ext_Nm;

    struct TireState tirestate_fl;
    struct TireState tirestate_fr;
    struct TireState tirestate_rl;
    struct TireState tirestate_rr;

    //DEBUG
    double runge_x;
    double runge_y;
    double runge_z;

    double runge_vx;
    double runge_vy;
    double runge_vz;

    double runge_ax;
    double runge_ay;
    double runge_az;

    /*
    //vx vy vz Ini KOOS
    //x y z Ini KOOS 
    //vx vy vz Body KOOS 
    //roll pith yaw angle Body KOOS 
    //Transformation Matrix ? 

    //results - outputs
    double v_ini[3];
    double v_body[3];
    double pos_ini[3];
    double rotation_body[3]; //roll pith yaw angle
    double transformation_ini_body[3][3];
    */


}VehicleState;

VehicleState *vehstate_new();

void vehstate_free(VehicleState* vehstate);

void copyVehstate(VehicleState *v1, VehicleState *v2);


void testSetPos(VehicleState* vehstate, double pos);
double getPosIni(VehicleState* vehstate);


//getter functions
double get_posx_ini(VehicleState* vehstate);
double get_posy_ini(VehicleState* vehstate);
double get_psi_ini(VehicleState* vehstate);

double get_vx_veh(VehicleState* vehstate);
double get_vy_veh(VehicleState* vehstate);
double get_dpsi_ini(VehicleState* vehstate);

double get_ax_veh(VehicleState* vehstate);
double get_ay_veh(VehicleState* vehstate);
double get_ddpsi_ini(VehicleState* vehstate);

double get_omega_fl(VehicleState* vehstate);
double get_omega_fr(VehicleState* vehstate);
double get_omega_rl(VehicleState* vehstate);
double get_omega_rr(VehicleState* vehstate);

double get_lambda_fl(VehicleState* vehstate);
double get_lambda_fr(VehicleState* vehstate);
double get_lambda_rl(VehicleState* vehstate);
double get_lambda_rr(VehicleState* vehstate);

double get_alpha_fl(VehicleState* vehstate);
double get_alpha_fr(VehicleState* vehstate);
double get_alpha_rl(VehicleState* vehstate);
double get_alpha_rr(VehicleState* vehstate);

double get_domega_fl(VehicleState* vehstate);
double get_domega_fr(VehicleState* vehstate);
double get_domega_rl(VehicleState* vehstate);
double get_domega_rr(VehicleState* vehstate);

double get_fx_tire_fl(VehicleState* vehstate);
double get_fx_tire_fr(VehicleState* vehstate);
double get_fx_tire_rl(VehicleState* vehstate);
double get_fx_tire_rr(VehicleState* vehstate);

double get_fy_tire_fl(VehicleState* vehstate);
double get_fy_tire_fr(VehicleState* vehstate);
double get_fy_tire_rl(VehicleState* vehstate);
double get_fy_tire_rr(VehicleState* vehstate);

double get_steeringangle(VehicleState* vehstate);

double get_torque_fl_Nm(VehicleState* vehstate);
double get_torque_fr_Nm(VehicleState* vehstate);
double get_torque_rl_Nm(VehicleState* vehstate);
double get_torque_rr_Nm(VehicleState* vehstate);

double get_brakepressure_fl_Pa(VehicleState* vehstate);
double get_brakepressure_fr_Pa(VehicleState* vehstate);
double get_brakepressure_rl_Pa(VehicleState* vehstate);
double get_brakepressure_rr_Pa(VehicleState* vehstate);


//setter functions
void set_steeringangle(VehicleState* vehstate, double angle_rad);

void set_torque_fl_Nm(VehicleState* vehstate, double torque_Nm);
void set_torque_fr_Nm(VehicleState* vehstate, double torque_Nm);
void set_torque_rl_Nm(VehicleState* vehstate, double torque_Nm);
void set_torque_rr_Nm(VehicleState* vehstate, double torque_Nm);

void set_brakepressure_fl_Pa(VehicleState* vehstate, double pressure_Pa);
void set_brakepressure_fr_Pa(VehicleState* vehstate, double pressure_Pa);
void set_brakepressure_rl_Pa(VehicleState* vehstate, double pressure_Pa);
void set_brakepressure_rr_Pa(VehicleState* vehstate, double pressure_Pa);

void set_posx_ini(VehicleState* vehstate, double posx);
void set_posy_ini(VehicleState* vehstate, double posy);
void set_psi_ini(VehicleState* vehstate, double psi);

void set_vx_veh(VehicleState* vehstate, double vx);
void set_vy_veh(VehicleState* vehstate, double vy);
void set_dpsi_ini(VehicleState* vehstate, double dpsi);

void set_ax_veh(VehicleState* vehstate, double ax);
void set_ay_veh(VehicleState* vehstate, double ay);
void set_ddpsi_ini(VehicleState* vehstate, double ddpsi);

void set_omega_fl(VehicleState* vehstate, double omega);
void set_omega_fr(VehicleState* vehstate, double omega);
void set_omega_rl(VehicleState* vehstate, double omega);
void set_omega_rr(VehicleState* vehstate, double omega);

void set_lambda_fl(VehicleState* vehstate, double lambda_0);
void set_lambda_fr(VehicleState* vehstate, double lambda_0);
void set_lambda_rl(VehicleState* vehstate, double lambda_0);
void set_lambda_rr(VehicleState* vehstate, double lambda_0);

void set_alpha_fl(VehicleState* vehstate, double alpha);
void set_alpha_fr(VehicleState* vehstate, double alpha);
void set_alpha_rl(VehicleState* vehstate, double alpha);
void set_alpha_rr(VehicleState* vehstate, double alpha);


#ifdef __cplusplus
}
#endif

#endif