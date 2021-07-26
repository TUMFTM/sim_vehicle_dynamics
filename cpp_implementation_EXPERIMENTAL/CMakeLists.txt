cmake_minimum_required(VERSION 3.1)

project(Sim_Vehicle_Dynamics VERSION 0.1
                             LANGUAGES C)

message(STATUS "CMAKE_C_COMPILER ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_C_COMPILER_ID ${CMAKE_C_COMPILER_ID}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

include_directories(src)

# Create list of files which will be compiled
set(SOURCES src/main.c)
list(APPEND SOURCES src/SingleTrackModel.c)
list(APPEND SOURCES src/VehicleState.c)
list(APPEND SOURCES src/execute_testcase.c)
list(APPEND SOURCES src/create_csv_testcases.c)
list(APPEND SOURCES src/ini.c)

add_executable(Sim_Vehicle_Dynamics ${SOURCES})


# Set compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|AppleClang")
    target_link_libraries(Sim_Vehicle_Dynamics PRIVATE m)
    target_compile_options(Sim_Vehicle_Dynamics PRIVATE -Wno-all)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    target_compile_options(Sim_Vehicle_Dynamics PRIVATE /w)
endif()