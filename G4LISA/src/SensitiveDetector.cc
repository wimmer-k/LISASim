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
  //G4cout << "edep " << edep;
  if(edep==0){
    return true;
    
  }
  LISAHit* newHit = new LISAHit();

   newHit->SetEdep(edep);
   //G4cout<<edep<<"EDEPPPPPPPPPPPPPPPPPp"<<G4endl;

  G4StepPoint* stepPoint;
  if(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")
    stepPoint = aStep->GetPreStepPoint();
  else
    stepPoint = aStep->GetPostStepPoint();

  G4ThreeVector position = stepPoint->GetPosition(); 
  // G4cout << ", at (" << position.x() << ", " << position.y() << ", " << position.z() << ")";
  newHit->SetPos(position);



///////////////nasty string manipulation//////////////////////////////////////

  G4String str = SensitiveDetectorName ;
  //G4cout<<SensitiveDetectorName<<"   Sens_det_name"<<G4endl;

  char last = str[str.size()-1];
  char last_2 = str[str.size()-2];
  char last_3 = str[str.size()-3];

  //G4cout<<str<<"    "<<last_3<<"   "<<last_2<<"  "<<last<<G4endl;
  
  // G4int last_3_int = (last_3 - '0') *100 +100 ;
  // G4int last_2_int = (last_2 - '0') *10 +10 ;
  // G4int last_int =  (last - '0') *1 +1 ;
  // G4int Det_No = last_3_int + last_2_int + last_int ;
  G4int last_3_int = (last_3 - '0');
  G4int last_2_int = (last_2 - '0');
  G4int last_int =  (last - '0');
  //G4cout<<str<<"    "<<last_3_int<<"   "<<last_2_int<<"  "<<last_int<<"   "<<Det_No<<G4endl;

  //G4int CollectionID = SDman->GetCollectionID(fhitsCollection);
   //G4cout<<", Csddddddddddddddddd = "<<fhitsCollection<<G4endl;
  //G4cout<<", CollectionID = "<<SensitiveDetectorName<<G4endl;
  //CollectionID -= SDman->GetCollectionID("layer_0");
  // G4cout<<", LayerID = "<<CollectionID<<G4endl;
  
  //newHit->SetLayerID(CollectionID);
  newHit->SetLayerID(last_3_int);
  newHit->SetX(last_int);
  newHit->SetY(last_2_int);
  //G4cout<<last_3_int<<"  lastint"<<G4endl; 
  //newHit->AddEdep(edep);
  fhitsCollection->insert(newHit);
  

  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {;}

