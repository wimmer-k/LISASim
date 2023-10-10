#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction(DataManager *data){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  fdata = data;
  fdata->Clear();
  fdata->Init();
}

RunAction::~RunAction(){
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/){
  fdata->Clear();
  fdata->Init();
}

void RunAction::EndOfRunAction(const G4Run* /*run*/){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  fdata->Close();
}
