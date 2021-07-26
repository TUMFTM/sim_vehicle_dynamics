%% manage paths

path_dict = manage_paths();

path2module = path_dict(1);
path2matlabcode_folder = path_dict(2);
path2input = path_dict(3);
path2output = path_dict(4);

%%
%Handover "mode", "another_map", "raceline_percentage_mode" & "raceline_percent_value" from Workspace
mode=evalin('base', 'mode');
another_map=evalin('base', 'another_map');
centerline_mode=evalin('base', 'centerline_mode');
raceline_percentage_mode=evalin('base', 'raceline_percentage_mode');
if raceline_percentage_mode==1
    raceline_percent_value=evalin('base', 'raceline_percent_value');
end
%Import Track file
if centerline_mode==1
    name=evalin('base','name');
    res_centerline_mode=evalin('base','resolution');
    track=importdata(strcat(path2output,'\tracks\Track_',name,'_',strrep((num2str(res_centerline_mode)),'.','-'),'.mat'));
    map_name=[name,'_',strrep((num2str(res_centerline_mode)),'.','-')];
else
    path_track=evalin('base','path_track');
    filename=evalin('base', 'filename');
    track=importdata(path_track);
    map_name=filename(7:end-4);
end
 
%Convert track to double
track=double(track);

%Get size of track_limits_filled file
pixelwidth_x=size(track,2);
pixelwidth_y=size(track,1);
if pixelwidth_x>=pixelwidth_y
    pixelwidth=pixelwidth_x;
else 
    pixelwidth=pixelwidth_y;
end

%Extract origin of coordinates from track_limits_filled file
x_min_lim=track(1,1);
x_max_lim=track(1,2);
y_min_lim=track(2,1);
y_max_lim=track(2,2);

%Generate x-y-range array
x_lim=[x_min_lim x_max_lim];
y_lim=[y_min_lim y_max_lim];

%Generate parameter for random mode depending on size of track_limits_filled.pgm file
rand_n=round(pixelwidth/113)+1;

%Extract resolution of Map
resolution=track(1,3)/100;

%Generate origin of coordinates Array
limits=[x_min_lim x_max_lim ; y_min_lim y_max_lim ];

%Delete origin information
track(1:2,1:3)=0;
%Calculate raceline mode "normal" and "percentage"
if strcmp(mode,'raceline') || raceline_percentage_mode ==1
        %Handover Raceline Path from base workspace
        path_raceline=evalin('base','path_raceline');
        %Read in Raceline
        fid=fopen(path_raceline,'r');
        exportraceline=textscan(fid, '%f %f %f %f %f %f %f', 'Headerlines', 3, 'delimiter', ';');
        %exportraceline=textscan(fid, '%f %f', 'Headerlines', 2, 'delimiter', ';');
        fclose(fid);
        %Separate Columns of Raceline file, short file and get size
        x_0_race=exportraceline{:,2};
        y_0_race=exportraceline{:,3};
        intervall=round(size(x_0_race,1)/300);
        x_0_race=x_0_race(1:intervall:end,:);
        y_0_race=y_0_race(1:intervall:end,:);
        height=size(x_0_race,1);
        %Calculate gradients and normals of all points
        m_tang_race=gradient(y_0_race,x_0_race);
        m_normal_race= (-1./m_tang_race);
        %Calculate X and Y-component of displacement of 2 meters
        x_komp_2m=sqrt((2^2)./((1+m_normal_race.^2)));
        y_komp_2m=m_normal_race.*x_komp_2m;
        %Get variables from base workspace
        if strcmp(mode,'raceline')
            raceline_value_1=evalin('base', 'raceline_value_1');
            raceline_value_2=evalin('base', 'raceline_value_2');
        elseif raceline_percentage_mode==1
            raceline_value_1=1+raceline_percent_value/100;
            if raceline_value_1<1
                raceline_value_2=-0.03;
            else
                raceline_value_2=0.03;
            end    
        end    
        %Calculate new coordinates with distance of 0m, 4m and 10 meters
        xyz_0m=[x_0_race y_0_race raceline_value_1*ones(height,1)];
        xyz_4m_plus= [x_0_race+2*(x_komp_2m) y_0_race+2*(y_komp_2m) raceline_value_1*exp(-raceline_value_2*0.1*4^2)*ones(height,1)];
        xyz_4m_minus= [x_0_race-2*(x_komp_2m) y_0_race-2*(y_komp_2m) raceline_value_1*exp(-raceline_value_2*0.1*4^2)*ones(height,1)];
        xyz_10m_plus= [x_0_race+5*(x_komp_2m) y_0_race+5*(y_komp_2m) raceline_value_1*exp(-raceline_value_2*0.1*10^2)*ones(height,1)];
        xyz_10m_minus= [x_0_race-5*(x_komp_2m) y_0_race-5*(y_komp_2m) raceline_value_1*exp(-raceline_value_2*0.1*10^2)*ones(height,1)];
        xyz=[xyz_0m;xyz_4m_plus;xyz_4m_minus;xyz_10m_plus;xyz_10m_minus];
        
        %Calculate conversion factors coordinates <-> pixels
        x_change=(pixelwidth_x/(abs(x_lim(1))+abs(x_lim(2))));
        y_change=(pixelwidth_y/(abs(y_lim(1))+abs(y_lim(2))));
        
        %Generate intervall in coordination space
        x_intervall=linspace(x_change*x_lim(1),x_change*x_lim(2),pixelwidth_x);
        y_intervall=linspace(y_change*y_lim(1),y_change*y_lim(2),pixelwidth_y);
        y_intervall=y_intervall(:);
        
        %Interpolate points in mesh
        [X,Y,Z]= griddata(x_change*xyz(:,1), y_change*xyz(:,2), xyz(:,3),x_intervall, y_intervall, 'cubic');
        Z=flipud(Z);
        %if raceline mode
        if strcmp(mode,'raceline')
            Z(isnan(Z))=0;
            Z(Z<0)=0;
        %if raceline percentage mode
        elseif raceline_percentage_mode==1
            Z(isnan(Z))=1;
            if raceline_value_1>1
                Z(Z<1)=1;
            else
                Z(Z>1)=1;
            end    
        end           
end

%Handover of other variables from Workspace depending on mode
%Insert origin of coordinates information and save file
currentFolder=cd;
switch mode
    case 'global'
         global_value=evalin('base', 'global_value');
         result=track.*global_value*100;
         if raceline_percentage_mode==1
             result=result.*Z;
         end
         result=int16(round(result));
         surf(result,'EdgeColor','none');
         set(gca,'YDir', 'reverse');
         set(gca,'XLim',[0, pixelwidth_x],'XTick',[0 pixelwidth_x]);
         set(gca,'YLim',[0, pixelwidth_y],'YTick',[0 pixelwidth_y]);
         view([0 90]);
         caxis([0 global_value*100+20]);
         colorbar
         result(1:2,1:2)=limits;
         result(1,3)=resolution*100;
         if raceline_percentage_mode==1
%             save([currentFolder,'\frictionmap_tools\matlab_code\outputs\maps\Map_',map_name,'Meter_Global_',strrep((num2str(global_value)),'.','-'),'_Raceline_', strrep((num2str(raceline_percent_value)),'.','-'),'_Percent.mat'], 'result');
            save([currentFolder,'\variable_friction\generate_map\outputs\maps\Map_',map_name,'Meter_Global_',strrep((num2str(global_value)),'.','-'),'_Raceline_', strrep((num2str(raceline_percent_value)),'.','-'),'_Percent.mat'], 'result');
         else
%             save([currentFolder,'\frictionmap_tools\matlab_code\outputs\maps\Map_',map_name,'Meter_Global_',strrep((num2str(global_value)),'.','-'),'.mat'], 'result');
            save([currentFolder,'\variable_friction\generate_map\outputs\maps\Map_',map_name,'Meter_Global_',strrep((num2str(global_value)),'.','-'),'.mat'], 'result');
         end
    case 'random'
         random_value_1=evalin('base', 'random_value_1');
         random_value_2=evalin('base', 'random_value_2');
         A=rand(rand_n);
         B=A.*(random_value_2-random_value_1)+random_value_1;
         C=interp2(B,7,'cubic',0);
         D=C(1:pixelwidth_y,1:pixelwidth_x);
         result=D.*track*100;
         if raceline_percentage_mode==1
             result=result.*Z;
         end
         result=int16(round(result));
         surf(result,'EdgeColor','none');
         set(gca,'YDir', 'reverse');
         set(gca,'XLim',[0, pixelwidth_x],'XTick',[0 pixelwidth_x]);
         set(gca,'YLim',[0, pixelwidth_y],'YTick',[0 pixelwidth_y]);
         caxis([random_value_1*100-20 random_value_2*100+20]);
         colorbar
         view([0 90]);
         result(1:2,1:2)=limits;
         result(1,3)=resolution*100;
         if raceline_percentage_mode==1
             save(strcat(path2output,'\maps\Map_',map_name,'Meter_Random_',strrep((num2str(random_value_1)),'.','-'),'_',strrep((num2str(random_value_2)),'.','-'),'_Raceline_', strrep((num2str(raceline_percent_value)),'.','-'),'_Percent.mat'), 'result');
         else
             save(strcat(path2output,'\maps\Map_',map_name,'Meter_Random_',strrep((num2str(random_value_1)),'.','-'),'_',strrep((num2str(random_value_2)),'.','-'),'.mat'), 'result');
         end    
    case 'raceline'
        result=Z.*track*100;
        result=int16(round(result));
        surf(result,'EdgeColor','none');
        set(gca,'YDir', 'reverse');
        set(gca,'XLim',[0, pixelwidth_x],'XTick',[0 pixelwidth_x]);
        set(gca,'YLim',[0, pixelwidth_y],'YTick',[0 pixelwidth_y]);
        view([0 90]);
        caxis([0 raceline_value_1*100]);
        colorbar
        result(1:2,1:2)=limits;
        result(1,3)=resolution*100;
        save([path2output, '\maps\Map_',map_name,'Meter_Raceline_',strrep((num2str(raceline_value_1)),'.','-'),'_',strrep((num2str(raceline_value_2)),'.','-'),'.mat'], 'result');
end
%If another_map==1, run Read_FrictionmodeGUI again
if another_map==1
    Read_FrictionmodeGUI();
    clc
    "Friction Coefficient Map(s) generated successfully!" %#ok<NOPTS>
elseif another_map==0  
    clc
    "Friction Coefficient Map(s) generated successfully!" %#ok<NOPTS>
    evalin('base','clear');
end
