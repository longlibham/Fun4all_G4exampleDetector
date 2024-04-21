#include "G4Example01Detector.h"

#include <g4main/PHG4Detector.h>  // for PHG4Detector

#include <Geant4/G4Box.hh>
#include <Geant4/G4Color.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4Material.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4SubtractionSolid.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4ThreeVector.hh>
#include <Geant4/G4Tubs.hh>
#include <Geant4/G4VisAttributes.hh>

#include <cmath>
#include <iostream>  // for operator<<, endl, bas...

class G4VSolid;
class PHCompositeNode;

using namespace std;

G4Example01Detector::G4Example01Detector(PHG4Subsystem *subsys, PHCompositeNode *Node, const std::string &dnam)
  : PHG4Detector(subsys, Node, dnam)
{
}

//_______________________________________________________________
//_______________________________________________________________
int G4Example01Detector::IsInDetector(G4VPhysicalVolume *volume) const
{
  set<G4VPhysicalVolume *>::const_iterator iter = m_PhysicalVolumesSet.find(volume);
  if (iter != m_PhysicalVolumesSet.end())
  {
    return 1;
  }

  return 0;
}

void G4Example01Detector::ConstructMe(G4LogicalVolume *logicWorld)
{
  double xdim = 20 * cm;
  double ydim = 20 * cm;
  double zdim = 20 * cm;
  G4VSolid *solidbox = new G4Box("Example01BoxSolid", xdim / 2., ydim / 2., zdim / 2.);
  G4VSolid *cylcut = new G4Tubs("CylinderCutSolid", 0., xdim / 4., zdim, 0., M_PI * rad);
  G4VSolid *subtract = new G4SubtractionSolid("HoleInBox", solidbox, cylcut);
  G4LogicalVolume *logical = new G4LogicalVolume(subtract, G4Material::GetMaterial("G4_Al"), "BoxWithHoleLogical");

  G4VisAttributes *vis = new G4VisAttributes(G4Color(G4Colour::Grey()));  // grey is good to see the tracks in the display
  vis->SetForceSolid(true);
  logical->SetVisAttributes(vis);
  G4VPhysicalVolume *phy = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0),
                                             logical, "BoxWithHole",
                                             logicWorld, 0, false, OverlapCheck());
  // add it to the list of placed volumes so the IsInDetector method
  // picks them up
  m_PhysicalVolumesSet.insert(phy);
  return;
}

void G4Example01Detector::Print(const std::string &what) const
{
  cout << "Example01 Detector:" << endl;
  if (what == "ALL" || what == "VOLUME")
  {
    cout << "Version 0.1" << endl;
  }
  return;
}
