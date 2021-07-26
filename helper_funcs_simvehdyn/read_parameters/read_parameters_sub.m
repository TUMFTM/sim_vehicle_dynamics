function [param] = read_parameters_sub(param_cell, search_string, filepath_tireparameters)

    %#codegen

    param = [];

    %% Durchlauf aller Zellen, bis Parameter gefunden wurde

    for i = 1 : length(param_cell)
        index_1 = strfind(param_cell{i}, '=');                                                  % "=" im String suchen

        if ~isempty(index_1)
            param_name = param_cell{i}(1 : index_1(1) - 1);                                     % Parametername anhand = auslesen
        else
            continue                                                                            % falls kein "=" im String vorhanden ist
        end

        if strcmpi(param_name, search_string)                                                   % falls richtige Zelle gefunden wurde

            switch search_string
                case 'TYRESIDE'
                    index_ = strfind(param_cell{i}, '''');                                      % '-Zeichen suchen, Struktur: 'TYRESIDE' = 'LEFT' $Comment
                    param = param_cell{i}(index_(1) + 1 : index_(2) - 1);                       % Parameterwert auslesen
                case 'ANGLE'
                    index_2 = length(param_cell{i});
                    param = param_cell{i}(index_1(1) + 2 : index_2(1) - 1);                     % Parameterwert auslesen
                otherwise
                    index_2 = strfind(param_cell{i}, '$');                                      % Position des Kommentarzeichens finden
                    if ~isempty(index_2)
                        param = str2double(param_cell{i}(index_1(1) + 1 : index_2(1) - 1));     % Parameterwert auslesen
                    else                                                                        % falls es keine Kommentarzeichen gibt, bis zum Ende auslesen
                        param = str2double(param_cell{i}(index_1(1) + 1 : end));                % Parameterwert auslesen
                    end
            end

            break                                                                               % leave for loop if parameter was found

        end
    end

    %% falls Parameter im File nicht vorhanden ist

    if isempty(param) && strcmp(search_string, 'TYRESIDE')
        fprintf('Warning: Parameter %s in file %s not found! Parameter is set to left! \n', search_string, filepath_tireparameters);
        param = 'LEFT';
    elseif isempty(param)
        fprintf('Warning: Parameter %s in file %s not found! Parameter is set to zero! \n', search_string, filepath_tireparameters);
        param = 0;
    end

end
