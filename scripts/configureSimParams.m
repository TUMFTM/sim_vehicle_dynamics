function configureSimParams(vehicle)
%
% Author: Alexander Wischnewski             Date: 28-09-2018
% 
% adjusted by: Leonhard Hermansdorfer       Date: 23.07.2019
%
% Description: 
%   configures the vehicle dynamics simulation repository 
%   to use a specific parameter set 
% 
% Input: 
% vehicle: The vehicle code which should be used (e.g. db, rc, pa, ...)

    % DDname: The main component data dictionary which shall be configured 
    DDname = 'nonlineardtm';
    % vehicles: contains possible vehicle configurations
    vehicles = {'db', 'rc', 'pa'};

    try 
        % configure a component to use the parametrization for a specific vehicle

        % check if DDname is missing data dictionary extension 
        if(isempty(strfind(DDname, '.sldd')))
          DDname = [DDname '.sldd']; 
        end

        % open main data dictionary for component which should be configured
        DD = Simulink.data.dictionary.open(DDname);
        DataSources = DD.DataSources;

        % find all references which link to a vehicle specific DD 
        for j = 1:size(vehicles,2)
            idxConfigureCells = strfind(DataSources,char(strcat(vehicles(j),'_')));

            if any(cell2mat(idxConfigureCells))
                break
            end

        end

        % get names of data dictionaries which should be added
        DataSources_new = strrep(DataSources(boolean(cell2mat(idxConfigureCells))), char(strcat(vehicles(j),'_')), strcat(vehicle,'_'));

        % remove old references 
        for i = 1:1:length(DataSources)
          % if the reference does not contain a vehicle specific DD continue with next 
          if(isempty(idxConfigureCells{i}))
            continue; 
          end
          % remove the vehicle specific DD 
          removeDataSource(DD, DataSources{i});
        end
        
        % add the new vehicle specific reference
        for k = 1:size(DataSources_new,1)
            addDataSource(DD, char(DataSources_new{k})); 
        end
    
    catch e
        warning(['Something went wrong during configuration of ' ...
                'vehicle dynamics simulation parameters']); 
        disp('******************************************');     
        disp('Exception: ');
        disp(getReport(e))
        disp('******************************************');
    end
    
end
