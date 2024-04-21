// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4EXAMPLE01STEPPINGACTION_H
#define G4EXAMPLE01STEPPINGACTION_H

#include <g4main/PHG4SteppingAction.h>

class G4Step;
class G4VPhysicalVolume;
class PHCompositeNode;
class G4Example01Detector;
class PHG4Hit;
class PHG4HitContainer;

class G4Example01SteppingAction : public PHG4SteppingAction
{
 public:
  //! constructor
  G4Example01SteppingAction(G4Example01Detector*);

  //! destructor
  virtual ~G4Example01SteppingAction();

  //! stepping action
  virtual bool UserSteppingAction(const G4Step*, bool);

  //! reimplemented from base class
  virtual void SetInterfacePointers(PHCompositeNode*);

 private:
  //! pointer to the detector
  G4Example01Detector* m_Detector;
  //! pointer to hit container
  PHG4HitContainer* m_HitContainer;
  PHG4Hit* m_Hit;
  PHG4HitContainer* m_SaveHitContainer;

  G4VPhysicalVolume* m_SaveVolPre;
  G4VPhysicalVolume* m_SaveVolPost;
  int m_SaveTrackId;
  int m_SavePreStepStatus;
  int m_SavePostStepStatus;
  double m_EdepSum;
  double m_EionSum;
};

#endif  // G4EXAMPLE01STEPPINGACTION_H
