#ifndef MATLAB_WRAPPER_DTM_H
#define MATLAB_WRAPPER_DTM_H

#include "../include/Param_dtm.h"
#include "../include/VehicleState.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wrapper_dtm{

    Parameters_dtm *param_dtm;
    VehicleState *vehstate;
    FILE* datafile;
    double counter;
    double duration_csv;

}Wrapper_dtm;



#ifdef __cplusplus
}
#endif

#endif