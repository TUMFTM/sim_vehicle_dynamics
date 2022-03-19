from DoubleTrackModelWrapper cimport *
import numpy as np
cimport numpy as cnp

cdef class DoubleTrackModel:
    cdef DoubleTrackModelWrapper *_c_model

    def __cinit__(self):
        self._c_model = new DoubleTrackModelWrapper()

    def __dealloc__(self):
        if self._c_model != NULL:
            del self._c_model

    def step(self):
        self._c_model.step()

    # set values ---------------------------------------------------------------

    def set_DriveTorque(self, cnp.ndarray[double, ndim=1, mode='c'] DriveTorque_Nm):
        self._c_model.set_DriveTorque(&DriveTorque_Nm[0])

    def set_BrakePressure(self, cnp.ndarray[double, ndim=1, mode='c'] p_Brake_pa):
        self._c_model.set_BrakePressure(&p_Brake_pa[0])

    def set_SteeringAngle(self, SteeringAngle_rad):
        self._c_model.set_SteeringAngle(SteeringAngle_rad)

    def set_externalForce(self, cnp.ndarray[double, ndim=1, mode='c'] extForce_N):
        self._c_model.set_externalForce(&extForce_N[0])

    def set_externalTorque(self, cnp.ndarray[double, ndim=1, mode='c'] extTorque_Nm):
        self._c_model.set_externalTorque(&extTorque_Nm[0])

    def set_lambdaMuex(self, cnp.ndarray[double, ndim=1, mode='c'] lambdaMuex):
        self._c_model.set_lambdaMuex(&lambdaMuex[0])

    def set_lambdaMuey(self, cnp.ndarray[double, ndim=1, mode='c'] lambdaMuey):
        self._c_model.set_lambdaMuey(&lambdaMuey[0])

    # get values ---------------------------------------------------------------

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

    def get_SteeringAngle_rad(self):
        return self._c_model.get_SteeringAngle_rad()

    def get_T_DriveTorqueFL_Nm(self):
        return self._c_model.get_T_DriveTorqueFL_Nm()

    def get_T_DriveTorqueFR_Nm(self):
        return self._c_model.get_T_DriveTorqueFR_Nm()

    def get_T_DriveTorqueRL_Nm(self):
        return self._c_model.get_T_DriveTorqueRL_Nm()

    def get_T_DriveTorqueRR_Nm(self):
        return self._c_model.get_T_DriveTorqueRR_Nm()

    def get_BrakePressureFL_pa(self):
        return self._c_model.get_BrakePressureFL_pa()

    def get_BrakePressureFR_pa(self):
        return self._c_model.get_BrakePressureFR_pa()

    def get_BrakePressureRL_pa(self):
        return self._c_model.get_BrakePressureRL_pa()

    def get_BrakePressureRR_pa(self):
        return self._c_model.get_BrakePressureRR_pa()

    def get_omegaWheelFL_radps(self):
        return self._c_model.get_omegaWheelFL_radps()

    def get_omegaWheelFR_radps(self):
        return self._c_model.get_omegaWheelFR_radps()

    def get_omegaWheelRL_radps(self):
        return self._c_model.get_omegaWheelRL_radps()

    def get_omegaWheelRR_radps(self):
        return self._c_model.get_omegaWheelRR_radps()


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
