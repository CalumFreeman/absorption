#!/usr/bin/env python3
import sys
from matplotlib import pyplot as plt
import numpy as np
import requests
from os.path import exists

sys.path.append('../GREENER/')
import analysis as a


def get_rindex(formula='H2O', density=-1, energy=15000):
    base = 'https://henke.lbl.gov/'
    url = base+'/cgi-bin/getdb.pl'
    myobj = {
        'Material': 'Enter Formula',
        'Formula': 'H2O',
        'Density': str(density),
        'Scan': 'Energy',
        'Min': str(energy),
        'Max': '30000',
        'Npts': '2',
        'Output': 'Text File'
    }

    print('post to url:', url)
    x = requests.post(url, data=myobj)

    end = x.text.split('If your file does not appear, click <a HREF="')[1]
    fname = end.split('">here.</a>')[0]

    url = base+fname
    result = requests.get(url)

    data = result.text.split('\n')[2].split('  ')
    delta = float(data[2])
    beta = float(data[3])
    print('delta:', delta, 'beta:', beta)
    return delta, beta


cxro_cache = '/home/calum/Documents/PhD/Code/v2GREENER/build/cxro_cache/'
plot_dir = "./build/test_10mrays/"
if len(sys.argv) > 1:
    plot_dir = sys.argv[1] + "/"

material = 'CH'
if 'CH' in plot_dir:
    material = 'CH'
elif 'water' in plot_dir:
    material = 'H2O'
elif 'SiO2' in plot_dir:
    material = 'SiO2'
n = 15
energy_eV = 15000
halfx = 0.001
show = False

energy_list = [x for x in plot_dir.split('_') if 'keV' in x]
if len(energy_list) == 1:
    energy_eV = float(energy_list[0].replace('/', '').replace('keV', ''))*1000
print('energy_eV', energy_eV)


densities = None
betas = None
deltas = None
name = '/'+material+'_'+str(energy_eV)+'_cxro_beta.npy'
if exists(cxro_cache+name):
    print('loading saved data:')
    data = np.load(cxro_cache+name)
    densities = data[0]
    deltas = data[1]
    betas = data[2]
    print('densities:', densities)
    print('betas:', betas)
    print('deltas:', betas)
else:
    # old config
    start = 0.4
    step = 0.2
    # SiO2 config
    start = 0.1
    step = 0.1
    densities = [(start+step*i) for i in range(n)]
    betas = []
    deltas = []
    for density in densities:
        d, b = get_rindex(energy=energy_eV, formula=material, density=density)
        deltas.append(d)
        betas.append(b)
    np.save(cxro_cache+name, [densities, deltas, betas])


a.box_plot(data_directory=plot_dir,
           det_px=500,
           det_full_width=0.004,
           source_radius_m=0.0017,
           nrays=10000000,
           box_half_height_m=0.0005,
           box_half_width_m=halfx,
           box_half_depth_m=0.0025,
           box_beta=betas,
           box_rhos=densities,
           box_delta=deltas[0],
           energy_eV=energy_eV,
           box_n=n,
           show_lineout=True,
           show=show,
           show_baseline=True,
           absorption_prediction=True,
           refraction_prediction=False,
           use_real_units=False,
           material=material)
