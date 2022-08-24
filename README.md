# Purpose
This exists as an example, to check the absorption coefficients are correct. 

The code raytraces a beam of x-rays through a target, giving some absorption, this can then be compared against data from CXRO's xray database (https://henke.lbl.gov/optical_constants/), to see if it's correct.

# Requirements:

Geant4 must be installed, and paths must be set up correctly, follow instructions on geant4.org for this, geant4 comes with a script that does a lot of the path setup stuff.

The simple_plot.py script relies on an analysis script which I haven't made public yet, sorry about that.

# Installation/running the code

With a terminal in the place you want to install the code, clone the repository and move into the folder created:

``` sh
git clone git@github.com:CalumFreeman/absorption.git
cd absorption
```
Then create a build folder

``` sh
mkdir build
cd build
```
Then source your geant4 installation's setup script

``` sh
source $G4INSTALLDIR/bin/geant4.sh
```
Now call cmake and make

``` sh
cmake ..
make
```
At this stage there is an executable `GREENER` which you can run to get to a geant4 gui, but to run a the code with geometry, particle sources, detector, etc set up, use the wrapper script:

``` sh
./wrapper <folder_name>
```
where `<folder_name>` is the folder you want to output the results (as `output.txt`) to. The folder will be created and have all the input scripts stored in it, this way the exact setup at runtime is preserved.

# Results/Improvements
This isn't giving the values for absorption I would expect, if you find any issues, please point me in the right direction! (email me, open an issue, etc).

Thanks!
