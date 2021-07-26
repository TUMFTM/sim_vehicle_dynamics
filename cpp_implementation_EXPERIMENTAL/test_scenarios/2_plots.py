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


def read_test_scenario(filename):
        # LAYOUT TEST DATA 
        # 0 time_s, 1 xPos_m, 2 yPos_m, 3 psi_rad, 4 dPsi_radps, 5 vx_mps, 6 vy_mps, 7 ax_mps2, 8 ay_mps2,
        # 9 lambdaFL_perc,    10 lambdaFR_perc,   11 lambdaRL_perc,   12 lambdaRR_perc,13 alphaFL_rad,
        # 14 alphaFR_rad,     15 alphaRL_rad,     16 alphaRR_rad, 
        # 17 T_WheelFL_Nm,    18 T_WheelFR_Nm,    19 T_WheelRL_Nm,    20 T_WheelRR_Nm,
        # 21 omega_WheelFL_radps, 22 omega_WheelFR_radps, 23 omega_WheelRL_radps, 24 omega_WheelRR_radps,
        # 25 p_BrakeF_bar,    26 p_BrakeR_bar,27 Delta_Wheel_rad
        torque = np.genfromtxt(filename, float, delimiter=",", skip_header=1,usecols=(0, 17, 18, 19, 20))
        pbrake =   np.genfromtxt(filename, float, delimiter=",", skip_header=1,usecols=(0, 25, 26))
        steer =  np.genfromtxt(filename, float, delimiter=",", skip_header=1,usecols=(0, 27))
        return torque, pbrake, steer


###################
### STEER SINUS ###
###################

torque, _, steer = read_test_scenario("steer_sinus_dt002.csv")

# figsize width, height in INCHES! 
# dpi  
fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# TORQUE
axes[0].set_autoscale_on(False)
axes[0].grid(b=True, axis='both')

axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)
axes[0].set_yticks(np.arange(0,200,20))
axes[0].set_yticklabels(np.arange(0,200,20), fontname='arial', fontsize=11)

axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)
axes[0].set_xticks(np.arange(0,80,10.))
axes[0].set_xticklabels(np.arange(0,80,10), fontname='arial', fontsize=11)

axes[0].plot(torque[:, 0], torque[:,1])

# STEERING
axes[1].set_autoscale_on(False)
axes[1].grid(b=True, axis='both')
axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)
axes[1].set_yticks(np.arange(-3,4,1))
axes[1].set_yticklabels(np.arange(-3,4,1), fontname='arial', fontsize=11)

axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)
axes[1].set_xticks(np.arange(0,80,10.))
axes[1].set_xticklabels(np.arange(0,80,10), fontname='arial', fontsize=11)


axes[1].plot(steer[:,0], steer[:,1]*(180/np.pi))

fig.tight_layout()



##################
### ACC SLOW 1 ###
##################

# torque, _, _ = read_test_scenario("acc_60s.csv")


# plt.figure(num='acc60s', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')
# plt.grid(b=True, axis='both')

# plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.plot(torque[:, 0], torque[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()


###################
### ACC 250Nm/s ###
###################

# torque, _, _ = read_test_scenario("acc_250Nmps.csv")


# plt.figure(num='acc_250Nmps', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')
# plt.grid(b=True, axis='both')

# plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.plot(torque[:, 0], torque[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()


###################
### BRAKING 100 ###
###################


# _, pbrake, _ = read_test_scenario("braking_100.csv")


# plt.figure(num='braking_100', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')
# plt.grid(b=True, axis='both')

# plt.xlabel("Zeit in s", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.ylabel("Bremsdruck in bar", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.plot(pbrake[:, 0], pbrake[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()


###################
### STEER ACC 1 ###
###################

# torque, _, steer = read_test_scenario("steer_acc.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')
# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)

# axes[0].plot(torque[:, 0], torque[:,1])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')
# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)


# axes[1].plot(steer[:,0], steer[:,1]*(180/np.pi))

# fig.tight_layout()


######################
### STEER ACC FAST ###
#####################

# torque, _, steer = read_test_scenario("steer_acc_fast.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')
# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)

# axes[0].plot(torque[:, 0], torque[:,1])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')
# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)


# axes[1].plot(steer[:,0], steer[:,1]*(180/np.pi))

# fig.tight_layout()


##################
### STEER RAMP ###
##################


# torque, _, steer = read_test_scenario("steer_ramp.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')
# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)

# axes[0].plot(torque[:, 0], torque[:,1])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')
# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)

# axes[1].plot(steer[:,0], steer[:,1]*(180/np.pi))

# fig.tight_layout()



###################
### REAL DATA 1 ###
###################


# torque, pbrake, steer = read_test_scenario("monte_day4_run5_straight.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')

# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)

# axes[0].plot(torque[:, 0]-598, torque[:,3])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')

# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)


# axes[1].plot(steer[:,0]-598, steer[:,1]*(180/np.pi))

# fig.tight_layout()

# plt.figure(num='braking_100', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')

# plt.ylabel("Bremsdruck in bar", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.xlabel("Zeit in s\n(c)", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.grid(b=True, axis='both')
# plt.plot(pbrake[:, 0]-598, pbrake[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()


###################
### REAL DATA 2 ###
###################

# torque, pbrake, steer = read_test_scenario("monte_day4_run5_curve1.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')

# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)

# axes[0].plot(torque[:, 0]-784, torque[:,3])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')

# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)


# axes[1].plot(steer[:,0]-784, steer[:,1]*(180/np.pi))
# axes[1].text(3, -9.8,"(b)", horizontalalignment='center',fontname='arial', fontsize=11)

# fig.tight_layout()

# plt.figure(num='braking_100', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')

# plt.ylabel("Bremsdruck in bar", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.xlabel("Zeit in s\n(c)", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.grid(b=True, axis='both')
# plt.plot(pbrake[:, 0]-784, pbrake[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()


###################
### REAL DATA 3 ###
###################


# torque, pbrake, steer = read_test_scenario("monte_day4_run5_turn2-3.csv")

# # figsize width, height in INCHES! 
# # dpi  
# fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(5.5, 3), dpi=100)

# # TORQUE
# axes[0].set_autoscale_on(True)
# axes[0].grid(b=True, axis='both')

# axes[0].set_ylabel("Antirebsmoment in Nm", fontname='arial', fontsize=11)

# axes[0].set_xlabel("Zeit in s\n(a)", fontname='arial', fontsize=11)
# axes[0].plot(torque[:, 0]-792, torque[:,3])

# # STEERING
# axes[1].set_autoscale_on(True)
# axes[1].grid(b=True, axis='both')

# axes[1].set_ylabel("Lenkwinkel in °", fontname='arial', fontsize=11)

# axes[1].set_xlabel("Zeit in s\n(b)", fontname='arial', fontsize=11)

# axes[1].plot(steer[:,0]-792, steer[:,1]*(180/np.pi))

# fig.tight_layout()

# plt.figure(num='braking_100', figsize=(3,3))
# plt.autoscale(enable=True, axis='both')

# plt.xlabel("Zeit in s\n(c)", fontname='arial', fontsize=11)
# plt.xticks(fontname='arial', fontsize=11)

# plt.ylabel("Bremsdruck in bar", fontname='arial', fontsize=11)
# plt.yticks(fontname='arial', fontsize=11)

# plt.grid(b=True, axis='both')

# plt.plot(pbrake[:, 0]-792, pbrake[:, 1],
#         marker='', linestyle='-', markersize=0.5, label="torque ")
# plt.tight_layout()



plt.draw()
plt.show()

