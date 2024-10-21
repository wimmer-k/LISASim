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

//getters

G4double    getRGRL(){return RGRL;}
G4double    getRGRL2(){return RGRL2;}


private:
  const G4Event* fevt; // to communicate with steppingaction
  DataManager* fdata;
  G4double RGRL ;
  G4double RGRL2 ;

};

#endif


