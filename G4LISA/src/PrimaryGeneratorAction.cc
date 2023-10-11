#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *detector){
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  auto particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(50.*MeV);
  fdetector = detector;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  G4double worldZHalfLength = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;
  if(worldLV){
    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  }

  if(worldBox){
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else{
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  }
  
  // Set gun position
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));

  fParticleGun->GeneratePrimaryVertex(anEvent);

  

  G4cout << G4endl << "------------------------------------------------------------" << G4endl;
  G4cout << "shooting " << fParticleGun->GetParticleDefinition()->GetParticleName() << " with  " << fParticleGun->GetParticleEnergy() << " MeV from (" << 0.<<", "<<0.<<", "<<-worldZHalfLength<<") to (";
  G4cout << fParticleGun->GetParticleMomentumDirection().x() <<", " << fParticleGun->GetParticleMomentumDirection().y() <<", " << fParticleGun->GetParticleMomentumDirection().x() <<")" << G4endl;
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;

  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
