// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4EXAMPLE02STEPPINGACTION_H
#define G4EXAMPLE02STEPPINGACTION_H

#include <g4main/PHG4SteppingAction.h>

class G4Step;
class G4VPhysicalVolume;
class PHCompositeNode;
class G4Example02Detector;
class PHG4Hit;
class PHG4HitContainer;
class PHParameters;

class G4Example02SteppingAction : public PHG4SteppingAction
{
 public:
  //! constructor
  G4Example02SteppingAction(G4Example02Detector*, const PHParameters* parameters);

  //! destructor
  virtual ~G4Example02SteppingAction();

  //! stepping action
  virtual bool UserSteppingAction(const G4Step*, bool);

  //! reimplemented from base class
  virtual void SetInterfacePointers(PHCompositeNode*);

 private:
  //! pointer to the detector
  G4Example02Detector* m_Detector;
  const PHParameters* m_Params;
  //! pointer to hit container
  PHG4HitContainer* m_HitContainer;
  PHG4Hit* m_Hit;
  PHG4HitContainer* m_SaveHitContainer;

  G4VPhysicalVolume* m_SaveVolPre;
  G4VPhysicalVolume* m_SaveVolPost;
  int m_SaveTrackId;
  int m_SavePreStepStatus;
  int m_SavePostStepStatus;
  int m_ActiveFlag;
  int m_BlackHoleFlag;
  double m_EdepSum;
  double m_EionSum;
};

#endif  // G4EXAMPLE02STEPPINGACTION_H
