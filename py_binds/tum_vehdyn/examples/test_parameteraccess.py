import numpy as np

from SingleTrackModel import SingleTrackModel
from DoubleTrackModel import DoubleTrackModel

stm = SingleTrackModel()
dtm = DoubleTrackModel()

list_parameter = ["VEH__Aerodynamics__A_LongitudinalDrag_m2",
                  "VEH__Brakes__mue_BrakePadsFrRe_kinetic__1",
                  "VEH__Brakes__n_BrakePadsNumberFrRe__2",
                  "VEH__VehicleData__I_K_Vehicle_kgm2__33",
                  "tireRL__MFSIMPLE__Iyy_Wheel_kgm2",
                  "x0_stm_vehiclestates",
                  "INIT__initialvalues__omega0_Wheels_radps__1",
                  "tireFL__INERTIAL__m_Wheel_kg"]


for ele in list_parameter:

    param_stm = stm.get_parameter(ele)
    param_dtm = dtm.get_parameter(ele)

    print(ele)
    print("stm: " + str(param_stm))
    print("dtm: " + str(param_dtm))


stm.set_externalForce(np.array([100,0,0], dtype='double'))
