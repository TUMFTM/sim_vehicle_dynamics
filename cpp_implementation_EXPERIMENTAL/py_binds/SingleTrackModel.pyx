cimport cSingleTrackModel
cimport cVehicleState
cimport cexecute_testcase

cdef class SingleTrackModel:
    cdef cSingleTrackModel.SingleTrackModel* _c_stm
    cdef cVehicleState.VehicleState* _c_vehstate
    cdef cSingleTrackModel.SingleTrackModel* _c_stm_tminus1
    cdef cVehicleState.VehicleState* _c_vehstate_tminus1

    def __cinit__(self, solver):      
        if solver == "euler":
            self._c_stm = cSingleTrackModel.stm_new()
            self._c_vehstate = cVehicleState.vehstate_new()
            cSingleTrackModel.set_solver_testcase(self._c_stm, 0)

            if self._c_stm is NULL:
                raise MemoryError()

        elif  solver == "heuns": 
            self._c_stm = cSingleTrackModel.stm_new()
            self._c_vehstate = cVehicleState.vehstate_new()
            cSingleTrackModel.set_solver_testcase(self._c_stm, 1)
            
            if self._c_stm is NULL:
                raise MemoryError()

        elif solver == "adams":
            self._c_stm = cSingleTrackModel.stm_new()
            self._c_vehstate = cVehicleState.vehstate_new()

            self._c_stm_tminus1 = cSingleTrackModel.stm_new()
            self._c_vehstate_tminus1 = cVehicleState.vehstate_new()

            cSingleTrackModel.set_solver_testcase(self._c_stm, 2)

            if self._c_stm is NULL:
                raise MemoryError()
        else: 
            raise ValueError("keyword for solver not recognized\nvalid input is: 'euler' 'heuns' 'adams'")

    def __dealloc__(self):
        if self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) <= 1:
            cSingleTrackModel.stm_free(self._c_stm)
            cVehicleState.vehstate_free(self._c_vehstate)

        elif self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) == 2:
            cSingleTrackModel.stm_free(self._c_stm)
            cSingleTrackModel.stm_free(self._c_stm_tminus1)

            cVehicleState.vehstate_free(self._c_vehstate)
            cVehicleState.vehstate_free(self._c_vehstate_tminus1)

    def step_simulation(self, **kwargs):
        if self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) == 0:
            cSingleTrackModel.calcLongForce_stm(self._c_stm, self._c_vehstate)
            cSingleTrackModel.vehicleModel(self._c_stm, self._c_vehstate)
            cSingleTrackModel.integrate_update_stm(self._c_stm, self._c_vehstate)

        elif self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) == 1:
            cSingleTrackModel.heun(self._c_stm, self._c_vehstate) 

        elif self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) == 2:
            cSingleTrackModel.adams_bashforth_stm(self._c_stm, self._c_stm_tminus1, self._c_vehstate, self._c_vehstate_tminus1, kwargs["step"])

        else: 
            raise ValueError("solver not identified!")


    ####################
    ### RUN TESTCASE ###
    ####################
    def run_testcase(self):
        if self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) <= 1:
            cexecute_testcase.testcase_euler_heun_stm_py(self._c_stm, self._c_vehstate)

        elif self._c_stm is not NULL and cSingleTrackModel.get_solver_testcase(self._c_stm) == 2:
            cexecute_testcase.testcase_adams_stm_py(self._c_stm, self._c_stm_tminus1, self._c_vehstate, self._c_vehstate_tminus1)


    ########################
    ### GETTER FUNCTIONS ###
    ########################
    def get_param_vehmass_test(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_param_vehmass_test(self._c_stm)

    def get_timestep(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_timestep(self._c_stm)

    def get_logging(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_logging(self._c_stm)

    def get_lograte_testcase(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_lograte_testcase(self._c_stm)

    def get_timestep(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_timestep(self._c_stm)

    def get_filename_testcase(self):
        if self._c_stm is not NULL: 
           return  cSingleTrackModel.get_filename_testcase(self._c_stm)

    def get_posx_ini(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_posx_ini(self._c_vehstate)

    def get_posy_ini(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_posy_ini(self._c_vehstate)

    def get_psi_ini(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_psi_ini(self._c_vehstate)

    def get_vx_veh(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_vx_veh(self._c_vehstate)

    def get_vy_veh(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_vy_veh(self._c_vehstate)

    def get_dpsi_ini(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_dpsi_ini(self._c_vehstate)

    def get_ax_veh(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_ax_veh(self._c_vehstate)

    def get_ay_veh(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_ay_veh(self._c_vehstate)

    def get_ddpsi_ini(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_ddpsi_ini(self._c_vehstate)

    def get_omega_fl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_omega_fl(self._c_vehstate)

    def get_omega_fr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_omega_fr(self._c_vehstate)

    def get_omega_rl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_omega_rl(self._c_vehstate)

    def get_omega_rr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_omega_rr(self._c_vehstate)

    def get_lambda_fl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_lambda_fl(self._c_vehstate)

    def get_lambda_fr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_lambda_fr(self._c_vehstate)

    def get_lambda_rl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_lambda_rl(self._c_vehstate)

    def get_lambda_rr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_lambda_rr(self._c_vehstate)

    def get_alpha_fl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_alpha_fl(self._c_vehstate)

    def get_alpha_fr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_alpha_fr(self._c_vehstate)

    def get_alpha_rl(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_alpha_rl(self._c_vehstate)

    def get_alpha_rr(self):
        if self._c_vehstate is not NULL:
            return cVehicleState.get_alpha_rr(self._c_vehstate)


    ########################
    ### SETTER FUNCTIONS ###
    ########################
    def setParams_stm(self):
        if self._c_stm is not NULL:
            cSingleTrackModel.setParameters_stm(self._c_stm)

    def set_timestep(self, timestep):
        if self._c_stm is not NULL:
            cSingleTrackModel.set_timestep(self._c_stm, timestep)
    def set_logging(self, number):
        # input is an integer 
        # int = 1 logging is activated 
        # else logging is deactivated
        # by default logging is deactivated 
        if self._c_stm is not NULL:
            cSingleTrackModel.set_logging(self._c_stm, number)

    def set_timecap_testcase(self, timecap):
        # time to be tested from the csv file 
        # csv file must at least be as long as the timecap 
        # default value is 65 s 
        if self._c_stm is not NULL:
            cSingleTrackModel.set_timecap_testcase(self._c_stm, timecap)

    def set_lograte_testcase(self, lograte):
        # define rate in which the results of the simualtion will be written to a csv file 
        # if logging is activated 
        # rate is given as a time
        # default value is 0.004 s 
        if self._c_stm is not NULL:
            cSingleTrackModel.set_lograte_testcase(self._c_stm, lograte)

    def set_testfile_testcase(self, testfilename):
        # set the name of the testfile which will be executed 
        # file must be located in the test_scenarios folder 
        # CAUTION the C function expects a argument of type char* 
        # therfore you have to pass an argument in python of type string bytes 
        # e.g. b"acc_60s"
        # CAUTION the maximun file name length is 300 characters
        if self._c_stm is not NULL:
            cSingleTrackModel.set_filename_testcase(self._c_stm, testfilename)

    def set_steeringangle(self, steeringangle_rad):
        if self._c_vehstate is not NULL:
            cVehicleState.set_steeringangle(self._c_vehstate, steeringangle_rad)

    def set_torque_fl_Nm(self, torque_Nm):
        if self._c_vehstate is not NULL:
            cVehicleState.set_torque_fl_Nm(self._c_vehstate, torque_Nm)

    def set_torque_fr_Nm(self, torque_Nm):
        if self._c_vehstate is not NULL:
            cVehicleState.set_torque_fr_Nm(self._c_vehstate, torque_Nm)

    def set_torque_rl_Nm(self, torque_Nm):
        if self._c_vehstate is not NULL:
            cVehicleState.set_torque_rl_Nm(self._c_vehstate, torque_Nm)

    def set_torque_rr_Nm(self, torque_Nm):
        if self._c_vehstate is not NULL:
            cVehicleState.set_torque_rr_Nm(self._c_vehstate, torque_Nm)

    def set_tiretorque_4w_Nm(self, torque_4w_Nm):
        if self._c_vehstate is not NULL:
            cVehicleState.set_torque_fl_Nm(self._c_vehstate, torque_4w_Nm[0])
            cVehicleState.set_torque_fr_Nm(self._c_vehstate, torque_4w_Nm[1])
            cVehicleState.set_torque_rl_Nm(self._c_vehstate, torque_4w_Nm[2])
            cVehicleState.set_torque_rr_Nm(self._c_vehstate, torque_4w_Nm[3])

    def set_brakepressure_fl_Pa(self, brakebressure_Pa):
        if self._c_vehstate is not NULL:
             cVehicleState.set_brakepressure_fl_Pa(self._c_vehstate, brakebressure_Pa)

    def set_brakepressure_fr_Pa(self, brakebressure_Pa):
        if self._c_vehstate is not NULL:
             cVehicleState.set_brakepressure_fr_Pa(self._c_vehstate, brakebressure_Pa)

    def set_brakepressure_rl_Pa(self, brakebressure_Pa):
        if self._c_vehstate is not NULL:
             cVehicleState.set_brakepressure_rl_Pa(self._c_vehstate, brakebressure_Pa)

    def set_brakepressure_rr_Pa(self, brakebressure_Pa):
        if self._c_vehstate is not NULL:
             cVehicleState.set_brakepressure_rr_Pa(self._c_vehstate, brakebressure_Pa)

    def set_brakepressure_4w_Pa(self, brakepressure_4w_Pa):
        if self._c_vehstate is not NULL:
             cVehicleState.set_brakepressure_fl_Pa(self._c_vehstate, brakepressure_4w_Pa[0])
             cVehicleState.set_brakepressure_fr_Pa(self._c_vehstate, brakepressure_4w_Pa[1])
             cVehicleState.set_brakepressure_rl_Pa(self._c_vehstate, brakepressure_4w_Pa[2])
             cVehicleState.set_brakepressure_rr_Pa(self._c_vehstate, brakepressure_4w_Pa[3])

    def set_posx_ini(self, posx_m):
        if self._c_vehstate is not NULL:
            cVehicleState.set_posx_ini(self._c_vehstate, posx_m)

    def set_posy_ini(self, posy_m):
        if self._c_vehstate is not NULL:
            cVehicleState.set_posy_ini(self._c_vehstate, posy_m)

    def set_psi_ini(self, psi_rad):
        if self._c_vehstate is not NULL:
            cVehicleState.set_psi_ini(self._c_vehstate, psi_rad)

    def set_vx_veh(self, vx_mps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_vx_veh(self._c_vehstate, vx_mps)

    def set_vy_veh(self, vy_mps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_vy_veh(self._c_vehstate, vy_mps)

    def set_dpsi_ini(self, dpsi_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_dpsi_ini(self._c_vehstate, dpsi_radps)

    def set_ax_veh(self, ax_mps2):
        if self._c_vehstate is not NULL:
            cVehicleState.set_ax_veh(self._c_vehstate, ax_mps2)

    def set_ay_veh(self, ay_mps2):
        if self._c_vehstate is not NULL:
            cVehicleState.set_ay_veh(self._c_vehstate, ay_mps2)

    def set_ddpsi_ini(self, ddpsi_radps2):
        if self._c_vehstate is not NULL:
            cVehicleState.set_ddpsi_ini(self._c_vehstate, ddpsi_radps2)

    def set_omega_fl(self, omega_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_omega_fl(self._c_vehstate, omega_radps)

    def set_omega_fr(self, omega_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_omega_fr(self._c_vehstate, omega_radps)

    def set_omega_rl(self, omega_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_omega_rl(self._c_vehstate, omega_radps)

    def set_omega_rr(self, omega_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_omega_rr(self._c_vehstate, omega_radps)

    def set_omega_4w(self, omega_4w_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_omega_fl(self._c_vehstate, omega_4w_radps[0])
            cVehicleState.set_omega_fr(self._c_vehstate, omega_4w_radps[1])
            cVehicleState.set_omega_rl(self._c_vehstate, omega_4w_radps[2])
            cVehicleState.set_omega_rr(self._c_vehstate, omega_4w_radps[3])

    def set_lambda_fl(self, lambda_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_lambda_fl(self._c_vehstate, lambda_radps)

    def set_lambda_fr(self, lambda_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_lambda_fr(self._c_vehstate, lambda_radps)

    def set_lambda_rl(self, lambda_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_lambda_rl(self._c_vehstate, lambda_radps)

    def set_lambda_rr(self, lambda_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_lambda_rr(self._c_vehstate, lambda_radps)

    def set_lambda_4w(self, lambda_4w_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_lambda_fl(self._c_vehstate, lambda_4w_radps[0])
            cVehicleState.set_lambda_fr(self._c_vehstate, lambda_4w_radps[1])
            cVehicleState.set_lambda_rl(self._c_vehstate, lambda_4w_radps[2])
            cVehicleState.set_lambda_rr(self._c_vehstate, lambda_4w_radps[3])

    def set_alpha_fl(self, alpha_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_alpha_fl(self._c_vehstate, alpha_radps)

    def set_alpha_fr(self, alpha_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_alpha_fr(self._c_vehstate, alpha_radps)

    def set_alpha_rl(self, alpha_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_alpha_rl(self._c_vehstate, alpha_radps)

    def set_alpha_rr(self, alpha_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_alpha_rr(self._c_vehstate, alpha_radps)

    def set_alpha_4w(self, alpha_4w_radps):
        if self._c_vehstate is not NULL:
            cVehicleState.set_alpha_fl(self._c_vehstate, alpha_4w_radps[0])
            cVehicleState.set_alpha_fr(self._c_vehstate, alpha_4w_radps[1])
            cVehicleState.set_alpha_rl(self._c_vehstate, alpha_4w_radps[2])
            cVehicleState.set_alpha_rr(self._c_vehstate, alpha_4w_radps[3])

