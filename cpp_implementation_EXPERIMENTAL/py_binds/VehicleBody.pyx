cimport cVehicleBody
cimport cVehicleState
cimport cParam_dtm


cdef class VehicleBody:
    cdef char* _c_vehbody
    cdef cParam_dtm.Vehicleparameters* _c_vehparam
    cdef cVehicleState.VehicleState* _c_vehstate

    def __cinit__(self):
        self._c_vehbody = cVehicleBody.setVehBodyPointer()
        self._c_vehparam = cParam_dtm.vehicle_param_new()        
        self._c_vehstate = cVehicleState.vehstate_new()

        if self._c_vehbody is NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._c_vehbody is not NULL:
            cVehicleBody.freeVehBodyPointer(self._c_vehbody)
            cParam_dtm.vehicle_param_free(self._c_vehparam)
            cVehicleState.vehstate_free(self._c_vehstate)

    def calcBodyAngles(self):
         if self._c_vehbody is not NULL:
            cVehicleBody.calcBodyStatus(self._c_vehparam, self._c_vehstate)
