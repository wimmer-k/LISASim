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
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *detConstruction, Incoming_Beam* BI,DataManager* data){
  fdetector = detConstruction;
  fbeamIn = BI;
  fdata = data;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
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

  ion =  ionTable->GetIon(fbeamIn->getZ(),fbeamIn->getA(),fbeamIn->getEx());
   

  n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  
  // auto particleDefinition = particleTable->FindParticle("e+");
 
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(50000*MeV);
  
 fParticleGun->SetParticleDefinition(ion);

  //G4cout<<fbeamIn->getZ()<<G4endl;
	
  position=fbeamIn->getPosition();
  fParticleGun->SetParticlePosition(position);
	
  direction=fbeamIn->getDirection();
  fParticleGun->SetParticleMomentumDirection(direction);
	
  KE=fbeamIn->getKE(ion);
  fParticleGun->SetParticleEnergy(KE);

  // fParticleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun->GeneratePrimaryVertex(anEvent);


  SimEvent* sim = fdata->GetSimEvent();
  sim->SetBeamEnergy(KE);
  sim->SetIncomingDirection(TVector3(direction.getX(),direction.getY(),direction.getZ()));
  sim->SetIncomingPosition(TVector3(position.getX(),position.getY(),position.getZ()));

  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
