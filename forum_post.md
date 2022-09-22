# Geant4 Absorption not matching cxro

Hi everyone!

I'm using Geant4 as a raytracer for xrays in the 1-30keV energy range, on low Z (water, CH) targets. I've had trouble with the absorption not matching what I would expect from experimental data (obtained from cxro: https://henke.lbl.gov/optical_constants/).

Does anyone have ideas as to why this might be?


Further details:
The testing setup is a series of slices, of equal dimensions, each with increasing density(so different absorption) being backlit by a flat (columnated) source (using /gps), with mono energetic photons initially at 15keV (later tests tried different energies). A schematic is shown:

As I'm a new user, I can't show more images, the images are given in the github which contains the geant4 code that generated the images:
https://github.com/CalumFreeman/absorption
the analysis was written in python and is part of another code, I'm working on extracting it to its own repository

The image on the detector (obtained using /scoring) is CH_15keV_output.png, a lineout is shown in blue. The expected absorption, calculated using the imaginary part of the refractive index(`beta`, different for each slice), is shown in red.

The expected transmission was calculated with this formula:
```
wavelength_m = 1239.842 * np.power(10.0, -9) / energy_eV
mu =  4 * np.pi * thickness_m * beta / wavelength_m
transmission_fraction = np.exp(-mu)
```

For each of these slices, the `beta` suggested by geant4's actual transmission can be calculated:
```
mu = -np.log(transmission)
wavelength_m = get_wavelength(energy_eV)
beta = mu*float(wavelength_m)/(4 * np.pi * float(thickness_m))
```

This can then be plotted against the `beta` from cxro to show there is a linear relationship, with a coefficient which is energy and material dependent. In the github, there are graphs for CH_15keV, CH_20keV, water_15keV, each of which have different coefficients (0.51, 0.62 and 1.08 respectively). For CH, the coefficients were linear with energy (so 25keV is 0.72).

Thanks for any help!

