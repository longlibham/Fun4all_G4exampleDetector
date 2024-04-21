# Some example detectors:
simple:

Simplest setup - a box with a half pipe hole at the center, active volume, all parameters hardcoded.

parameter:

Same detector but position, size and material are set by parameters which can be changed in the macro. Default is passive volume (no hits saved)

color:

Same multiple detectors with choice of color

template:

Use a script to create a template for a detector. It creates all necessary
files including the Makefile (if desired). You can use this to easily
implement your own
