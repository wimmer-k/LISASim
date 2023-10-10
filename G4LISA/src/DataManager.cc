#include "DataManager.hh"
ClassImp(SimEvent)
ClassImp(LISAEvent)

using namespace std;
using namespace CLHEP;

DataManager::DataManager(){
  Init();
}
DataManager::DataManager(G4String filename/*, int nevents*/){
  //fnevents = nevents;
  ffile = new TFile(filename,"RECREATE");
  Init();
}
DataManager::~DataManager(){
  this->Close();
  delete ftree;
  delete ffile;
  delete flisa;
  delete fsim;
}
void DataManager::Init(){
  ffile->cd();
  fsim = new SimEvent();
  flisa = new LISAEvent();
  ftree = new TTree("str", "LISA simulated data");
  ftree->Branch("simData", &fsim);
  ftree->Branch("lisaData", &flisa);
  ftree->BranchRef();
}
void DataManager::FillTree(EventInfo* info){

  Clear();
  fsim = info->GetSimEvent();
  flisa = info->GetLISAEvent();
  ftree->Fill();
}
void DataManager::Clear(const Option_t*){
  fsim->Clear();
  flisa->Clear();
}
void DataManager::Close(){
  ffile->cd();
  ffile->Write();  
  ffile->Close();
}



