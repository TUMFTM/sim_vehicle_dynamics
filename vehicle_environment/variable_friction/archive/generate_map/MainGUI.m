function varargout = MainGUI(varargin)
% Last Modified by GUIDE v2.5 11-Feb-2019 13:11:04
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @MainGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @MainGUI_OutputFcn, ...
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


% --- Executes just before MainGUI is made visible.
function MainGUI_OpeningFcn(hObject, eventdata, handles, varargin) %#ok<INUSL>
handles.output = hObject;
path = strsplit(pwd,"sim_vehicle_dynamics");
path2module = strcat(path(1), "sim_vehicle_dynamics");
addpath(strcat(path2module, "\variable_friction\generate_map\scripts"));
% Update handles structure
guidata(hObject, handles);


% --- Outputs from this function are returned to the command line.
function varargout = MainGUI_OutputFcn(hObject, eventdata, handles)  %#ok<INUSL>
% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles) %#ok<DEFNU,INUSL>
    if get(handles.radiobutton1,'Value')==1
        close(MainGUI);
        Read_CenterlineGUI;
    elseif get(handles.radiobutton2,'Value')==1
        close(MainGUI);
        Read_TrackGUI;
    elseif get(handles.radiobutton3,'Value')==1
        close(MainGUI);
        Read_MapGUI;
    end
