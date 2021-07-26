#ifndef VEHICLEBODY_H
#define VEHICLEBODY_H

#include "Param_dtm.h"
#include "VehicleState.h"

#ifdef __cplusplus
extern "C" {
#endif

//void* setVehBodyPointer();
char* setVehBodyPointer();

void freeVehBodyPointer(char* pointer);

void calcDerivatives(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);
void stepVehBody(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);
void stepVehBody_multistep(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);

void adams_bashforth(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);
void adams_bashforth2(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);
void runge_kutta(Parameters_dtm *param_dtm, struct Vehicleparameters *vehparam, VehicleState *vehstate);

#ifdef __cplusplus
}
#endif

#endif
