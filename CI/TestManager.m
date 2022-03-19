%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% THIS IS A GITLAB CI SCRIPT!! DO NOT RUN IT MANUALLY !!
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% store call path
call_path = pwd;
disp('Path after calling: ')
disp(call_path)
% deactivate warnings to make logs more readable
warning ('off','all');
%% run script
try
    %% Load project
    disp('******************************************');
    disp('Load simulink project');
    disp('******************************************');
    drawnow;
    proj=simulinkproject(ProjectName);
    % make sure scripts are run from project root
    cd(projectRoot);
    %% Run Testcases
    disp('Path before starting the testcases: ')
    disp(pwd)
    % R2017b does not support output detail parameter
    if(strcmp(version('-release'), '2018b'))
        results = runtests(TestCase, 'OutputDetail', 4);
    else
        results = runtests(TestCase);
    end
    %% Format results
    % create table and remove details column (no information in string
    % format available)
    results_tab = table(results);
    results_tab.Details = [];
    % the partial removal of HTML tags leads to the string being not
    % interpreted as formatted
    tmp = erase(evalc('disp(results_tab)'), '<strong>');
    % remove the rest of the HTML tags to make the output readable in the
    % command line
    tmp2 = erase(tmp, '</strong>');
    disp(tmp2);
    
    %% Handle exit
    % this if clause has to be evaluated first and exit code has to be stored since variables are
    % removed during close(proj)
    if(any([results.Failed]))
        % close project actively to prevent matlab asking to save changes
        close(proj);
        % close everything which is there forcefully, otherwise unsaved changes
        % dialogs can block CI
        bdclose('all');
        Simulink.data.dictionary.closeAll('-discard');
        exit_code = 1;
    else
        % close project actively to prevent matlab asking to save changes
        close(proj);
        % close everything which is there forcefully, otherwise unsaved changes
        % dialogs can block CI
        bdclose('all');
        Simulink.data.dictionary.closeAll('-discard');
        exit_code = 0;
    end
 catch e
    disp('******************************************');
    disp('!ERROR: Test failed');
    disp('******************************************');
    disp('******************************************');
    disp('Exception: ');
    disp(getReport(e))
    disp('******************************************'); 
    % close project actively to prevent matlab asking to save changes
    close(proj);
    % close everything which is there forcefully, otherwise unsaved changes
    % dialogs can block CI
    bdclose('all');
    Simulink.data.dictionary.closeAll('-discard');
    exit_code = 1;
end

quit(exit_code)
