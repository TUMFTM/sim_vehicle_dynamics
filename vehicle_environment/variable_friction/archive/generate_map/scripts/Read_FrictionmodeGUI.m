function varargout = Read_FrictionmodeGUI(varargin)
% Last Modified by GUIDE v2.5 11-Feb-2019 18:03:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Read_FrictionmodeGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Read_FrictionmodeGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before Read_FrictionmodeGUI is made visible.
function Read_FrictionmodeGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% Choose default command line output for Read_FrictionmodeGUI
handles.output = hObject;
a=get(handles.global_slider,'Value');                                           %Get slider value of "global slider"
set(handles.global_text,'String',num2str(a));                                   %Set text above "global slider" to slider value
set(findall(handles.random_panel1, '-property', 'enable'),'enable', 'off');     %Disable Random_panel1 
set(findall(handles.random_panel2, '-property', 'enable'),'enable', 'off');     %Disable Random_panel2
set(findall(handles.raceline_panel, '-property', 'enable'),'enable', 'off');    %Disable Raceline_panel
set(findall(handles.uipanel10, '-property', 'enable'),'enable', 'off');         %Disable Raceline percentage mode panel
handles.another_map_1=0;                                                        %Set default value of "another_map" to "0"
% Update handles structure
guidata(hObject, handles);

% --- Outputs from this function are returned to the command line.
function varargout = Read_FrictionmodeGUI_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;

% --- Executes on button press in global_button.
function global_button_Callback(hObject, eventdata, handles)
set(handles.raceline_pathname, 'String', '');                                   %Set raceline pathname to none
set(handles.random_text1,'String','');                                          %Set text above "random slider1" to none
set(handles.random_text2,'String','');                                          %Set text above "random slider2" to none
set(handles.slider1_text2,'String','');                                         %Set text above "raceline slider1" to none
set(handles.slider2_text2,'String','');                                         %Set text above "raceline slider2" to none
cla(handles.axes1);                                                             %Clear axes1
set(findall(handles.global_panel, '-property', 'enable'),'enable', 'on');       %Enable Global panel
set(handles.checkbox, 'Enable','on');                                           %Enable Checkbox of Raceline Percentage Mode
set(findall(handles.random_panel1, '-property', 'enable'),'enable', 'off');     %Disable Random_panel1
set(findall(handles.random_panel2, '-property', 'enable'),'enable', 'off');     %Disable Random_panel2
set(findall(handles.raceline_panel, '-property', 'enable'),'enable', 'off');    %Disable Raceline_panel
a=get(handles.global_slider,'Value');                                           %Get slider value of "global slider"
set(handles.global_text,'String',num2str(a));                                   %Set text above "global slider" to slider value

% --- Executes on button press in random_button.
function random_button_Callback(hObject, eventdata, handles) 
set(handles.raceline_pathname, 'String', '');                                   %Set raceline pathname to none
set(handles.global_text,'String','');                                           %Set text above "global slider" to none
set(handles.slider1_text2,'String','');                                         %Set text above "raceline slider1" to none
set(handles.slider2_text2,'String','');                                         %Set text above "raceline slider2" to none
cla(handles.axes1);                                                             %Clear axes1
set(findall(handles.global_panel, '-property', 'enable'),'enable', 'off');      %Disable Global panel
set(handles.checkbox, 'Enable','on');                                           %Enable Checkbox of Raceline Percentage Mode
set(findall(handles.random_panel1, '-property', 'enable'),'enable', 'on');      %Enable Random_panel1
set(findall(handles.random_panel2, '-property', 'enable'),'enable', 'on');      %Enable Random_panel2
set(findall(handles.raceline_panel, '-property', 'enable'),'enable', 'off');    %Disable Raceline_panel
a=get(handles.random_slider1,'Value');                                          %Get slider value of "random slider1"
b=get(handles.random_slider2,'Value');                                          %Get slider value of "random slider2"
set(handles.random_text1,'String',num2str(a));                                  %Set text above "random slider1" to slider value
set(handles.random_text2,'String',num2str(b));                                  %Set text above "random slider2" to slider value

% --- Executes on button press in raceline_button.
function raceline_button_Callback(hObject, eventdata, handles)
set(findall(handles.global_panel, '-property', 'enable'),'enable', 'off');      %Disable Global panel
set(handles.checkbox, 'Value', 0);                                              %Set Checkbox Value to "0"
checkbox_Callback(handles.checkbox, eventdata, handles);                        %Run Checkbox_Callback
set(handles.checkbox, 'Enable','off');                                          %Disable Checkbox of Raceline Percentage Mode
set(handles.raceline_pathname_percent,'String','');                             %Set raceline_pathname_percent to none
set(findall(handles.random_panel1, '-property', 'enable'),'enable', 'off');     %Disable Random_panel1
set(findall(handles.random_panel2, '-property', 'enable'),'enable', 'off');     %Disable Random_panel2
set(findall(handles.raceline_panel, '-property', 'enable'),'enable', 'on');     %Enable Raceline_panel
set(handles.global_text,'String','');                                           %Set text above "global slider" to none
set(handles.random_text1,'String','');                                          %Set text above "random slider1" to none
set(handles.random_text2,'String','');                                          %Set text above "random slider2" to none
a=get(handles.raceline_slider1,'Value');                                        %Get slider value of "raceline slider1"
b=get(handles.raceline_slider2,'Value');                                        %Get slider value of "raceline slider2"
set(handles.slider1_text2,'String',num2str(a));                                 %Set text above "raceline slider1" to slider value
set(handles.slider2_text2,'String',num2str(b));                                 %Set text above "raceline slider2" to slider value
x=-6:0.1:6;                                                                     %Generate array
y=a*exp(-b*0.1*x.^2);                                                           %Generate function value
plot(handles.axes1,x,y)                                                         %Plot function
set(handles.axes1, 'Xlim', [-6,6]);                                             %Set x-limits to [-6,6]

% --- Executes on button press in checkbox.
function checkbox_Callback(hObject, eventdata, handles)
if get(handles.checkbox, 'Value')==1                                            %If checkbox is activated: Enable all features!
    set(findall(handles.uipanel10, '-property', 'enable'),'enable', 'on');      %Enable Raceline percentage mode panel
    set(handles.browse3_button, 'Enable', 'On');                                %Enable Raceline percentage mode browser button
    set(handles.percent_value, 'Enable', 'On');                                 %Enable Raceline percentage mode Value Text 
elseif get(handles.checkbox, 'Value')==0                                        %If checkbox is not activated: Disable all features!
    set(findall(handles.uipanel10, '-property', 'enable'),'enable', 'off');     %Disable Raceline percentage mode panel
    set(handles.browse3_button, 'Enable', 'Off');                               %Disable Raceline percentage mode browser button
    set(handles.percent_value, 'Enable', 'Off');                                %Disable Raceline percentage mode Value Text
end  

% --- Executes on slider movement.
function raceline_slider1_Callback(hObject, eventdata, handles)
a=get(handles.raceline_slider1,'Value');                                        %Get slider value of "raceline slider1"
b=get(handles.raceline_slider2,'Value');                                        %Get slider value of "raceline slider2"
a=round(a*100)/100;                                                             %Round value of "raceline slider1" to 1/100
set(handles.raceline_slider1,'Value', a);                                       %Set slider value of "raceline slider1" to rounded value
set(handles.slider1_text2,'String',num2str(a));                                 %Set text above "raceline slider1" to slider value
x=-6:0.1:6;                                                                     %Generate array
y=a*exp(-b*0.1*x.^2);                                                           %Generate function value
plot(handles.axes1,x,y)                                                         %Plot function
set(handles.axes1, 'Xlim', [-6,6]);                                             %Set x-limits to [-6,6]

% --- Executes during object creation, after setting all properties.
function raceline_slider1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function raceline_slider2_Callback(hObject, eventdata, handles)
a=get(handles.raceline_slider1,'Value');                                        %Get slider value of "raceline slider1"
b=get(handles.raceline_slider2,'Value');                                        %Get slider value of "raceline slider2"
b=round(b*100)/100;                                                             %Round value of "raceline slider2" to 1/100
set(handles.raceline_slider2,'Value', b);                                       %Set slider value of "raceline slider2" to rounded value
set(handles.slider2_text2,'String',num2str(b));                                 %Set text above "raceline slider2" to slider value
x=-6:0.1:6;                                                                     %Generate array
y=a*exp(-b*0.1*x.^2);                                                           %Generate function value
plot(handles.axes1,x,y)                                                         %Plot function
set(handles.axes1, 'Xlim', [-6,6]);                                             %Set x-limits to [-6,6]

% --- Executes during object creation, after setting all properties.
function raceline_slider2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function random_slider1_Callback(hObject, eventdata, handles)
a=get(handles.random_slider1,'Value');                                          %Get slider value of "random slider1"
a=round(a*50)/50;                                                               %Round value of "random slider1" to 1/50
set(handles.random_slider1,'Value', a);                                         %Set slider value of "random slider1" to rounded value
set(handles.random_text1,'String',num2str(a));                                  %Set text above "random slider1" to slider value

% --- Executes during object creation, after setting all properties.
function random_slider1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function random_slider2_Callback(hObject, eventdata, handles)
a=get(handles.random_slider2,'Value');                                          %Get slider value of "random slider2"
a=round(a*50)/50;                                                               %Round value of "random slider2" to 1/50
set(handles.random_slider2,'Value', a);                                         %Set slider value of "random slider2" to rounded value
set(handles.random_text2,'String',num2str(a));                                  %Set text above "random slider2" to slider value

% --- Executes during object creation, after setting all properties.
function random_slider2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function global_slider_Callback(hObject, eventdata, handles)
a=get(handles.global_slider,'Value');                                           %Get slider value of "global slider"
a=round(a*50)/50;                                                               %Round value of "global slider" to 1/50
set(handles.global_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.global_text,'String',num2str(a));                                   %Set text above "global slider" to slider value

% --- Executes during object creation, after setting all properties.
function global_slider_CreateFcn(hObject, eventdata, handles) %#ok<*DEFNU,*INUSD>
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on button press in browse2_button.
function browse2_button_Callback(hObject, eventdata, handles)
[filename2, pathname2] = uigetfile('*.csv', 'Pick a .csv file');                    %Browse for file
handles.pathname_raceline = strcat(pathname2, filename2);                           %Connect path name and file name to one string 
data_type=lower(filename2(end-2:end));                                              %Extract data type and convert to string
if data_type =='csv'                                                 %#ok<*BDSCA>
    set(handles.raceline_pathname, 'String', handles.pathname_raceline);            %Set GUI.full_path to string fullpathname
else
    set(handles.raceline_pathname, 'String', 'ERROR');                              %Display "ERROR"
end
guidata(hObject, handles);

% --- Executes on button press in browse3_button.
function browse3_button_Callback(hObject, eventdata, handles)
[filename3, pathname3] = uigetfile('*.csv', 'Pick a .csv file');                                %Browse for file
handles.raceline_pathname_percent_name = strcat(pathname3, filename3);                          %Connect path name and file name to one string 
data_type=lower(filename3(end-2:end));                                                          %Extract data type and convert to string
if data_type =='csv'                                                 %#ok<*BDSCA>
    set(handles.raceline_pathname_percent, 'String', handles.raceline_pathname_percent_name);   %Set GUI.full_path to string fullpathname
else
    set(handles.raceline_pathname_percent, 'String', 'ERROR');                                  %Display "ERROR"
end
guidata(hObject, handles);

function percent_value_Callback(hObject, eventdata, handles)

% --- Executes during object creation, after setting all properties.
function percent_value_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in create_2_map_button.
function create_2_map_button_Callback(hObject, eventdata, handles)
handles.another_map_1=1;                                                            %Set value of "another_map" to "1"
create_map_button_Callback(handles.create_map_button, eventdata, handles);          %Run create_map_button_Callback

% --- Executes on button press in create_map_button.
function create_map_button_Callback(hObject, eventdata, handles) %#ok<*INUSL>
if handles.another_map_1==1                                                         %if "another_map" =1
    assignin('base', 'another_map', 1);                                             %Handover "another_map"==1 to base workspace
else
    assignin('base', 'another_map', 0);                                             %Handover "another_map"==0 to base workspace
end
a=0;                                                                                %Initialize a consistency check variable
%Check Raceline_percentage_panel on consistency
if get(handles.checkbox, 'Value')==1                                                %If Checkbox for Raceline Percentage Mode is activated
    d=str2double(get(handles.percent_value, 'String'));                                 %Get Raceline Percentage Value
    if d>-99 && d<99                                                                    %If Raceline Percentage Value is consistent
        path_percent = get(handles.raceline_pathname_percent, 'String');                    %Get Raceline Percentage Pathname
        if strcmp(path_percent, "") || strcmp(path_percent,'ERROR')                         %If Pathname is not consistent
            set(handles.raceline_pathname_percent, 'String', 'ERROR');                          %Set Raceline Percentage Pathname to "ERROR"  
        else                                                                                %Else (if pathname is consistent)
            assignin('base', 'raceline_percentage_mode', 1);                                    %Handover a positive ("1") raceline percentage mode
            assignin('base', 'raceline_percent_value', d);                                      %Handover the Raceline Percentage value
            assignin('base', 'path_raceline', path_percent);                                    %Handover Raceline Path
            a=1;                                                                                %Set Consistency Check Variable to "1"
        end                
    else                                                                                %Else (if raceline percentage value is not consistent)
        set(handles.percent_value, 'String', 'ERROR')                                       %Set Raceline Percentage value to "ERROR"
    end 
else                                                                                %Else (if checkbox for Raceline Percentage Mode is not activated)
    assignin('base', 'raceline_percentage_mode', 0);                                    %Handover a negative ("0") raceline percentage mode
    a=1;                                                                                %Set Consistency Check Variable to "1"
end
%End of Consistency Check: a=0: not consistent, a=1: consistent
% If everything is consistent, GUI continues 
if a==1
    if get(handles.global_button,'Value')                                   %If Global_Button is activated
        global_value=get(handles.global_slider,'Value');                        %Get slider value of "global slider"    
        assignin('base', 'global_value', global_value);                         %Handover "global value" to base workspace
        assignin('base', 'mode', 'global');                                     %Handover "mode" to base workspace
        close(Read_FrictionmodeGUI);                                                      %Close Read_FrictionmodeGUI
        Friction_Map_Creation();                                                %Run Friction_Map_Creation 
    elseif get(handles.random_button,'Value')                               %If Random_Button is activated
        random_value_1=get(handles.random_slider1,'Value');                     %Get slider value of "random slider1"
        random_value_2=get(handles.random_slider2,'Value');                     %Get slider value of "random slider2"
        if random_value_1<random_value_2                                        %if slider values are consistent
            assignin('base', 'random_value_1', random_value_1);                     %Handover "random value1" to base workspace
            assignin('base', 'random_value_2', random_value_2);                     %Handover "random value2" to base workspace
            assignin('base', 'mode', 'random');                                     %Handover "mode" to base workspace
            close(Read_FrictionmodeGUI);                                                      %Close Read_FrictionmodeGUI
            Friction_Map_Creation();                                                %Run Friction_Map_Creation
        else                                                                    %else (if slider values are not consistent)
            set(handles.random_text1, 'String', '');                                %Set text above "random slider1" to none 
            set(handles.random_text2, 'String', '');                                %Set text above "random slider2" to none
        end    
    elseif get(handles.raceline_button,'Value')                             %If Raceline_Button is activated
        path = get(handles.raceline_pathname, 'String');                        %Get Raceline Pathname
        if strcmp(path, "")                                                     %If Raceline Pathname is none
            set(handles.raceline_pathname, 'String', 'ERROR');                      %Set Raceline Pathname to "ERROR"
        elseif strcmp(path,'ERROR')                                             %If Raceline Pathname is "ERROR"
            set(handles.raceline_pathname, 'String', 'ERROR');                      %Set Raceline Pathname to "ERROR"
        else                                                                    %else (if Raceline Pathname is consistent)
            a=get(handles.raceline_slider1,'Value');                                %Get slider value of "raceline slider1"
            b=get(handles.raceline_slider2,'Value');                                %Get slider value of "raceline slider2"
            assignin('base', 'raceline_value_1', a);                                %Handover "raceline value1" to base workspace
            assignin('base', 'raceline_value_2', b);                                %Handover "raceline value2" to base workspace
            assignin('base', 'mode', 'raceline');                                   %Handover "mode" to base workspace
            assignin('base','path_raceline', handles.pathname_raceline);            %Handover Path Raceline
            close(Read_FrictionmodeGUI);                                                      %Close Read_FrictionmodeGUI
            Friction_Map_Creation();                                                %Run Friction_Map_Creation
        end    
    end
end
