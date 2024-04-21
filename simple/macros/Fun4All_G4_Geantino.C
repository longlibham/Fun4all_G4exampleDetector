#ifndef MACRO_FUN4ALLG4GEANTINO_C
#define MACRO_FUN4ALLG4GEANTINO_C

#include <g4exampledetector01/G4Example01Subsystem.h>

#include <g4detectors/PHG4DetectorSubsystem.h>

#include <g4histos/G4HitNtuple.h>

#include <g4main/PHG4ParticleGenerator.h>
#include <g4main/PHG4ParticleGeneratorBase.h>
#include <g4main/PHG4ParticleGun.h>
#include <g4main/PHG4Reco.h>
#include <g4main/PHG4SimpleEventGenerator.h>

#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllDummyInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <phool/recoConsts.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4detectors.so)
R__LOAD_LIBRARY(libg4example01detector.so)
R__LOAD_LIBRARY(libg4histos.so)

void Fun4All_G4_Geantino(int nEvents = 1)
{
  ///////////////////////////////////////////
  // Make the Server
  //////////////////////////////////////////
  Fun4AllServer *se = Fun4AllServer::instance();
  recoConsts *rc = recoConsts::instance();
  // if you want to fix the random seed to reproduce results
  // set this flag
  // rc->set_IntFlag("RANDOMSEED",12345);

  //
  // Particle Generator
  //

  // the PHG4ParticleGenerator makes cones using phi and eta
  PHG4ParticleGenerator *gen = new PHG4ParticleGenerator();
  gen->set_name("geantino");
  gen->set_vtx(0, 3, 0);
  gen->set_eta_range(-0.9, 0.9);
  gen->set_mom_range(1.0, 1.0);
  gen->set_z_range(0., 0.);
  gen->set_phi_range(0. * TMath::Pi(), 2. * TMath::Pi());
  se->registerSubsystem(gen);

  PHG4ParticleGun *gun = new PHG4ParticleGun();
  gun->set_name("pi-");
  //gun->set_name("geantino");
  //gun->set_name("proton");
  gun->set_vtx(0, -5, -20);  // shoots right into the original Examle01 volume
  gun->set_mom(0, 0, 1);
  //  se->registerSubsystem(gun);

  //
  // Geant4 setup
  //
  PHG4Reco *g4Reco = new PHG4Reco();
  g4Reco->set_field(0);  // no field
  g4Reco->save_DST_geometry(false);
  // try non default physics lists
  //g4Reco->SetPhysicsList("FTFP_BERT_HP");

  G4Example01Subsystem *example01 = new G4Example01Subsystem("HoleInBox");
  g4Reco->registerSubsystem(example01);

  se->registerSubsystem(g4Reco);

  ///////////////////////////////////////////
  // Fun4All modules
  ///////////////////////////////////////////

  G4HitNtuple *hits = new G4HitNtuple("Hits", "HitNtuple.root");
  hits->AddNode("HoleInBox", 0);
  se->registerSubsystem(hits);

  ///////////////////////////////////////////
  // IOManagers...
  ///////////////////////////////////////////

  // Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT","G4Example01.root");
  // out->Verbosity(10);
  // se->registerOutputManager(out);

  // this (dummy) input manager just drives the event loop
  Fun4AllInputManager *in = new Fun4AllDummyInputManager("Dummy");
  se->registerInputManager(in);
  // events = 0 => run forever
  if (nEvents <= 0)
  {
    return 0;
  }
  se->run(nEvents);
  example01->Print();
  se->End();
  std::cout << "All done" << std::endl;
  delete se;
  gSystem->Exit(0);
}

#endif
