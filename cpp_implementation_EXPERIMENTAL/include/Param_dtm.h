#ifndef PARAM_DTM_H
#define PARAM_DTM_H

#ifdef __cplusplus
extern "C" {
#endif


struct Vehicleparameters
{
    //Aerodynamics    
    double A_LongitudinalDrag_m2;
    double cw_LongitudinalDrag;
    double cl_LongitudinalLift;
    double cpm_LongDragPitchMomentCoeff;
    double beta_Wind_rad;
    double cs_LateralDragCoefficients;
    double cy_DragYawMomentCoefficients;

    //Environment
    double p_Air_Pa;
    double T_Air_K;
    double a_Gravity_mps2;

    //SensorData
    double r_K_KS1_m[3];
    double r_K_KS2_m[3];
    double r_K_KS3_m[3];
    double phi0_K_KS1_rad[3];
    double phi0_K_KS2_rad[3];
    double phi0_K_KS3_rad[3];

    //VehicleData
    double m_Vehicle_kg;
    double l_WheelbaseF_m; 
    double l_WheelbaseTotal_m; 
    double w_TrackF_m;
    double w_TrackR_m;
    double w_SymmetryLineCog_m;
    double h_AxlePlaneCog_m;
    double I_K_Vehicle_kgm2[3][3];

    //Tires
    double p_Tires_pa[4]; 
    double k1_WheelsFB_PT1[3];
    double k1_TireFB_PT1[3];
    double k2_TireFB_PT1[3];

    //VehicleSimulation
    double Sim_LongVelTol_mps;
    double Sim_LatOff_m;
    double Sim_LongOff_m;
    double Sim_VertOff_m;

    //Brakes
    double mue_BrakePadsFrRe_static[2];
    double mue_BrakePadsFrRe_kinetic[2];
    double d_BrakeActuatorBoreFrRe_m[2];
    double r_BrakePadsMeanLeverFrRe_m[2];
    double n_BrakePadsNumberFrRe[2];

    double r_A_fl[3];
    double r_A_fr[3];
    double r_A_rl[3];
    double r_A_rr[3];

    //Missing
    double r_gasConstant_JpkgK; //specific gas constant of dry air to calculate density of the air
    double airDensity_kgpm3;
    double timestep;

    //5 Parameter Pajeka
    double m_pac_front_lat[5];
    double m_pac_front_long[5];
    double m_pac_rear_lat[5];
    double m_pac_rear_long[5];

    //parameters for kinematic model
    double cRollFriction_Npmps;
    double MaxRollFriction_N;
    double T_LatVel_s;
    double T_YawRate_s;
    double T_Tire_s;
    double switchModelVel_mps;
    double switchModelBlend_mps;
    double PTLimitLowVel_N;
    double vx_min_mps;

};

struct Suspensionparmameters
{
    //Antisway
    double r_AntiSwayArmRadiusFrRe_m[2];
    double phi_AntiSwayNeutralAngleFrRe_rad[2];
    double c_AntiSwayTSpringFrRe_Nmprad[2];


    //Compliance
    double cz_SpringRateFrRe_Npm[2];
    double F0z_SpringPreloadFrRe_N[2];
    double Cz_DamperRateFrRe_Nspm[2];
    double Hmax_MaxHeightToHardblock_m;
    double h_InertialFrameOffset_COGtoAxle_m;


    //Kinematics
    double nu0_ToeATSteerCenterFrRe_rad[2];
    double k_RollSteerVSHeightFrRe_radpm[2];
    double k_ToeVSSteerF;
    double k_CasterATSteerCenterF[2];
    double k_CasterVSHeightFrRe[2];
    double k_CasterVSSteerFrRe;
    double k_CamberATSteerCenterF[2];
    double k_CamberVSHeightFrRe[2];
    double k_CamberVSSteerF;
    double k_HeightVSSteerF_mprad;    
};

struct Tireparameters
{
    //TIRE DATA
    double fnomin;
    double unloaded_radius;
    double longvl;
    char* tyreside;
    
    //INERTIAL
    double Iyy_Wheel_kgm2;
    double m_Wheel_kg;

    //SCALING PURE SLIP
    double lfzo;    // [LATERAL], Scale factor of nominal (rated) load
    double lcx;      // [LONGITUDINAL], Scale factor of Fx shape factor
    double lmux;    // [LONGITUDINAL], Scale factor of Fx peak friction coefficient
    double lex;      // [LONGITUDINAL], Scale factor of Fx curvature factor
    double lkx;      // [LONGITUDINAL], Scale factor of Fx slip stiffness
    double lhx;      // [LONGITUDINAL], Scale factor of Fx horizontal shift
    double lvx;      // [LONGITUDINAL], Scale factor of Fx vertical shift
    double lgax;    // [LONGITUDINAL], Scale factor of camber for Fx
    double lcy;      // [LATERAL], Scale factor of Fy shape factor
    double lmuy;    // [LATERAL], Scale factor of Fy peak friction coefficient
    double ley;      // [LATERAL], Scale factor of Fy curvature factor
    double lky;      // [LATERAL], Scale factor of Fy cornering stiffness
    double lhy;      // [LATERAL], Scale factor of Fy horizontal shift
    double lvy;      // [LATERAL], Scale factor of Fy vertical shift
    double lgay;    // [LATERAL], Scale factor of camber for Fy
    double ltr;      // [ALIGNING], Scale factor of Peak of pneumatic trail
    double lres;    // [ALIGNING], Scale factor for offset of residual torque
    double lgaz;    // [ALIGNING], Scale factor of camber for Mz
    double lmx;      // [OVERTURNING], Scale factor of overturning couple
    double lvmx;    // [OVERTURNING], Scale factor of Mx vertical shift
    double lmy;    // [ROLLING], Scale factor of rolling resistance torque, Nutzung fehlt in MF52 nach TNO

    //SCALING COMBINED SLIP
    double lxal;    // [LONGITUDINAL], Scale factor of alpha influence on Fx
    double lyka;    // [LATERAL], Scale factor of kappa influence on Fy
    double lvyka;  // [LATERAL], Scale factor of kappa induced Fy
    double ls;        // [ALIGNING], Scale factor of Moment arm of Fx

    //SCALING TRANSIENT RESPONSE
    double lsgkp;     // Scale factor of Relaxation length of Fx, nur falls transiente Schlupfberechnung
    double lsgal;    // Scale factor of Relaxation length of Fy, nur falls transiente Schlupfberechnung
    double lgyr;      // Scale factor of gyroscopic torque, nur falls transiente Schlupfberechnung
 
    //LONGITUDINAL COEFFICIENTS
    double pcx1;
    double pdx1;
    double pdx2;
    double pdx3;
    double pex1;
    double pex2;
    double pex3;
    double pex4;
    double pkx1;
    double pkx2;
    double pkx3;
    double phx1;
    double phx2;
    double pvx1;
    double pvx2;
    double rbx1;
    double rbx2;
    double rcx1;
    double rex1;
    double rex2;
    double rhx1;

    //OVERTURNING COEFFICIENTS
    double qsx1;
    double qsx2;
    double qsx3;


    //LATERAL COEFFICIENTS
    double pcy1;
    double pdy1;
    double pdy2;
    double pdy3;
    double pey1;
    double pey2;
    double pey3;
    double pey4;
    double pky1;
    double pky2;
    double pky3;
    double phy1;
    double phy2;
    double phy3;
    double pvy1;
    double pvy2;
    double pvy3;
    double pvy4;
    double rby1;
    double rby2;
    double rby3;
    double rcy1;
    double rey1;
    double rey2;
    double rhy1;
    double rhy2;
    double rvy1;
    double rvy2;
    double rvy3;
    double rvy4;
    double rvy5;
    double rvy6;

    //ROLLING COEFFICIENTS
    double qsy1;
    double qsy2;
    double qsy3;
    double qsy4;

    //ALIGNING COEFFICIENTS
    double qbz1;
    double qbz2;
    double qbz3;
    double qbz4;
    double qbz5;
    double qbz9;
    double qbz10;
    double qcz1;
    double qdz1;
    double qdz2;
    double qdz3;
    double qdz4;
    double qdz6;
    double qdz7;
    double qdz8;
    double qdz9;
    double qez1;
    double qez2;
    double qez3;
    double qez4;
    double qez5;
    double qhz1;
    double qhz2;
    double qhz3;
    double qhz4;
    double ssz1;
    double ssz2;
    double ssz3;
    double ssz4;

};


typedef struct Parameters_dtm
{
    struct Vehicleparameters vehicleparameters;

    struct Tireparameters tirefl;
    struct Tireparameters tirefr;
    struct Tireparameters tirerl;
    struct Tireparameters tirerr;

    struct Suspensionparmameters suspensionparam;

    char* spath;
    //for DEBUGGING
    char logfile_name[50];
}Parameters_dtm;

Parameters_dtm *param_dtm_new();
void param_dtm_free(Parameters_dtm* param_dtm);
struct Vehicleparameters *vehicle_param_new();
void vehicle_param_free(struct Vehicleparameters *vehicle_param);

void setParameters(Parameters_dtm* param_dtm);
void setTimeStep(Parameters_dtm* param_dtm, double dt);
double getVehicleMass(Parameters_dtm* param_dtm);

#ifdef __cplusplus
}
#endif

#endif
