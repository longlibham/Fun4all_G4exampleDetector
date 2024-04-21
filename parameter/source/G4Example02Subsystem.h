// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4EXAMPLE02SUBSYSTEM_H
#define G4EXAMPLE02SUBSYSTEM_H

#include <g4detectors/PHG4DetectorSubsystem.h>

#include <string>

class PHCompositeNode;
class PHG4Detector;
class G4Example02Detector;
class PHG4SteppingAction;

/**
   * \brief example Fun4All module
   *
   * The detector is constructed and registered via G4Example02Detector
   *
   *
   * \see G4Example02Detector
   * \see G4Example02Subsystem
   *
   */
class G4Example02Subsystem : public PHG4DetectorSubsystem
{
 public:
  //! constructor
  G4Example02Subsystem(const std::string& name = "Example02");

  //! destructor
  virtual ~G4Example02Subsystem() {}

  /*!
  creates the m_Detector object and place it on the node tree, under "DETECTORS" node (or whatever)
  reates the stepping action and place it on the node tree, under "ACTIONS" node
  creates relevant hit nodes that will be populated by the stepping action and stored in the output DST
  */
  virtual int InitRunSubsystem(PHCompositeNode*);

  //! event processing
  /*!
  get all relevant nodes from top nodes (namely hit list)
  and pass that to the stepping action
  */
  virtual int process_event(PHCompositeNode*);

  //! accessors (reimplemented)
  virtual PHG4Detector* GetDetector() const;

  virtual PHG4SteppingAction* GetSteppingAction() const { return m_SteppingAction; }
  //! Print info (from SubsysReco)
  virtual void Print(const std::string& what = "ALL") const;

 private:
  // \brief Set default parameter values
  void SetDefaultParameters();

  //! detector geometry
  /*! defives from PHG4Detector */
  G4Example02Detector* m_Detector;

  //! particle tracking "stepping" action
  /*! derives from PHG4SteppingActions */
  PHG4SteppingAction* m_SteppingAction;
};

#endif  // G4EXAMPLE02SUBSYSTEM_H
