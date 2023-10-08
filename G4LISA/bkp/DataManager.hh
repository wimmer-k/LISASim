#ifndef DataManager_h
#define DataManager_h 1

#include "G4UnitsTable.hh"
#include "globals.h"

class DataManager;
#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>

#include "EventInfo.hh"

class DataManager{
public:
  DataManager();
  DataManager(const char* filename, int nevents);
  ~DataManager();
  void Init(const char* filename);
  void FillTree(LISAEvent* lisa,SimEvent* sim);
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  LISAEvent* flisa;
  SimEvent* fsim;
  TTree* ftree;
  TFile* ffile;
};

#endif

