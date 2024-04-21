#template

run create_me.sh in source to create all files needed. This will create a 
Fun4All Geant4 detector MyDetector and gives instructions how to build it 
and add the installation to the environment. Three classes are created:

\<detector\>Subsystem

\<detector\>Detector

\<detector\>SteppingAction

The example detector is a G4Box which can be replaced by anything you implement.

In macros, the Fun4All_G4_MyDetector.C macro will run the just created module 
for 10000 geantinos. The hits are stored in an ntuple which then are plotted
If you use this for your own detector use

CreateG4Subsystem.pl <your detector name>

options are:

  --all : Also create autogen.sh, configure.ac and Makefile.am
  
  --overwrite : overwrite existing files (handle with care, we only have snapshots on our $HOME disk)

