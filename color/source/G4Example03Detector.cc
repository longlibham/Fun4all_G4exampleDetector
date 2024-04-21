#include "G4Example03Detector.h"

#include "G4Example03DisplayAction.h"

#include <phparameter/PHParameters.h>

#include <g4main/PHG4Detector.h>       // for PHG4Detector
#include <g4main/PHG4DisplayAction.h>  // for PHG4DisplayAction
#include <g4main/PHG4Subsystem.h>

#include <Geant4/G4Box.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4Material.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4RotationMatrix.hh>
#include <Geant4/G4SubtractionSolid.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4ThreeVector.hh>
#include <Geant4/G4Tubs.hh>

#include <cmath>
#include <iostream>  // for operator<<, endl, bas...

class G4VSolid;
class PHCompositeNode;

using namespace std;

G4Example03Detector::G4Example03Detector(PHG4Subsystem *subsys,
                                         PHCompositeNode *Node,
                                         PHParameters *parameters,
                                         const std::string &dnam)
  : PHG4Detector(subsys, Node, dnam)
  , m_Params(parameters)
  , m_DisplayAction(dynamic_cast<G4Example03DisplayAction *>(subsys->GetDisplayAction()))
{
}

//_______________________________________________________________
//_______________________________________________________________
int G4Example03Detector::IsInDetector(G4VPhysicalVolume *volume) const
{
  set<G4VPhysicalVolume *>::const_iterator iter =
      m_PhysicalVolumesSet.find(volume);
  if (iter != m_PhysicalVolumesSet.end())
  {
    return 1;
  }

  return 0;
}

void G4Example03Detector::ConstructMe(G4LogicalVolume *logicWorld)
{
  double xdim = m_Params->get_double_param("size_x") * cm;
  double ydim = m_Params->get_double_param("size_y") * cm;
  double zdim = m_Params->get_double_param("size_z") * cm;
  G4VSolid *solidbox =
      new G4Box("Example03BoxSolid", xdim / 2., ydim / 2., zdim / 2.);
  G4VSolid *cylcut =
      new G4Tubs("CylinderCutSolid", 0., xdim / 4., zdim, 0., M_PI * rad);
  G4VSolid *subtract = new G4SubtractionSolid("HoleInBox", solidbox, cylcut);
  G4LogicalVolume *logical = new G4LogicalVolume(subtract, G4Material::GetMaterial("G4_Al"), "BoxWithHoleLogical");
  m_DisplayAction->SetMyVolume(logical);
  G4RotationMatrix *rotm = new G4RotationMatrix();
  rotm->rotateX(m_Params->get_double_param("rot_x") * deg);
  rotm->rotateY(m_Params->get_double_param("rot_y") * deg);
  rotm->rotateZ(m_Params->get_double_param("rot_z") * deg);

  G4VPhysicalVolume *phy = new G4PVPlacement(
      rotm,
      G4ThreeVector(m_Params->get_double_param("place_x") * cm,
                    m_Params->get_double_param("place_y") * cm,
                    m_Params->get_double_param("place_z") * cm),
      logical, "BoxWithHole", logicWorld, 0, false, OverlapCheck());
  // add it to the list of placed volumes so the IsInDetector method
  // picks them up
  m_PhysicalVolumesSet.insert(phy);
  return;
}

void G4Example03Detector::Print(const std::string &what) const
{
  cout << "Example03 Detector:" << endl;
  if (what == "ALL" || what == "VOLUME")
  {
    cout << "Version 0.1" << endl;
    cout << "Parameters:" << endl;
    m_Params->Print();
  }
  return;
}
