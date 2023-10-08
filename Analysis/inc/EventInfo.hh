#ifndef EventInformation_h
#define EventInformation_h 1

#include "G4VUserEventInformation.hh"
//#include "G4ThreeVector.hh"
//#include "G4SystemOfUnits.hh"

#include <vector>

#include "TObject.h"
#include "TVector3.h"
using namespace std;

class LISAEvent : public TObject {
public:
  LISAEvent(){
    Clear();
  }
  void Clear(Option_t * /*option*/ =""){
    fEdet.clear();
  }
  void SetEdet(vector<double> Edet){fEdet = Edet;}
  
  vector<double> GetEnergyDetected(){return fEdet;}
  
protected:
  vector<double> fEdet;
  ClassDef(LISAEvent, 1);
};


class SimEvent : public TObject {
public:
  SimEvent(){
    Clear();
  }
  void Clear(Option_t * /*option*/ =""){
    fincdir.SetXYZ(-100,0,0);
    fincpos.SetXYZ(-10,0,0);
    fEbeam = 0;

    foutdir.SetXYZ(-100,0,0);
    foutpos.SetXYZ(-10,0,0);
    
    fbetas.clear();
    freacpos.SetXYZ(-10,0,0);
  }
  // setters
  void SetNLayers(int n){fbetas.resize(n);}
  void SetEventID(int n){feventID = n;}

  void SetIncomingDirection(TVector3 dir){fincdir = dir;}
  void SetIncomingPosition(TVector3 pos){fincpos = pos;}
  void SetBeamEnergy(double Ebeam){fEbeam = Ebeam;}

  void SetOutGoingDirection(TVector3 dir){foutdir = dir;}
  void SetOutGoingPosition(TVector3 pos){foutpos = pos;}
  void SetOutGoingBeta(vector<double> betas){fbetas = betas;}
  void SetOutGoingBeta(int n,double beta){fbetas[n] = beta;}

  void SetReactionPosition(TVector3 pos){freacpos = pos;}
  
  // getters
  Int_t GetEventID(){return feventID;}
  UShort_t GetNLayers(){return fbetas.size();}
  TVector3 GetIncomingDirection(){return fincdir;}
  TVector3 GetIncomingPosition(){return fincpos;}
  double GetBeamEnergy(){return fEbeam;}

  TVector3 GetOutgoingDirection(){return foutdir;}
  TVector3 GetOutgoingPosition(){return foutpos;}
  vector<double> GetOutGoingBeta(){return fbetas;}
  double GetOutGoingBeta(int n){return fbetas[n];}
  
  TVector3 GetReactionPosition(){return freacpos;}
  
protected:
  Int_t feventID;
  TVector3 fincdir;
  TVector3 fincpos;
  double fEbeam;
  TVector3 foutdir;
  TVector3 foutpos;
  

  vector<double> fbetas;
  
  TVector3 freacpos;
  
  ClassDef(SimEvent, 1);
};


class EventInfo : public G4VUserEventInformation {
public:

  EventInfo(){
    fsimevent = new SimEvent;
    flisaevent = new LISAEvent;
  }
  SimEvent* GetSimEvent(){return fsimevent;}
  LISAEvent* GetLISAEvent(){return flisaevent;}
  ~EventInfo(){};

  inline virtual void Print()const{;}
private:
  SimEvent* fsimevent;
  LISAEvent* flisaevent;
};


#endif
