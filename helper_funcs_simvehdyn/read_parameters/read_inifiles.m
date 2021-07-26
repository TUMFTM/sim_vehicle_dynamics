function struct_params = read_inifiles(filepath2inifile)

    ini = IniConfig();
    ini.ReadFile(filepath2inifile);
    sections = ini.GetSections();

	struct_params = struct();
    
    for i_count=1:length(sections)

        [keys, count_keys] = ini.GetKeys(sections{i_count});
        values = ini.GetValues(sections{i_count}, keys);

        sections_stripped = erase(sections{i_count}, '[');
        sections_stripped = erase(sections_stripped, ']');

        % fill struct with keys (field names) and values
        for j_count=1:count_keys
            
            % continue if line contains a comment (leading '%')
            if contains(keys(j_count), '%')
                continue
            end
            
            value = cell2mat(values(j_count));

            % convert arrays written as char to numerical arrays
            if ischar(value)
                value = str2num(value);  
            end

            struct_params(1).(sections_stripped).(cell2mat(keys(j_count))) = value;

        end

    end

end
