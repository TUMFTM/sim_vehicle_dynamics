cimport cVehicleState

cdef class VehicleState:
    cdef cVehicleState.VehicleState* _c_vehstate

    def __cinit__(self):
        self._c_vehstate = cVehicleState.vehstate_new()
        if self._c_vehstate is NULL:
            raise MemoryError()
    
    def __dealloc__(self):
        if self._c_vehstate is not NULL:
            cVehicleState.vehstate_free(self._c_vehstate)

    def testSetPos(self, pos):
        if self._c_vehstate is not NULL:
            cVehicleState.testSetPos(self._c_vehstate, pos)

    def getPosIni(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.getPosIni(self._c_vehstate)
