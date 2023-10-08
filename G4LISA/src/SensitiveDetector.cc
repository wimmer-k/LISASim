/***********************************************************************
 *
 *    sensitive detector for detector read-out of hodoscope
 *
 ***********************************************************************/

#include "SensitiveDetector.hh"

using namespace std;
SensitiveDetector::SensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name)
{
  collectionName.insert(name);
}

SensitiveDetector::~SensitiveDetector(){;}

void SensitiveDetector::Initialize(G4HCofThisEvent* evnt){
  //G4cout << __PRETTY_FUNCTION__ << "\t" << HC << "\t"<< name << G4endl;
  G4cout << __PRETTY_FUNCTION__ << "\t" << SensitiveDetectorName <<"\t";
  static G4int HCID;
  HCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  G4cout << "-------------------->>>>>>>>>>>>>>>>>>> HCID " << HCID << G4endl;
  fhitsCollection = new LISAHitsCollection(SensitiveDetectorName,SensitiveDetectorName);

  evnt->AddHitsCollection(HCID, fhitsCollection);
  //G4cout << "added " << G4endl;
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();


  G4double edep = aStep->GetTotalEnergyDeposit();
  G4cout << "edep " << edep;
  if(edep==0)
    return true;

  LISAHit* newHit = new LISAHit();

  //newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  //newHit->SetParentID(aStep->GetTrack()->GetParentID());
  newHit->SetEdep(edep);

  G4StepPoint* stepPoint;
  if(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")
    stepPoint = aStep->GetPreStepPoint();
  else
    stepPoint = aStep->GetPostStepPoint();

  G4ThreeVector position = stepPoint->GetPosition(); 
  G4cout << ", at (" << position.x() << ", " << position.y() << ", " << position.z() << ")";
  newHit->SetPos(position);

  /*
  G4TouchableHandle theTouchable = stepPoint->GetTouchableHandle();

  G4ThreeVector det_position = theTouchable->GetHistory()->GetTopTransform().TransformPoint(position);
  newHit->SetPosInDet(det_position);
  */


  //check which HitCollectionID this is
  //G4cout << "checking collection id entries " <<fhitsCollection->entries() << G4endl;
  int CollectionID = SDman->GetCollectionID(fhitsCollection);
  G4cout<<", CollectionID = "<<CollectionID;
  CollectionID -= SDman->GetCollectionID("layer_0");
  G4cout<<", LayerID = "<<CollectionID<<G4endl;
  
  newHit->SetLayerID(CollectionID);
 

  /*
  newHit->SetTrack(aStep->GetTrack());
  newHit->SetProcName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
  newHit->SetStep(aStep->GetTrack()->GetCurrentStepNumber());
  
  if( aStep->GetTrack()->GetNextVolume() != 0 ) 
    { 
      newHit->SetVolume(aStep->GetTrack()->GetVolume()->GetName());
    } 
  else 
    {
      newHit->SetVolume("OutOfWorld");
    }
*/
  fhitsCollection->insert(newHit);
  

  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{;}

