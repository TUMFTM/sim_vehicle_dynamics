cdef extern from "SingleTrackModel.h":
    cdef struct SingleTrackModel:
        pass

    cdef extern from "VehicleState.h":
        ctypedef struct VehicleState:
            pass

    SingleTrackModel *stm_new()
    void stm_free(SingleTrackModel* stm)
    void copy_stm_diffS(SingleTrackModel* stm1, SingleTrackModel* stm2)

    void vehicleModel(SingleTrackModel* stm, VehicleState *vehstate)
    void calcWheelSlips_stm(SingleTrackModel* stm, VehicleState *vehstate)
    void tireModelPacejka(SingleTrackModel* stm, VehicleState *vehstate)
    void calcLongForce_stm(SingleTrackModel* stm, VehicleState *vehstate)

    void setParameters_stm(SingleTrackModel* stm)

    void integrate_update_stm(SingleTrackModel* stm, VehicleState *vehstate)
    void heun(SingleTrackModel* stm, VehicleState *vehstate)
    void adams_bashforth_stm(SingleTrackModel* stm, SingleTrackModel* stm_tminus1, VehicleState *vehstate, VehicleState *vehstate_tminus1, int step)

    
    void set_timestep(SingleTrackModel* stm, double timestep)
    void set_logging(SingleTrackModel* stm, int value)
    void set_solver_testcase(SingleTrackModel* stm, int value)
    void set_lograte_testcase(SingleTrackModel* stm, double value)
    void set_timecap_testcase(SingleTrackModel* stm, double value)
    void set_filename_testcase(SingleTrackModel* stm, char* filename)

    double get_param_vehmass_test(SingleTrackModel* stm)
    double get_timestep(SingleTrackModel* stm)
    int get_logging(SingleTrackModel* stm)
    int get_solver_testcase(SingleTrackModel* stm)
    double get_lograte_testcase(SingleTrackModel* stm)
    double get_timecap_testcase(SingleTrackModel* stm)
    char* get_filename_testcase(SingleTrackModel* stm)
