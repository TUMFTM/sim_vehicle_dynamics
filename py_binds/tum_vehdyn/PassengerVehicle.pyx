from PassengerVehicleWrapper cimport *
import numpy as np
cimport numpy as cnp

cdef class PassengerVehicle:
    cdef PassengerVehicleWrapper *_c_model

    def __cinit__(self):
        self._c_model = new PassengerVehicleWrapper()

    def __dealloc__(self):
        if self._c_model != NULL:
            del self._c_model

    def step(self):
        self._c_model.step()

    def set_VehicleStartPoint(self, cnp.ndarray[double, ndim=1, mode='c'] VehicleStartPoint):
        self._c_model.set_VehicleStartPoint(&VehicleStartPoint[0])

    def set_tpamapReference(self, cnp.ndarray[double, ndim=1, mode='c'] tpa_map, cnp.ndarray[double, ndim=1, mode='c'] interpTime, double tpa_map_mode):
        self._c_model.set_tpamapReference(&tpa_map[0], &interpTime[0], tpa_map_mode)

    def set_SteeringAngle(self, SteeringAngle):
        self._c_model.set_SteeringAngle(SteeringAngle)

    def set_DriveForce(self, DriveForce):
        self._c_model.set_DriveForce(DriveForce)

    def get_x_m(self):
        return self._c_model.get_x_m()

    def get_y_m(self):
        return self._c_model.get_y_m()

    def get_psi_rad(self):
        return self._c_model.get_psi_rad()

    def get_dPsi_radps(self):
        return self._c_model.get_dPsi_radps()

    def get_vx_mps(self):
        return self._c_model.get_vx_mps()

    def get_vy_mps(self):
        return self._c_model.get_vy_mps()

    def get_ax_mps2(self):
        return self._c_model.get_ax_mps2()

    def get_ay_mps2(self):
        return self._c_model.get_ay_mps2()

    def set_parameter(self, param, value):
        idx = self._c_model.set_parameter(param.encode('UTF-8'), value)
        if idx >= 0:
          print('Found ' + param + ' at index ' + str(idx) + \
          ' and updated to ' + str(self._c_model.get_parameter(param.encode('UTF-8'))))
        else:
          print(param + ' not found')

    def get_parameter(self, param):
        value = self._c_model.get_parameter(param.encode('UTF-8'))
        print('Value found for ' + param + ' is: ' + str(value))
        return value
