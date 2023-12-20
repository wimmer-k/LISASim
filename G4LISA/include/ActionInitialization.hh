#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include <G4String.hh>

#include "DetectorConstruction.hh"
#include "DataManager.hh"
#include "Beam.hh"
/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
public:
  ActionInitialization(DataManager*, DetectorConstruction*,Beam*);
  ~ActionInitialization() override;

  void BuildForMaster() const override;
  void Build() const override;
  
private:
  DataManager* fdata;
  DetectorConstruction* fdetector;
  Beam* fbeamIn ;
  
};
#endif


