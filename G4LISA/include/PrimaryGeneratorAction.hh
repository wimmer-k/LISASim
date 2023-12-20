#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include <vector>
#include <string>

#include "globals.hh"
#include "Randomize.hh"
#include "DataManager.hh"
#include "Beam.hh"
#include "DetectorConstruction.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"


class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction(DetectorConstruction*,Beam*, DataManager*);
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* event) override;
  
  // set methods
  void SetRandomFlag(G4bool value);

private:
  G4ParticleGun* fParticleGun ; // G4 particle gun
  DetectorConstruction* fdetector;
  Beam* fbeamIn;
  DataManager* fdata;
  
  G4int n_particle;
  
  G4ParticleTable* particleTable;
  G4IonTable* ionTable;
  G4ParticleDefinition* ion;
  G4ThreeVector  direction;
  G4ThreeVector  position;
  G4double       KE;

};

#endif
