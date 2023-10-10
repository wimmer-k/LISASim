#include "SensitiveDetector.hh"

using namespace std;
SensitiveDetector::SensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name) {
  collectionName.insert(name);
}

SensitiveDetector::~SensitiveDetector(){;}

void SensitiveDetector::Initialize(G4HCofThisEvent* evnt){
  //G4cout << __PRETTY_FUNCTION__ << "\t" << HC << "\t"<< name << G4endl;
  static G4int HCID;
  HCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  fhitsCollection = new LISAHitsCollection(SensitiveDetectorName,SensitiveDetectorName);

  evnt->AddHitsCollection(HCID, fhitsCollection);
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();


  G4double edep = aStep->GetTotalEnergyDeposit();
  // G4cout << "edep " << edep;
  if(edep==0)
    return true;

  LISAHit* newHit = new LISAHit();

   newHit->SetEdep(edep);

  G4StepPoint* stepPoint;
  if(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")
    stepPoint = aStep->GetPreStepPoint();
  else
    stepPoint = aStep->GetPostStepPoint();

  G4ThreeVector position = stepPoint->GetPosition(); 
  // G4cout << ", at (" << position.x() << ", " << position.y() << ", " << position.z() << ")";
  newHit->SetPos(position);


  int CollectionID = SDman->GetCollectionID(fhitsCollection);
  // G4cout<<", CollectionID = "<<CollectionID;
  CollectionID -= SDman->GetCollectionID("layer_0");
  // G4cout<<", LayerID = "<<CollectionID<<G4endl;
  
  newHit->SetLayerID(CollectionID);
 
  fhitsCollection->insert(newHit);
  

  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {;}

