#include "Detector_Messenger.hh"


Detector_Messenger::Detector_Messenger(DetectorConstruction* det)
:fDetector(det){
  DetectorDir = new G4UIdirectory("/Detector/");
  DetectorDir->SetGuidance("Detector control.");

  UpdateCmd = new G4UIcmdWithoutParameter("/Detector/Update", this);
  UpdateCmd->SetGuidance("Update geometry.");
  UpdateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  LayerCmd = new G4UIcmdWithAnInteger("/Detector/NLayer",this);
  LayerCmd->SetGuidance("Select the number of layers");
  LayerCmd->SetParameterName("choice",false);
  LayerCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  XdimCmd = new G4UIcmdWithAnInteger("/Detector/X_dim",this);
  XdimCmd->SetGuidance("Set the number of detectors in X direction");
  XdimCmd->SetParameterName("choice",false);
  XdimCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YdimCmd = new G4UIcmdWithAnInteger("/Detector/Y_dim",this);
  YdimCmd->SetGuidance("Set the number of detectors in Y direction");
  YdimCmd->SetParameterName("choice",false);
  YdimCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}
Detector_Messenger::~Detector_Messenger(){
  delete LayerCmd;
  delete XdimCmd;
  delete YdimCmd;
}

void Detector_Messenger::SetNewValue(G4UIcommand* command,G4String newValue){
  if( command == LayerCmd )
    fDetector->SetNbOfLayers(LayerCmd->GetNewIntValue(newValue));
  if( command == XdimCmd )
    fDetector->SetXdim(XdimCmd->GetNewIntValue(newValue));
  if( command == YdimCmd )
    fDetector->SetYdim(YdimCmd->GetNewIntValue(newValue));
  if( command == UpdateCmd ) {
    fDetector->ConstructLISA();
  } 
  
}
