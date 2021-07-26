#include "../include/Param_dtm.h"
#include "../include/ini.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h>
    //TODO change Paths here and cpp_implementation_EXPERIMENTAL!!! 
    //#define getdirectory _getcwd
    char *file_initialparameters="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_initialparameters.ini";
    char *file_vehicleparameters="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_vehicleparameters.ini";
    char *file_suspensionparameters="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_suspensionparameters.ini";
    char *file_tirefl="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_tireparameters_frontleft.tir";
    char *file_tirefr="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_tireparameters_frontright.tir";
    char *file_tirerl="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_tireparameters_rearleft.tir";
    char *file_tirerr="\\cpp_implementation_EXPERIMENTAL\\parameters\\sim_dtm_tireparameters_rearright.tir";
    
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
    //#define getdirectory getcwd
    char *file_initialparameters="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_initialparameters.ini";
    char *file_vehicleparameters="/cpp_implementation_EXPERIMENTAL/parameters/sim_vehicleparameters.ini";
    char *file_suspensionparameters="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_suspensionparameters.ini";
    char *file_tirefl="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_tireparameters_frontleft.tir";
    char *file_tirefr="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_tireparameters_frontright.tir";
    char *file_tirerl="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_tireparameters_rearleft.tir";
    char *file_tirerr="/cpp_implementation_EXPERIMENTAL/parameters/sim_dtm_tireparameters_rearright.tir";
    #define getIniPath() \
    char cwd[200]; \
    char *ptr; \
    char mod[] = "/mod_control"; \
    char sim[] = "/cpp_implementation_EXPERIMENTAL"; \
    getcwd(cwd,sizeof(cwd)); \
    ptr = strrchr(cwd, '/'); \
    while(strcmp(mod, ptr)!=0 && strcmp(sim, ptr)!=0){ \
        ptr = strrchr(cwd, '/');    \
        *ptr = '\0';                \
        ptr = strrchr(cwd, '/');    \
    }

#endif

Parameters_dtm *param_dtm_new(){
    
    Parameters_dtm *param_dtm, buffer = {0};
    param_dtm = (Parameters_dtm*)malloc(sizeof(Parameters_dtm));
    *param_dtm = buffer;
    return param_dtm;
}


void param_dtm_free(Parameters_dtm* param_dtm){
    
    free(param_dtm);
}


struct Vehicleparameters *vehicle_param_new(){
    struct Vehicleparameters *vehicle_param;
    vehicle_param = (struct Vehicleparameters*)malloc(sizeof(struct Vehicleparameters));

    return vehicle_param;

}


void vehicle_param_free(struct Vehicleparameters *vehicle_param){
    free(vehicle_param);
}


static int suspensionparameters(void* user, const char* section, const char* name, const char* value){
    
    struct Suspensionparmameters *suspensionparam = (struct Suspensionparmameters*)user;
    
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
 //TODO find params which were moved from the suspension.ini !!!! 
    
    /*
    //Brakes
    
    if(MATCH("Brakes", "mue_BrakePadsFrRe_static")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            suspensionparam->mue_BrakePadsFrRe_static[i] = atof(token);
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
            suspensionparam->mue_BrakePadsFrRe_kinetic[i] = atof(token);
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
            suspensionparam->d_BrakeActuatorBoreFrRe_m[i] = atof(token);
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
            suspensionparam->r_BrakePadsMeanLeverFrRe_m[i] = atof(token);
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
            suspensionparam->n_BrakePadsNumberFrRe[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
    }else{
        return 0; //unknown section/ name error
    }
    */
    return 1;
}


static int vehicleparameters(void* user, const char* section, const char* name, const char* value){
    
    struct Vehicleparameters *vehicleparam = (struct Vehicleparameters*)user;
    
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
 
    //Aerodynamics
    if(MATCH("Aerodynamics", "A_LongitudinalDrag_m2")){
        vehicleparam->A_LongitudinalDrag_m2 = atof(value);
    }else if(MATCH("Aerodynamics","cw_LongitudinalDrag")){
        vehicleparam->cw_LongitudinalDrag = atof(value);
    }else if(MATCH("Aerodynamics","cl_LongitudinalLift")){
        vehicleparam->cl_LongitudinalLift = atof(value);
    }else if(MATCH("Aerodynamics","cpm_LongDragPitchMomentCoeff")){
        vehicleparam->cpm_LongDragPitchMomentCoeff = atof(value);
    }
    //VehicleData
    else if(MATCH("VehicleData","m_Vehicle_kg")){
        vehicleparam->m_Vehicle_kg = atof(value);
    }else if(MATCH("VehicleData","l_WheelbaseF_m")){
        vehicleparam->l_WheelbaseF_m = atof(value);
    }else if(MATCH("VehicleData","l_WheelbaseTotal_m")){
        vehicleparam->l_WheelbaseTotal_m = atof(value);
    }else if(MATCH("VehicleData","w_TrackF_m")){
        vehicleparam->w_TrackF_m = atof(value);
    }else if(MATCH("VehicleData","w_TrackR_m")){
        vehicleparam->w_TrackR_m = atof(value);
    }else if(MATCH("VehicleData","h_AxlePlaneCog_m")){
        vehicleparam->h_AxlePlaneCog_m = atof(value);
    }else if(MATCH("VehicleData","w_SymmetryLineCog_m")){
        vehicleparam->w_SymmetryLineCog_m = atof(value);
    }else if(MATCH("VehicleData","I_K_Vehicle_kgm2")){    
        char* token;
        int i=0, j=0;

        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            if(i==2){
                vehicleparam->I_K_Vehicle_kgm2[j][i] = atof(token);
                token = strtok(NULL," ");
                i=0;
                j++;
            }else{
                vehicleparam->I_K_Vehicle_kgm2[j][i] = atof(token);
                token = strtok(NULL," ");
                i++;
            } 
        }
    }
    //Environment
     else if(MATCH("Environment","p_Air_Pa")){
        vehicleparam->p_Air_Pa = atof(value);
    }else if(MATCH("Environment","T_Air_K")){
        vehicleparam->T_Air_K = atof(value);
    }else if(MATCH("Environment","a_Gravity_mps2")){
        vehicleparam->a_Gravity_mps2 = atof(value);
    }
    //Brakes
    if(MATCH("Brakes", "mue_BrakePadsFrRe_static")){
        char* token;
        int i=0;
        token = strdup(value);
        size_t len = strlen(token);
        memmove(token, token+1, len-2);
        token = strtok(token, " ");
        
        while(token != NULL){
            vehicleparam->mue_BrakePadsFrRe_static[i] = atof(token);
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
            vehicleparam->mue_BrakePadsFrRe_kinetic[i] = atof(token);
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
            vehicleparam->d_BrakeActuatorBoreFrRe_m[i] = atof(token);
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
            vehicleparam->r_BrakePadsMeanLeverFrRe_m[i] = atof(token);
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
            vehicleparam->n_BrakePadsNumberFrRe[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        }
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
            vehicleparam->m_pac_front_lat[i] = atof(token);
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
            vehicleparam->m_pac_front_long[i] = atof(token);
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
            vehicleparam->m_pac_rear_lat[i] = atof(token);
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
            vehicleparam->m_pac_rear_long[i] = atof(token);
            token = strtok(NULL," ");
            i++;
        } 

    }//STM SPECIFIC for kinematic model
    else if(MATCH("STMspecific","cRollFriction_Npmps")){
        vehicleparam->cRollFriction_Npmps = atof(value);
    }else if(MATCH("STMspecific","MaxRollFriction_N")){
        vehicleparam->MaxRollFriction_N = atof(value);
    }else if(MATCH("STMspecific","T_YawRate_s")){
        vehicleparam->T_YawRate_s = atof(value);
    }else if(MATCH("STMspecific","T_LatVel_s")){
        vehicleparam->T_LatVel_s = atof(value);
    }else if(MATCH("STMspecific","T_Tire_s")){
        vehicleparam->T_Tire_s = atof(value);
    }else if(MATCH("STMspecific","PTLimitLowVel_N")){
        vehicleparam->PTLimitLowVel_N = atof(value);
    }else if(MATCH("STMspecific","switchModelVel_mps")){
        vehicleparam->switchModelVel_mps = atof(value);
    }else if(MATCH("STMspecific","switchModelBlend_mps")){
        vehicleparam->switchModelBlend_mps = atof(value);
    }else {
        return 0; //unknown section/ name error        
    }

    return 1;
}


static int tireparameters(void* user, const char* section, const char* name, const char* value){

    struct Tireparameters *tire =(struct Tireparameters*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
 
    //tire data
    if(MATCH("WHEEL", "FNOMIN")){
        tire->fnomin = atof(value);
    }else if(MATCH("DIMENSION","UNLOADED_RADIUS")){
        tire->unloaded_radius = atof(value);
    }else if(MATCH("MODEL","LONGVL")){
        tire->longvl = atof(value);
    }else if(MATCH("MODEL","TYRESIDE")){
        tire->tyreside = strdup(value);
    }
    //inertial 
    else if(MATCH("INERTIAL","Iyy_Wheel_kgm2")){
        tire->Iyy_Wheel_kgm2 = atof(value);
    }else if(MATCH("INERTIAL","m_Wheel_kg")){
        tire->m_Wheel_kg = atof(value);
    }
    //scaling pure slip
    else if(MATCH("SCALING_COEFFICIENTS","LFZO")){
        tire->lfzo = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LCX")){
        tire->lcx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LMUX")){
        tire->lmux = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LEX")){
        tire->lex = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LKX")){
        tire->lkx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LHX")){
        tire->lhx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LVX")){
        tire->lvx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LGAX")){
        tire->lgax = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LCY")){
        tire->lcy = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LMUY")){
        tire->lmuy = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LEY")){
        tire->ley = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LKY")){
        tire->lky = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LHY")){
        tire->lhy = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LVY")){
        tire->lvy = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LGAY")){
        tire->lgay = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LTR")){
        tire->ltr = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LRES")){
        tire->lres = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LGAZ")){
        tire->lgaz = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LMX")){
        tire->lmx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LVMX")){
        tire->lvmx = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LMY")){
        tire->lmy = atof(value);
    }
    //scaling combined slip
    else if(MATCH("SCALING_COEFFICIENTS","LXAL")){
        tire->lxal = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LYKA")){
        tire->lyka = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LVYKA")){
        tire->lvyka = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LS")){
        tire->ls = atof(value);
    }
    //scaling transient response
    else if(MATCH("SCALING_COEFFICIENTS","LSGKP")){
        tire->lsgkp = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LSGAL")){
        tire->lsgal = atof(value);
    }else if(MATCH("SCALING_COEFFICIENTS","LGYR")){
        tire->lgyr = atof(value);
    }
    //longitudinal coefficients
    else if(MATCH("LONGITUDINAL_COEFFICIENTS","PCX1")){
        tire->pcx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PDX1")){
        tire->pdx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PDX2")){
        tire->pdx2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PDX3")){
        tire->pdx3 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PEX1")){
        tire->pex1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PEX2")){
        tire->pex2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PEX3")){
        tire->pex3 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PEX4")){
        tire->pex4 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PKX1")){
        tire->pkx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PKX2")){
        tire->pkx2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PKX3")){
        tire->pkx3 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PHX1")){
        tire->phx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PHX2")){
        tire->phx2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PVX1")){
        tire->pvx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","PVX2")){
        tire->pvx2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","RBX1")){
        tire->rbx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","RBX2")){
        tire->rbx2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","RCX1")){
        tire->rcx1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","REX1")){
        tire->rex1 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","REX2")){
        tire->rex2 = atof(value);
    }else if(MATCH("LONGITUDINAL_COEFFICIENTS","RHX1")){
        tire->rhx1 = atof(value);
    }
    //overturning coefficients
    else if(MATCH("OVERTURNING_COEFFICIENTS","QSX1")){
        tire->qsx1 = atof(value);
    }else if(MATCH("OVERTURNING_COEFFICIENTS","QSX2")){
        tire->qsx2 = atof(value);
    }else if(MATCH("OVERTURNING_COEFFICIENTS","QSX3")){
        tire->qsx3 = atof(value);
    }
    //LATERAL_COEFFICIENTS
    else if(MATCH("LATERAL_COEFFICIENTS","PCY1")){
        tire->pcy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PDY1")){
        tire->pdy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PDY2")){
        tire->pdy2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PDY3")){
        tire->pdy3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PEY1")){
        tire->pey1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PEY2")){
        tire->pey2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PEY3")){
        tire->pey3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PEY4")){
        tire->pey4 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PKY1")){
        tire->pky1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PKY2")){
        tire->pky2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PKY3")){
        tire->pky3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PHY1")){
        tire->phy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PHY2")){
        tire->phy2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PHY3")){
        tire->phy3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PVY1")){
        tire->pvy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PVY2")){
        tire->pvy2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PVY3")){
        tire->pvy3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","PVY4")){
        tire->pvy4 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RBY1")){
        tire->rby1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RBY2")){
        tire->rby2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RBY3")){
        tire->rby3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RCY1")){
        tire->rcy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","REY1")){
        tire->rey1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","REY2")){
        tire->rey2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RHY1")){
        tire->rhy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RHY2")){
        tire->rhy2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY1")){
        tire->rvy1 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY2")){
        tire->rvy2 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY3")){
        tire->rvy3 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY4")){
        tire->rvy4 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY5")){
        tire->rvy5 = atof(value);
    }else if(MATCH("LATERAL_COEFFICIENTS","RVY6")){
        tire->rvy6 = atof(value);
    }
    //ROLLING_COEFFICIENTS
    else if(MATCH("ROLLING_COEFFICIENTS","QSY1")){
        tire->qsy1 = atof(value);
    }else if(MATCH("ROLLING_COEFFICIENTS","QSY2")){
        tire->qsy2 = atof(value);
    }else if(MATCH("ROLLING_COEFFICIENTS","QSY3")){
        tire->qsy3 = atof(value);
    }else if(MATCH("ROLLING_COEFFICIENTS","QSY4")){
        tire->qsy4 = atof(value);
    }
    //ALIGNING_COEFFICIENTS
    else if(MATCH("ALIGNING_COEFFICIENTS","QBZ1")){
        tire->qbz1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ2")){
        tire->qbz2 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ3")){
        tire->qbz3 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ4")){
        tire->qbz4 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ5")){
        tire->qbz5 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ9")){
        tire->qbz9 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QBZ10")){
        tire->qbz10 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QCZ1")){
        tire->qcz1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ1")){
        tire->qdz1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ2")){
        tire->qdz2 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ3")){
        tire->qdz3 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ4")){
        tire->qdz4 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ6")){
        tire->qdz6 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ7")){
        tire->qdz7 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ8")){
        tire->qdz8 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QDZ9")){
        tire->qdz9 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QEZ1")){
        tire->qez1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QEZ2")){
        tire->qez2 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QEZ3")){
        tire->qez3 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QEZ4")){
        tire->qez4 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QEZ5")){
        tire->qez5 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QHZ1")){
        tire->qhz1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QHZ2")){
        tire->qhz2 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QHZ3")){
        tire->qhz3 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","QHZ4")){
        tire->qhz4 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","SSZ1")){
        tire->ssz1 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","SSZ2")){
        tire->ssz2 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","SSZ3")){
        tire->ssz3 = atof(value);
    }else if(MATCH("ALIGNING_COEFFICIENTS","SSZ4")){
        tire->ssz4 = atof(value);
    }
    else {
        return 0; //unknown section/ name error
    }
    return 1;
}

void setParameters(Parameters_dtm* param_dtm){

    char path_initial[200];
    char path_vehicle[200];
    char path_suspension[200];
    char path_tirefl[200];
    char path_tirefr[200];
    char path_tirerl[200];
    char path_tirerr[200];

    struct Tireparameters* tirefl = &param_dtm->tirefl;
    struct Tireparameters* tirefr = &param_dtm->tirefr;
    struct Tireparameters* tirerl = &param_dtm->tirerl;
    struct Tireparameters* tirerr = &param_dtm->tirerr;
    struct Suspensionparmameters* supensionparam = &param_dtm->suspensionparam;
    struct Vehicleparameters* vehicleparam = &param_dtm->vehicleparameters;

    // GETINIPATH MACRO
    getIniPath();

    //load initial parameters
    strcpy(path_vehicle, cwd);
    strcat(path_vehicle, file_vehicleparameters);
    ini_parse(path_vehicle, vehicleparameters, vehicleparam);

    //load suspension parameters
    strcpy(path_suspension, cwd);
    strcat(path_suspension, file_suspensionparameters);
    ini_parse(path_suspension, suspensionparameters, supensionparam);

    //load tire parameters front left
    strcpy(path_tirefl, cwd);
    strcat(path_tirefl, file_tirefl);
    ini_parse(path_tirefl, tireparameters, tirefl);

    //load tire parameters front right
    strcpy(path_tirefr, cwd);
    strcat(path_tirefr, file_tirefr);
    ini_parse(path_tirefr, tireparameters, tirefr);


    //load tire parameters rear left
    strcpy(path_tirerl, cwd);
    strcat(path_tirerl, file_tirerl);
    ini_parse(path_tirerl, tireparameters, tirerl);


    //load tire parameters rear right
    strcpy(path_tirerr, cwd);
    strcat(path_tirerr, file_tirerr);
    ini_parse(path_tirerr, tireparameters, tirerr);

    param_dtm->vehicleparameters.r_gasConstant_JpkgK = 287.058;
    param_dtm->vehicleparameters.airDensity_kgpm3 = param_dtm->vehicleparameters.p_Air_Pa/(param_dtm->vehicleparameters.r_gasConstant_JpkgK*param_dtm->vehicleparameters.T_Air_K);
    
    param_dtm->spath = path_vehicle;

    //reset sign of Lift parameter 
    //TODO check resigning  
    param_dtm->vehicleparameters.cl_LongitudinalLift *= -1.0;
    param_dtm->vehicleparameters.vx_min_mps = 0.5 * param_dtm->vehicleparameters.switchModelVel_mps;

    //set vectors to tire mounting point 
    param_dtm->vehicleparameters.r_A_fl[0] = param_dtm->vehicleparameters.l_WheelbaseF_m;
    param_dtm->vehicleparameters.r_A_fl[1] = param_dtm->vehicleparameters.w_TrackF_m*0.5;
    param_dtm->vehicleparameters.r_A_fl[2] = -param_dtm->vehicleparameters.h_AxlePlaneCog_m;

    param_dtm->vehicleparameters.r_A_fr[0] = param_dtm->vehicleparameters.l_WheelbaseF_m;
    param_dtm->vehicleparameters.r_A_fr[1] = -param_dtm->vehicleparameters.w_TrackF_m*0.5;
    param_dtm->vehicleparameters.r_A_fr[2] = -param_dtm->vehicleparameters.h_AxlePlaneCog_m;

    param_dtm->vehicleparameters.r_A_rl[0] = -(param_dtm->vehicleparameters.l_WheelbaseTotal_m - param_dtm->vehicleparameters.l_WheelbaseF_m);
    param_dtm->vehicleparameters.r_A_rl[1] = param_dtm->vehicleparameters.w_TrackR_m*0.5;
    param_dtm->vehicleparameters.r_A_rl[2] = -param_dtm->vehicleparameters.h_AxlePlaneCog_m;

    param_dtm->vehicleparameters.r_A_rr[0] = -(param_dtm->vehicleparameters.l_WheelbaseTotal_m - param_dtm->vehicleparameters.l_WheelbaseF_m);
    param_dtm->vehicleparameters.r_A_rr[1] = -param_dtm->vehicleparameters.w_TrackR_m*0.5;
    param_dtm->vehicleparameters.r_A_rr[2] = -param_dtm->vehicleparameters.h_AxlePlaneCog_m;
}


void setTimeStep(Parameters_dtm* param_dtm, double dt){
    param_dtm->vehicleparameters.timestep = dt;
}


double getVehicleMass(Parameters_dtm* param_dtm){
    return param_dtm->vehicleparameters.m_Vehicle_kg;
}
