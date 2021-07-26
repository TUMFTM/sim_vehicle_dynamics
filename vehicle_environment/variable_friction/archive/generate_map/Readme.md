# Friction Map Generation
This repository contains everything which is used for creation, customization and parameterization of friction maps.
**For better usability check "Frictionmap_Workflow.pdf" first!** (only in german yet)

# Folder structure and content
*  frictionmap_data (contains track and map data created by "MainGUI.m"-function)
    * maps          (contains automatic generated friction maps)
    * maps_gimp_custom (contains customized friction maps)
    * tracks (contains automatic generated track maps)
*  maps2datadict (contains filled-in friction maps for automatic generated Simulink data dictionary)
*  scripts (contains scripts which are used within "MainGUI.m" and "CreateDatadictGUI.m")
    * `BasicGUI_2.fig`
    * `BasicGUI_2.m`
    * `Datadict_Creation.m`
    * `Friction_Map_Creation.m`
    * `GIMP_Correction.m`
    * `Read_CenterlineGUI.fig`
    * `Read_CenterlineGUI.m`
    * `Read_FrictionmodeGUI.fig`
    * `Read_FrictionmodeGUI.m`
    * `Read_MapGUI.fig`
    * `Read_MapGUI.m`
    * `Read_TrackGUI.fig`
    * `Read_TrackGUI.m`
    * `Track_Creation.m`
    * `importfile.m`
*  `CreateDatadictGUI.fig`
*  **`CreateDatadictGUI.m`** (Mainfunction for automated creation of Simulink data dictionary)
*  `MainGUI.fig`
*  **`MainGUI.m`** (Mainfunction for creation, customization and parameterization of friction maps)
*  `Frictionmap_Workflow.pdf`

Developer: Dieter Pfahl
