%Thsi script will compile the single track model which is written in C to
%a matlab .mex64 file so it can be used for a S-Function 

project = simulinkproject;
projectRoot = project.RootFolder;

% store current path
currentPath = pwd;
% switch to project root
cd(projectRoot);


try
    % locate standard toolchain
    disp('Start building  nstm S-Function mex file ...');
    cc = mex.getCompilerConfigurations('C');
    % build project dependencies
    if(contains(cc.Name, 'Microsoft'))
        disp('Found Microsoft Visual C as standard compiler ... ');
        mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/stmInterface.c cpp_implementation_EXPERIMENTAL/src/SingleTrackModel.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build -DWINDOWS_BUILD
        % mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/testInterface_stm.c cpp_implementation_EXPERIMENTAL/src/Param_dtm.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build -DWINDOWS_BUILD
    else
        if(contains(cc.Name, 'gcc'))
                disp('Found gcc as standard compiler ... ');
                mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/stmInterface.c cpp_implementation_EXPERIMENTAL/src/SingleTrackModel.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                % mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/testInterface_stm.c cpp_implementation_EXPERIMENTAL/src/Param_dtm.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
            else
                if(contains(cc.Name,'Clang'))
                    disp('Found Clang as standard compiler ...');
                    mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/stmInterface.c cpp_implementation_EXPERIMENTAL/src/SingleTrackModel.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                    % mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/testInterface_stm.c cpp_implementation_EXPERIMENTAL/src/Param_dtm.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                    % test interface for dtm
                    % mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/testInterface.c cpp_implementation_EXPERIMENTAL/src/Param_dtm.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                else
                    disp('Found MinGW as standard compiler ... ');
                    mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/stmInterface.c cpp_implementation_EXPERIMENTAL/src/SingleTrackModel.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                    % mex -g cpp_implementation_EXPERIMENTAL/matlab_binds/testInterface_stm.c cpp_implementation_EXPERIMENTAL/src/Param_dtm.c cpp_implementation_EXPERIMENTAL/src/VehicleState.c cpp_implementation_EXPERIMENTAL/src/ini.c -outdir build
                end
            end
    end
    
    disp('Building of project dependencies successful ...');
    % copy tlc files to build folders due to path restrictions in code generation
    copyfile('cpp_implementation_EXPERIMENTAL/matlab_binds/stmInterface.tlc', 'build/stmInterface.tlc');
    
    %configure Params, so the standard .ini file is inside the build folder
    %disp('Configure params to passanger vehicle ...');
    %configureSimParams('pa')
    
catch e
    disp('Exception: ');
    disp(getReport(e))
    disp('Make sure that you have a compiler installed and setup for usewith MATLAB using: mex -setup');
    error('Building of project dependencies failed ...');
end

myCacheFolder = fullfile(projectRoot, 'build');
myCodeFolder = fullfile(projectRoot, 'build');

Simulink.fileGenControl('set',...
    'CacheFolder', myCacheFolder,...
    'CodeGenFolder', myCodeFolder,...
    'createDir', true)
 
cd(currentPath);

