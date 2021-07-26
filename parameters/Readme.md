# Package overview
This is a description of all vehicle related parameters which are used in the simulation. Please adjust all values properly to your vehicle. Note that the parameters are organized in a structure called `<VehicleIdentifier>_sim_<VehDynModelType>_<ParameterType>`. This name must not be changed.

# Parameter description
Both model (single-track and double-track model) can be parametrized with a variety of parameters. A description of the different parameters is provided below.

## Initial position and orientation
The initial position of the vehicle model is specified with the variable `x0_initialstates`. This variable is handed to the referenced subsystem as a model argument.
To set the initial position and heading of the vehicle right-click the referenced submodel block which reference on one of the vehicle dynamics models.
Click on `Block Parameters (ModelReference)`, then click `Arguments` where you can find the variable `x0_initialstates`.

`x0_initialstates` has dimension 6x1 and specifies following initial values in the given earth-fixed coordinate systems:

| initial state     | unit  | description   |
| ----------------- | ----- | ------------- |
| x-position        | m     | sets the initial x-position of the vehicle's CoG |
| y-position        | m     | sets the initial y-position of the vehicle's CoG |
| z-position        | m     | sets the initial z-position of the vehicle's CoG |
| roll angle        | rad   | sets the initial roll angle about the vehicle's x-axis |
| pitch angle       | rad   | sets the initial pitch angle about the vehicle's y-axis |
| yaw angle         | rad   | sets the initial yaw angle about the vehicle's z-axis (heading) |


## Single-track and double-track model
General parameters of both models are located in the parameter file  `pa_sim_vehicleparameters.ini`. A short description of the parameters can be found below:

### pa_sim_vehicleparameters.ini

#### Vehicle data
| Variable                  | Unit  | Description
| ------------------------- | ----- | -----------
| m_Vehicle_kg              | kg    | total vehicle mass in kg
| l_WheelbaseF_m            | m     | front wheelbase (CoG to front axle) in m
| l_WheelbaseTotal_m        | m     | total wheelbase (front to rear axle) in m
| w_GeomCenterlineToCOG_m   | m     | Lateral distance from vehicle middle plane to CoG, along vehicle fixed y-axis
| h_AxlePlaneToCOG_m        | m     | Vertical distance from CoG to axle plane
| w_TrackF_m                | m     | Track width at front axle
| w_TrackR_m                | m     | Track width at rear axle
| I_K_Vehicle_kgm2          | kgm^2 | Vehicle yaw inertia in kgm^2

#### Aerodynamics
| Variable                      | Unit  | Description
| ----------------------------- | ----- | -----------
| A_LongitudinalDrag_m2         | m^2   | Effective vehicle cross-sectional area for aerodynamic forces
| cw_LongitudinalDrag           | -     | Drag coefficient at CoG
| cl_LongitudinalLift           | -     | Lift coefficient at CoG
| cpm_LongDragPitchMomentCoeff  | -     | Longitudinal drag pitch moment coefficient
| beta_wind_start_rad           | rad   | Relative wind angle vector (start -> = 0)
| beta_wind_end_rad             | rad   | Relative wind angle vector (end)
| beta_wind_step_rad            | rad   | Relative wind angle vector (step size)
| Cs_LatDragCoeff_start         | -     | Side force coefficient vector in dependence of relative wind angle vector (start -> = 0)
| Cs_LatDragCoeff_end           | -     | Side force coefficient vector in dependence of relative wind angle vector (end)
| Cs_LatDragCoeff_step          | -     | Side force coefficient vector in dependence of relative wind angle vector (step size)
| Cym_DragYawMomentCoeff_start  | -     | Yaw moment coefficient vector in dependence of relative wind angle vector (start -> = 0)
| Cym_DragYawMomentCoeff_end    | -     | Yaw moment coefficient vector in dependence of relative wind angle vector (end)
| Cym_DragYawMomentCoeff_step   | -     | Yaw moment coefficient vector in dependence of relative wind angle vector (step size)

#### Environment
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| p_Air_Pa                | Pa     | Ambient air pressure
| T_Air_K                 | K      | Ambient air temperature
| a_Gravity_mps2          | m/s^2  | gravity

#### Tires
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| p_Tires_pa                | pa      | Tire pressure for each tire

#### Brakes
| Variable                  | Unit  | Description
| ------------------------- | ----- | -----------
| BrakeBias_Front               | -     | brake bias at (regarding front axle)
| mue_BrakePadsFrRe_static      | -     | static friction coefficient of brake pads
| mue_BrakePadsFrRe_kinetic     | -     | dynamic friction coefficient of brake pads
| d_BrakeActuatorBoreFrRe_m     | m     | brake actuator bore diameter (area where brake pressure is working on)
| r_BrakePadsMeanLeverFrRe_m    | m     | distance between brake pads and wheel center
| n_BrakePadsNumberFrRe         | m     | number of brake pads

#### Steering
| Variable                  | Unit  | Description
| ------------------------- | ----- | -----------
| T_Steering_s              | s     | Steering system response time constant

#### Actuator limitation
| Variable                  | Unit  | Description
| ------------------------- | ----- | -----------
| Fx_Throttle_max_N         | N     | max. possible overall acceleration force
| Fx_Brake_max_N            | N     | max. possible overall braking force
| deltaSteering_max_rad     | rad   | max. possible steering angle
| deltaSteering_min_rad     | rad   | min. possible steering angle

#### Simulation
| Variable                  | Unit  | Description
| ------------------------- | ----- | -----------
| Sim_LongVelTolerance_mps  | m/s   | Longitudinal velocity tolerance
| Sim_LongOff_m             | m     | Geometric longitudinal offset from axle plane
| Sim_LatOff_m              | m     | Geometric lateral offset from axle plane
| Sim_VertOff_m             | m     | Geometric vertical offset from axle plane

#### STM specific
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| cLiftF                  | -      | Aero lift coefficient at front axle
| cLiftR                  | -      | Aero lift coefficient at rear axle
| CoGz_m                  | m      | Centre of gravity height with respect to the ground plane
| cRollFriction_Npmps     | Npmps  | Speed dependent roll friction coefficient
| MaxRollFriction_N       | N      | Maximum friction force for roll friction
| T_YawRate_s             | s      | Yaw rate response time constant for simplified kinematic vehicle model at very low speeds
| T_LatVel_s              | s      | Lateral velocity response time constant for simplified kinematic vehicle model at very low speeds
| T_Tire_s                | s      | Tire force response time constant
| switchModelBlend_mps    | mps    | Width of blending window to switch between slow vehicle model and fast vehicle model
| PTLimitLowVel_N         | N      | Maximum negative force applied to the slow vehicle model (ensures that its possible to apply brakes at standstill)
| switchModelVel_mps      | mps    | Speed at which the simulation model blends between slow and fast simulation models

### pa_sim_initialparameters.ini
This parameter file contains the initial states of the vehicle dynamics simulation.

### Initial values
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| Vehicle_InitialRollAngle      | rad   | sets the initial roll angle about the vehicle's x-axis
| Vehicle_InitialPitchAngle     | rad   | sets the initial pitch angle about the vehicle's y-axis
| Vehicle_InitialYawAngle       | rad   | sets the initial yaw angle about the vehicle's z-axis
| Vehicle_InitialRollRate_radps | rad/s | sets the initial roll rate about the vehicle's x-axis
| Vehicle_InitialPitchRate_radps| rad/s | sets the initial pitch rate about the vehicle's y-axis
| Vehicle_InitialYawRate_radps  | rad/s | sets the initial yaw rate about the vehicle's z-axis
| Vehicle_InitialVelocity_mps   | m/s   | sets the initial vehicle CoG velocity
| x0_verticaldynamics           | m/s   | Initial vehicle orientation of double-track model specific values (roll, pitch and z-position of chassis)
| omega0_Wheels_radps           | rad/s | sets the initial rotational velocities of wheels
| v0z_Wheels_mps                | m/s   | sets the initial vertical velocities of wheels
| z0_TireDeflection_m           | m     | sets the initial tire deflection

**NOTE: Initial position of vehicle is handed-over via a model argument and must be specified by right-clicking on the referenced vehicle dynamics models. Further description see above.**

### pa_sim_powertrainparameters.ini
This parameter file contains the parameters used to model the powertrain of the vehicle dynamics simulation. The powertrain model includes a combustion engine, clutch, transmission and differential.

The default setting is a electric powertrain which directly controls the wheel torque individually. The wheel torque is calculated from a requested, overall acceleration force.

### Mode
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| activate_CombustionEngine     | -     | activates the combustion engine (default: electric powertrain)
| activate_ManualGearbox        | -     | activates manual gear shifting
| activate_ThrottleInterface    | -     | activates throttle interface (default: force interface)

### Engine
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| n_idle_rpm        | rpm       | engine idle rpm
| n_0_rpm           | rpm       |
| n_ub_rpm          | rpm       | rpm for up-shifting
| n_limit_rpm       | rpm       | max. engine rpm
| n_lb_rpm          | rpm       |
| I_engine_kgm2     | kgm^2     | engine rotational inertia

### Clutch
| Variable              | Unit   | Description
| --------------------- | ------ | -----------
| T_max_cap_Nm          | Nm     | max. transmissible torque of clutch
| clutch_time_s         | s      | time of clutch engagement

### Transmission
| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| initial_gear          | Nm    | initial gear (0 = neutral)
| I_transmission_kgm2   | kgm^2 | gearbox rotational inertia
| gear                  | -     | available gears
| gear_ratio            | -     | ration of available gears
| gear_efficiency       | -     | efficiency of available gears

### Differential
| Variable              | Unit   | Description
| --------------------- | ------ | -----------
| I_drivetrain_kgm2     | kgm^2 | differential rotational inertia
| c_diff_ratio          | -     | ratio of central differential
| c_diff_efficiency     | -     | efficiency of central differential
| f_diff_ratio          | -     | ratio of front differential
| f_diff_efficiency     | -     | efficiency of front differential
| r_diff_ratio          | -     | ratio of rear differential
| r_diff_efficiency     | -     | efficiency of rear differential

### pa_sim_tireparameters.tir
This parameter file contains the tire parameters of the vehicle dynamics simulation. Different tire models are used for the single- and double-track model.

Note: You can specify all vehicle tires individually. By appending "_front", and "_rear" to the .tir file (e.g. "pa_sim_tireparameters_front.tir"), two separate tire configurations can be applied for front and rear axle. By appending "_frontleft", "_frontright", "_rearleft" and "_rearright", four separate tire configurations can be applied.

#### Single-track model
The Single-track model uses a 5-parameter Pacejka model. Front and rear tires can be modeled separately.

| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| PacLong_B         | -     | Pacejka B parameter (long.)
| PacLong_C         | -     | Pacejka C parameter (long.)
| PacLong_D         | -     | Pacejka D parameter (long.)
| PacLong_E         | -     | Pacejka E parameter (long.)
| PacLong_Fznom     | N     | Nominal tire load (for longitudinal tire forces)
| PacLong_eps_load  | -     | vertical tire load degressivity factor (long.)
| PacLat_B          | -     | Pacejka B parameter (lat.)
| PacLat_C          | -     | Pacejka C parameter (lat.)
| PacLat_D          | -     | Pacejka D parameter (lat.)
| PacLat_E          | -     | Pacejka E parameter (lat.)
| PacLat_Fznom      | N     | Nominal tire load (for lateral tire forces)
| PacLat_eps_load   | -     | vertical tire load degressivity factor (lat.)
| r_tire_m          | m     | tire radius
| Iyy_Wheel_kgm2    | kgm2  | Wheel inertia about the wheel spin axis


#### Double-track model
The wheel and tire block `Combined Slip Wheel 2DOF` with disc brakes from the Matlab Vehicle Dynamics Blockset is used for tire modeling of the double-track model.
This parameter file contains wheel and tire Pacejka parameters. For further description of the Pacejka parameters consult the Matlab documentation or
literature.
A short description of the parameters is provided below and the extended description is partially taken from the MATLAB-Documentation:

<table class="relative-table wrapped confluenceTable"><colgroup><col style="width: 25.0904%;" /><col style="width: 4.28373%;" /><col style="width: 20.6398%;" /><col style="width: 6.50904%;" /><col style="width: 43.2823%;" /></colgroup><tbody><tr><th class="confluenceTh" colspan="1"><p>parameter name</p></th><th class="confluenceTh" colspan="1">unit</th><th class="confluenceTh">short description</th><th class="confluenceTh" colspan="1">dimension</th><th class="confluenceTh">extended description</th></tr><tr><td class="highlight-blue confluenceTd" colspan="5" data-highlight-colour="blue">Wheels</td></tr><tr><td class="confluenceTd" colspan="1">m_WheelsFB_kg</td><td class="confluenceTd" colspan="1">kg</td><td class="confluenceTd" colspan="1">Unsprung wheel mass</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Unsprung masses on every wheel, for front axle and rear axle separately</td></tr><tr><td class="confluenceTd" colspan="1">Iyy_WheelsFB_kgm2</td><td class="confluenceTd" colspan="1">kgm2</td><td class="confluenceTd" colspan="1">Wheel inertia</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Wheel inertia about the wheel spin axis, for front and rear axle separately</td></tr><tr><td class="confluenceTd" colspan="1">a_Gravity_mps2</td><td class="confluenceTd" colspan="1">mps2</td><td class="confluenceTd" colspan="1">Gravitational acceleration</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Gravitational acceleration positive constant</td></tr><tr><td class="confluenceTd" colspan="1">mue_Wheels</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Rotational damping</td><td class="confluenceTd" colspan="1">1x4</td><td class="confluenceTd" colspan="1">Wheel rotational viscous damping about the wheel spin axis, for every wheel</td></tr><tr><td class="confluenceTd" colspan="1">UNLOADED_RADIUS</td><td class="confluenceTd" colspan="1">m</td><td class="confluenceTd" colspan="1">Unloaded Radius of each tire</td><td class="confluenceTd" colspan="1">1x4</td><td class="confluenceTd" colspan="1">Unloaded radius of each tire (FL FR RL RR)</td></tr><tr><td class="confluenceTd" colspan="1">NOMPRES</td><td class="confluenceTd" colspan="1">PA</td><td class="confluenceTd" colspan="1">Nominal tire pressure</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Nominal tire pressure under which the measurement of the Pacejka parameters has been conducted (should be provided in tire data set)</td></tr><tr><td class="confluenceTd" colspan="1">FNOMIN</td><td class="confluenceTd" colspan="1">N</td><td class="confluenceTd" colspan="1">Nominal vertical tire force</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Nominal vertical tire force under which the measurement of the Pacejka parameters has been conducted (should be provided in tire data set)</td></tr><tr><td class="confluenceTd" colspan="1">WIDTH</td><td class="confluenceTd" colspan="1">m</td><td class="confluenceTd" colspan="1">Width of each tire</td><td class="confluenceTd" colspan="1">1x4</td><td class="confluenceTd" colspan="1">Width of each tire (FL FR RL RR)</td></tr></tbody></table>

**Note: The MF-Tire 6.1 parameters are not listed above but can be found within the MATLAB documentation of the Combined Slip Wheel 2DOF block or in literature.**

## Suspension of the double-track model
The suspension system parameters of the double-track model are located in `pa_sim_dtm_suspensionparameters.ini`.
A short description of the parameters can be found below and a more detailed in the Matlab Documentation of the Vehicle Dynamics Blockset.

### pa_sim_dtm_suspensionparameters.ini
The suspension block `independent suspension - double wishbone`from the Matlab Vehicle Dynamics Blockset is used for suspension modeling.
A short description of the parameters is provided below and the extended description is partially taken from the MATLAB-Documentation:

<table class="relative-table wrapped confluenceTable"><colgroup><col style="width: 25.0904%;" /><col style="width: 4.28373%;" /><col style="width: 20.6398%;" /><col style="width: 6.50904%;" /><col style="width: 43.2823%;" /></colgroup><tbody><tr><th class="confluenceTh" colspan="1"><p>parameter name</p></th><th class="confluenceTh" colspan="1">unit</th><th class="confluenceTh">short description</th><th class="confluenceTh" colspan="1">dimension</th><th class="confluenceTh">extended description</th></tr><tr><td class="highlight-blue confluenceTd" title="Hintergrundfarbe : Blau" colspan="5" data-highlight-colour="blue">Compliance</td></tr><tr><td class="confluenceTd" colspan="1">c_SpringSuspensionFB_Npm</td><td class="confluenceTd" colspan="1">Npm</td><td class="confluenceTd" colspan="1">Suspension spring constant</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Linear vertical suspension spring constant for the front and rear axle, spring constants referred to the track widths</td></tr><tr><td class="confluenceTd" colspan="1">d_DamperSuspensionFB_Nspm</td><td class="confluenceTd" colspan="1">Nspm</td><td class="confluenceTd" colspan="1">Suspension damper constant</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1"><span>Linear vertical suspension damper constant for the front and rear axle, damper constants referred to the track widths</span></td></tr><tr><td class="confluenceTd" colspan="1">hmax_SuspensionFB_m</td><td class="confluenceTd" colspan="1">m</td><td class="confluenceTd" colspan="1">Suspension hardstop extension</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Suspension relative maximum and minimum height, suspension hardstop heights</td></tr><tr><td class="confluenceTd" colspan="1">F0z_SpringSuspensionFB_N</td><td class="confluenceTd" colspan="1">N</td><td class="confluenceTd" colspan="1">Initial axle loads</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Initial axle loads at front and rear axle, only positive, along rear axle fixed z-axis</td></tr><tr><td class="highlight-blue confluenceTd" title="Hintergrundfarbe : Blau" colspan="5" data-highlight-colour="blue">Anti-sway</td></tr><tr><td class="confluenceTd" colspan="1">r_AntiSwayArmRadiusFB_m</td><td class="confluenceTd" colspan="1">m</td><td class="confluenceTd" colspan="1">Anti-sway arm radius</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Anti sway arm radius for front and rear axle</td></tr><tr><td class="confluenceTd" colspan="1">c_SpringAntiSwayFB_Nmprad</td><td class="confluenceTd" colspan="1">Nmprad</td><td class="confluenceTd" colspan="1">Anti-sway torsion spring constant</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Anti-sway torsion spring constant at front and rear axle</td></tr><tr><td class="confluenceTd" colspan="1">phi_AntiSwayNeutralArmFB_rad</td><td class="confluenceTd" colspan="1">rad</td><td class="confluenceTd" colspan="1">Anti-sway arm neutral angle</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1"><span>Anti-sway arm neutral angle for nominal suspension height at front and rear axle</span></td></tr><tr><td class="highlight-blue confluenceTd" title="Hintergrundfarbe : Blau" colspan="5" data-highlight-colour="blue">Suspension kinematics</td></tr><tr><td class="confluenceTd">gamma0_SuspensionCamberFB_rad</td><td class="confluenceTd">rad</td><td class="confluenceTd">Nominal camber angle</td><td class="confluenceTd">1x2</td><td class="confluenceTd">Nominal camber angle at zero steering angle, at front and rear axle, relative to the road plane</td></tr><tr><td class="confluenceTd" colspan="1">tau0_SuspensionCasterFB_rad</td><td class="confluenceTd" colspan="1">rad</td><td class="confluenceTd" colspan="1">Nominal caster angle</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Nominal caster angle at zero steering angle, at front and rear axle, relative to the road plane</td></tr><tr><td class="confluenceTd" colspan="1">nu0_SuspensionToeFB_rad</td><td class="confluenceTd" colspan="1">rad</td><td class="confluenceTd" colspan="1">Nominal toe angle</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Nominal toe angle at zero steering angle, at front and rear axle, relative to the road plane</td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionHeightOverSteeringF_mprad</td><td class="confluenceTd" colspan="1">mprad</td><td class="confluenceTd" colspan="1">Suspension height vs steering angle slope</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Steering angle to vertical force slope at front axle, at suspension wheel carrier reference point<span>, relative to the road plane</span></td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionCamberOverSteeringF</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Camber angle vs steering angle slope</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Camber angle vs steering angle slope at front axle<span>, relative to the road plane</span></td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionCasterOverSteeringF</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Caster angle vs steering angle slope</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Caster angle vs steering angle slope at front axle<span>, relative to the road plane</span></td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionToeOverSteeringF</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Toe angle steering slope</td><td class="confluenceTd" colspan="1">1x1</td><td class="confluenceTd" colspan="1">Toe angle vs steering angle slope at front axle<span>, relative to the road plane</span></td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionRollSteerOverHeightFB</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Steer angle suspension slope</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Roll steer angle vs suspension height slope at front and rear axle, relative to the road plane</td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionCamberOverHeightFB</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Camber angle vs suspension height slope</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Camber angle vs suspension height slope at front and rear axle, relative to the road plane</td></tr><tr><td class="confluenceTd" colspan="1">k_SuspensionCasterOverHeightFB</td><td class="confluenceTd" colspan="1"><br /></td><td class="confluenceTd" colspan="1">Caster angle vs suspension height slope</td><td class="confluenceTd" colspan="1">1x2</td><td class="confluenceTd" colspan="1">Caster angle vs suspension height slope at front and rear axle, relative to the road plane</td></tr></tbody></table>
