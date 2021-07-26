#ifndef TIREMODEL_H
#define TIREMODEL_H
#include "Param_dtm.h"
#include "VehicleState.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
TODO check if this works with the struct defined in VehicleState.h
struct Tirestatestruct
{
    //interim results
    double fz;
    double kappa;
    double alpha;

    //results - outputs
    double fx;
    double fy;
    double mx;
    double my;
    double mz;

    double debug;

}tirestate; 
*/

//TODO change tirestate struct to be referenced from VehicleState.h !!! ########

void testinput(struct TireState* tirestate, const double *fz, const double *kappa, const double *alpha);

//void calcTirestatus(Parameters_dtm *param_dtm, struct TireState *tirestate, const double *vx, const double *vy, const double *psidot);
void calcFz(Parameters_dtm* param_dtm, VehicleState *vehstate);

void magicFormula52(struct Tireparameters *tire_param, struct TireState* tirestate, const double *gamma, const double *vx);
void magicFormula52_c(struct Tireparameters *tire_param, struct TireState* tirestate, VehicleState *vehstate);

void Pacejka5Param(Parameters_dtm *param_dtm, VehicleState *vehstate);

//TODO calculate Fz, kappa/lambda and alpha !! 

void calcWheelSlips(Parameters_dtm *param_dtm, VehicleState *vehstate);
void calcWheelSpeed(Parameters_dtm *param_dtm, VehicleState *vehstate);
void calcLongForce(Parameters_dtm *param_dtm, VehicleState *vehstate);


#ifdef __cplusplus
}
#endif

#endif
