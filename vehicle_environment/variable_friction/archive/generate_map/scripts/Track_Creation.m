%% manage paths

path_dict = manage_paths();

path2module = path_dict(1);
path2matlabcode_folder = path_dict(2);
path2input = path_dict(3);
path2output = path_dict(4);


%% -------------------------------------------------
% Start of Part 1: Einlesen & Parametrisierung

%Handover Referenceline path and resolution from base workspace
path_centerline=evalin('base', 'path_centerline');
resolution=evalin('base','resolution');
name=evalin('base','name');

%Import referenceline-.csv file
centerlinegmap=importfile(path_centerline);

%Separate different columns
x_0=centerlinegmap{:,1};
y_0=centerlinegmap{:,2};
%d=centerlinegmap{:,3};
d_rechts=centerlinegmap{:,3};
d_links=centerlinegmap{:,4};

% End of Part 1: Einlesen & Parametrisierung
%-------------------------------------------------
%-------------------------------------------------
% Start of Part 2: Berechnung

%Calculate distance between first and last point
x_distance=x_0(1)-x_0(end);
y_distance=y_0(1)-y_0(end);
xy_distance=sqrt(x_distance^2+y_distance^2);

%Calculate gradients of all points
m_tang=gradient(y_0,x_0);

%Calculate normal of all points
    %"." behind 1 means "componentwise"
m_normal= (-1./m_tang);

%Calculate X-component of displacement
%x_komp=sqrt((d.^2)./(4*(1+m_normal.^2)));
x_komp_links=sqrt((d_links.^2)./(1+m_normal.^2));
x_komp_rechts=sqrt((d_rechts.^2)./(1+m_normal.^2));

%Number of points 
l=size(x_0,1);

%Calculate 2nd derivation for orientation of curves (right/left)
curve_pos_x=gradient(x_0);
curve_pos_y=gradient(y_0);

%Initialize new coordinates
x_neu_links=zeros(l,1);
y_neu_links=zeros(l,1);
x_neu_rechts=zeros(l,1);
y_neu_rechts=zeros(l,1);

%Calculate new coordinates
for i=1:l
    if curve_pos_y(i) < 0
    	x_neu_links(i)=x_0(i)+ x_komp_links(i);
        y_neu_links(i)=y_0(i)+  m_normal(i)*x_komp_links(i);
        x_neu_rechts(i)=x_0(i)- x_komp_rechts(i);
        y_neu_rechts(i)=y_0(i)- m_normal(i)*x_komp_rechts(i);
    elseif curve_pos_y(i) > 0
        x_neu_links(i)=x_0(i)- x_komp_links(i);
        y_neu_links(i)=y_0(i)- m_normal(i)*x_komp_links(i);
        x_neu_rechts(i)=x_0(i)+ x_komp_rechts(i);
        y_neu_rechts(i)=y_0(i)+ m_normal(i)*x_komp_rechts(i);
    elseif curve_pos_y(i)==0
        x_neu_links(i)=x_0(i);
        x_neu_rechts(i)=x_0(i);
            if y_neu_links(i-1)-y_0(i)<0
                y_neu_links(i)=y_0(i)- d_links(i);
                y_neu_rechts(i)=y_0(i)+ d_rechts(i);
            elseif y_neu_links(i-1)-y_0(i)>0    
                y_neu_links(i)=y_0(i)+ d_links(i);
                y_neu_rechts(i)=y_0(i)- d_rechts(i);
            end    
    end      
end

% End of Part 2: Berechnung
%-------------------------------------------------
%-------------------------------------------------
% Start of Part 3: Visualisierung & Speicherung

%Plot track and save it
    %Initialize plot
    hold on
    grid on
    axis equal
    set(gca,'Visible','off','Position',[0 0 1 1]);
    set(gcf,'Visible', 'on');
    %Set range and axis ticks
    x_range_max=ceil(max(max([x_neu_rechts,x_neu_links]))/50)*50;
    if x_range_max-max(max([x_neu_rechts,x_neu_links]))<20
        x_range_max=x_range_max+50;
    end
    x_range_min=floor(min(min([x_neu_rechts,x_neu_links]))/50)*50;
    if x_range_min-min(min([x_neu_rechts,x_neu_links]))>-20
        x_range_min=x_range_min-50;
    end 
    y_range_max=ceil(max(max([y_neu_rechts,y_neu_links]))/50)*50;
    if y_range_max-max(max([y_neu_rechts,y_neu_links]))<20
        y_range_max=y_range_max+50;
    end
    y_range_min=floor(min(min([y_neu_rechts,y_neu_links]))/50)*50;
    if y_range_min-min(min([y_neu_rechts,y_neu_links]))>-20
        y_range_min=y_range_min-50;
    end 
    xlim([x_range_min x_range_max]);
    ylim([y_range_min y_range_max]);
    set(gca,'XTick',(x_range_min : 50 : x_range_max));
    set(gca,'YTick',(y_range_min : 50 : y_range_max));
    %Plot curves
        %plot([x_0;x_0(1)],[y_0;y_0(1)],'-r')
        if xy_distance<20
            plot([x_neu_links;x_neu_links(1)],[y_neu_links;y_neu_links(1)], 'k')
            plot([x_neu_rechts;x_neu_rechts(1)],[y_neu_rechts;y_neu_rechts(1)], 'k')
        else
            x_neu_rechts=flipud(x_neu_rechts);
            y_neu_rechts=flipud(y_neu_rechts);
            plot([x_neu_links;x_neu_rechts;x_neu_links(1)],[y_neu_links;y_neu_rechts;y_neu_links(1)], 'k')
        end
    %Print out Range
    x_range=xlim;
    y_range=ylim;
    %Adjust figure to right resolution, save and close it
    x_range_value=x_range_max-x_range_min;
    y_range_value=y_range_max-y_range_min;
    pixelwidth_x=round(x_range_value/resolution);
    pixelwidth_y=round(y_range_value/resolution);
    if x_range_value>y_range_value
        if (pixelwidth_x/pixelwidth_y)>=1.66
            set(gcf,'Units','pixels','Position',[20 60 1000 1000*(pixelwidth_y/pixelwidth_x)]);
        else
            set(gcf,'Units','pixels','Position',[20 60 600*(pixelwidth_x/pixelwidth_y) 600]);
        end
    else
        set(gcf,'Units','pixels','Position',[20 60 600*(pixelwidth_x/pixelwidth_y) 600]);
    end
    track_limits=frame2im(getframe(gcf));
    track_limits=imresize(track_limits, [pixelwidth_y, pixelwidth_x], 'bilinear');
    track_limits_resize=track_limits(:,:,1);
    track_limits_resize(track_limits_resize==0)=100;
    track_limits_resize(track_limits_resize>238)=0;
    track_limits_0_1=logical(track_limits_resize);
    close gcf
    
%Calculate coordinate inside the track. Therefore use fifth point of reference line
%Coordinates converted to pixels
track_limits_x=round((x_0(5)-x_range(1))/resolution);
track_limits_y=round((y_range(2)-y_0(5))/resolution);
%Fill track with "1"
track_limits_filled=imfill(track_limits_0_1, [track_limits_y track_limits_x],4);
track=int16(track_limits_filled);
    
% End of Part 3: Visualisierung & Speicherung
%-------------------------------------------------
%-------------------------------------------------
% Start of Part 4: Einbringen der Koordinatenursprungsinformation   

%Fill coordinate information
track(1,1:2)=x_range;
track(2,1:2)=y_range;
track(1,3)=int16(resolution*100);
currentFolder=cd;
save(strcat(path2output,'\tracks\Track_',name,'_',strrep((num2str(resolution)),'.','-'),'.mat'),'track');
% End of Part 4: Einbringen der Koordinatenursprungsinformation
%-------------------------------------------------   
    
%Delete track-limits.pgm file
assignin('base','centerline_mode',1);
clc
"Track generated successfully! Click in 'Command Window' and press any key to continue." %#ok<NOPTS>
pause;
Read_FrictionmodeGUI();
