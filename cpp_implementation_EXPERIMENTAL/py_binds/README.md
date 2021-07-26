# Workflow building and installing the Cython wheel
First of all make sure that you are in an [virtual python environment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/).

Then activate your virtual environment (name of the environment here is (.venv) on Linux by typing in your terminal
```
source /PATHTO/.venv/bin/activate
```   
To install the necessary packages install the requirements.txt via
```
pip install -r py_binds/requirements.txt
```
Then execute the following command inside the `/py_binds` folder
```
python setup.py bdist_wheel
```
This will produce different directories including the `/dist` . Inside this directory is a file named:

__SimVehicle-1.0.0-**.whl__

You can now install this file via pip
```
pip install dist/SimVehicle-0.1.1-**.whl
````

Now that we successfully installed al dependencies you can run the main.py
```
python main.py
````

## References
The Cython framework was used to integrate the C source code into Python.
For more information on how to integrate C code, visit the Cython [documentation](https://cython.readthedocs.io/en/latest/src/quickstart/overview.html).
