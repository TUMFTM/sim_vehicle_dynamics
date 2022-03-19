# import PassengerVehicle
import numpy as np
import matplotlib.pyplot as plt
from PassengerVehicle import PassengerVehicle

if __name__ == '__main__':

    # initialize vehicle
    veh = PassengerVehicle()
    # set initial pose
    veh.set_VehicleStartPoint(np.array([0, 0, 0, 1], dtype='double'))

    # allocate memory for logs
    n_sim = 50000
    vx_mps = np.zeros(n_sim)
    dPsi_radps = np.zeros(n_sim)
    ay_mps2 = np.zeros(n_sim)
    time = [0.002*t for t in range(0, n_sim)]

    # steering request
    SteeringAngle_rad = 0.05
    # force request
    DriveForce_N = 1000

    # simulate model with constant steering angle and force request
    for i in range(n_sim):
        # get current vehicle dynamic state
        vx_mps[i] = veh.get_vx_mps()
        dPsi_radps[i] = veh.get_dPsi_radps()
        ay_mps2[i] = veh.get_ay_mps2()
        # update inputs
        veh.set_SteeringAngle(SteeringAngle_rad)
        veh.set_DriveForce(DriveForce_N)
        # simulate
        veh.step()

    # visualize results
    fig, ax = plt.subplots(3, 1)
    ax[0].plot(time, dPsi_radps)
    ax[0].grid()
    ax[0].set_ylabel('Yaw rate\n in radps')
    ax[1].plot(time, ay_mps2)
    ax[1].grid()
    ax[1].set_ylabel('Lateral acceleration\n in mps2')
    ax[2].plot(time, vx_mps)
    ax[2].grid()
    ax[2].set_xlabel('Time in s')
    ax[2].set_ylabel('Velocity\n in mps')
    plt.show()
