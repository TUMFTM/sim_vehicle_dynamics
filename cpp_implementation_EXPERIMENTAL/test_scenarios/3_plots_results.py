import os
import glob
import numpy as np
import matplotlib.font_manager
import matplotlib.pyplot as plt


# TUM Colors
TUM_blue_dark = '#003359'
TUM_blue_dark2 = '#005293'
TUM_blue = '#3070b3'
TUM_blue_medium = '#64A0C8'
TUM_blue_light = '#98C6EA'
TUM_grey_dark = '#333333'

TUM_grey_dark2 = '#9a9a9a'
TUM_orange = '#E37222'
TUM_green = '#A2AD00'



###########################################################################################################
############################################# COMPARE SOLVER ##############################################
###########################################################################################################

pos_steer_ramp =    False
pos_steer_sinus =   False
acc_braking =       True

# set activating plots 
stm_c_euler =   False
stm_c_adams =   False
stm_c_heuns =   False

stm_mat =       False 

# Postion
pos_show =      True
posx_show =     False
posy_show =     False

# Velocity
vx_show =       False
vy_show =       False

# Acceleration
ax_show =       True
ay_show =       False

#Psi
psi_show =      False
dpsi_show =     False

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
        
        pos     = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 1, 2, 3))
        vel     = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 5, 6, 4))
        acc     = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 7, 8))
        torque  = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 9, 10, 11, 12))
        omega   = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 13, 14, 15, 16))
        pb      = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 17, 18, 19, 20))
        steer   = np.genfromtxt(filename, float, delimiter=",", skip_footer=10,usecols=(0, 21))

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

#############
### EULER ###
#############
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
stm_euler_rolling100_2 =      "../log/.csv"
stm_euler_steer_acc_fast_2 =  "../log/.csv"
stm_euler_steer_acc_2 =       "../log/.csv"
stm_euler_steer_ramp_2 =      "../log/2021.01.20-14:48:11_comp_STM_real.csv" 
stm_euler_steer_sinus_2 =     "../log/.csv"


#################
### NEW ADAMS ###
#################
stm_adams_acc60s =            "../log/2021.01.20-14:08:59_comp_STM_real.csv"
stm_adams_250Nmps =           "../log/2021.01.20-09:49:04_comp_STM_real.csv"
stm_adams_braking100 =        "../log/2021.01.20-14:09:38_comp_STM_real.csv"
stm_adams_rolling100 =        "../log/2021.01.20-14:11:17_comp_STM_real.csv"
stm_adams_steer_acc_fast =    "../log/2021.01.20-14:12:10_comp_STM_real.csv"
stm_adams_steer_acc =         "../log/2021.01.20-14:13:29_comp_STM_real.csv"
stm_adams_steer_ramp =        "../log/2021.01.20-14:14:02_comp_STM_real.csv" 
stm_adams_steer_sinus =       "../log/2021.01.20-14:16:00_comp_STM_real.csv"


### TIMESTEP 0.002 s ###
stm_adams_acc60s_2 =          "../log/csv"
stm_adams_250Nmps_2 =         "../log/.csv"
stm_adams_braking100_2 =      "../log/.csv"
stm_adams_rolling100_2 =      "../log/.csv"
stm_adams_steer_acc_fast_2 =  "../log/.csv"
stm_adams_steer_acc_2 =       "../log/.csv"
stm_adams_steer_ramp_2 =      "../log/2021.01.20-14:44:34_comp_STM_real.csv" 
stm_adams_steer_sinus_2 =     "../log/.csv"


############
### HEUN ###
############
stm_heuns_acc60s =            "../log/2021.01.20-14:08:24_comp_STM_real.csv"
stm_heuns_250Nmps =           "../log/2021.01.20-13:38:17_comp_STM_real.csv"
stm_heuns_braking100 =        "../log/2021.01.20-14:10:07_comp_STM_real.csv"
stm_heuns_rolling100 =        "../log/2021.01.20-14:10:54_comp_STM_real.csv"
stm_heuns_steer_acc_fast =    "../log/2021.01.20-14:12:31_comp_STM_real.csv"
stm_heuns_steer_acc =         "../log/2021.01.20-14:12:59_comp_STM_real.csv"
stm_heuns_steer_ramp =        "../log/2021.01.20-14:15:01_comp_STM_real.csv"
stm_heuns_steer_sinus =       "../log/2021.01.20-14:15:35_comp_STM_real.csv"


### TIMESTEP 0.002 s ###
stm_heuns_acc60s_2 =          "../log/.csv"
stm_heuns_250Nmps_2 =         "../log/.csv"
stm_heuns_braking100_2 =      "../log/.csv"
stm_heuns_rolling100_2 =      "../log/.csv"
stm_heuns_steer_acc_fast_2 =  "../log/.csv"
stm_heuns_steer_acc_2 =       "../log/.csv"
stm_heuns_steer_ramp_2 =      "../log/2021.01.20-14:46:54_comp_STM_real.csv" 
stm_heuns_steer_sinus_2 =     "../log/.csv"


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



#################
### FILE LIST ###
#################

list_data_files = [[stm_euler_acc60s, stm_euler_250Nmps, stm_euler_braking100, stm_euler_rolling100, stm_euler_steer_acc_fast, stm_euler_steer_acc, stm_euler_steer_ramp_2, stm_euler_steer_sinus],
                   [stm_adams_acc60s, stm_adams_250Nmps, stm_adams_braking100, stm_adams_rolling100, stm_adams_steer_acc_fast, stm_adams_steer_acc, stm_adams_steer_ramp_2, stm_adams_steer_sinus],
                   [stm_heuns_acc60s, stm_heuns_250Nmps, stm_heuns_braking100, stm_heuns_rolling100, stm_heuns_steer_acc_fast, stm_heuns_steer_acc, stm_heuns_steer_ramp_2, stm_heuns_steer_sinus],
                   [mat_stm_acc60s,   mat_stm_250Nmps,   mat_stm_braking100,   mat_stm_rolling100,   mat_stm_steer_acc_fast,   mat_stm_steer_acc,   mat_stm_steer_ramp,   mat_stm_steer_sinus]]



############################################################################################################
################################################# PLOTTING #################################################
############################################################################################################

################################################
################ POS STEER RAMP ################
################################################


if pos_steer_ramp:
    
    szenario = 6

    ### Matlab ###
    pos_matlab, vel, acc, torque, omega, brakepressure, steer = read_file_matlab(list_data_files[3][szenario])
    
    ### C Euler ### 
    pos_sim_stm_euler, vel_sim_stm_euler, acc_sim_stm_euler, omega_sim_stm_euler, kappa_sim_stm_euler, alpha_sim_stm_euler, fx_sim_stm_euler, fy_sim_stm_euler, fxpt_sim_stm_euler, brakepressure_sim_stm_euler, steer_sim_stm_euler = read_file_stm(list_data_files[0][szenario])

    ### C ADAMS ###
    pos_sim_stm_adams, vel_sim_stm_adams, acc_sim_stm_adams, omega_sim_stm_adams, kappa_sim_stm_adams, alpha_sim_stm_adams, fx_sim_stm_adams, fy_sim_stm_adams, fxpt_sim_stm_adams, brakepressure_sim_stm_adams, steer_sim_stm_adams = read_file_stm(list_data_files[1][szenario])

    ### C Heuns ###
    pos_sim_stm_heuns, vel_sim_stm_heuns, acc_sim_stm_heuns, omega_sim_stm_heuns, kappa_sim_stm_heuns, alpha_sim_stm_heuns, fx_sim_stm_heuns, fy_sim_stm_heuns, fxpt_sim_stm_heuns, brakepressure_sim_stm_heuns, steer_sim_stm_heuns = read_file_stm(list_data_files[2][szenario])


    fig_pos_steer_ramp, axes_1 = plt.subplots(nrows=2, ncols=2, figsize=(5.5, 5), dpi=100)

    if pos_show:

        ## Rotation MATLAB
        rotangle = np.pi*0.5 
        pos_turned = np.zeros((pos_matlab.shape[0], 3))

        for i in range(0, pos_matlab.shape[0]):
            pos_turned[i, 0] = pos_matlab[i, 0]
            pos_turned[i, 1] = pos_matlab[i, 1]*np.cos(rotangle) + pos_matlab[i, 2]*np.sin(rotangle)
            pos_turned[i, 2] = -pos_matlab[i, 1]*np.sin(rotangle) + pos_matlab[i, 2]*np.cos(rotangle) 

        ### PLOT MATLAB ###
        axes_1[0, 0].set_autoscale_on(False)
        axes_1[0, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_xticks(np.arange(0,5000,1000))
        axes_1[0, 0].set_xticklabels(np.arange(0,5000,1000), fontname='arial', fontsize=11)

        axes_1[0, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_yticks(np.arange(-50,60,10))
        axes_1[0, 0].set_yticklabels(np.arange(-50,60,10), fontname='arial', fontsize=11)


        axes_1[0, 0].plot(pos_turned[:, 1], pos_turned[:, 2],
            color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm matlab euler")
        axes_1[0, 0].text(2000, -90,"(a)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 0].legend(loc='upper left')

        ### PLOT C EULER ###
        axes_1[0, 1].set_autoscale_on(False)
        axes_1[0, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_xticks(np.arange(0,5000,1000))
        axes_1[0, 1].set_xticklabels(np.arange(0,5000,1000), fontname='arial', fontsize=11)

        axes_1[0, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_yticks(np.arange(-50,60,10))
        axes_1[0, 1].set_yticklabels(np.arange(-50,60,10), fontname='arial', fontsize=11)
        
        axes_1[0, 1].plot(pos_sim_stm_euler[:, 1], pos_sim_stm_euler[:, 2],
                color=TUM_blue_medium, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        axes_1[0, 1].text(2000, -90,"(b)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 1].legend(loc='upper left')

        ### PLOT C ADAMS ###
        axes_1[1, 0].set_autoscale_on(False)
        axes_1[1, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_xticks(np.arange(0,5000,1000))
        axes_1[1, 0].set_xticklabels(np.arange(0,5000,1000), fontname='arial', fontsize=11)

        axes_1[1, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_yticks(np.arange(-50,60,10))
        axes_1[1, 0].set_yticklabels(np.arange(-50,60,10), fontname='arial', fontsize=11)
        
        axes_1[1, 0].plot(pos_sim_stm_adams[:, 1], pos_sim_stm_adams[:, 2],
                color=TUM_blue, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        axes_1[1, 0].text(2000, -90,"(c)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 0].legend(loc='upper left')

        ### PLOT C HEUNS ###
        axes_1[1, 1].set_autoscale_on(False)
        axes_1[1, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_xticks(np.arange(0,5000,1000))
        axes_1[1, 1].set_xticklabels(np.arange(0,5000,1000), fontname='arial', fontsize=11)

        axes_1[1, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_yticks(np.arange(-50,60,10))
        axes_1[1, 1].set_yticklabels(np.arange(-50,60,10), fontname='arial', fontsize=11)
        
        axes_1[1, 1].plot(pos_sim_stm_heuns[:, 1], pos_sim_stm_heuns[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c heuns")
        axes_1[1, 1].text(2000, -90,"(d)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 1].legend(loc='upper left')

        fig_pos_steer_ramp.tight_layout()


#################################################
################ POS STEER SINUS ################
#################################################


if pos_steer_sinus:
    
    szenario = 7

    ### Matlab ###
    pos_matlab, vel, acc, torque, omega, brakepressure, steer = read_file_matlab(list_data_files[3][szenario])
    
    ### C Euler ### 
    pos_sim_stm_euler, vel_sim_stm_euler, acc_sim_stm_euler, omega_sim_stm_euler, kappa_sim_stm_euler, alpha_sim_stm_euler, fx_sim_stm_euler, fy_sim_stm_euler, fxpt_sim_stm_euler, brakepressure_sim_stm_euler, steer_sim_stm_euler = read_file_stm(list_data_files[0][szenario])

    ### C ADAMS ###
    pos_sim_stm_adams, vel_sim_stm_adams, acc_sim_stm_adams, omega_sim_stm_adams, kappa_sim_stm_adams, alpha_sim_stm_adams, fx_sim_stm_adams, fy_sim_stm_adams, fxpt_sim_stm_adams, brakepressure_sim_stm_adams, steer_sim_stm_adams = read_file_stm(list_data_files[1][szenario])

    ### C Heuns ###
    pos_sim_stm_heuns, vel_sim_stm_heuns, acc_sim_stm_heuns, omega_sim_stm_heuns, kappa_sim_stm_heuns, alpha_sim_stm_heuns, fx_sim_stm_heuns, fy_sim_stm_heuns, fxpt_sim_stm_heuns, brakepressure_sim_stm_heuns, steer_sim_stm_heuns = read_file_stm(list_data_files[2][szenario])


    fig_pos_steer_sinus, axes_1 = plt.subplots(nrows=2, ncols=2, figsize=(5.5, 5.5), dpi=100)

    if pos_show:

        ## Rotation MATLAB
        rotangle = np.pi*0.5 
        pos_turned = np.zeros((pos_matlab.shape[0], 3))

        for i in range(0, pos_matlab.shape[0]):
            pos_turned[i, 0] = pos_matlab[i, 0]
            pos_turned[i, 1] = pos_matlab[i, 1]*np.cos(rotangle) + pos_matlab[i, 2]*np.sin(rotangle)
            pos_turned[i, 2] = -pos_matlab[i, 1]*np.sin(rotangle) + pos_matlab[i, 2]*np.cos(rotangle) 

        ### PLOT MATLAB ###
        axes_1[0, 0].set_autoscale_on(False)
        axes_1[0, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_xticks(np.arange(0,600,200))
        axes_1[0, 0].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[0, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_yticks(np.arange(-500,200,100))
        axes_1[0, 0].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)


        axes_1[0, 0].plot(pos_turned[:, 1], pos_turned[:, 2],
            color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm matlab euler")
        # axes_1[0, 0].text(2000, -90,"(a)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 0].legend(loc='upper right')

        ### PLOT C EULER ###
        axes_1[0, 1].set_autoscale_on(False)
        axes_1[0, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_xticks(np.arange(0,600,200))
        axes_1[0, 1].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[0, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_yticks(np.arange(-500,200,100))
        axes_1[0, 1].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[0, 1].plot(pos_sim_stm_euler[:, 1], pos_sim_stm_euler[:, 2],
                color=TUM_blue_medium, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        # axes_1[0, 1].text(2000, -90,"(b)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 1].legend(loc='upper right')

        ### PLOT C ADAMS ###
        axes_1[1, 0].set_autoscale_on(False)
        axes_1[1, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_xticks(np.arange(0,600,200))
        axes_1[1, 0].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[1, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_yticks(np.arange(-500,200,100))
        axes_1[1, 0].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[1, 0].plot(pos_sim_stm_adams[:, 1], pos_sim_stm_adams[:, 2],
                color=TUM_blue, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        # axes_1[1, 0].text(2000, -90,"(c)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 0].legend(loc='upper right')

        ### PLOT C HEUNS ###
        axes_1[1, 1].set_autoscale_on(False)
        axes_1[1, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_xticks(np.arange(0,600,200))
        axes_1[1, 1].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[1, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_yticks(np.arange(-500,200,100))
        axes_1[1, 1].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[1, 1].plot(pos_sim_stm_heuns[:, 1], pos_sim_stm_heuns[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c heuns")
        # axes_1[1, 1].text(2000, -90,"(d)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 1].legend(loc='upper right')

        fig_pos_steer_sinus.tight_layout()

#############################################
################ ACC BRAKING ################
#############################################


if acc_braking:
    
    szenario = 2

    ### Matlab ###
    pos_matlab, vel, acc, torque, omega, brakepressure, steer = read_file_matlab(list_data_files[3][szenario])
    
    ### C Euler ### 
    pos_sim_stm_euler, vel_sim_stm_euler, acc_sim_stm_euler, omega_sim_stm_euler, kappa_sim_stm_euler, alpha_sim_stm_euler, fx_sim_stm_euler, fy_sim_stm_euler, fxpt_sim_stm_euler, brakepressure_sim_stm_euler, steer_sim_stm_euler = read_file_stm(list_data_files[0][szenario])

    ### C ADAMS ###
    pos_sim_stm_adams, vel_sim_stm_adams, acc_sim_stm_adams, omega_sim_stm_adams, kappa_sim_stm_adams, alpha_sim_stm_adams, fx_sim_stm_adams, fy_sim_stm_adams, fxpt_sim_stm_adams, brakepressure_sim_stm_adams, steer_sim_stm_adams = read_file_stm(list_data_files[1][szenario])

    ### C Heuns ###
    pos_sim_stm_heuns, vel_sim_stm_heuns, acc_sim_stm_heuns, omega_sim_stm_heuns, kappa_sim_stm_heuns, alpha_sim_stm_heuns, fx_sim_stm_heuns, fy_sim_stm_heuns, fxpt_sim_stm_heuns, brakepressure_sim_stm_heuns, steer_sim_stm_heuns = read_file_stm(list_data_files[2][szenario])


    fig_acc_braking, axes_1 = plt.subplots(nrows=2, ncols=2, figsize=(5.5, 5.5), dpi=100)

    if ax_show:

        # ## Rotation MATLAB
        # rotangle = np.pi*0.5 
        # pos_turned = np.zeros((pos_matlab.shape[0], 3))

        # for i in range(0, pos_matlab.shape[0]):
        #     pos_turned[i, 0] = pos_matlab[i, 0]
        #     pos_turned[i, 1] = pos_matlab[i, 1]*np.cos(rotangle) + pos_matlab[i, 2]*np.sin(rotangle)
        #     pos_turned[i, 2] = -pos_matlab[i, 1]*np.sin(rotangle) + pos_matlab[i, 2]*np.cos(rotangle) 

        ### PLOT MATLAB ###
        axes_1[0, 0].set_autoscale_on(False)
        axes_1[0, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_xticks(np.arange(0,600,200))
        axes_1[0, 0].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[0, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 0].set_yticks(np.arange(-500,200,100))
        axes_1[0, 0].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)


        axes_1[0, 0].plot(pos_turned[:, 1], pos_turned[:, 2],
            color=TUM_blue_light, marker='', linestyle='-', markersize=0.5, label="stm matlab euler")
        # axes_1[0, 0].text(2000, -90,"(a)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 0].legend(loc='upper right')

        ### PLOT C EULER ###
        axes_1[0, 1].set_autoscale_on(False)
        axes_1[0, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_xticks(np.arange(0,600,200))
        axes_1[0, 1].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[0, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[0, 1].set_yticks(np.arange(-500,200,100))
        axes_1[0, 1].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[0, 1].plot(pos_sim_stm_euler[:, 1], pos_sim_stm_euler[:, 2],
                color=TUM_blue_medium, marker='', linestyle='-', markersize=0.5, label="stm c euler")
        # axes_1[0, 1].text(2000, -90,"(b)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[0, 1].legend(loc='upper right')

        ### PLOT C ADAMS ###
        axes_1[1, 0].set_autoscale_on(False)
        axes_1[1, 0].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_xticks(np.arange(0,600,200))
        axes_1[1, 0].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[1, 0].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 0].set_yticks(np.arange(-500,200,100))
        axes_1[1, 0].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[1, 0].plot(pos_sim_stm_adams[:, 1], pos_sim_stm_adams[:, 2],
                color=TUM_blue, marker='', linestyle='-', markersize=0.5, label="stm c adams")
        # axes_1[1, 0].text(2000, -90,"(c)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 0].legend(loc='upper right')

        ### PLOT C HEUNS ###
        axes_1[1, 1].set_autoscale_on(False)
        axes_1[1, 1].set_ylabel("x Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_xticks(np.arange(0,600,200))
        axes_1[1, 1].set_xticklabels(np.arange(0,600,200), fontname='arial', fontsize=11)

        axes_1[1, 1].set_xlabel("y Position in m", fontname='arial', fontsize=11)
        axes_1[1, 1].set_yticks(np.arange(-500,200,100))
        axes_1[1, 1].set_yticklabels(np.arange(-500,200,100), fontname='arial', fontsize=11)
        
        axes_1[1, 1].plot(pos_sim_stm_heuns[:, 1], pos_sim_stm_heuns[:, 2],
                color=TUM_blue_dark, marker='', linestyle='-', markersize=0.5, label="stm c heuns")
        # axes_1[1, 1].text(2000, -90,"(d)", horizontalalignment='center',fontname='arial', fontsize=11)
        axes_1[1, 1].legend(loc='upper right')

        fig_acc_braking.tight_layout()



plt.draw()
plt.show()



