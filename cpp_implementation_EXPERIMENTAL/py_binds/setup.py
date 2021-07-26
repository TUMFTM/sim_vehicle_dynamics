from setuptools import Extension, setup
from Cython.Build import cythonize
import os
import platform
import numpy


def prepare_param_dtm(relPathPyBinds, relSrcC, relIncludeC):
    #Source files for Cython

    source_files = [os.path.join(relPathPyBinds, 'Param_dtm.pyx'),
                    os.path.join(relSrcC, 'Param_dtm.c'),
                    os.path.join(relSrcC, 'ini.c'),
                    ]


    include_dirs = [numpy.get_include(),
                    relIncludeC,
                    ]

    # compiler flags
    if platform.system() == 'Windows':
        compile_args = []
    elif platform.system() == 'Linux' or platform.system() == 'Darwin':
        compile_args = ['-fpermissive', '-w']
    else:
        raise OSError('System not identified!')


    # prepare everything as python extension module
    param_dtm_extension = Extension(name="Param_dtm",
                                           sources=source_files,
                                           include_dirs=include_dirs,
                                           language="c",
                                           extra_compile_args=compile_args)
    #TODO check if I need to add some linraries here with arg libraries=["m"] for the math.h library
    #See dynamic linking https://cython.readthedocs.io/en/latest/src/tutorial/external.html 
    
    return param_dtm_extension


def prepare_vehicle_state(relPathPyBinds, relSrcC, relIncludeC):
    #Source files for Cython
    source_files = [os.path.join(relPathPyBinds, 'VehicleState.pyx'),
                    os.path.join(relSrcC, 'VehicleState.c'),
                    ]

    include_dirs = [numpy.get_include(),
                    relIncludeC,
                    ]  

    # compiler flags
    if platform.system() == 'Windows':
        compile_args = []
    elif platform.system() == 'Linux' or platform.system() == 'Darwin':
        compile_args = ['-fpermissive', '-w']
    else:
        raise OSError('System not identified!')


    # prepare everything as python extension module
    vehicle_state_extension = Extension(name="VehicleState",
                                           sources=source_files,
                                           include_dirs=include_dirs,
                                           language="c",
                                           extra_compile_args=compile_args,
                                           libraries=["m"])
    #TODO check if I need to add some linraries here with arg libraries=["m"] for the math.h library
    #See dynamic linking https://cython.readthedocs.io/en/latest/src/tutorial/external.html 
    
    return vehicle_state_extension


def prepare_vehicle_body(relPathPyBinds, relSrcC, relIncludeC):
    #Source files for Cython
    source_files = [os.path.join(relPathPyBinds, 'VehicleBody.pyx'),
                    os.path.join(relSrcC, 'VehicleBody.c'),
                    ]

    include_dirs = [numpy.get_include(),
                    relIncludeC,
                    ]  

    # compiler flags
    if platform.system() == 'Windows':
        compile_args = []
    elif platform.system() == 'Linux' or platform.system() == 'Darwin':
        compile_args = ['-fpermissive', '-w']
    else:
        raise OSError('System not identified!')


    # prepare everything as python extension module
    vehicle_body_extension = Extension(name="VehicleBody",
                                           sources=source_files,
                                           include_dirs=include_dirs,
                                           language="c",
                                           extra_compile_args=compile_args,
                                           libraries=["m"])
    #TODO check if I need to add some linraries here with arg libraries=["m"] for the math.h library
    #See dynamic linking https://cython.readthedocs.io/en/latest/src/tutorial/external.html 
    
    return vehicle_body_extension


def prepare_vehicle(relPathPyBinds, relSrcC, relIncludeC):
    #Source files for Cython
    source_files = [os.path.join(relPathPyBinds, 'Vehicle.pyx'),
                    ]

    include_dirs = [numpy.get_include(),
                    relIncludeC,
                    ]  

    # compiler flags
    if platform.system() == 'Windows':
        compile_args = []
    elif platform.system() == 'Linux' or platform.system() == 'Darwin':
        compile_args = ['-fpermissive', '-w']
    else:
        raise OSError('System not identified!')


    # prepare everything as python extension module
    vehicle_extension = Extension(name="Vehicle",
                                           sources=source_files,
                                           include_dirs=include_dirs,
                                           language="c",
                                           extra_compile_args=compile_args,
                                           libraries=["m"])
    #TODO check if I need to add some linraries here with arg libraries=["m"] for the math.h library
    #See dynamic linking https://cython.readthedocs.io/en/latest/src/tutorial/external.html 
    
    return vehicle_extension


def prepare_stm(relPathPyBinds, relSrcC, relIncludeC):
    #Source files for Cython
    source_files = [os.path.join(relPathPyBinds, 'SingleTrackModel.pyx'),
                    os.path.join(relSrcC, 'SingleTrackModel.c'),
                    os.path.join(relSrcC, 'VehicleState.c'),
                    os.path.join(relSrcC, 'execute_testcase.c'),
                    os.path.join(relSrcC, 'ini.c'),
                    ]

    include_dirs = [numpy.get_include(),
                    relIncludeC,
                    ]  

    # compiler flags
    if platform.system() == 'Windows':
        compile_args = []
    elif platform.system() == 'Linux' or platform.system() == 'Darwin':
        compile_args = ['-fpermissive', '-w']
    else:
        raise OSError('System not identified!')


    # prepare everything as python extension module
    stm_extension = Extension(name="SingleTrackModel",
                                           sources=source_files,
                                           include_dirs=include_dirs,
                                           language="c",
                                           extra_compile_args=compile_args,
                                           libraries=["m"])
    #TODO check if I need to add some linraries here with arg libraries=["m"] for the math.h library
    #See dynamic linking https://cython.readthedocs.io/en/latest/src/tutorial/external.html 
    
    return stm_extension


########################################################################################################################
# prepare and find paths
########################################################################################################################
# Current working directory
dirCurrent = os.path.abspath(os.getcwd())

# Build directory
dirBuild_SimVehicle = os.path.abspath(os.path.join(os.path.abspath(__file__), '..', 'build'))

# Relative paths to build directories
relPathBuild_SimVehicle = os.path.relpath(dirBuild_SimVehicle, dirCurrent)

 
# Relative path to bindings
relPathPyBinds = os.path.relpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../py_binds'), dirCurrent)

# Relative Path to include files in C
relIncludeC = os.path.relpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../include'), dirCurrent)

# Relative Path to include files in C
relSrcC = os.path.relpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../src'), dirCurrent)

definition_files_dir = [relPathPyBinds]
########################################################################################################################
# setup and compile cython modules
########################################################################################################################

# get extensions
print("relPathPybinds: \n", relPathPyBinds)
print("relSrcC: \n", relSrcC)
print("relIncludeC: \n", relIncludeC)

param_dtm_ext = prepare_param_dtm(relPathPyBinds, relSrcC, relIncludeC)
vehicle_state_ext = prepare_vehicle_state(relPathPyBinds, relSrcC, relIncludeC)
vehicle_body_ext = prepare_vehicle_body(relPathPyBinds, relSrcC, relIncludeC)
vehicle_ext = prepare_vehicle(relPathPyBinds, relSrcC, relIncludeC)
stm_ext = prepare_stm(relPathPyBinds, relSrcC, relIncludeC)

# list all required extensions
# cython_extensions = [param_dtm_ext, vehicle_state_ext, vehicle_body_ext, vehicle_ext]
cython_extensions = [stm_ext]


setup(
    name="SimVehicle",
    version="1.0.0",
    install_requires=['numpy'],
    ext_modules=cythonize(cython_extensions,
    compiler_directives={'language_level': "3"}, force=True),
    )