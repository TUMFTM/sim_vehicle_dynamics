%% manage paths

path = strsplit(pwd,"sim_vehicle_dynamics");
path2module = strcat(path(1), "sim_vehicle_dynamics");
path2frictionmodel_folder = strcat(path2module, "\variable_friction\frictionmodel");
path2input = strcat(path2frictionmodel_folder, "\GUI\inputs");
path2output = strcat(path2frictionmodel_folder, "\GUI\outputs");

filepath2output_sldd=strcat(path2output, "\frictionmaps.sldd");
filepath2output_config=strcat(path2output, "\Gridmap_Config.txt");

%Handover Referenceline path and resolution from base workspace
Grid_mode=evalin('base', 'Grid_mode');
InterpTime=evalin('base','InterpTime');

%Set Variables

fid=fopen(filepath2output_config, 'wt');
Gridmap_Ident=zeros(3,3);

%% generate data dictionaries containing friction maps

switch Grid_mode
    
    case 1
        filename_1 = dir(strcat(path2input, '\1*.mat'));
    	filename_1 = filename_1.name;

        Gridmap_1 = importdata(strcat(path2input, '\', filename_1));
        Gridmap_2 = int8(zeros(size(Gridmap_1,1),size(Gridmap_1,2)));
        Gridmap_3 = Gridmap_2;
        Gridmap_4 = Gridmap_2;
        
        fprintf(fid, ['Gridmap_1: ', filename_1, ...
            '\nGridmap_2: 0 \nGridmap_3: 0 \nGridmap_4: 0 ']);
        
        fclose(fid);
        Gridmap_Ident(1:2,1:2)  = Gridmap_1(1:2,1:2);
        Gridmap_Ident(1,3)      = Gridmap_1(1,3);
        Gridmap_Ident(3,1)      = size(Gridmap_1,1);
        Gridmap_Ident(3,2)      = size(Gridmap_1,2);
        
    case 2
        filename_1 = dir(strcat(path2input, '\1*.mat'));
        filename_2 = dir(strcat(path2input, '\2*.mat'));
     	filename_1 = filename_1.name;
        filename_2 = filename_2.name;

        Gridmap_1 = importdata(strcat(path2input, '\', filename_1));
        Gridmap_2 = importdata(strcat(path2input, '\', filename_2));
        Gridmap_3 = int8(zeros(size(Gridmap_1,1),size(Gridmap_1,2)));
        Gridmap_4 = Gridmap_3;
        
        fprintf(fid, ['Gridmap_1: ', filename_1, ...
            '\nGridmap_2: ', filename_2, ...
            '\nGridmap_3: 0 \nGridmap_4: 0 ']);
        
        fclose(fid);
        Gridmap_Ident(1:2,1:2)  = Gridmap_1(1:2,1:2);
        Gridmap_Ident(1,3)      = Gridmap_1(1,3);
        Gridmap_Ident(3,1)      = size(Gridmap_1,1);
        Gridmap_Ident(3,2)      = size(Gridmap_1,2);
        
    case 3
        filename_1 = dir(strcat(path2input, '\1*.mat'));
        filename_2 = dir(strcat(path2input, '\2*.mat'));
     	filename_3 = dir(strcat(path2input, '\3*.mat'));
     	filename_1 = filename_1.name;
        filename_2 = filename_2.name;
    	filename_3 = filename_3.name;

        Gridmap_1 = importdata(strcat(path2input, '\', filename_1));
        Gridmap_2 = importdata(strcat(path2input, '\', filename_2));
        Gridmap_3 = importdata(strcat(path2input, '\', filename_3));
        Gridmap_4 = int8(zeros(size(Gridmap_1,1),size(Gridmap_1,2)));
        
        fprintf(fid, ['Gridmap_1: ', filename_1, ...
            '\nGridmap_2: ', filename_2, ...
            '\nGridmap_3: ', filename_3, ...
            '\nGridmap_4: 0 ']);
        
        fclose(fid);
        Gridmap_Ident(1:2,1:2)  = Gridmap_1(1:2,1:2);
        Gridmap_Ident(1,3)      = Gridmap_1(1,3);
        Gridmap_Ident(3,1)      = size(Gridmap_1,1);
        Gridmap_Ident(3,2)      = size(Gridmap_1,2);
        
    case 4
        filename_1 = dir(strcat(path2input, '\1*.mat'));
        filename_2 = dir(strcat(path2input, '\2*.mat'));
     	filename_3 = dir(strcat(path2input, '\3*.mat'));
        filename_4 = dir(strcat(path2input, '\4*.mat'));
     	filename_1 = filename_1.name;
        filename_2 = filename_2.name;
    	filename_3 = filename_3.name;
      	filename_4 = filename_4.name;

        Gridmap_1 = importdata(strcat(path2input, '\', filename_1));
        Gridmap_2 = importdata(strcat(path2input, '\', filename_2));
        Gridmap_3 = importdata(strcat(path2input, '\', filename_3));
        Gridmap_4 = importdata(strcat(path2input, '\', filename_4));
        
        fprintf(fid, ['Gridmap_1: ', filename_1, ...
            '\nGridmap_2: ',filename_2, ...
            '\nGridmap_3: ',filename_3, ...
            '\nGridmap_4: ',filename_4]);
        
        Gridmap_Ident(1:2,1:2)  = Gridmap_1(1:2,1:2);
        Gridmap_Ident(1,3)      = Gridmap_1(1,3);
        Gridmap_Ident(3,1)      = size(Gridmap_1,1);
        Gridmap_Ident(3,2)      = size(Gridmap_1,2);
        
end       

%Create Datadict
if exist(filepath2output_sldd, 'file')==0
    myDictionaryObj = Simulink.data.dictionary.create(filepath2output_sldd);
    dDataSectObj = getSection(myDictionaryObj,'Design Data');
    addEntry(dDataSectObj,'Grid_map_1',Gridmap_1);
    addEntry(dDataSectObj,'Grid_map_2',Gridmap_2);
    addEntry(dDataSectObj,'Grid_map_3',Gridmap_3);
    addEntry(dDataSectObj,'Grid_map_4',Gridmap_4);
    addEntry(dDataSectObj,'InterpTime',InterpTime);
    addEntry(dDataSectObj,'Gridmap_Ident',Gridmap_Ident);
    
else
    myDictionaryObj = Simulink.data.dictionary.open(filepath2output_sldd);
    dDataSectObj = getSection(myDictionaryObj,'Design Data');
    assignin(dDataSectObj,'Grid_map_1',Gridmap_1);
    assignin(dDataSectObj,'Grid_map_2',Gridmap_2);
    assignin(dDataSectObj,'Grid_map_3',Gridmap_3);
    assignin(dDataSectObj,'Grid_map_4',Gridmap_4);
    assignin(dDataSectObj,'InterpTime',InterpTime);
    assignin(dDataSectObj,'Gridmap_Ident',Gridmap_Ident);
    
end

%Save Changes
saveChanges(myDictionaryObj);

%Finish
clc
"Datadict generated successfully! It is located in \frictionmodel\GUI\outputs" %#ok<NOPTS>
