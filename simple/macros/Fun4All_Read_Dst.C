#ifndef MACRO_FUN4ALLREADDST_C
#define MACRO_FUN4ALLREADDST_C

#include <g4histos/G4HitNtuple.h>

#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllDummyInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <phool/recoConsts.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4testbench.so)
R__LOAD_LIBRARY(libg4histos.so)

void Fun4All_Read_Dst(int nEvents = 1)
{
  ///////////////////////////////////////////
  // Make the Server
  //////////////////////////////////////////
  Fun4AllServer *se = Fun4AllServer::instance();
  recoConsts *rc = recoConsts::instance();
  // if you want to fix the random seed to reproduce results
  // set this flag
  // rc->set_IntFlag("RANDOMSEED",12345);

  G4HitNtuple *hits = new G4HitNtuple("Hits", "HitsFromDst.root");
  hits->AddNode("HoleInBox", 0);
  se->registerSubsystem(hits);

  ///////////////////////////////////////////
  // IOManagers...
  ///////////////////////////////////////////

  // Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT","G4Example01.root");
  // out->Verbosity(10);
  // se->registerOutputManager(out);

  // this (dummy) input manager just drives the event loop
  Fun4AllInputManager *in = new Fun4AllDstInputManager("DSTin");
  in->fileopen("G4Example01.root");
  se->registerInputManager(in);
  // events = 0 => run till end of input file
  if (nEvents < 0)
  {
    return 0;
  }
  se->run(nEvents);
  se->End();
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
}

#endif
