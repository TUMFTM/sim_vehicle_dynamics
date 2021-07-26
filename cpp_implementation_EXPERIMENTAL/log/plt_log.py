import os
import glob
import numpy as np
import matplotlib.font_manager
import matplotlib.pyplot as plt


# TUM Colors
TUM_blue = '#3070b3'
TUM_blue_dark = '#003359'
TUM_blue_medium = '#64A0C8'
TUM_blue_light = '#98C6EA'
TUM_grey_dark = '#9a9a9a'
TUM_orange = '#E37222'
TUM_green = '#A2AD00'


def read_file_stm(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        # "time_s, xpos_m, ypos_m, psi_rad, vx_mps, vy_mps, dpsi_radps, ax_mps2, ay_mps2,"
        # "omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        # "lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        # "alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        # "Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        # "Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        # "FxPowertrain_FL_N, FxPowertrain_FR_N, FxPowertrain_RL_N, FxPowertrain_RR_N, " 
        # "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        # "SteeringAngle_rad
        pos     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 1, 2, 3))
        vel     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 4, 5, 6))
        acc     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 7, 8))
        omega   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 9, 10, 11, 12))
        kappa   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 13, 14, 15, 16))
        alpha   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 17, 18, 19, 20))
        fx      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 21, 22, 23, 24))
        fy      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 25, 26, 27, 28))
        fxpt    = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 29, 30, 31, 32))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 33, 34, 35, 36))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 37))
        ddpsi   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 38))
        
        return pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, pb, steer, ddpsi


def read_file_dtm(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        # "time_s, xpos_m, ypos_m, psi_rad, vx_mps, vy_mps, dpsi_radps, ax_mps2, ay_mps2,"
        # "omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        # "lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        # "alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        # "Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        # "Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        # "FxPowertrain_FL_N, FxPowertrain_FR_N, FxPowertrain_RL_N, FxPowertrain_RR_N, " 
        # "p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        # "SteeringAngle_rad
        pos     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 1, 2, 3))
        vel     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 4, 5, 6))
        acc     = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 7, 8))
        omega   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 9, 10, 11, 12))
        kappa   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 13, 14, 15, 16))
        alpha   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 17, 18, 19, 20))
        fx      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 21, 22, 23, 24))
        fy      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 25, 26, 27, 28))
        fxpt    = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 29, 30, 31, 32))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 33, 34, 35, 36))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 37))
        return pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, pb, steer


def read_file_dtm_angles(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        #"time_s, xpos_ini_m, ypos_ini_m, psi_ini_rad, vx_veh_mps, vy_veh_mps, dpsi_ini_radps, ax_veh_mps2, ay_veh_mps2,"
        #"omegaFL_radps, omegaFR_radps, omegaRL_radps, omegaRR_radps, "
        #"lambdaFL, lambdaFR, lambdaRL, lambdaRR, " 
        #"alphaFL_rad, alphaFR_rad, alphaRL_rad, alphaRR_rad, " 
        #"Fx_FL_N, Fx_FR_N, Fx_RL_N, Fx_RR_N, " 
        #"Fy_FL_N, Fy_FR_N, Fy_RL_N, Fy_RR_N, " 
        #"theta_veh_rad, phi_veh_rad, dtheta_veh_radps. dphi_veh_radps"
        #"theta_ini_rad, phi_ini_rad, dtheta_ini_radps. dphi_ini_radps"
        #"p_BrakeFL_bar, p_BrakeFR_bar, p_BrakeRL_bar, p_BrakeRR_bar, "
        #"SteeringAngle_rad\n"
        pos             = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 1, 2, 3))
        vel             = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 4, 5, 6))
        acc             = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 7, 8))
        omega           = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 9, 10, 11, 12))
        kappa           = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 13, 14, 15, 16))
        alpha           = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 17, 18, 19, 20))
        fx              = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 21, 22, 23, 24))
        fy              = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 25, 26, 27, 28))
        angles_veh      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 29, 30, 31, 32))
        angles_ini      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 23, 34, 35, 36))
        pb              = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 37, 38, 39, 40))
        steer           = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 41))
        acc_angles      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 42, 43, 44))
        return pos, vel, acc, omega, kappa, alpha, fx, fy, angles_veh, angles_ini, pb, steer, acc_angles


def read_file_dtm_movement(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        # "time_s, xpos_ini_m, ypos_ini_m, psi_ini_rad, vx_veh_mps, vy_veh_mps, dpsi_ini_radps, ax_veh_mps2, ay_veh_mps2,"
        # "xpos_runge_m, ypos_runge_m, vx_runge_mps, vy_runge_mps, ax_runge_mps2, ay_runge_mps2"
        # "SteeringAngle_rad\n");

        pos_euler       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 1, 2, 3))
        vel_euler       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 4, 5, 6))
        acc_euler       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 7, 8))
        pos_runge       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 9, 10))
        vel_runge       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 11, 12))
        acc_runge       = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 13, 14))
        steer           = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 15))
        return pos_euler, vel_euler, acc_euler, pos_runge, vel_runge, acc_runge, steer



################
### POSITION ###
################
def plot_pos(pos, color, savefigure):
        plt.figure(num='Position')
        plt.axis('equal')

        plt.plot(pos[:, 1], pos[:, 2],
                color=color, marker='.', linestyle='--', markersize=0.5)
        plt.ylabel("yPos in m", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("xPos in m", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_pos2.png')
                plt.close()


################
### VELOCITY ###
################
def plot_vx(vel, color, savefigure):
        plt.figure(num='v_x over time')
        #plt.axis('equal')

        plt.plot(vel[:, 0], vel[:, 1],
                color=color, marker='.', linestyle=':', markersize=0.5)
        plt.ylabel("v_x in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_vx1.png')
                plt.close()

def plot_vy(vel, savefigure):
        plt.figure(num='v_y over time')
        # plt.axis('equal')

        plt.plot(vel[:, 0], vel[:, 2],
                color=TUM_blue_dark, marker='.', linestyle='', markersize=0.5)
        plt.ylabel("v_y in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_vy1.png')
                plt.close()


####################
### ACCELERATION ###
####################
def plot_ax(acc, color, savefigure):
        plt.figure(num='a_x over time')

        plt.plot(acc[:, 0], acc[:, 1],
                color=color, marker='.', linestyle=':', markersize=0.5)
        plt.ylabel("a_x in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_vx1.png')
                plt.close()


##################
### WHEELSPEED ###
##################
def plot_wheelspeed(wheelspeed, savefigure):
        plt.figure()
        plt.axis('equal')

        plt.plot(wheelspeed[:, 0], wheelspeed[:, 1],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(wheelspeed[:, 0], wheelspeed[:, 3],
                color=TUM_blue_dark, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("omega in rad/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_wheelspeed.png')
                plt.close()


#################
### WHEELSLIP ###
#################
def plot_slip(slip, savefigure):
        plt.figure()

        plt.plot(slip[:, 0], slip[:, 1],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(slip[:, 0], slip[:, 3],
                color=TUM_blue_dark, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("Wheelslip", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_tireforceFX.png')
                plt.close()


####################
### TIREFORCE FX ###
####################
def plot_tireforce_fx(fx, savefigure):
        plt.figure()

        plt.plot(fx[:, 0], fx[:, 1],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(fx[:, 0], fx[:, 3],
                color=TUM_blue_dark, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("Tireforce in N", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_tireforceFX.png')
                plt.close()


###############################
### TIREFORCE FX POWERTRAIN ###
###############################
def plot_tireforce_fxpt(fx_pt, savefigure):
        plt.figure()

        plt.plot(fx_pt[:, 0], fx_pt[:, 1],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(fx_pt[:, 0], fx_pt[:, 3],
                color=TUM_blue_dark, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("Tireforce Powertrain X in N", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_tireforceFXPT.png')
                plt.close()


##############
### ANGLES ###
##############
def plot_angles(angles_veh, savefigure):
        plt.figure()

        plt.plot(angles_veh[:, 0], angles_veh[:, 3],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(angles_veh[:, 0], angles_veh[:, 4],
                color=TUM_orange, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("Angles veh in rad", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_angles_veh.png')
                plt.close()


def plot_diifferential_angles(diff_angles_veh, savefigure):
        plt.figure()

        plt.plot(angles_veh[:, 0], angles_veh[:, 1],
                color=TUM_blue, marker='.', linestyle='', markersize=0.5)
        plt.plot(angles_veh[:, 0], angles_veh[:, 2],
                color=TUM_orange, marker='.', linestyle='', markersize=0.5)

        plt.ylabel("Angles veh in rad", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_angles_veh.png')
                plt.close()


def plot_psi_dpsi(pos, vel, savefigure):
        plt.figure()

        plt.plot(pos[:, 0], pos[:, 3],
                color=TUM_blue, marker='.', linestyle='--', markersize=0.5, label="Psi")
        plt.plot(vel[:, 0], vel[:, 3],
                color=TUM_orange, marker='.', linestyle='-.', markersize=0.5, label="dPsi")

        plt.ylabel("Angles veh in rad", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.xlabel("time in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)
        plt.legend()

        #save figure
        if savefigure == True:
                plt.savefig(dirCurrent + '/plt_figures/plt_angles_veh.png')
                plt.close()


# Current working directory
dirCurrent = os.path.abspath(os.getcwd())

#creating filepath an name input files 
file1 = "./19.11.2020-11:53:26_STM.csv"
file2 = "./23.11.2020-13:26:46_DTM.csv"
file3 = "./01.12.2020-10:01:19_DTM_angles.csv"


file_euler = "./01.12.2020-13:27:27_DTM_angles_euler.csv"
file_adam = "./01.12.2020-13:28:18_DTM_angles_adam.csv"
file_runge = "./01.12.2020-13:28:55_DTM_angles_runge.csv"

file_vormittag = "./01.12.2020-10:39:02_DTM_angles.csv"
file_euler_0KM = "./01.12.2020-14:08:33_DTM_angles_euler_withoutKM.csv"
file_adam_0KM = "./01.12.2020-14:09:22_DTM_angles_adam_withoutKM.csv"
file_euler_0KM1 = "./01.12.2020-14:37:03_DTM_angles_euler_0KM_1.csv"
file_adam_0KM1 = "./01.12.2020-14:58:58_DTM_angles_adam_0KM_1.csv"
file_euler_0KM2 = "./01.12.2020-14:37:03_DTM_angles_euler_0KM_2.csv"
file_adam_0KM2 = "./01.12.2020-14:58:58_DTM_angles_adam_0KM_2.csv"

file_euler_0KM_0s = "./01.12.2020-15:23:19_euler_0KM_0steering.csv"
file_adam_0KM_0s = "./01.12.2020-15:18:45_adam_0KM_0steering_2.csv"
file_runge_0KM_0s = "./01.12.2020-15:24:21_runge_0KM_0steering.csv"


file_euler_t005_0steer  = "2020.12.02-09:43:13_euler_t005_0steer.csv"
file_euler_t005_steer  = "2020.12.02-09:52:22_euler_t005_steer.csv"
file_euler_t001_0steer = "2020.12.02-09:56:32_euler_t001_0steer.csv"
file_euler_t001_steer = "2020.12.02-10:00:08_euler_t001_steer.csv"
file_euler_t0005_steer = "2020.12.02-10:47:47_euler_t0005_steer.csv"

file_adam_t005_0steer  = "2020.12.02-09:48:47_adam_t005_0steer.csv"
file_adam_t005_steer  = "2020.12.02-09:53:01_adam_t005_steer.csv"
file_adam_t001_0steer  = "2020.12.02-09:58:39_adam_t001_0steer.csv"
file_adam_t001_steer  = "2020.12.02-10:00:39_adam_t001_steer.csv"
file_adam_t0005_steer  = "2020.12.02-10:49:06_adam_t0005_steer.csv"



file_runge_t005_0steer  = "2020.12.02-09:49:21_runge_t005_0steer.csv"
file_runge_t005_steer  = "2020.12.02-09:53:43_runge_t005_steer.csv"
file_runge_t001_0steer  = "2020.12.02-09:59:25_runge_t001_0steer.csv"
file_runge_t001_steer  = "2020.12.02-10:01:13_runge_t001_steer.csv"
file_runge_t0005_steer  = "2020.12.02-10:49:36_runge_t0005_steer.csv"



#get latest file 
list_of_files = glob.glob('./*.csv')
latest_file = max(list_of_files, key=os.path.getctime)


# pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, brake_pressure, steeringangle, ddpsi = read_file_stm(latest_file)

# plot_pos(pos, False)
# plot_vx(vel, False)
# plot_psi_dpsi(pos, vel, False)
# plt.plot(ddpsi[:, 0], ddpsi[:, 1],
#         color=TUM_grey_dark, marker='', linestyle='-.', markersize=1.5)

# plt.figure()
# plt.plot(pos[:, 0], pos[:, 2],
#         color=TUM_blue, marker='x', linestyle='-', markersize=1.5)

# plt.figure()
# plt.plot(steeringangle[:, 0], steeringangle[:, 1],
#         color=TUM_blue, marker='x', linestyle='-', markersize=1.5)

# plot_vy(vel, False)
# plot_ax(acc, False)
# plot_slip(kappa, False)
# plot_tireforce_fx(fx, False)
# plot_wheelspeed(omega, False)
#plot_tireforce_fxpt(fxpt, False)


# plot angles

# pos, vel_latest, acc, omega, kappa, alpha, fx, fy, angles_veh, angles_ini, pb, steer, acc_angles = read_file_dtm_angles(latest_file)

# # plot_angles(angles_veh, False)
# # plot_angles(angles_ini, False)
# # plot_tireforce_fx(fx, False)
# # # plot_diifferential_angles(angles_veh, False)
# # # plot_diifferential_angles(angles_ini, False)

# plot_psi_dpsi(pos, vel, False)

# pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, brake_pressure, steeringangle = read_file_dtm(file_euler)

# plt.figure()
# plt.axis('equal')

# plt.plot(vel[:, 0], vel[:, 1],
#         color=TUM_blue, marker='x', linestyle='-', markersize=1.5)
# plt.ylabel("v_x in m/s", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)
# plt.xlabel("time in s", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, brake_pressure, steeringangle = read_file_dtm(file_runge)

# plt.plot(vel[:, 0], vel[:, 1],
#         color=TUM_orange, marker='o', linestyle='-.', markersize=0.5)


# PLOT MOVEMENT 

# pos_euler, vel_euler, acc_euler, pos_runge, vel_runge, acc_runge, steer = read_file_dtm_movement(latest_file)

# plot_pos(pos_euler, False)
# plot_pos(pos_runge, False)
# plot_vx(vel_euler, False)
# plot_vx(vel_runge, False)
# plot_ax(acc_euler,False)
# plot_ax(acc_runge,False)


# plt.figure()
# plt.axis('equal')

# plt.plot(acc_euler[:, 0], acc_euler[:, 1]-acc_runge[:, 1],
#         color=TUM_orange, marker='x', linestyle='-', markersize=1.5)


###############
### comapre ###
###############

# pos, vel, acc, omega, kappa, alpha, fx, fy, angles_veh, angles_ini, pb, steer, acc_angles = read_file_dtm_angles(file_euler_t0005_steer)

# # plt.figure(num='posx over time')
# # plt.plot(pos[:, 0], pos[:, 1],
# #         color=TUM_green, marker='', linestyle='-', markersize=1.5)

# plt.figure(num='fx over time')
# plt.plot(fx[:, 0], fx[:, 1],
#         color=TUM_green, marker='', linestyle=':', markersize=1.5)

# plt.figure(num='slip over time')
# plt.plot(kappa[:, 0], kappa[:, 1],
#         color=TUM_green, marker='', linestyle=':', markersize=1.5)

# plot_pos(pos, TUM_green, False)
# plot_vx(vel, TUM_green, False)
# plot_ax(acc, TUM_green, False)

# pos, vel, acc, omega, kappa, alpha, fx, fy, angles_veh, angles_ini, pb, steer, acc_angles = read_file_dtm_angles(file_adam_t0005_steer)

# # plt.figure(num='posx over time')
# # plt.plot(pos[:, 0], pos[:, 1],
# #         color=TUM_grey_dark, marker='', linestyle='-.', markersize=1.5)

# plot_pos(pos, TUM_grey_dark, False)
# plot_vx(vel, TUM_grey_dark, False)
# plot_ax(acc, TUM_grey_dark, False)

# pos, vel, acc, omega, kappa, alpha, fx, fy, angles_veh, angles_ini, pb, steer, acc_angles = read_file_dtm_angles(file_runge_t0005_steer)

# plot_pos(pos, TUM_orange, False)
# plot_vx(vel, TUM_orange, False)
# plot_ax(acc, TUM_orange, False)


# #add legends 
# plt.figure(num='Position')
# plt.legend(labels=['euler', 'adams', 'runge'])

# plt.figure(num='v_x over time')
# plt.legend(labels=['euler', 'adams', 'runge'])

# plt.figure(num='a_x over time')
# plt.legend(labels=['euler', 'adams', 'runge'])


###############
### BRAKING ###
###############

pos, vel, acc, omega, kappa, alpha, fx, fy, fxpt, pb, steer = read_file_dtm(latest_file)

plot_pos(pos, TUM_blue, False)
plot_vx(vel, TUM_blue, False)
plot_ax(acc, TUM_blue, False)
plot_tireforce_fx(fx, False)
plot_tireforce_fxpt(fxpt, False)
plot_wheelspeed(omega, False)
plot_slip(kappa, False)

#show figures 
plt.draw()
plt.show()
