#include "SteppingAction.hh"
#include "G4VProcess.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "util.hh"
#include "G4HadronicProcess.hh"
#include "G4ParticleTypes.hh"
SteppingAction::SteppingAction(){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  feventAction = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
}
SteppingAction::~SteppingAction(){ }


void SteppingAction::UserSteppingAction(const G4Step* aStep){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "electron")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);

  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "gamma")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  
  if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "e-")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);

  if( aStep->GetTrack()->GetParentID() > 0 && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "ionIoni")
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);


 G4VPhysicalVolume* volume10 = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
 //G4cout <<volume10->GetName()<<endl;



  
  //if(aStep->GetPostStepPoint()->GetStepStatus() != fWorldBoundary){
    //G4cout << aStep->GetTrack()->GetDefinition()->GetParticleType() <<" " << aStep->GetTrack()->GetDefinition()->GetPDGMass() <<" " << aStep->GetTrack()->GetParentID() << " " << aStep->GetPostStepPoint()->GetStepStatus() << " " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << aStep->GetTrack()->GetParentID() << G4endl;
  //}


//G4cout <<  aStep -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName()<<endl;


// G4VPhysicalVolume* volume4 = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();


// u_char last_3a = volume4->GetName()[volume4->GetName().size()-3];
// auto last_3_inta = (last_3a - '0')  ;


// //FAILED REACTION LAYER IDENTIFICATION -> TO BE DISCUSSED?????

// // if( aStep->GetTrack()!=nullptr && aStep->GetTrack()->GetCreatorProcess()!=nullptr && (G4StrUtil::contains(volume4->GetName(), "Diamond"))  && ReactionLayer < last_3_inta){

// // G4String procName = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
// // if(procName=="Reaction"){ReactionLayer=last_3_inta;
// // cout<<last_3_inta<<endl;

// // }
// //cout<<procName<<endl;
//  //G4cout<< aStep->GetTrack()->GetCreatorProcess()->GetProcessName()<<endl;

//  //G4cout<<"  "<<volume4->GetName()<<G4endl;
// //G4cout << aStep->GetPreStepPoint()->GetPosition().z()<<G4endl;

 
// }


  
  //G4cout<<"  "<<volume4->GetName()<<" "<<aStep->GetTotalEnergyDeposit()/CLHEP::keV<<" deposit? "<<aStep->GetTrack()->GetDefinition()->GetParticleType()<<G4endl;
  

   EventInfo* eventInfo = (EventInfo*)feventAction->GetEvent()->GetUserInformation();
    if( aStep->GetTrack()->GetDefinition()->GetParticleType() == "nucleus" && aStep->GetPostStepPoint()->GetStepStatus() != fWorldBoundary ){
  //    // get initial and final volumes of the current step
      G4VPhysicalVolume* volume1 = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
      G4VPhysicalVolume* volume2= aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume(); 
      
      if((G4StrUtil::contains(volume1->GetName(), "Diamond") && volume2->GetName() == "World")||(G4StrUtil::contains(volume1->GetName(), "Diamond") && volume2->GetName() == "plate_general" )){
       
  //G4cout<<SensitiveDetectorName<<"   Sens_det_name"<<G4endl;
    
       u_char last = volume1->GetName()[volume1->GetName().size()-1];
       u_char last_2 = volume1->GetName()[volume1->GetName().size()-2];
       u_char last_3 = volume1->GetName()[volume1->GetName().size()-3];

    auto last_3_int = (last_3 - '0') *100 +100 ;
    auto last_2_int = (last_2 - '0') *10 +10 ;
    auto last_int =  (last - '0') *1 +1 ;
      auto k = last_3_int + last_2_int + last_int ;

        //int t = getfirstintegerfromstring(volume1->GetName());
        G4ThreeVector pDir = aStep->GetTrack()->GetMomentumDirection();
        //G4cout << "going out of target number " << k << " with velocity " << aStep->GetTrack()->GetStep()->GetPostStepPoint()->GetBeta() << G4endl;
        //G4cout<<k<<endl;
        //eventInfo->GetSimEvent()->SetNLayers(1000);
        eventInfo->GetSimEvent()->SetOutGoingBeta(100,aStep->GetTrack()->GetStep()->GetPostStepPoint()->GetBeta());
        
        //G4cout<<eventInfo->GetSimEvent()->GetNLayers()<<endl;
        //G4cout<<eventInfo->GetSimEvent()->GetOutGoingBeta(k)<<endl;
      }
    }

//eventInfo->GetSimEvent()->SetReactionLayer(ReactionLayer);


}

