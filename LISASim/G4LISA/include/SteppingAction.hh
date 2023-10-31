#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include "EventAction.hh"
#include "EventInfo.hh"

class SteppingAction : public G4UserSteppingAction{
public:
  SteppingAction();
  virtual ~SteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  EventAction*   feventAction;  
  //EventInfo*     feventInfo;
};

#endif
