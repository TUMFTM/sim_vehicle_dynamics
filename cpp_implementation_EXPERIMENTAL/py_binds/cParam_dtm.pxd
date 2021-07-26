cdef extern from "Param_dtm.h":
    cdef struct Vehicleparameters:
        pass

    cdef struct Tireparameters:
        pass

    ctypedef struct Parameters_dtm:
        pass

    Parameters_dtm *param_dtm_new()
    void param_dtm_free(Parameters_dtm* param_dtm)
    Vehicleparameters *vehicle_param_new()
    void vehicle_param_free(Vehicleparameters *vehicle_param)

    void setParameters(Parameters_dtm* param_dtm)
    double getVehicleMass(Parameters_dtm* param_dtm)
