function varargout = CreateDatadictGUI(varargin)
    % Begin initialization code - DO NOT EDIT
    gui_Singleton = 1;
    
    gui_State = struct('gui_Name',       mfilename, ...
                       'gui_Singleton',  gui_Singleton, ...
                       'gui_OpeningFcn', @CreateDatadictGUI_OpeningFcn, ...
                       'gui_OutputFcn',  @CreateDatadictGUI_OutputFcn, ...
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

function CreateDatadictGUI_OpeningFcn(hObject, eventdata, handles, varargin)
    handles.output = hObject;
    path = strsplit(pwd,"sim_vehicle_dynamics");
    path2module = strcat(path(1), "sim_vehicle_dynamics");
    addpath(strcat(path2module, '\variable_friction\frictionmodel\GUI\scripts'));
    guidata(hObject, handles);

function varargout = CreateDatadictGUI_OutputFcn(hObject, eventdata, handles) 
    varargout{1} = handles.output;

function time1_Callback(hObject, eventdata, handles)
function time1_CreateFcn(hObject, eventdata, handles)
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end

function time2_Callback(hObject, eventdata, handles)
function time2_CreateFcn(hObject, eventdata, handles)
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end

function time3_Callback(hObject, eventdata, handles)
function time3_CreateFcn(hObject, eventdata, handles)
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end

function time4_Callback(hObject, eventdata, handles)
function time4_CreateFcn(hObject, eventdata, handles)
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end

function Grid1_Callback(hObject, eventdata, handles)
    set(handles.time2, 'Enable','off');
    set(handles.time3, 'Enable','off');
    set(handles.time4, 'Enable','off');
    set(handles.time1, 'String', '0');
    set(handles.time2, 'String', '0');
    set(handles.time3, 'String', '0');
    set(handles.time4, 'String', '0');

function Grid2_Callback(hObject, eventdata, handles)
    set(handles.time3, 'Enable','off');
    set(handles.time4, 'Enable','off');
    set(handles.time2, 'Enable','on');
    set(handles.time1, 'String', '0');
    set(handles.time2, 'String', '20');
    set(handles.time3, 'String', '0');
    set(handles.time4, 'String', '0');

function Grid3_Callback(hObject, eventdata, handles)
    set(handles.time4, 'Enable','off');
    set(handles.time2, 'Enable','on');
    set(handles.time3, 'Enable','on');
    set(handles.time1, 'String', '0');
    set(handles.time2, 'String', '20');
    set(handles.time3, 'String', '40');
    set(handles.time4, 'String', '0');

function Grid4_Callback(hObject, eventdata, handles)
    set(handles.time2, 'Enable','on');
    set(handles.time3, 'Enable','on');
    set(handles.time4, 'Enable','on');
    set(handles.time1, 'String', '0');
    set(handles.time2, 'String', '20');
    set(handles.time3, 'String', '40');
    set(handles.time4, 'String', '60');

function checkbox1_Callback(hObject, eventdata, handles)
    if get(handles.checkbox1,'Value')
        set(handles.pushbutton1, 'Enable', 'on');
    else
        set(handles.pushbutton1, 'Enable', 'off');
    end    

function pushbutton1_Callback(hObject, eventdata, handles)
    if get(handles.Grid1,'Value')
        assignin('base', 'Grid_mode', 1);
        assignin('base', 'InterpTime', [0;0;0;0]);
        close(CreateDatadictGUI);
        Datadict_Creation();
        
    elseif get(handles.Grid2,'Value')
        a=str2double(get(handles.time2, 'String'));
        b=str2double(get(handles.time1, 'String'));
        
        if a>b && b>=0
            assignin('base', 'Grid_mode', 2);
            assignin('base', 'InterpTime', [b;a;0;0]);
            close(CreateDatadictGUI);
            Datadict_Creation();
            
        else 
            set(handles.time1,'String', 'ERROR');
            set(handles.time2,'String', 'ERROR');
            
        end
        
    elseif get(handles.Grid3,'Value')
        a=str2double(get(handles.time3, 'String'));
        b=str2double(get(handles.time2, 'String'));
        c=str2double(get(handles.time1, 'String'));
        
        if a>b && b>c && c>=0
            assignin('base', 'Grid_mode', 3);
            assignin('base', 'InterpTime', [c;b;a;0]);
            close(CreateDatadictGUI);
            Datadict_Creation();
            
        else 
            set(handles.time1,'String', 'ERROR');
            set(handles.time2,'String', 'ERROR');
            set(handles.time3,'String', 'ERROR');
            
        end
        
    elseif get(handles.Grid4,'Value')
        a=str2double(get(handles.time4, 'String'));
        b=str2double(get(handles.time3, 'String'));
        c=str2double(get(handles.time2, 'String'));
        d=str2double(get(handles.time1, 'String'));
        
        if a>b && b>c && c>d && d>=0
            assignin('base', 'Grid_mode', 4);
            assignin('base', 'InterpTime', [d;c;b;a]);
            close(CreateDatadictGUI);
            Datadict_Creation();
            
        else
            set(handles.time1,'String', 'ERROR');
            set(handles.time2,'String', 'ERROR');
            set(handles.time3,'String', 'ERROR');
            set(handles.time4,'String', 'ERROR');
            
        end
        
    end
