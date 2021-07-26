# import SimVehicle
#from SimVehicle import Param_dtm
#from SimVehicle import Vehicle_State
import Param_dtm
# import VehicleState
# import VehicleBody
import Vehicle
# import SingleTrackModel

print("In main.py\n")


######################
### TEST PARAM_DTM ###
######################

#help(Param_dtm)

#initalize object of Python class Param_dtm()
param_dtm = Param_dtm.Param_dtm()
#param_dtm = Param_dtm()

param_dtm.setParameters()
print(param_dtm.getVehicleMass())

print(param_dtm)

m = param_dtm.getVehicleMass()
print("Mass: ",m, "\n")

del param_dtm

#########################
### TEST VehicleState ###
#########################

#help(VehicleState)

state = VehicleState.VehicleState()

print("Set VehicleSate Pos")
state.testSetPos(5)

x = state.getPosIni()

print("getPosIni: ", x)

#########################
### TEST VehicleBody ###
#########################

#help(VehicleBody)

body = VehicleBody.VehicleBody()



####################
### TEST Vehicle ###
####################

#help(Vehicle)

veh = Vehicle.Vehicle()

veh.test()

veh.setParams()

print("Veh mass from Vehicle class: \n", veh.getVehicleMass())



#############################
### TEST SingleTrackModel ###
#############################

# stm = SingleTrackModel.SingleTrackModel()

# stm.test()

