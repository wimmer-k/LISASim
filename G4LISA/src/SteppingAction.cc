#include "SteppingAction.hh"

#include "EventAction.hh"
#include "EventInfo.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "util.hh"
SteppingAction::SteppingAction()                                         
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  feventAction = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
}
SteppingAction::~SteppingAction(){ }


void SteppingAction::UserSteppingAction(const G4Step* aStep){
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "electron")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  
  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "e-")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);

  if( aStep->GetTrack()->GetParentID() > 0 && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "ionIoni")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  
  if(aStep->GetPostStepPoint()->GetStepStatus() != fWorldBoundary){
    G4cout << aStep->GetTrack()->GetDefinition()->GetParticleType() <<" " << aStep->GetTrack()->GetDefinition()->GetPDGMass() <<" " << aStep->GetTrack()->GetParentID() << " " << aStep->GetPostStepPoint()->GetStepStatus() << " " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << aStep->GetTrack()->GetParentID() << G4endl;
  }
  
  feventInfo = (EventInfo*)feventAction->GetEvent()->GetUserInformation();
  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "nucleus" && aStep->GetPostStepPoint()->GetStepStatus() != fWorldBoundary ){
    // get initial and final volumes of the current step
    G4VPhysicalVolume* volume1 = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* volume2= aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
    if(G4StrUtil::contains(volume1->GetName(), "Diamond") && volume2->GetName() == "World" ){
      int t = getfirstintegerfromstring(volume1->GetName());
      G4ThreeVector pDir = aStep->GetTrack()->GetMomentumDirection();
      G4cout << "going out of target number " << t << " with velocity " << aStep->GetTrack()->GetStep()->GetPostStepPoint()->GetBeta() << G4endl;
      feventInfo->GetSimEvent()->SetOutGoingBeta(t,aStep->GetTrack()->GetStep()->GetPostStepPoint()->GetBeta());

    }
  }

}

