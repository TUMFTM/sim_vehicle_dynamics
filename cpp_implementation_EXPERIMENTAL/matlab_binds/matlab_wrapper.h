#ifndef MATLAB_WRAPPER_H
#define MATLAB_WRAPPER_H

#include "../include/SingleTrackModel.h"
#include "../include/VehicleState.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wrapper_stm{

    SingleTrackModel *stm;
    VehicleState *vehstate;
}Wrapper_stm;



#ifdef __cplusplus
}
#endif

#endif