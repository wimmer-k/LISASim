#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "Incoming_Beam.hh"

ActionInitialization::ActionInitialization(DataManager* data,DetectorConstruction *detector,Incoming_Beam* BI){
  fdata = data;
  fdetector = detector;
  fBI = BI ;
}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const{
  SetUserAction(new RunAction(fdata));
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction(fdetector,fBI));
  SetUserAction(new RunAction(fdata));
  SetUserAction(new EventAction(fdata));
  SetUserAction(new SteppingAction);
}
