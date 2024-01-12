#ifndef DataManager_h
#define DataManager_h 1


#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include "globals.hh"
#include "EventInfo.hh"
#include "G4UnitsTable.hh"

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
  SimEvent* GetSimEvent(){return fsim;}
  LISAEvent* GetLISAEvent(){return flisa;}
  
  
private:
  int fnevents;
  SimEvent* fsim;
  LISAEvent* flisa;
  TTree* ftree;
  TFile* ffile;
};

#endif

