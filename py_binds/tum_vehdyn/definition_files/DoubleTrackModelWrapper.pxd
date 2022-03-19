from rtwtypes cimport *
from libcpp.string cimport string

cdef extern from "DoubleTrackModelWrapper.h":
    cdef cppclass DoubleTrackModelWrapper:
        DoubleTrackModelWrapper() except +
        void step()

        # set actuator commands
        void set_DriveTorque(real_T* T_DriveTorque_Nm);
        void set_BrakePressure(real_T* p_BrakePressure_pa);
        void set_SteeringAngle(real_T SteeringAngle);
        void set_externalForce(real_T* extForce_N);
        void set_externalTorque(real_T* extTorque_Nm);

        void set_lambdaMuex(real_T* lambdaMuex);
        void set_lambdaMuey(real_T* lambdaMuey);


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
        real_T get_SteeringAngle_rad();
        real_T get_T_DriveTorqueFL_Nm();
        real_T get_T_DriveTorqueFR_Nm();
        real_T get_T_DriveTorqueRL_Nm();
        real_T get_T_DriveTorqueRR_Nm();
        real_T get_BrakePressureFL_pa();
        real_T get_BrakePressureFR_pa();
        real_T get_BrakePressureRL_pa();
        real_T get_BrakePressureRR_pa();
        real_T get_omegaWheelFL_radps();
        real_T get_omegaWheelFR_radps();
        real_T get_omegaWheelRL_radps();
        real_T get_omegaWheelRR_radps();

        # Parameters
        int set_parameter(string param, double value);
        double get_parameter(string param);
