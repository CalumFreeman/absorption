#!/usr/bin/env python3
import sys
from matplotlib import pyplot as plt
sys.path.append('../GREENER/')
import analysis as a

import sys

plot_dir = "./build/test/"
if len(sys.argv) > 1:
    plot_dir = sys.argv[1]+"/"


a.box_plot(
    data_directory=plot_dir,
    det_px=500,
    det_full_width=0.004,
    source_radius_m=0.0017,
    box_half_height_m=0.001/2,
    box_half_width_m=0.001/2,
    box_half_depth_m=0.005/2,
    box_beta=4.84226548E-10,
    box_delta=1.10211784E-06,
    show_lineout=True,
    show=True,
    show_baseline=True,
    absorption_prediction=True,
    refraction_prediction=False,
    use_real_units=False
)

