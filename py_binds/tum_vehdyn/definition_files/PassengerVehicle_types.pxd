from rtwtypes cimport *

cdef extern from "trajectory_planning_dev_py_types.h":
    ctypedef uint16_T TUMHealthStatus

    ctypedef uint16_T TUMStrategyState

    ctypedef uint16_T TUMVehicleState

    ctypedef enum TUMStateEstimationState:
        SE_OFF = 0
        SE_NORMAL
        SE_BYPASS
        SE_ODOM
        SE_FAIL

    ctypedef struct CartPos:
        real_T x_m
        real_T y_m
        real_T psi_rad

    ctypedef struct Trajectory:
        uint32_T LapCnt
        uint32_T TrajCnt
        real_T s_loc_m[50]
        real_T s_glob_m[50]
        real_T x_m[50]
        real_T y_m[50]
        real_T psi_rad[50]
        real_T kappa_radpm[50]
        real_T v_mps[50]
        real_T ax_mps2[50]

    ctypedef struct VehicleDynamicState:
        TUMHealthStatus SE_Status
        TUMStateEstimationState SE_State
        CartPos Pos
        real_T z_m
        real_T PosAccuracy[3]
        real_T VelAccuracy[3]
        real_T dPsi_radps
        real_T vx_mps
        real_T vy_mps
        real_T v_mps
        real_T beta_rad
        real_T ax_mps2
        real_T ay_mps2
        real_T psi_vel_rad
        real_T kappa_radpm
        real_T dBeta_radps
        real_T ddPsi_radps2
        real_T ax_vel_mps2
        real_T ay_vel_mps2
        real_T lambdaFL_perc
        real_T lambdaFR_perc
        real_T lambdaRL_perc
        real_T lambdaRR_perc
        real_T alphaFL_rad
        real_T alphaFR_rad
        real_T alphaRL_rad
        real_T alphaRR_rad
        real_T DiffFRAlpha_rad

    ctypedef struct TrajPlanner_Send:
        TUMVehicleState TUMVehicleState
        uint8_T BDriveMode
