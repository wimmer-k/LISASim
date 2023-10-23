#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
EventAction::EventAction(DataManager* data){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  fevt = NULL;
  fdata = data;
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event* event){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  fevt = event;
  EventInfo* eventInfo = new EventInfo();
  //cout << "fdata->GetSimEvent()->GetBeamEnergy() " << fdata->GetSimEvent()->GetBeamEnergy() << endl;
  eventInfo->SetSimEvent(fdata->GetSimEvent());
  
  G4EventManager::GetEventManager()->SetUserInformation(eventInfo);
  eventInfo = (EventInfo*)fevt->GetUserInformation();
  //cout << "eventInfo->GetSimEvent()->GetBeamEnergy() " << eventInfo->GetSimEvent()->GetBeamEnergy() << endl;
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  int ntargets = 0;
  for(int t=0;t<MAXTARGETS;t++){
    char name[100];
    sprintf(name, "layer_%d", t); 
    G4int id = (SDman->GetHCtable())->GetCollectionID(name);
    if(id<0)
      break;
    //cout << "event action CollectionID["<<t<<"] " << endl;//<< ionCollectionID[t] << endl;
    ntargets++;
  }
  eventInfo->GetSimEvent()->SetNLayers(ntargets);
}

void EventAction::EndOfEventAction(const G4Event* event){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  fevt = event;
  EventInfo* eventInfo = (EventInfo*)fevt->GetUserInformation();
  eventInfo->GetSimEvent()->SetEventID(fevt->GetEventID());
  //cout << "eventInfo->GetSimEvent()->GetBeamEnergy() " << eventInfo->GetSimEvent()->GetBeamEnergy() << endl;
  //cout << "event number " << eventInfo->GetSimEvent()->GetEventID()  << " with " <<  eventInfo->GetSimEvent()->GetNLayers() << " targets " << endl;
  G4HCofThisEvent * HCE = event->GetHCofThisEvent();
  for(int i=0;i<eventInfo->GetSimEvent()->GetNLayers();i++){
    LISAHitsCollection* collection = (LISAHitsCollection*)(HCE->GetHC(i));
    //G4cout << i << ", collection->entries()" << collection->entries() << endl;
    /*
      G4int Nhits = collection->entries();
      if(Nhits>1){
      G4cout << __PRETTY_FUNCTION__ << G4endl;
      G4cout << "more than one hit in collection ID "<< i << ", collection->entries(): " << collection->entries() << G4endl;
      for(UShort_t j=0;j<collection->entries();j++){
      G4cout << "layer " << (*collection)[0]->GetLayerID() <<", E = " << (*collection)[0]->GetEdep() << G4endl;
      }
      }
      if(Nhits==0){
      G4cout << "no hit in collection ID "<< i << ", collection->entries()" << collection->entries() << G4endl;
      }
      else{
      //(*collection)[0]->Print();
      eventInfo->GetLISAEvent()->AddHit((*collection)[0]->GetLayerID(), (*collection)[0]->GetEdep());
      }
    */
    if(collection->entries()>0)
      eventInfo->GetLISAEvent()->AddHit((*collection)[0]->GetLayerID(), (*collection)[0]->GetEdep());
  }// layers
  fdata->FillTree(eventInfo);
}
