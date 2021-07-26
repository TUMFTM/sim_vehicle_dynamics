function varargout = Read_MapGUI(varargin)
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Read_MapGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Read_MapGUI_OutputFcn, ...
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
% --- Executes just before Read_MapGUI is made visible.
function Read_MapGUI_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
guidata(hObject, handles);
% --- Outputs from this function are returned to the command line.
function varargout = Read_MapGUI_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;

% --- Executes on button press in browser_button.
function browser_button_Callback(hObject, eventdata, handles)
[filename, pathname] = uigetfile('*.mat', 'Pick a .mat file');      %Browse for file
handles.fullpathname=strcat(pathname, filename);                    %Connect path name and file name to one string
handles.filename=filename;
set(handles.continue_button, 'Enable', 'Inactive');                 %Disable Continue button
data_type=lower(filename(end-2:end));                               %Extract data type and convert to string
if data_type =='mat'                                                 %#ok<BDSCA>
    set(handles.text4, 'String', handles.fullpathname);         %Set GUI.full_path to string fullpathname
    if filename(1:5)=="Track"
        set(handles.text4, 'String', 'ERROR');
    else
        set(handles.continue_button, 'Enable', 'On');                   %Enable Continue button    
    end
else
    set(handles.text4, 'String', 'ERROR');                      %Display "ERROR"
end
guidata(hObject, handles); 

% --- Executes on slider movement.
function yellow_slider_Callback(hObject, eventdata, handles)
a=get(handles.yellow_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*100)/100;                                                               %Round value of "global slider" to 1/50
set(handles.yellow_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.text_yellow,'String',num2str(a));                                   %Set text above "global slider" to slider value
% --- Executes during object creation, after setting all properties.
function yellow_slider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function green_slider_Callback(~, eventdata, handles)
a=get(handles.green_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*100)/100;                                                               %Round value of "global slider" to 1/50
set(handles.green_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.text_green,'String',num2str(a));                                   %Set text above "global slider" to slider value
% --- Executes during object creation, after setting all properties.
function green_slider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function blue_slider_Callback(hObject, eventdata, handles)
a=get(handles.blue_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*100)/100;                                                               %Round value of "global slider" to 1/50
set(handles.blue_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.text_blue,'String',num2str(a));                                   %Set text above "global slider" to slider value
% --- Executes during object creation, after setting all properties.
function blue_slider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function red_slider_Callback(hObject, eventdata, handles)
a=get(handles.red_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*100)/100;                                                               %Round value of "global slider" to 1/50
set(handles.red_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.text_red,'String',num2str(a));                                   %Set text above "global slider" to slider value
% --- Executes during object creation, after setting all properties.
function red_slider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function white_slider_Callback(hObject, eventdata, handles)
a=get(handles.white_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*100)/100;                                                               %Round value of "global slider" to 1/50
set(handles.white_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.text_white,'String',num2str(a));                                   %Set text above "global slider" to slider value
% --- Executes during object creation, after setting all properties.
function white_slider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on button press in continue_button.
function continue_button_Callback(~, eventdata, handles) %#ok<*INUSL>
assignin ('base', 'path_map', handles.fullpathname);         %Assignin referenceline path to workspace
assignin ('base', 'filename_map', handles.filename);
yellow=get(handles.yellow_slider,'Value');
green=get(handles.green_slider,'Value');
blue=get(handles.blue_slider,'Value');
red=get(handles.red_slider,'Value');
white=get(handles.white_slider,'Value');
assignin ('base', 'yellow', yellow);
assignin ('base', 'green', green);
assignin ('base', 'blue', blue);
assignin ('base', 'red', red);
assignin ('base', 'white', white);
set(handles.continue_button, 'Enable', 'Off');
set(handles.browser_button, 'Enable', 'Off');
set(findall(handles.uipanel5, '-property', 'enable'),'enable', 'off');
GIMP_Correction;
