cdef extern from "VehicleState.h":
    cdef struct TireState:
        pass

    ctypedef struct VehicleState:
        pass

    VehicleState *vehstate_new()
    void vehstate_free(VehicleState* vehstate)
    
    void copyVehstate(VehicleState *v1, VehicleState *v2)

    void testSetPos(VehicleState* vehstate, double pos)
    double getPosIni(VehicleState* vehstate)


    double get_posx_ini(VehicleState* vehstate)
    double get_posy_ini(VehicleState* vehstate)
    double get_psi_ini(VehicleState* vehstate)

    double get_vx_veh(VehicleState* vehstate)
    double get_vy_veh(VehicleState* vehstate)
    double get_dpsi_ini(VehicleState* vehstate)

    double get_ax_veh(VehicleState* vehstate)
    double get_ay_veh(VehicleState* vehstate)
    double get_ddpsi_ini(VehicleState* vehstate)

    double get_omega_fl(VehicleState* vehstate)
    double get_omega_fr(VehicleState* vehstate)
    double get_omega_rl(VehicleState* vehstate)
    double get_omega_rr(VehicleState* vehstate)

    double get_lambda_fl(VehicleState* vehstate)
    double get_lambda_fr(VehicleState* vehstate)
    double get_lambda_rl(VehicleState* vehstate)
    double get_lambda_rr(VehicleState* vehstate)

    double get_alpha_fl(VehicleState* vehstate)
    double get_alpha_fr(VehicleState* vehstate)
    double get_alpha_rl(VehicleState* vehstate)
    double get_alpha_rr(VehicleState* vehstate)

    double get_domega_fl(VehicleState* vehstate)
    double get_domega_fr(VehicleState* vehstate)
    double get_domega_rl(VehicleState* vehstate)
    double get_domega_rr(VehicleState* vehstate)

    double get_fx_tire_fl(VehicleState* vehstate)
    double get_fx_tire_fr(VehicleState* vehstate)
    double get_fx_tire_rl(VehicleState* vehstate)
    double get_fx_tire_rr(VehicleState* vehstate)

    double get_fy_tire_fl(VehicleState* vehstate)
    double get_fy_tire_fr(VehicleState* vehstate)
    double get_fy_tire_rl(VehicleState* vehstate)
    double get_fy_tire_rr(VehicleState* vehstate)

    double get_steeringangle(VehicleState* vehstate)

    double get_torque_fl_Nm(VehicleState* vehstate)
    double get_torque_fr_Nm(VehicleState* vehstate)
    double get_torque_rl_Nm(VehicleState* vehstate)
    double get_torque_rr_Nm(VehicleState* vehstate)

    double get_brakepressure_fl_Pa(VehicleState* vehstate)
    double get_brakepressure_fr_Pa(VehicleState* vehstate)
    double get_brakepressure_rl_Pa(VehicleState* vehstate)
    double get_brakepressure_rr_Pa(VehicleState* vehstate)


    void set_steeringangle(VehicleState* vehstate, double angle_rad)

    void set_torque_fl_Nm(VehicleState* vehstate, double torque_Nm)
    void set_torque_fr_Nm(VehicleState* vehstate, double torque_Nm)
    void set_torque_rl_Nm(VehicleState* vehstate, double torque_Nm)
    void set_torque_rr_Nm(VehicleState* vehstate, double torque_Nm)

    void set_brakepressure_fl_Pa(VehicleState* vehstate, double pressure_Pa)
    void set_brakepressure_fr_Pa(VehicleState* vehstate, double pressure_Pa)
    void set_brakepressure_rl_Pa(VehicleState* vehstate, double pressure_Pa)
    void set_brakepressure_rr_Pa(VehicleState* vehstate, double pressure_Pa)

    void set_posx_ini(VehicleState* vehstate, double posx)
    void set_posy_ini(VehicleState* vehstate, double posy)
    void set_psi_ini(VehicleState* vehstate, double psi)

    void set_vx_veh(VehicleState* vehstate, double vx)
    void set_vy_veh(VehicleState* vehstate, double vy)
    void set_dpsi_ini(VehicleState* vehstate, double dpsi)

    void set_ax_veh(VehicleState* vehstate, double ax)
    void set_ay_veh(VehicleState* vehstate, double ay)
    void set_ddpsi_ini(VehicleState* vehstate, double ddpsi)

    void set_omega_fl(VehicleState* vehstate, double omega)
    void set_omega_fr(VehicleState* vehstate, double omega)
    void set_omega_rl(VehicleState* vehstate, double omega)
    void set_omega_rr(VehicleState* vehstate, double omega)

    void set_lambda_fl(VehicleState* vehstate, double lambda_0)
    void set_lambda_fr(VehicleState* vehstate, double lambda_0)
    void set_lambda_rl(VehicleState* vehstate, double lambda_0)
    void set_lambda_rr(VehicleState* vehstate, double lambda_0)

    void set_alpha_fl(VehicleState* vehstate, double alpha)
    void set_alpha_fr(VehicleState* vehstate, double alpha)
    void set_alpha_rl(VehicleState* vehstate, double alpha)
    void set_alpha_rr(VehicleState* vehstate, double alpha)
