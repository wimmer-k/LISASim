#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *detConstruction, Incoming_Beam* BI):BeamIn(BI),fdetector(detConstruction)


{
  
  // n_particle = 1;
  // fParticleGun = new G4ParticleGun(n_particle);

  // // default particle kinematic
  
  // auto particleDefinition
  //   = G4ParticleTable::GetParticleTable()->FindParticle("e+");
  // fParticleGun->SetParticleDefinition(particleDefinition);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(100.*MeV);
   
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
 


   particleTable = G4ParticleTable::GetParticleTable();
   ionTable = G4IonTable::GetIonTable();

	ion =  ionTable->GetIon(BeamIn->getZ(),BeamIn->getA(),BeamIn->getEx());
   

  n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  
  auto particleDefinition
    = particleTable->FindParticle("e+");
  fParticleGun->SetParticleDefinition(ion);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(50000*MeV);



   G4cout<<BeamIn->getZ()<<G4endl;
	
	 position=BeamIn->getPosition();
	 fParticleGun->SetParticlePosition(position);
	
	 direction=BeamIn->getDirection();
	 fParticleGun->SetParticleMomentumDirection(direction);
	
	 KE=BeamIn->getKE(ion);
	 fParticleGun->SetParticleEnergy(KE);

	// fParticleGun->GeneratePrimaryVertex(anEvent);
fParticleGun->GeneratePrimaryVertex(anEvent);
  


  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
