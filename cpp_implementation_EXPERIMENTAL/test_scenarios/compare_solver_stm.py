
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


TUM_blue = '#3070b3'
TUM_blue_medium = '#64A0C8'


# set activating plots 
stm_c_euler =   True
stm_c_adams =   True
stm_c_heuns =   True

stm_mat =       True 

dtm_c_euler =   True

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

# Distance Position
diff_pos =      True

### choose szenario ###
# stm_euler_acc60s          = 0         5 seconds standstill then accelerate with 12.5 Nm/sec             
# stm_euler_250Nmps         = 1         5 seconds standstill then accelerate with 250 Nm/sec 
# stm_euler_braking100      = 2         start with 100 km/h and brake with 15 bar/ wheel after 0.008 s 
# stm_euler_rolling100      = 3         start with 100 km/h and then free rooling for 65 sec 
# stm_euler_steer_acc_fast  = 4         
# stm_euler_steer_acc       = 5       
# stm_euler_steer_ramp      = 6      
# stm_euler_steer_sinus     = 7     

szenario = 1


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


#########################################################################
############################### SIM files ###############################
#########################################################################

######################################
########## SingleTrackModel ##########
######################################

### TIME STEP = 0.004 s ###

### EULER ###
stm_euler_acc60s =            "../log/2021.01.19-09:23:53_comp_STM_real.csv"
stm_euler_250Nmps =           "../log/2021.01.19-09:24:35_comp_STM_real.csv"
stm_euler_braking100 =        "../log/2021.01.19-09:24:59_comp_STM_real.csv"
stm_euler_rolling100 =        "../log/2021.01.19-09:25:27_comp_STM_real.csv"
stm_euler_steer_acc_fast =    "../log/2021.01.19-09:26:18_comp_STM_real.csv"
stm_euler_steer_acc =         "../log/2021.01.19-09:27:14_comp_STM_real.csv" 
stm_euler_steer_ramp =        "../log/2021.01.19-09:27:42_comp_STM_real.csv"
stm_euler_steer_sinus =       "../log/2021.01.19-09:28:13_comp_STM_real.csv"

### TIMESTEP 0.002 s ###
stm_euler_acc60s_2 =          "../log/csv"
stm_euler_250Nmps_2 =         "../log/.csv"
stm_euler_braking100_2 =      "../log/.csv"
stm_euler_rolling100_2 =      "../log/2021.01.30-16:16:15_comp_STM_real.csv"
stm_euler_steer_acc_fast_2 =  "../log/.csv"
stm_euler_steer_acc_2 =         "../log/2021.02.01-08:48:03_comp_STM_real.csv"
stm_euler_steer_ramp_2 =      "../log/2021.01.20-14:48:11_comp_STM_real.csv" 
stm_euler_steer_sinus_2 =     "../log/2021.02.01-21:54:51_comp_STM_real.csv"


### ADAMS ###
stm_adams_acc60s =            "../log/2021.01.20-14:08:59_comp_STM_real.csv"
stm_adams_250Nmps =           "../log/2021.01.20-09:49:04_comp_STM_real.csv"
stm_adams_braking100 =        "../log/2021.01.30-10:11:24_comp_STM_real.csv" 
stm_adams_rolling100 =        "../log/2021.01.30-16:28:44_comp_STM_real.csv"
stm_adams_steer_acc_fast =    "../log/2021.01.20-14:12:10_comp_STM_real.csv"
stm_adams_steer_acc =         "../log/2021.01.20-14:13:29_comp_STM_real.csv"
stm_adams_steer_ramp =        "../log/2021.01.20-14:14:02_comp_STM_real.csv" 
stm_adams_steer_sinus =       "../log/2021.01.20-14:16:00_comp_STM_real.csv"


### TIMESTEP 0.002 s ###
stm_adams_acc60s_2 =          "../log/csv"
stm_adams_250Nmps_2 =         "../log/.csv"
stm_adams_braking100_2 =      "../log/.csv"
stm_adams_rolling100_2 =      "../log/2021.01.30-16:21:43_comp_STM_real.csv"
stm_adams_steer_acc_fast_2 =  "../log/.csv"
stm_adams_steer_acc_2 =       "../log/2021.02.01-21:08:00_comp_STM_real.csv"
stm_adams_steer_ramp_2 =      "../log/2021.02.01-21:25:44_comp_STM_real.csv"
stm_adams_steer_sinus_2 =     "../log/2021.02.01-21:55:53_comp_STM_real.csv"



# ### HEUN ###
stm_heuns_acc60s =            "../log/2021.01.20-14:08:24_comp_STM_real.csv"
stm_heuns_250Nmps =           "../log/2021.01.20-13:38:17_comp_STM_real.csv"
stm_heuns_braking100 =        "../log/2021.01.29-19:08:57_comp_STM_real.csv"
stm_heuns_rolling100 =        "../log/2021.01.30-16:51:44_comp_STM_real.csv"
stm_heuns_steer_acc_fast =    "../log/2021.01.20-14:12:31_comp_STM_real.csv"
stm_heuns_steer_acc =         "../log/2021.01.20-14:12:59_comp_STM_real.csv"
stm_heuns_steer_ramp =        "../log/2021.01.20-14:15:01_comp_STM_real.csv"
stm_heuns_steer_sinus =       "../log/2021.01.20-14:15:35_comp_STM_real.csv"


### TIMESTEP 0.002 s ###
stm_heuns_acc60s_2 =          "../log/.csv"
stm_heuns_250Nmps_2 =         "../log/.csv"
stm_heuns_braking100_2 =      "../log/.csv"
stm_heuns_rolling100_2 =      "../log/2021.01.30-19:33:32_comp_STM_real.csv"
stm_heuns_steer_acc_fast_2 =  "../log/.csv"
stm_heuns_steer_acc_2 =       "../log/2021.02.01-21:08:48_comp_STM_real.csv"
stm_heuns_steer_ramp_2 =      "../log/2021.01.20-14:46:54_comp_STM_real.csv" 
stm_heuns_steer_sinus_2 =     "../log/2021.02.01-22:02:30_comp_STM_real.csv"


####################################
########## DualTrackModel ##########
####################################

### TIMESTEP 0.004 s ###
### EULER ###
dtm_euler_acc60s =            "../log/.csv"
dtm_euler_250Nmps =           "../log/2021.01.29-16:33:56_comp_DTM_real.csv"
dtm_euler_braking100 =        "../log/2021.01.29-18:47:05_comp_DTM_real.csv"
dtm_euler_rolling100 =        "../log/2021.01.30-16:31:54_comp_DTM_real.csv"
dtm_euler_steer_acc_fast =    "../log/2021.01.31-10:49:36_comp_DTM_real.csv"
dtm_euler_steer_acc =         "../log/2021.01.31-10:52:37_comp_DTM_real.csv"
dtm_euler_steer_ramp =        "../log/.csv"
dtm_euler_steer_sinus =       "../log/.csv"

### TIMESTEP 0.002 s ###
dtm_euler_rolling100_2 =      "../log/2021.01.30-19:48:30_comp_DTM_real.csv"
dtm_euler_steer_acc_2 =       "../log/2021.01.31-11:06:23_comp_DTM_real.csv"


### DTM ###
dtm_euler_steer_ramp_2 =      "../log/2021.01.24-18:22:26_comp_DTM_real.csv" 


############################################################################
############################### MATLAB files ###############################
############################################################################


######################################
########## SingleTrackModel ##########
######################################

### TIME STEP = 0.004 s ###
# ode 1 for check_nstm.slx and ode4 for stm model V2 
mat_stm_acc60s =            "../log/log_matlab/2021.01.18-mat_exp_STM_runge_acc60s.csv"
mat_stm_250Nmps =           "../log/log_matlab/2021.01.18-mat_exp_STM_runge_acc_250Nmps.csv"
mat_stm_braking100 =        "../log/log_matlab/2021.01.18-mat_exp_STM_runge_braking_100.csv"
mat_stm_rolling100 =        "../log/log_matlab/2021.01.18-mat_exp_STM_runge_rolling_100.csv"
mat_stm_steer_acc_fast =    "../log/log_matlab/2021.01.18-mat_exp_STM_runge_steer_acc_fast.csv"
mat_stm_steer_acc =         "../log/log_matlab/2021.01.18-mat_exp_STM_runge_steer_acc.csv"
mat_stm_steer_ramp =        "../log/log_matlab/2021.01.18-mat_exp_STM_runge_steer_ramp.csv"
mat_stm_steer_sinus =       "../log/log_matlab/2021.01.18-mat_exp_STM_runge_steer_sinus.csv"


### TIME STEP = 0.004 s ###
# ode 2 for check_nstm.slx and ode4 for stm model V2 
# mat_stm_acc60s =            "../log/log_matlab/2021.01.19-mat_exp_STM_heun_acc_60s.csv"
# mat_stm_250Nmps =           "../log/log_matlab/2021.01.19-mat_exp_STM_heun_acc_250Nmps.csv"
# mat_stm_braking100 =        "../log/log_matlab/.csv"
# mat_stm_rolling100 =        "../log/log_matlab/.csv"
# mat_stm_steer_acc_fast =    "../log/log_matlab/.csv"
# mat_stm_steer_acc =         "../log/log_matlab/.csv"
# mat_stm_steer_ramp =        "../log/log_matlab/.csv"
# mat_stm_steer_sinus =       "../log/log_matlab/.csv"


### TIME STEP = 0.002 s ###
# ode1

# mat_stm_rolling100_2 =      "../log/log_matlab/PA_2021.01.30-mat_exp_STM_euler_rolling_100_t002.csv"    # used wrong parameters for Passenger Vehicle!! 
# mat_stm_steer_acc_2 =       "../log/log_matlab/PA_2021.01.31-mat_exp_STM_euler_steer_acc_t002.csv"      # used wrong parameters for Passenger Vehicle!! 
mat_stm_rolling100_2 =      "../log/log_matlab/2021.01.31-mat_exp_STM_euler_rolling_100_t002.csv"
mat_stm_steer_acc_2 =       "../log/log_matlab/2021.01.31-mat_exp_STM_euler_steer_acc_t002.csv"
mat_stm_steer_ramp_2 =      "../log/log_matlab/2021.01.31-mat_exp_STM_euler_steer_ramp_t002.csv"
mat_stm_steer_sinus_2 =     "../log/log_matlab/2021.01.31-mat_exp_STM_euler_steer_sinus_t002.csv"


#################
### FILE LIST ###
#################

list_data_files = [[stm_euler_acc60s, stm_euler_250Nmps, stm_euler_braking100, stm_euler_rolling100, stm_euler_steer_acc_fast, stm_euler_steer_acc_2, stm_euler_steer_ramp_2, stm_euler_steer_sinus_2],
                   [stm_adams_acc60s, stm_adams_250Nmps, stm_adams_braking100, stm_adams_rolling100, stm_adams_steer_acc_fast, stm_adams_steer_acc_2, stm_adams_steer_ramp_2, stm_adams_steer_sinus_2],
                   [stm_heuns_acc60s, stm_heuns_250Nmps, stm_heuns_braking100, stm_heuns_rolling100, stm_heuns_steer_acc_fast, stm_heuns_steer_acc_2, stm_heuns_steer_ramp_2, stm_heuns_steer_sinus_2],
                   [mat_stm_acc60s,   mat_stm_250Nmps,   mat_stm_braking100,   mat_stm_rolling100,   mat_stm_steer_acc_fast,   mat_stm_steer_acc_2,   mat_stm_steer_ramp_2,   mat_stm_steer_sinus_2],
                   [dtm_euler_acc60s, dtm_euler_250Nmps, dtm_euler_braking100, dtm_euler_rolling100, dtm_euler_steer_acc_fast, dtm_euler_steer_acc_2, dtm_euler_steer_ramp, dtm_euler_steer_sinus]]


############################################################################################################
################################################# PLOTTING #################################################
############################################################################################################

##########################################################
################ SingleTrackModel C EULER ################
##########################################################

if stm_c_euler:
    pos_stm_c_euler, vel_stm_c_euler, acc_stm_c_euler, omega_stm_c_euler, kappa_sim_stm, alpha_sim_stm, fx_sim_stm, fy_sim_stm, fxpt_sim_stm, brakepressure_sim_stm, steer_sim_stm = read_file_stm(list_data_files[0][szenario])

    if pos_show:
        plt.figure(num='Position', figsize=(5.6,3.5))
        plt.plot(pos_stm_c_euler[:, 1], pos_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="stm c euler")
        
        plt.grid(b=True, axis='both')
        plt.xlabel("x Position in m", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("y Position in m", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_euler[:, 0], pos_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="stm c euler")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_euler[:, 0], pos_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="stm c euler")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="stm c euler")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="stm c euler")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle=':', markersize=0.5, label="stm c euler")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle=':', markersize=0.5, label="stm c euler")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_euler[:, 0], pos_stm_c_euler[:, 3],
                color=TUM_orange, marker='', linestyle=':', markersize=0.5, label="stm c euler")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 3],
                color=TUM_orange, marker='', linestyle=':', markersize=0.5, label="stm c euler")
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

    if pos_show:
        plt.figure(num='Position')
        plt.plot(pos_stm_c_adams[:, 1], pos_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='--', markersize=0.5, label="stm c adams")
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_adams[:, 0], pos_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='--', markersize=0.5, label="stm c adams")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_adams[:, 0], pos_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='--', markersize=0.5, label="stm c adams")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='--', markersize=0.5, label="stm c adams")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='--', markersize=0.5, label="stm c adams")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle=':', markersize=0.5, label="stm c adams")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle=':', markersize=0.5, label="stm c adams")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_adams[:, 0], pos_stm_c_adams[:, 3],
                color=TUM_blue_dark, marker='', linestyle=':', markersize=0.5, label="stm c adams")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 3],
                color=TUM_blue_dark, marker='', linestyle=':', markersize=0.5, label="stm c adams")
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

    if pos_show:
        plt.figure(num='Position')
        plt.axis('equal')
        plt.plot(pos_stm_c_heuns[:, 1], pos_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='--', markersize=0.5, label="stm c heun")
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_stm_c_heuns[:, 0], pos_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='--', markersize=0.5, label="stm c heun")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_stm_c_heuns[:, 0], pos_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='--', markersize=0.5, label="stm c heun")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='--', markersize=0.5, label="stm c heun")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='--', markersize=0.5, label="stm c heun")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle=':', markersize=0.5, label="stm c heun")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle=':', markersize=0.5, label="stm c heun")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_stm_c_heuns[:, 0], pos_stm_c_heuns[:, 3],
                color=TUM_blue_light, marker='', linestyle=':', markersize=0.5, label="stm c heun")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 3],
                color=TUM_blue_light, marker='', linestyle=':', markersize=0.5, label="stm c heun")
        plt.legend()

    plt.figure(num='omega')
    plt.plot(omega_stm_c_heuns[:, 0], omega_stm_c_heuns[:, 1],
            color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="omega fl stm c heun ")
    plt.legend()


##########################################################
################ DualTrackModel C EULER ################
##########################################################

if dtm_c_euler:
    pos_dtm_c_euler, vel_dtm_c_euler, acc_dtm_c_euler, omega_dtm_c_euler, kappa_sim_dtm, alpha_sim_dtm, fx_sim_dtm, fy_sim_dtm, fxpt_sim_dtm, brakepressure_sim_dtm, steer_sim_dtm = read_file_stm(list_data_files[4][szenario])

    if pos_show:
        plt.figure(num='Position')
        plt.plot(pos_dtm_c_euler[:, 1], pos_dtm_c_euler[:, 2],
                color=violett, marker='', linestyle='--', markersize=0.5, label="dtm c euler")
        plt.legend()

    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_dtm_c_euler[:, 0], pos_dtm_c_euler[:, 1],
                color=violett, marker='', linestyle='--', markersize=0.5, label="dtm c euler")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_dtm_c_euler[:, 0], pos_dtm_c_euler[:, 2],
                color=violett, marker='', linestyle='--', markersize=0.5, label="dtm c euler")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_dtm_c_euler[:, 0], vel_dtm_c_euler[:, 1],
                color=violett, marker='', linestyle='--', markersize=0.5, label="dtm c euler")
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_dtm_c_euler[:, 0], vel_dtm_c_euler[:, 2],
                color=violett, marker='', linestyle='--', markersize=0.5, label="dtm c euler")
        plt.legend()

    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 1],
                color=violett, marker='', linestyle=':', markersize=0.5, label="dtm c euler")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 2],
                color=violett, marker='', linestyle=':', markersize=0.5, label="dtm c euler")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_dtm_c_euler[:, 0], pos_dtm_c_euler[:, 3],
                color=violett, marker='', linestyle=':', markersize=0.5, label="dtm c euler")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_dtm_c_euler[:, 0], vel_dtm_c_euler[:, 3],
                color=violett, marker='', linestyle=':', markersize=0.5, label="dtm c euler")
        plt.legend()

    plt.figure(num='omega')
    plt.plot(omega_dtm_c_euler[:, 0], omega_dtm_c_euler[:, 1],
            color=violett, marker='', linestyle='-', markersize=0.5, label="omega fl dtm c euler ")
    plt.legend()


######################################################################################################################
###################################################### PLOT MATLAB ###################################################
######################################################################################################################

#########################################################
################ SingleTrackModel MATLAB ################
#########################################################

if stm_mat:
    pos_mat_euler, vel_mat_euler, acc_mat_euler, torque, omega_mat_euler, brakepressure, steer = read_file_matlab(list_data_files[3][szenario])
    

#     pos_mat_euler = np.delete(pos_mat_euler, list(range(0, pos_mat_euler.shape[0], 2)), axis=0)
#     vel_mat_euler = np.delete(vel_mat_euler, list(range(0, vel_mat_euler.shape[0], 2)), axis=0)
#     acc_mat_euler = np.delete(acc_mat_euler, list(range(0, acc_mat_euler.shape[0], 2)), axis=0)

    rotangle = np.pi*0.5 

    pos_mat_euler_turned = np.zeros((pos_mat_euler.shape[0], 3))


    for i in range(0, pos_mat_euler.shape[0]):
        pos_mat_euler_turned[i, 0] = pos_mat_euler[i, 0]
        pos_mat_euler_turned[i, 1] = pos_mat_euler[i, 1]*np.cos(rotangle) + pos_mat_euler[i, 2]*np.sin(rotangle)
        pos_mat_euler_turned[i, 2] = -pos_mat_euler[i, 1]*np.sin(rotangle) + pos_mat_euler[i, 2]*np.cos(rotangle) 


    plt.figure(num='Position')
    plt.plot(pos_mat_euler_turned[:, 1], pos_mat_euler_turned[:, 2],
            color=TUM_grey, marker='', linestyle='-.', markersize=0.5, label="mat stm")
    plt.legend(loc='upper left')


    if posx_show:
        plt.figure(num='Pos X')
        plt.plot(pos_mat_euler_turned[:, 0], pos_mat_euler_turned[:, 1],
                color=TUM_grey, marker='', linestyle='--', markersize=0.5, label="stm mat")
        plt.legend()

    if posy_show:
        plt.figure(num='Pos Y')
        plt.plot(pos_mat_euler_turned[:, 0], pos_mat_euler_turned[:, 2],
                color=TUM_grey, marker='', linestyle='--', markersize=0.5, label="stm mat")
        plt.legend()


    if vx_show:
        plt.figure(num='vx')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='--', markersize=0.5, label="stm mat")
        
        plt.legend()

    if vy_show:
        plt.figure(num='vy')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='--', markersize=0.5, label="stm mat")
        plt.legend()


    if ax_show:
        plt.figure(num='ax')
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle=':', markersize=0.5, label="stm mat")
        plt.legend()

    if ay_show:
        plt.figure(num='ay')
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle=':', markersize=0.5, label="stm mat")
        plt.legend()

    if psi_show:
        plt.figure(num='psi')
        plt.plot(pos_mat_euler[:, 0], pos_mat_euler[:, 3],
                color=TUM_grey, marker='', linestyle=':', markersize=0.5, label="stm mat")
        plt.legend()

    if dpsi_show:
        plt.figure(num='dpsi')
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 3],
                color=TUM_grey, marker='', linestyle=':', markersize=0.5, label="stm mat")
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

    #try zoomed plot 
    sub_axes = plt.axes([.6, .6, .25, .25])
    # plot the zoomed portion
    sub_axes.plot(omega_mat_euler[975:1250, 0], omega_mat_euler[975:1250, 1], color=TUM_grey) 
    
    plt.legend()


if diff_pos:
        #create plot with differences 
        #sqrt((x2-x1)^2 + (y2-y1)^2)

        #pos_stm_c_euler
        #pos_mat_euler
        #pos_stm_c_heuns
        #pos_stm_s_adams
        
        print("Shape pos mat euler turned")
        print(pos_mat_euler_turned.shape)
        print("Shape pos stm c euler ")
        print(pos_stm_c_euler.shape)

        diff_mat_ceuler = np.zeros((pos_stm_c_euler.shape[0], 1))
        diff_mat_cheuns = np.zeros((pos_stm_c_heuns.shape[0], 1))
        diff_mat_cadams = np.zeros((pos_stm_c_adams.shape[0], 1))

        # # diff for t = 0.004 
        diff_mat_ceuler = np.sqrt(np.square(pos_stm_c_euler[:, 1] - pos_mat_euler_turned[:-1, 1]) + np.square(pos_stm_c_euler[:, 2] - pos_mat_euler_turned[:-1, 2]))
        diff_mat_cheuns = np.sqrt(np.square(pos_stm_c_heuns[:, 1] - pos_mat_euler_turned[:-1, 1]) + np.square(pos_stm_c_heuns[:, 2] - pos_mat_euler_turned[:-1, 2]))
        diff_mat_cadams = np.sqrt(np.square(pos_stm_c_adams[:, 1] - pos_mat_euler_turned[:-1, 1]) + np.square(pos_stm_c_adams[:, 2] - pos_mat_euler_turned[:-1, 2]))
        diff_mat_ceuler_dtm = np.sqrt(np.square(pos_dtm_c_euler[:, 1] - pos_mat_euler_turned[:-1, 1]) + np.square(pos_dtm_c_euler[:, 2] - pos_mat_euler_turned[:-1, 2]))

        # diff for t = 0.002 
        # diff_mat_ceuler = np.sqrt(np.square(pos_stm_c_euler[:, 1] - pos_mat_euler_turned[:, 1]) + np.square(pos_stm_c_euler[:, 2] - pos_mat_euler_turned[:, 2]))
        # diff_mat_cheuns = np.sqrt(np.square(pos_stm_c_heuns[:, 1] - pos_mat_euler_turned[:, 1]) + np.square(pos_stm_c_heuns[:, 2] - pos_mat_euler_turned[:, 2]))
        # diff_mat_cadams = np.sqrt(np.square(pos_stm_c_adams[:, 1] - pos_mat_euler_turned[:, 1]) + np.square(pos_stm_c_adams[:, 2] - pos_mat_euler_turned[:, 2]))
        # # diff_mat_ceuler_dtm = np.sqrt(np.square(pos_dtm_c_euler[:, 1] - pos_mat_euler_turned[:, 1]) + np.square(pos_dtm_c_euler[:, 2] - pos_mat_euler_turned[:, 2]))


        ################
        ### DIFF POS ###
        ################

        plt.figure(num='diff Pos',figsize=(5.6,3.5))
        plt.plot(pos_stm_c_euler[:, 0], diff_mat_ceuler[:],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="diff mat c-euler stm")

        # plt.plot(pos_stm_c_euler[:, 0], diff_mat_ceuler_dtm[:],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="diff mat c-euler dtm")

        plt.plot(pos_stm_c_euler[:, 0], diff_mat_cheuns[:],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="diff mat c-heuns stm")

        plt.plot(pos_stm_c_euler[:, 0], diff_mat_cadams[:],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="diff mat c-adams stm")

        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)

        plt.ylabel("Abstand in m", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        # #try zoomed plot [left, bottom, width, height]
        # sub_axes = plt.axes([.5, .45, .45, .4])
        # # plot the zoomed portion
        # sub_axes.plot(pos_stm_c_euler[15000:15250, 0], diff_mat_ceuler[15000:15250], color=TUM_orange) 
        # sub_axes.plot(pos_stm_c_euler[15000:15250, 0], diff_mat_cheuns[15000:15250], color=TUM_blue_light) 
        # sub_axes.plot(pos_stm_c_euler[15000:15250, 0], diff_mat_cadams[15000:15250], color=TUM_blue_dark) 
        
        # sub_axes.grid()


        # plt.figure(num='vx zoom', figsize=(5.6,3.5))
        
        # plt.plot(vel_mat_euler[11000:11250, 0], vel_mat_euler[11000:11250, 1],
        #         color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        # plt.plot(vel_stm_c_euler[11000:11250, 0], vel_stm_c_euler[11000:11250, 1],
        #         color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        # plt.plot(vel_stm_c_heuns[11000:11250, 0], vel_stm_c_heuns[11000:11250, 1],
        #         color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        # plt.plot(vel_stm_c_adams[11000:11250, 0], vel_stm_c_adams[11000:11250, 1],
        #         color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        # # plt.plot(vel_dtm_c_euler[11000:11250, 0], vel_dtm_c_euler[11000:11250, 1],
        # #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        # plt.grid(b=True, axis='both')
        # plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        # plt.xticks(fontname='arial', fontsize=11)        
        # plt.ylabel("Längsgeschwindigkeit in m/s", fontname='arial', fontsize=11)
        # plt.yticks(fontname='arial', fontsize=11)
        # plt.tight_layout()
        # plt.legend()

        
        # plt.grid(b=True, axis='both')
        # plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        # plt.xticks(fontname='arial', fontsize=11)        
        # plt.ylabel("Längsgeschwindigkeit in m/s", fontname='arial', fontsize=11)
        # plt.yticks(fontname='arial', fontsize=11)
        # plt.tight_layout()
        
        #try zoomed plot [left, bottom, width, height]
        # sub_axes = plt.axes([.5, .45, .45, .4])
        # # plot the zoomed portion
        # sub_axes.plot(vel_mat_euler[900:1000, 0], vel_mat_euler[900:1000, 1], color=TUM_grey) 
        # sub_axes.plot(vel_stm_c_euler[900:1000, 0], vel_stm_c_euler[900:1000, 1], color=TUM_orange) 
        # sub_axes.plot(vel_stm_c_heuns[900:1000, 0], vel_stm_c_heuns[900:1000, 1], color=TUM_blue_light) 
        # sub_axes.plot(vel_stm_c_adams[900:1000, 0], vel_stm_c_adams[900:1000, 1], color=TUM_blue_dark) 
        # sub_axes.plot(vel_dtm_c_euler[900:1000, 0], vel_dtm_c_euler[900:1000, 1], color=violett) 
        
        # sub_axes.grid()

 
        # plt.figure(num='ax 10s', figsize=(5.6,3.5))
        
        # plt.plot(acc_mat_euler[0:1250, 0], acc_mat_euler[0:1250, 1],
        #         color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        # plt.plot(acc_stm_c_euler[0:1250, 0], acc_stm_c_euler[0:1250, 1],
        #         color=TUM_orange, marker='', linestyle='--', markersize=0.5, label="c-euler stm")
        # plt.plot(acc_stm_c_heuns[0:1250, 0], acc_stm_c_heuns[0:1250, 1],
        #         color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        # plt.plot(acc_stm_c_adams[0:1250, 0], acc_stm_c_adams[0:1250, 1],
        #         color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        # plt.plot(acc_dtm_c_euler[0:1250, 0], acc_dtm_c_euler[0:1250, 1],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        # plt.legend()

        
        # plt.grid(b=True, axis='both')
        # plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        # plt.xticks(fontname='arial', fontsize=11)        
        # plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        # plt.yticks(fontname='arial', fontsize=11)
        # plt.tight_layout()


        # # single plot DTM AX
        # plt.figure(num='ax dtm', figsize=(5.6,3))
        # plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 1],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        # plt.legend()

        
        # plt.grid(b=True, axis='both')
        # plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        # plt.xticks(fontname='arial', fontsize=11)        
        # plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        # plt.yticks(fontname='arial', fontsize=11)
        # plt.tight_layout()


        ##########################
        ### AX Rolling einzeln ###
        ##########################
        plt.figure(num='ax grid', figsize=(5.6, 3.5))
        
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        # plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 1],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()


        plt.figure(num='ay grid', figsize=(5.6, 3.5))
        
        plt.plot(acc_mat_euler[:, 0], acc_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(acc_stm_c_euler[:, 0], acc_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        # plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 2],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Querbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()




        plt.figure(num='ax c-adams', figsize=(5.6, 3.5))
        
        plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        # plt.plot(acc_dtm_c_euler[:, 0], acc_dtm_c_euler[:, 1],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        plt.plot(acc_stm_c_adams[:, 0], acc_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
        plt.legend()

        # plt.figure(num='ax c-heuns', figsize=(5.6, 3.5))
        
        # plt.plot(acc_stm_c_heuns[:, 0], acc_stm_c_heuns[:, 1],
        #         color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns Stm")
        # plt.grid(b=True, axis='both')
        # plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        # plt.xticks(fontname='arial', fontsize=11)        
        # plt.ylabel("Längsbeschleunigung in m/s^2", fontname='arial', fontsize=11)
        # plt.yticks(fontname='arial', fontsize=11)
        # plt.tight_layout()
        # plt.legend()
    

        plt.figure(num='vx stm grid 2?', figsize=(5.6,3.5))
        
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 1],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 1],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 1],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 1],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        # plt.plot(vel_dtm_c_euler[:, 0], vel_dtm_c_euler[:, 1],
        #         color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        plt.legend()

        
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Längsgeschwindigkeit in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
 


        plt.figure(num='vy stm grid', figsize=(5.6,3.5))
        
        plt.plot(vel_mat_euler[:, 0], vel_mat_euler[:, 2],
                color=TUM_grey, marker='', linestyle='-', markersize=0.5, label="mat stm")
        plt.plot(vel_stm_c_euler[:, 0], vel_stm_c_euler[:, 2],
                color=TUM_orange, marker='', linestyle='-', markersize=0.5, label="c-euler stm")
        plt.plot(vel_stm_c_heuns[:, 0], vel_stm_c_heuns[:, 2],
                color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="c-heuns stm")
        plt.plot(vel_stm_c_adams[:, 0], vel_stm_c_adams[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="c-adams stm")
        plt.plot(vel_dtm_c_euler[:, 0], vel_dtm_c_euler[:, 2],
                color=violett, marker='', linestyle='-', markersize=0.5, label="c-euler dtm")
        plt.legend()

        
        plt.grid(b=True, axis='both')
        plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
        plt.xticks(fontname='arial', fontsize=11)        
        plt.ylabel("Quergeschwindigkeit in m/s", fontname='arial', fontsize=11)
        plt.yticks(fontname='arial', fontsize=11)
        plt.tight_layout()
 
        ############
        ### dPSI ###
        ############
        plt.figure(num='dpsi grid', figsize=(5.6, 3.5))
        
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


plt.draw()
plt.show()

