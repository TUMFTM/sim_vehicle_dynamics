
cdef extern from "VehicleBody.h":
    cdef extern from "Param_dtm.h":
        cdef struct Vehicleparameters:
            pass

    cdef extern from "VehicleState.h":
        ctypedef struct VehicleState:
            pass

    cdef char* pVehicleBody
    #IDEA create a simple pointer from type void* to use for the creation of a VehicleBody... 

    char* setVehBodyPointer()
    void freeVehBodyPointer(char* pointer)

    #check if the struct keyword is needed here .... 
    void calcBodyAngles(Vehicleparameters *vehparam, VehicleState *vehstate);
    void calcBodyStatus(Vehicleparameters *vehparam, VehicleState *vehstate);   
    