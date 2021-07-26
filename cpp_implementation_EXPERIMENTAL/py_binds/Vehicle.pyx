cimport cVehicleBody
cimport cVehicleState
cimport cParam_dtm


cdef class Vehicle:
    cdef cParam_dtm.Parameters_dtm* _c_param_dtm
    cdef cParam_dtm.Vehicleparameters* _c_vehparam
    cdef cVehicleState.VehicleState* _c_vehstate

    def __cinit__(self):
        self._c_param_dtm = cParam_dtm.param_dtm_new()
        self._c_vehparam = cParam_dtm.vehicle_param_new()        
        self._c_vehstate = cVehicleState.vehstate_new()

        if self._c_param_dtm is NULL:
            raise MemoryError()
        if self._c_vehparam is NULL:
            raise MemoryError()
        if self._c_vehstate is NULL:
            raise MemoryError()


    def __dealloc__(self):
        if self._c_vehstate is not NULL:
            cParam_dtm.param_dtm_free(self._c_param_dtm)
            #TODO ceck if we could here just use the initalized struct fro, _c_param_dtm !!!
            cParam_dtm.vehicle_param_free(self._c_vehparam)
            cVehicleState.vehstate_free(self._c_vehstate)


    def setParams(self):
        if self._c_param_dtm is not NULL:
            cParam_dtm.setParameters(self._c_param_dtm)

    def getVehicleMass(self):
        if self._c_param_dtm is not NULL:
           return cParam_dtm.getVehicleMass(self._c_param_dtm)
