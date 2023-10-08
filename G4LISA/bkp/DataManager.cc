#include "DataManager.hh"

using namespace std;
using namespace CLHEP;

DataManager::DataManager(){
}
DataManager::DataManager(const char* filename, int nevents){
  fnevents = nevents;
  ffile = new TFile(filename,"RECREATE");
  ffile->cd();
  flisa = new LISAEvent;
  fsim = new SimEvent;
  ftree = new TTree("str","simulation data");
  ftree->Branch("LISAEvent",&flisa,32000);
  ftree->Branch("SimEvent",&fsim,32000);
  ftree->BranchRef();
}
DataManager::~DataManager(){
  this->Close();
  delete ftree;
  delete ffile;
  delete flisa;
  delete fsim;
}
void DataManager::FillTree(LISAEvent *inlisa, SimEvent *insim){
  flisa->Clear();
  flisa = inlisa;
  fsim->Clear();
  fsim = insim;
  ftree->Fill();
}
void DataManager::Clear(const Option_t*){
  flisa->Clear();
  fsim->Clear();
}
void DataManager::Close(){
  ffile->cd();
  ftree->Write();
  ffile->Close();
}



