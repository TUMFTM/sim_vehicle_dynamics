# import PassengerVehicle
import numpy as np
import matplotlib.pyplot as plt
from SingleTrackModel import SingleTrackModel

if __name__ == '__main__':

    # initialize vehicle
    stm = SingleTrackModel()
    # set initial pose

    # allocate memory for logs
    n_sim = 50000
    x_m = np.zeros(n_sim)
    y_m = np.zeros(n_sim)
    vx_mps = np.zeros(n_sim)
    dPsi_radps = np.zeros(n_sim)
    ax_mps2 = np.zeros(n_sim)
    ay_mps2 = np.zeros(n_sim)
    time = [0.002*t for t in range(0, n_sim)]

    # steering request
    SteeringAngle_rad = 0.01
    # force request
    T_DriveTorque_Nm = np.array([200,200,300,300], dtype='double')
    p_BrakePressure_pa = np.array([0,0,0,0], dtype='double')

    T_externalTorque_Nm = np.array([0, 0, 200], dtype='double')

    # simulate model with constant steering angle and force request
    for i in range(n_sim):
        # get current vehicle dynamic state
        x_m[i] = stm.get_x_m()
        y_m[i] = stm.get_y_m()
        vx_mps[i] = stm.get_vx_mps()
        dPsi_radps[i] = stm.get_dPsi_radps()
        ax_mps2[i] = stm.get_ax_mps2()
        ay_mps2[i] = stm.get_ay_mps2()
        # update inputs
        stm.set_SteeringAngle(SteeringAngle_rad)
        stm.set_DriveTorque(T_DriveTorque_Nm)
        stm.set_BrakePressure(p_BrakePressure_pa)

        stm.set_externalTorque(T_externalTorque_Nm)

        # simulate
        stm.step()

    # visualize results
    fig, ax = plt.subplots(3, 1)
    ax[0].plot(time, dPsi_radps)
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
