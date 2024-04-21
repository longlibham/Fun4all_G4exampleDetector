#include "G4Example01Subsystem.h"
#include "G4Example01Detector.h"
#include "G4Example01SteppingAction.h"

#include <g4main/PHG4HitContainer.h>
#include <g4main/PHG4SteppingAction.h>  // for PHG4SteppingAction

#include <phool/PHCompositeNode.h>
#include <phool/PHIODataNode.h>    // for PHIODataNode
#include <phool/PHNode.h>          // for PHNode
#include <phool/PHNodeIterator.h>  // for PHNodeIterator
#include <phool/PHObject.h>        // for PHObject
#include <phool/getClass.h>

using namespace std;

//_______________________________________________________________________
G4Example01Subsystem::G4Example01Subsystem(const std::string &name)
  : PHG4Subsystem(name)
  , m_Detector(nullptr)
  , m_SteppingAction(nullptr)
{
}

//_______________________________________________________________________
int G4Example01Subsystem::Init(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  PHNodeIterator dstIter(dstNode);
  PHCompositeNode *DetNode = dynamic_cast<PHCompositeNode *>(dstIter.findFirst("PHCompositeNode", Name()));
  if (!DetNode)
  {
    DetNode = new PHCompositeNode(Name());
    dstNode->addNode(DetNode);
  }
  string g4hitnodename = "G4HIT_" + Name();
  PHG4HitContainer *g4_hits = findNode::getClass<PHG4HitContainer>(DetNode, g4hitnodename);
  if (!g4_hits)
  {
    g4_hits = new PHG4HitContainer(g4hitnodename);
    DetNode->addNode(new PHIODataNode<PHObject>(g4_hits, g4hitnodename, "PHObject"));
  }

  // create detector
  m_Detector = new G4Example01Detector(this, topNode, Name());
  m_Detector->OverlapCheck(CheckOverlap());

  // create stepping action
  m_SteppingAction = new G4Example01SteppingAction(m_Detector);

  return 0;
}

//_______________________________________________________________________
int G4Example01Subsystem::process_event(PHCompositeNode *topNode)
{
  // pass top node to stepping action so that it gets
  // relevant nodes needed internally
  if (m_SteppingAction)
  {
    m_SteppingAction->SetInterfacePointers(topNode);
  }
  return 0;
}

void G4Example01Subsystem::Print(const string &what) const
{
  //cout << "PSTOF Parameters: " << endl;
  if (m_Detector)
  {
    m_Detector->Print(what);
  }
  return;
}

//_______________________________________________________________________
PHG4Detector *G4Example01Subsystem::GetDetector(void) const
{
  return m_Detector;
}
