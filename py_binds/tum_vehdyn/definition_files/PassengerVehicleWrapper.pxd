from rtwtypes cimport *
from libcpp.string cimport string

cdef extern from "PassengerVehicleWrapper.h":
    cdef cppclass PassengerVehicleWrapper:
        PassengerVehicleWrapper() except +
        void step()

        void set_VehicleStartPoint(real_T* VehicleStartPoint);

        void set_tpamapReference(real_T* tpa_map, real_T* interpTime, real_T tpa_map_mode);

        # set actuator commands
        void set_SteeringAngle(real_T SteeringAngle);
        void set_DriveForce(real_T DriveForce);

        # get vehicle dynamic state
        real_T get_x_m();
        real_T get_y_m();
        real_T get_psi_rad();
        real_T get_dPsi_radps();
        real_T get_vx_mps();
        real_T get_vy_mps();
        real_T get_v_mps();
        real_T get_ax_mps2();
        real_T get_ay_mps2();

        # Parameters
        int set_parameter(string param, double value);
        double get_parameter(string param);
