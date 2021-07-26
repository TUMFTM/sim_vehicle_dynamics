function varargout = Read_TrackGUI(varargin)
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Read_TrackGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Read_TrackGUI_OutputFcn, ...
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
% --- Executes just before Read_TrackGUI is made visible.
function Read_TrackGUI_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
guidata(hObject, handles);
% --- Outputs from this function are returned to the command line.
function varargout = Read_TrackGUI_OutputFcn(hObject, eventdata, handles) 
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
    if filename(1:3)=="Map"
        set(handles.text4, 'String', 'ERROR');
    elseif filename(1:6)=="Custom"
        set(handles.text4, 'String', 'ERROR');    
    else
        set(handles.continue_button, 'Enable', 'On');                   %Enable Continue button    
    end
else
    set(handles.text4, 'String', 'ERROR');                      %Display "ERROR"
end
guidata(hObject, handles); 


% --- Executes on button press in continue_button.
function continue_button_Callback(~, eventdata, handles) %#ok<*INUSL>
assignin ('base', 'path_track', handles.fullpathname);         %Assignin referenceline path to workspace
assignin('base', 'filename', handles.filename);
assignin('base','centerline_mode',0);
close(Read_TrackGUI);                                                    %Close GUI
Read_FrictionmodeGUI;
