# MASTER 1 PROJECT

This project was released by BERGOIN Raphäel and BOUT Clément, students in the University of Cergy-Pontoise. The main purpose is to grasp the using of MAVLink in C with a SOLO 3DR drone to interface it with a Neural Network.

## Introduction

As part of our studies, in the [Master 1 Computer sciences and engineering of complex systems (IISC)][miisc], we work with the [ETIS][etis] laboratory to release a sort of ground station (GS) in C for a 3DR Solo Drone with the aim to implement a neural network able to control the drone by using this GS.

In order to realize our project we have decided to use the [c_library_v1][c_lib] (MIT-licenced project) and we realized a little tutorial that you can see [here][ourtuto]

## Architecture

In **doc/**, you can find some global documentation.

In **include/**, the mavlink c library

In **ressources/**, a copy of the library in case of suppression by the owner and some trames and logss used to understand mavlink.

In **src/**, our little program to grasp mavlink and its usings.



[ardupilot]: http://ardupilot.org/dev/docs/copter-commands-in-guided-mode.html	"Ardupilot copter commands"
[c_lib]: https://github.com/mavlink/c_library_v1	"C library v1 repository"
[mavlink_step_by_step]: https://discuss.ardupilot.org/t/mavlink-step-by-step/9629	"The MAVLink step by step by Pedro Albuquerque"
[etis]: https://www-etis.ensea.fr/	"ETIS laboratory's website"
[miisc]: https://depinfo.u-cergy.fr/master/m1-iisc-master-1	"Master's website"
[mavio]: https://mavlink.io/en/messages/common.html
[ourtuto]: https://github.com/cbout/MAVLink_C_example