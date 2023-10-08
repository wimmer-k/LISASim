//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
//#include "CalorimeterSD.hh"
//#include "CalorHit.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(){
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  fHCID=-1;
  fevt = NULL;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
CalorHitsCollection*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  auto hitsCollection
    = static_cast<CalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void EventAction::PrintEventStatistics(
                              G4double absoEdep, G4double absoTrackLength,
                              G4double gapEdep, G4double gapTrackLength) const
{
  // print event statistics
  G4cout
     << "   Absorber: total energy: "
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: "
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  fevt = event;
  G4EventManager::GetEventManager()->SetUserInformation(new EventInfo);
  EventInfo* eventInfo = (EventInfo*)fevt->GetUserInformation();
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  int ntargets = 0;
  for(int t=0;t<MAXTARGETS;t++){
    char name[100];
    sprintf(name, "layer_%d", t); 
    G4int id = (SDman->GetHCtable())->GetCollectionID(name);
    if(id<0)
      break;
    //ionCollectionID[t]=id;
    cout << "event action CollectionID["<<t<<"] " << endl;//<< ionCollectionID[t] << endl;
    ntargets++;
  }
  eventInfo->GetSimEvent()->SetNLayers(ntargets);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;

  fevt = event;
  EventInfo* eventInfo = (EventInfo*)fevt->GetUserInformation();
  eventInfo->GetSimEvent()->SetEventID(fevt->GetEventID());
  cout << "event number " << eventInfo->GetSimEvent()->GetEventID()  << " with " <<  eventInfo->GetSimEvent()->GetNLayers() << " targets " << endl;
  G4HCofThisEvent * HCE = event->GetHCofThisEvent();
  for(int i=0;i<eventInfo->GetSimEvent()->GetNLayers();i++){
    LISAHitsCollection* collection = (LISAHitsCollection*)(HCE->GetHC(i));
    //G4cout << i << ", collection->entries()" << collection->entries() << endl;
    G4int Nhits = collection->entries();
    if(Nhits>1){
      G4cout << "more than one hit in collection ID "<< i << ", collection->entries()" << collection->entries() << endl;
    }
    if(Nhits==0){
      G4cout << "no hit in collection ID "<< i << ", collection->entries()" << collection->entries() << endl;
    }
    else{
      (*collection)[0]->Print();
      eventInfo->GetLISAEvent();
    }
  }// layers
  cout << "ende " << endl;
  /*
  // Get hits collections IDs (only once)
  if ( fAbsHCID == -1 ) {
    fAbsHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AbsorberHitsCollection");
    fGapHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("GapHitsCollection");
  }

  // Get hits collections
  auto absoHC = GetHitsCollection(fAbsHCID, event);
  auto gapHC = GetHitsCollection(fGapHCID, event);

  // Get hit with total values
  auto absoHit = (*absoHC)[absoHC->entries()-1];
  auto gapHit = (*gapHC)[gapHC->entries()-1];

  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;

    PrintEventStatistics(
      absoHit->GetEdep(), absoHit->GetTrackLength(),
      gapHit->GetEdep(), gapHit->GetTrackLength());
  }

  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, absoHit->GetEdep());
  analysisManager->FillH1(1, gapHit->GetEdep());
  analysisManager->FillH1(2, absoHit->GetTrackLength());
  analysisManager->FillH1(3, gapHit->GetTrackLength());

  // fill ntuple
  analysisManager->FillNtupleDColumn(0, absoHit->GetEdep());
  analysisManager->FillNtupleDColumn(1, gapHit->GetEdep());
  analysisManager->FillNtupleDColumn(2, absoHit->GetTrackLength());
  analysisManager->FillNtupleDColumn(3, gapHit->GetTrackLength());
  analysisManager->AddNtupleRow();
*/

  
  // G4HCofThisEvent * HCE = event->GetHCofThisEvent();
  // for(int i=0;i<32;i++){
  //   LISAHitsCollection* collection = (LISAHitsCollection*)(HCE->GetHC(i));
  //   G4cout << "collection->entries()" << collection->entries() << endl;
  // }
  // cout << "ende " << endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
