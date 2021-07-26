import SingleTrackModel



#############################
### TEST SingleTrackModel ###
#############################

print("In main.py\n")

stm = SingleTrackModel.SingleTrackModel("euler")

stm.setParams_stm()
stm.set_timestep(0.004)

print("set input torque to 100 Nm")
torwue_4w = [100, 100, 200, 200]
stm.set_tiretorque_4w_Nm(torwue_4w)

print("set vx to 0 ")
stm.set_vx_veh(0)

for i in range(500):
    stm.step_simulation()
    
    #NOTE if the solver amdams is used, the step_simulation functions needs the keyword argument step! 
    #stm.step_simulation(step=i)

print("pos x: ")
print(stm.get_posx_ini())

print("pos y: ")
print(stm.get_posy_ini())

print("vx veh: ")
print(stm.get_vx_veh())

####################
### RUN TESTCASE ###
####################
# print("activate logging")
# stm.set_logging(1)

# print("reset time logging")
# stm.set_timecap_testcase(10)

# print("reset log rate")
# stm.set_lograte_testcase(1)

# print("set timestep")
# stm.set_timestep(0.004)

# print("run testcase")

# testcase_name = b"acc_60s.csv"
# stm.set_testfile_testcase(testcase_name)

# stm.run_testcase()