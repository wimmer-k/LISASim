#ifndef DataManager_h
#define DataManager_h 1

#include "G4UnitsTable.hh"
#include "globals.hh"

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>

#include "EventInfo.hh"

class DataManager{
public:
  DataManager();
  DataManager(G4String filename/*, int nevents*/);
  ~DataManager();
  void Init();
  void FillTree(EventInfo* info);
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  SimEvent* fsim;
  LISAEvent* flisa;
  TTree* ftree;
  TFile* ffile;
};

#endif

