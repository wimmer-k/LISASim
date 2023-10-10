#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"

#include "TTree.h"
#include "DataManager.hh"
#include "SensitiveDetector.hh"
#include "globals.h"


class EventAction : public G4UserEventAction{
public:
  EventAction(DataManager *fdata);
  ~EventAction() override;

  void  BeginOfEventAction(const G4Event* event) override;
  void  EndOfEventAction(const G4Event* event) override;
  const G4Event* GetEvent() { return fevt; }

private:
  const G4Event* fevt; // to communicate with steppingaction
  DataManager* fdata;
};

#endif


