function varargout = Read_CenterlineGUI(varargin)
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Read_CenterlineGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Read_CenterlineGUI_OutputFcn, ...
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
% --- Executes just before Read_CenterlineGUI is made visible.
function Read_CenterlineGUI_OpeningFcn(hObject, eventdata, handles, varargin)
a=get(handles.resolution_slider,'Value');                                           %Get slider value of "global slider"
set(handles.resolution_text,'String',num2str(a));
handles.output = hObject;
guidata(hObject, handles);
% --- Outputs from this function are returned to the command line.
function varargout = Read_CenterlineGUI_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;

% --- Executes on button press in browser_button.
function browser_button_Callback(hObject, eventdata, handles)
[filename, pathname] = uigetfile('*.csv', 'Pick a .csv file');      %Browse for file
handles.fullpathname=strcat(pathname, filename);                    %Connect path name and file name to one string
set(handles.continue_button, 'Enable', 'Inactive');                 %Disable Continue button
data_type=lower(filename(end-2:end));                               %Extract data type and convert to string
if data_type =='csv'                                                 %#ok<BDSCA>
    set(handles.text4, 'String', handles.fullpathname);         %Set GUI.full_path to string fullpathname
    set(handles.continue_button, 'Enable', 'On');                   %Enable Continue button    
else
    set(handles.text4, 'String', 'ERROR');                      %Display "ERROR"
end
guidata(hObject, handles); 

% --- Executes on slider movement.
function resolution_slider_Callback(hObject, eventdata, handles)
a=get(handles.resolution_slider,'Value');                                       %Get slider value of "global slider"
a=round(a*20)/20;                                                               %Round value of "global slider" to 1/50
set(handles.resolution_slider,'Value', a);                                          %Set slider value of "global slider" to rounded value
set(handles.resolution_text,'String',num2str(a));                                   %Set text above "global slider" to slider value

% --- Executes during object creation, after setting all properties.
function resolution_slider_CreateFcn(hObject, eventdata, handles) %#ok<*INUSD,*DEFNU>
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

function edit1_Callback(hObject, eventdata, handles)
% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in continue_button.
function continue_button_Callback(hObject, eventdata, handles) %#ok<*INUSL>
name=get(handles.edit1, 'String');
if name == ""
    set(handles.edit1,'String','ERROR');
elseif name == "ERROR"
    set(handles.edit1,'String','ERROR');
else
    assignin ('base', 'path_centerline', handles.fullpathname);         %Assignin referenceline path to workspace
    resolution=get(handles.resolution_slider,'Value');
    assignin ('base', 'resolution', resolution);
    assignin ('base', 'name', name);
    close(Read_CenterlineGUI);                                                    %Close GUI
    Track_Creation;
end
