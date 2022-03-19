# import PassengerVehicle
import numpy as np
import matplotlib.pyplot as plt
from DoubleTrackModel import DoubleTrackModel

if __name__ == '__main__':

    timestep_sim_s = 0.002


    # initialize vehicle
    dtm = DoubleTrackModel()
    # set initial pose

    # allocate memory for logs
    n_sim = 100000
    x_m = np.zeros(n_sim)
    y_m = np.zeros(n_sim)
    vx_mps = np.zeros(n_sim)
    Psi_rad = np.zeros(n_sim)
    dPsi_radps = np.zeros(n_sim)
    ax_mps2 = np.zeros(n_sim)
    ay_mps2 = np.zeros(n_sim)
    Torque_out = np.zeros([n_sim, 4])
    omegaWheel_radps = np.zeros([n_sim, 4])

    lambdaMuex = np.array([1.0, 1.0, 1.0, 1.0], dtype='double')
    lambdaMuey = np.array([1.0, 1.0, 1.0, 1.0], dtype='double')

    time = [timestep_sim_s*t for t in range(0, n_sim)]

    # steering request
    SteeringAngle_rad = 0.0

    # force request
    T_front_max = 500
    T_rear_max = 800

    array_T_DrTo_front = np.linspace(0, T_front_max, int(10/timestep_sim_s))[:, np.newaxis]
    array_T_DrTo_rear = np.linspace(0, T_rear_max, int(10/timestep_sim_s))[:, np.newaxis]

    if int(10/timestep_sim_s) < n_sim:

        array_fill_front = np.ones([n_sim - int(10/timestep_sim_s), 1]) * T_front_max
        array_fill_rear = np.ones([n_sim - int(10/timestep_sim_s), 1]) * T_rear_max

        array_T_DrTo_front = np.vstack([array_T_DrTo_front, array_fill_front])
        array_T_DrTo_rear = np.vstack([array_T_DrTo_rear, array_fill_rear])

    T_DriveTorque_Nm = np.hstack([array_T_DrTo_front,array_T_DrTo_front,array_T_DrTo_rear,array_T_DrTo_rear]).astype('double')

    # test
    T_DriveTorque_Nm = np.array([200,200,200,200], dtype='double')
    p_BrakePressure_pa = np.array([0,0,0,0], dtype='double')

    # set external torque working on vehicle body
    T_ext_Nm = np.array([0,0,0], dtype='double')
    F_ext_N = np.array([0,0,0], dtype='double')

    # simulate model with constant steering angle and force request
    for i in range(n_sim):

        # set tire scale factors
        dtm.set_lambdaMuex(lambdaMuex)
        dtm.set_lambdaMuey(lambdaMuey)

        # get current vehicle dynamic state
        x_m[i] = dtm.get_x_m()
        y_m[i] = dtm.get_y_m()
        vx_mps[i] = dtm.get_vx_mps()
        Psi_rad[i] = dtm.get_psi_rad()
        dPsi_radps[i] = dtm.get_dPsi_radps()
        ax_mps2[i] = dtm.get_ax_mps2()
        ay_mps2[i] = dtm.get_ay_mps2()

        # update inputs
        dtm.set_SteeringAngle(SteeringAngle_rad)
        dtm.set_DriveTorque(T_DriveTorque_Nm)
        #dtm.set_DriveTorque(T_DriveTorque_Nm[i, :])
        dtm.set_BrakePressure(p_BrakePressure_pa)

        dtm.set_externalForce(F_ext_N)
        dtm.set_externalTorque(T_ext_Nm)

        Torque_out[i, 0] = dtm.get_T_DriveTorqueFL_Nm()
        Torque_out[i, 1] = dtm.get_T_DriveTorqueFR_Nm()
        Torque_out[i, 2] = dtm.get_T_DriveTorqueRL_Nm()
        Torque_out[i, 3] = dtm.get_T_DriveTorqueRR_Nm()

        omegaWheel_radps[i, 0] = dtm.get_omegaWheelFL_radps()
        omegaWheel_radps[i, 1] = dtm.get_omegaWheelFR_radps()
        omegaWheel_radps[i, 2] = dtm.get_omegaWheelRL_radps()
        omegaWheel_radps[i, 3] = dtm.get_omegaWheelRR_radps()

        # simulate
        dtm.step()

    # visualize results
    fig, ax = plt.subplots(3, 1)
    ax[0].plot(time, Psi_rad)
    ax[0].grid()
    ax[0].set_ylabel('Yaw rate\n in radps')
    ax[1].plot(time, ax_mps2)
    ax[1].plot(time, ay_mps2)
    ax[1].grid()
    ax[1].set_ylabel('Long./Lat. acceleration\n in mps2')
    ax[2].plot(time, vx_mps)
    ax[2].grid()
    ax[2].set_xlabel('Time in s')
    ax[2].set_ylabel('Velocity\n in mps')
    plt.show()

    #fig2 = plt.figure()

    #plt.scatter(time, x_m)

    #plt.show()

    #fig3 = plt.figure()

    #plt.plot(time, Torque_out[:, 0])
    #plt.plot(time, Torque_out[:, 1])
    #plt.plot(time, Torque_out[:, 2])
    #plt.plot(time, Torque_out[:, 3])

    #plt.show()

    fig4 = plt.figure()

    plt.plot(time, omegaWheel_radps[:, 0])
    plt.plot(time, omegaWheel_radps[:, 1])
    plt.plot(time, omegaWheel_radps[:, 2])
    plt.plot(time, omegaWheel_radps[:, 3])

    plt.show()
