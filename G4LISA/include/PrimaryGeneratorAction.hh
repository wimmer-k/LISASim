#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction(DetectorConstruction*);
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* event) override;

  // set methods
  void SetRandomFlag(G4bool value);

private:
  G4ParticleGun* fParticleGun = nullptr; // G4 particle gun
  DetectorConstruction* fdetector;
};

#endif
