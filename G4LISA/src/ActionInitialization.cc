#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(DataManager* data,DetectorConstruction *detector){
  fdata = data;
  fdetector = detector;
}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const{
  SetUserAction(new RunAction(fdata));
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction(fdetector));
  SetUserAction(new RunAction(fdata));
  SetUserAction(new EventAction(fdata));
  SetUserAction(new SteppingAction);
}
