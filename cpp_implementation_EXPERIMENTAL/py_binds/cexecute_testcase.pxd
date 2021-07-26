from libc.stdio cimport * 

cdef extern from "execute_testcase.h":

    cdef extern from "SingleTrackModel.h":
        cdef struct SingleTrackModel:
            pass

    cdef extern from "VehicleState.h":
        ctypedef struct VehicleState:
            pass


    void testcase_stm()
    void testcase_euler_heun_stm_py(SingleTrackModel *stm, VehicleState* vehstate)
    void testcase_adams_stm_py(SingleTrackModel *stm, SingleTrackModel *stm_tminus1, VehicleState* vehstate, VehicleState* vehstate_tminus1)

    void create_logfile_stm_realdata(SingleTrackModel *stm, VehicleState* vehstate)
    void write_logfile_stm_realdata(SingleTrackModel *stm, VehicleState* vehstate, double timestep)

    void initialize_input_data(FILE* datafile, VehicleState* vehstate)
    void update_input_data(FILE* datafile, VehicleState* vehstate)
