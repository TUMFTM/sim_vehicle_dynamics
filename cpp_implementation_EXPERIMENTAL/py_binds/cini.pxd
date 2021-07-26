cdef extern from "ini.h":
      
    int ini_parse(const char* filename, ini_handler handler, void* user)
    int ini_parse_file(FILE* file, ini_handler handler, void* user)
    int ini_parse_stream(ini_reader reader, void* stream, ini_handler handler, void* user)
    int ini_parse_string(const char* string, ini_handler handler, void* user)
