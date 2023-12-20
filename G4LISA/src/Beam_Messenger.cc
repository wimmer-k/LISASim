#include "Beam_Messenger.hh"


Beam_Messenger::Beam_Messenger(Beam* BI)
:fBeam(BI)
{ 
 
  BeamDir = new G4UIdirectory("/Beam/");
  BeamDir->SetGuidance("Incoming beam control.");

  fcDir = new G4UIdirectory("/Beam/Focus/");
  fcDir->SetGuidance("Incoming beam focal point control.");
  
  ACmd = new G4UIcmdWithAnInteger("/Beam/A",this);
  ACmd->SetGuidance("Select the mass number for the incoming beam.");
  ACmd->SetParameterName("choice",false);
  ACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithAnInteger("/Beam/Z",this);
  ZCmd->SetGuidance("Select the atomic number for the incoming beam.");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KECmd = new G4UIcmdWithADoubleAndUnit("/Beam/KE",this);
  KECmd->SetGuidance("Set kinetic energy for the incoming beam.");
  KECmd->SetParameterName("choice",false);
  KECmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KEuCmd = new G4UIcmdWithADoubleAndUnit("/Beam/KEu",this);
  KEuCmd->SetGuidance("Set kinetic energy per nucleon for the incoming beam.");
  KEuCmd->SetParameterName("choice",false);
  KEuCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcXCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/X",this);
  fcXCmd->SetGuidance("Set focal point X position for the incoming beam.");
  fcXCmd->SetParameterName("choice",false);
  fcXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcDXCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/DX",this);
  fcDXCmd->SetGuidance("Set focal point DX size for the incoming beam.");
  fcDXCmd->SetParameterName("choice",false);
  fcDXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcYCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/Y",this);
  fcYCmd->SetGuidance("Set focal point Y position for the incoming beam.");
  fcYCmd->SetParameterName("choice",false);
  fcYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcDYCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/DY",this);
  fcDYCmd->SetGuidance("Set focal point DY size for the incoming beam.");
  fcDYCmd->SetParameterName("choice",false);
  fcDYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fcZCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/Z",this);
  fcZCmd->SetGuidance("Set focal point Z position for the incoming beam.");
  fcZCmd->SetParameterName("choice",false);
  fcZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  maxACmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/maxAta",this);
  maxACmd->SetGuidance("Set dispersive direction angular divergence for the incoming beam.");
  maxACmd->SetParameterName("choice",false);
  maxACmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  maxBCmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/maxBta",this);
  maxBCmd->SetGuidance("Set non dispersive direction angular divergence for the incoming beam.");
  maxBCmd->SetParameterName("choice",false);
  maxBCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  DppCmd = new G4UIcmdWithADouble("/Beam/Dpp",this);
  DppCmd->SetGuidance("Set momentum acceptance for the incoming beam.");
  DppCmd->SetParameterName("choice",false);
  DppCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RepCmd = new G4UIcmdWithoutParameter("/Beam/Report",this);
  RepCmd->SetGuidance("Report parameters for the incoming beam");

  Ata0Cmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/Ata0",this);
  Ata0Cmd->SetGuidance("Set Ata angle on target for the incoming beam.");
  Ata0Cmd->SetParameterName("choice",false);
  Ata0Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  Bta0Cmd = new G4UIcmdWithADoubleAndUnit("/Beam/Focus/Bta0",this);
  Bta0Cmd->SetGuidance("Set Bta angle on target for the incoming beam.");
  Bta0Cmd->SetParameterName("choice",false);
  Bta0Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}



Beam_Messenger::~Beam_Messenger()
{
  delete maxACmd;
  delete maxBCmd;
  delete fcXCmd;
  delete fcYCmd;
  delete fcZCmd;
  delete fcDXCmd;
  delete fcDYCmd;
  delete DppCmd;
  delete KEuCmd;
  delete KECmd;
  delete RepCmd;
  delete ZCmd;
  delete ACmd;
  delete Ata0Cmd;
  delete Bta0Cmd;
}


void Beam_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

  if( command == ACmd )
    { fBeam->setA(ACmd->GetNewIntValue(newValue));}
  if( command == ZCmd )
    { fBeam->setZ(ZCmd->GetNewIntValue(newValue));}
  if( command == KECmd )
    { fBeam->setKE(KECmd->GetNewDoubleValue(newValue));}
  if( command == KEuCmd )
    { fBeam->setKEu(KEuCmd->GetNewDoubleValue(newValue));}
  if( command == DppCmd )
    { fBeam->setDpp(DppCmd->GetNewDoubleValue(newValue));}
  if( command == fcXCmd )
    { fBeam->setfcX(fcXCmd->GetNewDoubleValue(newValue));}
  if( command == fcDXCmd )
    { fBeam->setfcDX(fcDXCmd->GetNewDoubleValue(newValue));}
  if( command == fcYCmd )
    { fBeam->setfcY(fcYCmd->GetNewDoubleValue(newValue));}
  if( command == fcDYCmd )
    { fBeam->setfcDY(fcDYCmd->GetNewDoubleValue(newValue));}
  if( command == fcZCmd )
    { fBeam->setfcZ(fcZCmd->GetNewDoubleValue(newValue));}
  if( command == maxACmd )
    { fBeam->setmaxAta(maxACmd->GetNewDoubleValue(newValue));}
 if( command == maxBCmd )
    { fBeam->setmaxBta(maxBCmd->GetNewDoubleValue(newValue));}
  if( command == Ata0Cmd )
    { fBeam->setAta0(Ata0Cmd->GetNewDoubleValue(newValue));}
  if( command == Bta0Cmd )
    { fBeam->setBta0(Bta0Cmd->GetNewDoubleValue(newValue));}
  if( command == RepCmd )
    { fBeam->Report();}

}
