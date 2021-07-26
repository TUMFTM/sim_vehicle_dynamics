
import os
import glob
import numpy as np
import matplotlib.font_manager
import matplotlib.pyplot as plt
import math

import array


# Colors
TUM_grey =              '#CCCCCC'       #mat stm euler
TUM_grey_dark =         '#333333'       #mat dtm euler 
TUM_orange =            '#E37222'       #c stm  euler
TUM_blue_dark =         '#003359'       #c stm  adams
TUM_blue_light =        '#98C6EA'       #c stm  heuns

violett =               '#6600CC'       #c dtm  euler 
TUM_green =             '#A2AD00'       #rel data    



# set activating plots 
stm_c_euler =   False
stm_c_heuns =   False
stm_c_adams =   False

stm_mat =       False 

real_data =     True

# Postion
pos_show =      True
posx_show =     True
posy_show =     True

# Velocity
vx_show =       True
vy_show =       True

# Acceleration
ax_show =       True
ay_show =       True

#Psi
psi_show =      True
dpsi_show =     True


diff_pos =      True


# choose szenario 
# test1         = 0           straight
# test2         = 1           turn 1            
# test3         = 2           turn 2 and 3 

szenario = 1

if szenario == 0:
        test_offset = 598               # duration 10 s 
        test_xoffset = 32.8198
        test_yoffset = -70.3332
        test_psioffset = 0.9765

if szenario == 1:
        test_offset = 784               # duration 06 s 
        test_xoffset = -529.6469
        test_yoffset = 314.5790
        test_psioffset = 0.2377

if szenario == 2:
        test_offset = 792               # duration 12 s 
        test_xoffset = -376.700100
        test_yoffset = 287.085000
        test_psioffset = -2.2243

def read_real_data(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        # 'time_s', 'xPos_m', 'yPos_m', 'psi_rad', 'dPsi_radps', ...
        # 'vx_mps', 'vy_mps'  'ax_mps2' 'ay_mps2', ...
        # 'lambdaFL_perc', 'lambdaFR_perc', 'lambdaRL_perc', 'lambdaRR_perc', ...
        # 'alphaFL_rad', 'alphaFR_rad', 'alphaRL_rad', 'alphaRR_rad', ...
        # 'T_WheelFL_Nm', 'T_WheelFR_Nm', 'T_WheelRL_Nm', 'T_WheelRR_Nm', ...
        # 'omega_WheelFL_radps', 'omega_WheelFR_radps', 'omega_WheelRL_radps', 'omega_WheelRR_radps',...
        # 'p_BrakeF_bar', 'p_BrakeR_bar', 'Delta_Wheel_rad'
        pos     = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 1, 2, 3))
        vel     = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 5, 6, 4))
        acc     = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 7, 8))
        kappa   = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 9, 10, 11, 12))
        alpha   = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 13, 14, 15, 16))
        torque  = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 17, 18, 19, 20))
        omega   = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 21, 22, 23, 24))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 25, 26))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_header=1, usecols=(0, 27))

        return pos, vel, acc, kappa, alpha, torque, omega, steer, pb


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
        # "tireDriveTirque_FL_N, tireDriveTirque_FR_N, tireDriveTirque_RL_N, tireDriveTirque_RR_N, " 
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
        torque  = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 29, 30, 31, 32))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 33, 34, 35, 36))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_header=7, usecols=(0, 37))
        return pos, vel, acc, omega, kappa, alpha, fx, fy, torque, pb, steer


def read_file_matlab(filename):
        ###################
        ### FORMAT .csv ###
        ###################
        # 'time_s', 'xPos_m', 'yPos_m', 'psi_rad', 'dPsi_radps',
        # 'vx_mps', 'vy_mps'  'ax_mps2' 'ay_mps2', 
        # 'T_WheelFL_Nm', 'T_WheelFR_Nm', 'T_WheelRL_Nm', 'T_WheelRR_Nm', 
        # 'omega_WheelFL_radps', 'omega_WheelFR_radps', 'omega_WheelRL_radps', 'omega_WheelRR_radps',
        # 'p_BrakeFL_bar', 'p_BrakeFR_bar', 'p_BrakeRL_bar', , 'p_BrakeRR_bar'  
        # 'Delta_Wheel_rad'
        
        pos     = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 1, 2, 3))
        vel     = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 5, 6, 4))
        acc     = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 7, 8))
        torque  = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 9, 10, 11, 12))
        omega   = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 13, 14, 15, 16))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 17, 18, 19, 20))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_footer=0,usecols=(0, 21))

        return pos, vel, acc, torque, omega, pb, steer


###########################################################################################################
################################################ DATA FLES ################################################
###########################################################################################################

####################################
########## REAL TEST DATA ##########
####################################

test1 =                 "monte_day4_run5_straight.csv"
test2 =                 "monte_day4_run5_turn1.csv"
test3 =                 "monte_day4_run5_turn2-3.csv"

#########################################################################
############################### SIM files ###############################
#########################################################################


######################################
########## SingleTrackModel ##########
######################################

### EULER ###
stm_euler_test1 =       "../log/2021.02.01-10:34:17_comp_STM_real.csv"
stm_euler_test2 =       "../log/2021.02.01-10:36:21_comp_STM_real.csv"
stm_euler_test3 =       "../log/2021.02.01-09:00:47_comp_STM_real.csv"


### HEUNS ###
stm_heuns_test1 =       "../log/2021.02.01-10:34:50_comp_STM_real.csv"
stm_heuns_test2 =       "../log/2021.02.01-10:36:45_comp_STM_real.csv"
stm_heuns_test3 =       "../log/2021.02.01-09:01:53_comp_STM_real.csv"


### ADAMS ###
stm_adams_test1 =       "../log/2021.02.01-10:35:13_comp_STM_real.csv"
stm_adams_test2 =       "../log/2021.02.01-10:37:05_comp_STM_real.csv"
stm_adams_test3 =       "../log/2021.02.01-09:01:29_comp_STM_real.csv"


############################################################################
############################### MATLAB files ###############################
############################################################################

######################################
########## SingleTrackModel ##########
######################################
### EULER ###
mat_euler_test1 =       "../log/log_matlab/2021.01.31-mat_exp_STM_euler_monte_day4_run5_straight.csv"
mat_euler_test2 =       "../log/log_matlab/2021.01.31-mat_exp_STM_euler_monte_day4_run5_turn1.csv"
mat_euler_test3 =       "../log/log_matlab/2021.01.31-mat_exp_STM_euler_monte_day4_run5_turn2-3.csv"


list_data_files = [[stm_euler_test1, stm_euler_test2, stm_euler_test3],
                   [stm_adams_test1, stm_adams_test2, stm_adams_test3],
                   [stm_heuns_test1, stm_heuns_test2, stm_heuns_test3],
                   [mat_euler_test1, mat_euler_test2, mat_euler_test3],
                   [test1,           test2,           test3]]


############################################################################################################
################################################# PLOTTING #################################################
############################################################################################################

##########################################################
################ SingleTrackModel C EULER ################
##########################################################

if stm_c_euler:
    pos_stm_c_euler, vel_stm_c_euler, acc_stm_c_euler, omega_stm_c_euler, kappa_sim_stm, alpha_sim_stm, fx_sim_stm, fy_sim_stm, fxpt_sim_stm, brakepressure_sim_stm, steer_sim_stm = read_file_stm(list_data_files[0][szenario])

    rotangle = -np.pi*0.5

    pos_stm_c_euler_turned = np.zeros((pos_stm_c_euler.shape[0], 3))
    pos_stm_c_euler[:, 1] = pos_stm_c_euler[:, 1] - test_xoffset 
    pos_stm_c_euler[:, 2] = pos_stm_c_euler[:, 2] - test_yoffset 

    for i in range(0, pos_stm_c_euler.shape[0]):
        pos_stm_c_euler_turned[i, 0] = pos_stm_c_euler[i, 0]
        pos_stm_c_euler_turned[i, 1] = pos_stm_c_euler[i, 1]*np.cos(rotangle) + pos_stm_c_euler[i, 2]*np.sin(rotangle)
        pos_stm_c_euler_turned[i, 2] = -pos_stm_c_euler[i, 1]*np.sin(rotangle) + pos_stm_c_euler[i, 2]*np.cos(rotangle) 


    if pos_show:
        plt.figure(num='Position', figsize=(5.6,3.5))
        plt.plot(pos_stm_c_euler_turned[:, 1] + test_xoffset, pos_stm_c_euler_turned[:, 2] + test_yoffset,
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        
        plt.grid(b=True, axis='both')
        plt.xlabel("x Position in m", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("y Position in m", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_euler_turned[:, 0], pos_stm_c_euler_turned[:, 1] + test_xoffset,
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_euler_turned[:, 0], pos_stm_c_euler_turned[:, 2] + test_yoffset,
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_euler[:, 0], pos_stm_c_euler[:, 3],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 3],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        plt.legend()

#     plt.figure(num='steeringangle')
#     plt.plot(steer_sim_stm[:, 0], steer_sim_stm[:, 1],
#             color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="steeringangle stm c euler ")
#     plt.legend()

    # plt.figure(num='torque per wheel')
    # plt.plot(fxpt_sim_stm[:, 0], fxpt_sim_stm[:, 1],
    #         color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="fxpt stm c euler ")
    # plt.legend()

    plt.figure(num='omega')
    plt.plot(omega_stm_c_euler[:, 0], omega_stm_c_euler[:, 1],
            color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="omega fl stm c euler ")
    plt.legend()



##########################################################
################ SingleTrackModel C ADAMS ################
##########################################################

if stm_c_adams:
    pos_stm_c_adams, vel_stm_c_adams, acc_stm_c_adams, omega_stm_c_adams, kappa_sim_stm, alpha_sim_stm, fx_sim_stm, fy_sim_stm, fxpt_sim_stm, brakepressure_sim_stm, steer_sim_stm = read_file_stm(list_data_files[1][szenario])


    rotangle = -np.pi*0.5

    pos_stm_c_adams_turned = np.zeros((pos_stm_c_adams.shape[0], 3))
    pos_stm_c_adams[:, 1] = pos_stm_c_adams[:, 1] - test_xoffset 
    pos_stm_c_adams[:, 2] = pos_stm_c_adams[:, 2] - test_yoffset 

    for i in range(0, pos_stm_c_adams.shape[0]):
        pos_stm_c_adams_turned[i, 0] = pos_stm_c_adams[i, 0]
        pos_stm_c_adams_turned[i, 1] = pos_stm_c_adams[i, 1]*np.cos(rotangle) + pos_stm_c_adams[i, 2]*np.sin(rotangle)
        pos_stm_c_adams_turned[i, 2] = -pos_stm_c_adams[i, 1]*np.sin(rotangle) + pos_stm_c_adams[i, 2]*np.cos(rotangle) 


    if pos_show:
        plt.figure(num='Position')
        plt.plot(pos_stm_c_adams_turned[:, 1] + test_xoffset, pos_stm_c_adams_turned[:, 2] + test_yoffset,
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_adams_turned[:, 0], pos_stm_c_adams_turned[:, 1] + test_xoffset,
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_adams_turned[:, 0], pos_stm_c_adams_turned[:, 2] + test_yoffset,
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_adams[:, 0], pos_stm_c_adams[:, 3],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 3],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        plt.legend()

    plt.figure(num='omega')
    plt.plot(omega_stm_c_adams[:, 0], omega_stm_c_adams[:, 1],
            color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="omega fl stm c adams ")
    plt.legend()


##########################################################
################ SingleTrackModel C HEUNS ################
##########################################################

if stm_c_heuns:
    pos_stm_c_heuns, vel_stm_c_heuns, acc_stm_c_heuns, omega_stm_c_heuns, kappa_sim_stm, alpha_sim_stm, fx_sim_stm, fy_sim_stm, fxpt_sim_stm, brakepressure_sim_stm, steer_sim_stm = read_file_stm(list_data_files[2][szenario])

    rotangle = -np.pi*0.5

    pos_stm_c_heuns_turned = np.zeros((pos_stm_c_heuns.shape[0], 3))
    pos_stm_c_heuns[:, 1] = pos_stm_c_heuns[:, 1] - test_xoffset 
    pos_stm_c_heuns[:, 2] = pos_stm_c_heuns[:, 2] - test_yoffset 

    for i in range(0, pos_stm_c_heuns.shape[0]):
        pos_stm_c_heuns_turned[i, 0] = pos_stm_c_heuns[i, 0]
        pos_stm_c_heuns_turned[i, 1] = pos_stm_c_heuns[i, 1]*np.cos(rotangle) + pos_stm_c_heuns[i, 2]*np.sin(rotangle)
        pos_stm_c_heuns_turned[i, 2] = -pos_stm_c_heuns[i, 1]*np.sin(rotangle) + pos_stm_c_heuns[i, 2]*np.cos(rotangle) 



    if pos_show:
        plt.figure(num='Position')
        plt.axis('equal')
        plt.plot(pos_stm_c_heuns_turned[:, 1] + test_xoffset, pos_stm_c_heuns_turned[:, 2] + test_yoffset,
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_heuns_turned[:, 0], pos_stm_c_heuns_turned[:, 1] + test_xoffset,
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_heuns_turned[:, 0], pos_stm_c_heuns_turned[:, 2] + test_yoffset,
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_heuns[:, 0], pos_stm_c_heuns[:, 3],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 3],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm c heun")
        plt.legend()

    plt.figure(num='omega')
    plt.plot(omega_stm_c_heuns[:, 0], omega_stm_c_heuns[:, 1],
            color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="omega fl stm c heun ")
    plt.legend()


######################################################################################################################
###################################################### PLOT MATLAB ###################################################
######################################################################################################################

#########################################################
################ SingleTrackModel MATLAB ################
#########################################################

if stm_mat:
    pos_mat_euler, vel_mat_euler, acc_mat_euler, torque, omega_mat_euler, brakepressure, steer = read_file_matlab(list_data_files[3][szenario])
    
    rotangle = -test_psioffset # 0.0 #np.pi #

    pos_mat_euler_turned = np.zeros((pos_mat_euler.shape[0], 3))


    for i in range(0, pos_mat_euler.shape[0]):
        pos_mat_euler_turned[i, 0] = pos_mat_euler[i, 0]
        pos_mat_euler_turned[i, 1] = pos_mat_euler[i, 1]*np.cos(rotangle) + pos_mat_euler[i, 2]*np.sin(rotangle)
        pos_mat_euler_turned[i, 2] = -pos_mat_euler[i, 1]*np.sin(rotangle) + pos_mat_euler[i, 2]*np.cos(rotangle) 


    plt.figure(num='Position', figsize=(5.6,3.5))
    plt.plot(pos_mat_euler_turned[:, 1] + test_xoffset, pos_mat_euler_turned[:, 2] + test_yoffset,
            color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
    plt.legend(loc='upper left')

    plt.grid(b=True, axis='both')
    plt.xlabel("x Position in m", fontname='arial', fontsize=11)
    plt.xticks(fontname='arial', fontsize=11)        
    plt.ylabel("y Position in m", fontname='arial', fontsize=11)
    plt.yticks(fontname='arial', fontsize=11)
    plt.tight_layout()
    plt.legend()


    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_mat_euler_turned[:, 0], pos_mat_euler_turned[:, 1] + test_xoffset,
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_mat_euler_turned[:, 0], pos_mat_euler_turned[:, 2] + test_yoffset,
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()


    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_mat_euler[:, 0], pos_mat_euler[:, 3] + test_psioffset,
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 3],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="stm mat")
        plt.legend()


    plt.figure(num='omega')
    plt.plot(omega_mat_euler[:, 0], omega_mat_euler[:, 1],
            color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="omega fl stm mat ")


    plt.grid(b=True, axis='both')
    plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
    plt.xticks(fontname='arial', fontsize=11)
    
    plt.ylabel("Umfangsgeschwindigkeit in rad/s", fontname='arial', fontsize=11)
    plt.yticks(fontname='arial', fontsize=11)
    plt.tight_layout()
    plt.legend()


################################################
################ REAL TEST DATA ################
################################################


if real_data:

        pos_real, vel_real, acc_real, kappa_real, alpha_real, torque_real, omega_real, steer_real, pb_real = read_real_data(list_data_files[4][szenario])

        if pos_show:
                plt.figure(num='Position')
                plt.plot(pos_real[:, 1], pos_real[:, 2],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if posx_show:
                plt.figure(num='Pos X')
                plt.plot(pos_real[:, 0] - test_offset, pos_real[:, 1],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if posy_show:
                plt.figure(num='Pos Y')
                plt.plot(pos_real[:, 0] - test_offset, pos_real[:, 2],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()


        if vx_show:
                plt.figure(num='vx')
                plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 1],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if vy_show:
                plt.figure(num='vy')
                plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 2],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if ax_show:
                plt.figure(num='ax')
                plt.plot(acc_real[:, 0] - test_offset, acc_real[:, 1],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if ay_show:
                plt.figure(num='ay')
                plt.plot(acc_real[:, 0] - test_offset, acc_real[:, 2],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if psi_show:
                plt.figure(num='psi')
                plt.plot(pos_real[:, 0] - test_offset, pos_real[:, 3],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        if dpsi_show:
                plt.figure(num='dpsi')
                plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 3],
                        color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real data")
                plt.legend()

        plt.figure(num='omega')
        plt.plot(omega_real[:, 0] - test_offset, omega_real[:, 1],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="omega fl real data ")
        plt.legend()


if diff_pos:
        #create plot with differences 
        #sqrt((x2-x1)^2 + (y2-y1)^2)

        #pos_stm_c_euler_turned
        #pos_mat_euler_turned
        #pos_stm_c_heuns_turned
        #pos_stm_s_adams_turned
        
        print("Shape pos mat euler turned")
        print(pos_mat_euler_turned.shape)
        print("Shape pos stm c euler ")
        print(pos_stm_c_euler.shape)

        diff_real_mat_euler = np.zeros((pos_mat_euler_turned.shape[0], 1))
        diff_real_ceuler = np.zeros((pos_stm_c_euler.shape[0], 1))
        diff_real_cheuns = np.zeros((pos_stm_c_heuns.shape[0], 1))
        diff_real_cadams = np.zeros((pos_stm_c_adams.shape[0], 1))
        
        # TODO change to pos_real !!! 
        # # diff for t = 0.004 
        diff_real_mat_euler = np.sqrt(np.square(pos_mat_euler_turned[:, 1] + test_xoffset - pos_real[:, 1]) + np.square(pos_mat_euler_turned[:, 2] + test_yoffset - pos_real[:, 2]))
        diff_real_ceuler = np.sqrt(np.square(pos_stm_c_euler_turned[:, 1] + test_xoffset - pos_real[:-1, 1]) + np.square(pos_stm_c_euler_turned[:, 2] + test_yoffset - pos_real[:-1, 2]))
        diff_real_cheuns = np.sqrt(np.square(pos_stm_c_heuns_turned[:, 1] + test_xoffset - pos_real[:-1, 1]) + np.square(pos_stm_c_heuns_turned[:, 2] + test_yoffset - pos_real[:-1, 2]))
        diff_real_cadams = np.sqrt(np.square(pos_stm_c_adams_turned[:, 1] + test_xoffset - pos_real[:-1, 1]) + np.square(pos_stm_c_adams_turned[:, 2] + test_yoffset - pos_real[:-1, 2]))

        ### RMSE 

        rmse_mat_euler = np.sqrt((diff_real_mat_euler ** 2).mean())
        rmse_stm_ceuler = np.sqrt((diff_real_ceuler ** 2).mean())
        rmse_stm_cheuns = np.sqrt((diff_real_cheuns ** 2).mean())
        rmse_stm_cadams = np.sqrt((diff_real_cadams ** 2).mean())

        print("RMSE mat: " + str(rmse_mat_euler))
        print("RMSE c euler: " + str(rmse_stm_ceuler))
        print("RMSE c heuns: " + str(rmse_stm_cheuns))
        print("RMSE c admas: " + str(rmse_stm_cadams))

        ################
        ### DIFF POS ###
        ################

        plt.figure(num='diff Pos',figsize=(5.6,3.5))
        plt.plot(pos_mat_euler_turned[:, 0], diff_real_mat_euler[:],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="diff real mat stm")

        plt.plot(pos_stm_c_euler[:, 0], diff_real_ceuler[:],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="diff real c-euler stm")

        plt.plot(pos_stm_c_euler[:, 0], diff_real_cheuns[:],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="diff real c-heuns stm")

        plt.plot(pos_stm_c_euler[:, 0], diff_real_cadams[:],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="diff real c-adams stm")

        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        plt.ylabel("Abstand in m", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        ##########
        ### AX ###
        ##########
        plt.figure(num='ax grid', figsize=(5.6, 3.5))
        
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.plot(acc_real[:, 0] - test_offset, acc_real[:, 1],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend(loc='upper right')


        ##########
        ### AY ###
        ##########
        plt.figure(num='ay grid', figsize=(5.6, 3.5))
        
        plt.plot(acc_real[:, 0] - test_offset, acc_real[:, 2],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Querbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        ##########
        ### VY ###
        ##########
        plt.figure(num='vy grid', figsize=(5.6, 3.5))
        
        plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 2],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Quergeschwindigkeit in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        ############
        ### dPSI ###
        ############
        plt.figure(num='dpsi grid', figsize=(5.6, 3.5))
        
        plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 3],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 3],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 3],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 3],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 3],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Gierschwindigkeit in rad/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        ##########
        ### VX ###
        ##########
        plt.figure(num='vx grid', figsize=(5.6, 3.5))
        
        plt.plot(vel_real[:, 0] - test_offset, vel_real[:, 1],
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Längsgeschwindigkeit in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        ###########
        ### PSI ###
        ###########
        plt.figure(num='psi grid', figsize=(5.6, 3.5))
        
        plt.plot(pos_real[:, 0] - test_offset, pos_real[:, 3] * (180.0/np.pi),
                color=TUM_green, marker='', linestyle='-', markersize=0.5, label="real")
        plt.plot(pos_mat_euler[:, 0], (pos_mat_euler[:, 3] + test_psioffset) * (180.0/np.pi),
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(pos_stm_c_euler[:, 0], pos_stm_c_euler[:, 3] * (180.0/np.pi),
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(pos_stm_c_heuns[:, 0], pos_stm_c_heuns[:, 3] * (180.0/np.pi),
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(pos_stm_c_adams[:, 0], pos_stm_c_adams[:, 3] * (180.0/np.pi),
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Gierwinkel in °", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


plt.draw()
plt.show()

