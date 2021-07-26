function path_dict = manage_paths()

    path = strsplit(pwd,"sim_vehicle_dynamics");
    path2module = strcat(path(1), "sim_vehicle_dynamics");
    path2mainfolder = strcat(path2module, "\variable_friction\generate_map");
    path2input = strcat(path2mainfolder, "\inputs");
    path2output = strcat(path2mainfolder, "\outputs");
    
    path_dict = [path2module, path2mainfolder, path2input, path2output];
