# General
This is a description of all vehicle related parameters which are used in the simulation. Please adjust all values properly to your vehicle. Note, that the parameters are organized in a structure called `veh_param_<VehicleIdentifier>`. This name must not be changed.

# Parameter description

| Variable                | Unit   | Description
| ----------------------- | ------ | -----------
| cLiftF                  | -      | Aero lift coefficient at front axle
| cLiftR                  | -      | Aero lift coefficient at rear axle
| CoGx_m                  | m      | Centre of gravity longitudinal with respect to front axle
| CoGy_m                  | m      | Centre of gravity lateral with respect to front axle mid point
| CoGz_m                  | m      | Centre of gravity height with respect to the ground plane
| cDrag                   | m      | Aero drag coefficient
| Aref_m2                 | m^2    | Aero reference area
| Gearratio               | -      | Gearbox ratio (Wheeltorque = Gearratio*Motortorque)
| Wheelbase_m             | m      | Distance between the axles
| PacLatF                 | -      | Vector with pacjeka coefficients for lateral model at front axle
| PacLongF                | -      | Vector with pacjeka coefficients for longitudinal model at front axle
| PacLatF                 | -      | Vector with pacjeka coefficients for lateral model at rear axle
| PacLatF                 | -      | Vector with pacjeka coefficients for longitudinal model at rear axle
| cRollFriction_Npmps     | Npmps  | Speed dependent roll friction coefficient
| MaxRollFriction_N       | N      | Maximum friction force for roll friction
| T_YawRate_s             | s      | Yaw rate response time constant for simplified kinematic vehicle model at very low speeds
| T_LatVel_s              | s      | Lateral velocity response time constant for simplified kinematic vehicle model at very low speeds
| TrackWidthF_m           | m      | Track width at front axle
| TrackwidthR_m           | m      | Track width at rear axle
| VehicleInertia_kgm2     | kgm^2  | Vehicle yaw inertia
| WheelInertiaF_kgm2      | kgm^2  | Wheel inertia (one wheel) at front axle
| WheelInertiaR_kgm2      | kgm^2  | Wheel inertia (one wheel) at rear axle
| VehicleMass_kg          | kg     | Overall vehicle mass
| switchModelBlend_mps    | mps    | Width of blending window to switch between slow vehicle model and fast vehicle model
| PTLimitLowVel_N         | N      | Maximum negative force applied to the slow vehicle model (ensures that its possible to apply brakes at standstill)
| switchModelVel_mps      | mps    | Speed at which the simulation model blends between slow and fast simulation models
| T_Tire_s                | s      | Tire force response time constant
