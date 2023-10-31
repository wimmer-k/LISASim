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
  G4int ntargets = 0;
  G4int f_dim_x = 6; //////////////////////////
  G4int f_dim_y = 6; //////////////////////////
  G4int fNofLayers = 5;
  
  for(G4int t=0;t<fNofLayers;t++){
      for(G4int j=0; j<f_dim_x; j++){ 
          for(G4int k=0; k<f_dim_y; k++){ 
             



                  char name[100];
                  sprintf(name, "layer_%d%d%d", t,k,j);
                  //G4cout<<name<<G4endl; 
                  //G4String s = name ;
                  G4int id = (SDman->GetHCtable())->GetCollectionID(name);
                  //G4cout<<id<<G4endl;
                  if(id<0) {
                    break;}
                  //G4cout<<id<<G4endl;
                  //cout << "event action CollectionID["<<t<<"] " << endl;//<< ionCollectionID[t] << endl;
                  ntargets++;

          }
      }
  }
  eventInfo->GetSimEvent()->SetNLayers(ntargets);
  //G4cout<<ntargets<<"dsadsaasd"<<endl;
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
      //eventInfo->GetLISAEvent()->AddHit("kdd", (*collection)[0]->GetEdep());
  }// layers
  fdata->FillTree(eventInfo);
}
