%% manage paths

path_dict = manage_paths();

path2module = path_dict(1);
path2matlabcode_folder = path_dict(2);
path2input = path_dict(3);
path2output = path_dict(4);


%%
%Handover Map path and from base workspace
path_map=evalin('base', 'path_map');
filename=evalin('base', 'filename_map');
yellow=evalin('base', 'yellow');
green=evalin('base', 'green');
blue=evalin('base', 'blue');
red=evalin('base', 'red');
white=evalin('base', 'white');
friction_map=importdata(path_map);

%Extract origin of coordinates from friction_map file
x_min_lim=friction_map(1,1);
x_max_lim=friction_map(1,2);
y_min_lim=friction_map(2,1);
y_max_lim=friction_map(2,2);
resolution=friction_map(1,3);
friction_map(1:2,1:3)=0;

%Change Values from Friction Coefficient to Color
friction_map_max=max(max(friction_map));
B=friction_map;
B(B==0)=100;
friction_map_min=min(min(B));
BB=(friction_map+10-friction_map_min);
BB(BB<0)=0;
C=uint16(BB);
D=C.*uint16(65000/(friction_map_max-friction_map_min+10));

%Create RGB Image and save
A = ind2rgb(D, parula(65536));
imwrite(A, strcat(path2output,'\maps_custom\GIMP_Map.png'));

%Clear Command Window, print User Information and pause
clc
ans_user='GIMP Map generated successfully! \nIt is located in /outputs/maps_custom folder as "GIMP_Map.png" \nPlease make your corrections via GIMP and save the file as "GIMP_Map_Custom.png" in the same folder. \nWhen you have finished, click in "Command Window" and press any key to continue. \nThe GUI stays open to check your choosen Friction Coefficients.';
fprintf(ans_user);
pause;

%Import customized GIMP_Map
GIMP_Map=importdata(strcat(path2output,'\maps_custom\GIMP_Map_Custom.png'));
close(Read_MapGUI);
        %Legende:  gelb:  ffff00    Z: 255  ZZ: 255 ZZZ: 0
        %          grün:  00ff00    Z: 0    ZZ: 255 ZZZ: 0
        %          blau:  0000ff    Z: 0    ZZ: 0   ZZZ: 255
        %          rot:   ff0000    Z: 255  ZZ: 0   ZZZ: 0
        %          weiss: ffffff    Z: 255  ZZ: 255 ZZZ: 255
Z=GIMP_Map(:,:,1);
ZZ=GIMP_Map(:,:,2);
ZZZ=GIMP_Map(:,:,3);

friction_map_final=friction_map;
%Change values in friction map according to customized GIMP_Map     
for i=1:size(GIMP_Map,1)
    for j=1:size(GIMP_Map,2)
        if Z(i,j)==255 && ZZ(i,j)==255 && ZZZ(i,j)==0
            friction_map_final(i,j)=yellow*100;
        elseif Z(i,j)==0 && ZZ(i,j)==255 && ZZZ(i,j)==0
            friction_map_final(i,j)=green*100;
        elseif Z(i,j)==0 && ZZ(i,j)==0 && ZZZ(i,j)==255
            friction_map_final(i,j)=blue*100;
        elseif Z(i,j)==255 && ZZ(i,j)==0 && ZZZ(i,j)==0
            friction_map_final(i,j)=red*100;
        elseif Z(i,j)==255 && ZZ(i,j)==255 && ZZZ(i,j)==255
            friction_map_final(i,j)=white*100;
        end
    end
end

%Insert coordinate information
friction_map_final(1,1)=x_min_lim;
friction_map_final(1,2)=x_max_lim;
friction_map_final(2,1)=y_min_lim;
friction_map_final(2,2)=y_max_lim;
friction_map_final(1,3)=resolution;

%Visualize and save map
c=max(max(friction_map_final(3:end,:)));
surf(friction_map_final,'EdgeColor','none');
set(gca,'YDir', 'reverse');
pixelwidth_x=size(Z,2);
pixelwidth_y=size(Z,1);
set(gca,'XLim',[0, pixelwidth_x],'XTick',[0 pixelwidth_x]);
set(gca,'YLim',[0, pixelwidth_y],'YTick',[0 pixelwidth_y]);
view([0 90]);
colorbar
E=friction_map_final;
E(E==0)=100;
d=min(min(E(3:end,:)));
caxis([d-5 c]);
currentFolder=cd;
save(strcat(path2output, '\maps_custom\Custom_', filename), 'friction_map_final');

clc

"Custom GIMP Map generated successfully!" %#ok<NOPTS>
