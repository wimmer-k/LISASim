
#include "DetectorConstruction_Messenger.hh"

DetectorConstruction_Messenger::DetectorConstruction_Messenger(DetectorConstruction* Det)
:DetIn(Det)
{ 
 
  DetInDir = new G4UIdirectory("/DetIn/");
  DetInDir->SetGuidance("geometry control.");
  
  fNofLayersCmd = new G4UIcmdWithAnInteger("/DetIn/NLay",this);
  fNofLayersCmd->SetGuidance("Select the number of layers");
  fNofLayersCmd->SetParameterName("choice",false);
  fNofLayersCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  f_dim_xCmd = new G4UIcmdWithAnInteger("/DetIn/DimX",this);
  f_dim_xCmd->SetGuidance("Select the X dimension of the detector array");
  f_dim_xCmd->SetParameterName("choice",false);
  f_dim_xCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  f_dim_yCmd = new G4UIcmdWithAnInteger("/DetIn/DimY",this);
  f_dim_yCmd->SetGuidance("Select the Y dimension of the detector array");
  f_dim_yCmd->SetParameterName("choice",false);
  f_dim_yCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DiamondSizeXYCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/SizeXY",this);
  DiamondSizeXYCmd->SetGuidance("Select the radius for the target");
  DiamondSizeXYCmd->SetParameterName("choice",false);
  DiamondSizeXYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PCB_thicknessCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/PCB_thic",this);
  PCB_thicknessCmd->SetGuidance("Select the X length for the target");
  PCB_thicknessCmd->SetParameterName("choice",false);
  PCB_thicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  f_space_xCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/SpaceX",this);
  f_space_xCmd->SetGuidance("Select the Y length for the target");
  f_space_xCmd->SetParameterName("choice",false);
  f_space_xCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  f_space_yCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/SpaceY",this);
  f_space_yCmd->SetGuidance("Select the Y length for the target");
  f_space_yCmd->SetParameterName("choice",false);
  f_space_yCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  bot_distCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/BotDist",this);
  bot_distCmd->SetGuidance("Select the position of the target along the X axis.");
  bot_distCmd->SetParameterName("choice",false);
  bot_distCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  top_distCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/TopDist",this);
  top_distCmd->SetGuidance("Select the position of the target along the Y axis.");
  top_distCmd->SetParameterName("choice",false);
  top_distCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  side_distCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/SideDist",this);
  side_distCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  side_distCmd->SetParameterName("choice",false);
  side_distCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KW_radiusCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/KWRad",this);
  KW_radiusCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  KW_radiusCmd->SetParameterName("choice",false);
  KW_radiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KW_thiccCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/KWThic",this);
  KW_thiccCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  KW_thiccCmd->SetParameterName("choice",false);
  KW_thiccCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  KW_ZdimCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/KWZ",this);
  KW_ZdimCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  KW_ZdimCmd->SetParameterName("choice",false);
  KW_ZdimCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KW_switchCmd = new G4UIcmdWithAnInteger("/DetIn/KWSwitch",this);
  KW_switchCmd->SetGuidance("Select the number of steps in the target");
  KW_switchCmd->SetParameterName("choice",false);
  KW_switchCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KW_hCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/KWh",this);
  KW_hCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  KW_hCmd->SetParameterName("choice",false);
  KW_hCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLayerThickCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/LayThic",this);
  fLayerThickCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  fLayerThickCmd->SetParameterName("choice",false);
  fLayerThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fLayerGaCmd = new G4UIcmdWithADoubleAndUnit("/DetIn/LayGap",this);
  fLayerGaCmd->SetGuidance("Select the position of the target along the beam axis (Z direction.");
  fLayerGaCmd->SetParameterName("choice",false);
  fLayerGaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // RepCmd = new G4UIcmdWithoutParameter("/DetIn/Report",this);
  // RepCmd->SetGuidance("Report geometry parameters");  

}



DetectorConstruction_Messenger::~DetectorConstruction_Messenger()
{
  delete fNofLayersCmd;    
  delete f_dim_xCmd;
  delete f_dim_yCmd;
  delete DiamondSizeXYCmd;
  delete PCB_thicknessCmd;
  delete f_space_xCmd;
  delete f_space_yCmd ;
  delete bot_distCmd;
  delete top_distCmd ;
  delete side_distCmd;
  delete KW_radiusCmd;
  delete KW_thiccCmd;
  delete KW_ZdimCmd; 
  delete KW_switchCmd;
  delete KW_hCmd;
  delete fLayerThickCmd;
  delete fLayerGaCmd;
}


void DetectorConstruction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  

  if( command == fNofLayersCmd )
   { DetIn->SetNbOfLayers(fNofLayersCmd->GetNewIntValue(newValue));}

  if( command == f_dim_xCmd )
  { DetIn->Setdim_x(f_dim_xCmd->GetNewIntValue(newValue));}

  if( command == f_dim_yCmd )
   { DetIn->Setdim_y(f_dim_yCmd->GetNewIntValue(newValue));}

  if( command == DiamondSizeXYCmd )
   { DetIn->SetDiamondSizeXY(DiamondSizeXYCmd->GetNewDoubleValue(newValue));}

  if( command == PCB_thicknessCmd )
   { DetIn->SetPCB_thickness(PCB_thicknessCmd->GetNewDoubleValue(newValue));}

  if( command == f_space_xCmd )
   { DetIn->Setspace_x(f_space_xCmd->GetNewDoubleValue(newValue));}

  if( command == f_space_yCmd )
   { DetIn->Setspace_y(f_space_yCmd->GetNewDoubleValue(newValue));}

  if( command == bot_distCmd )
   { DetIn->Setbot_dist(bot_distCmd->GetNewDoubleValue(newValue));}

  if( command == top_distCmd )
   { DetIn->Settop_dist(top_distCmd->GetNewDoubleValue(newValue));}

  if( command == side_distCmd )
   { DetIn->Setsidedist(side_distCmd->GetNewDoubleValue(newValue));}

  if( command == KW_radiusCmd )
   { DetIn->SetKW_radius(KW_radiusCmd->GetNewDoubleValue(newValue));}


  if( command == KW_thiccCmd )
   { DetIn->SetKW_thicc(KW_thiccCmd->GetNewDoubleValue(newValue));}

  if( command == KW_ZdimCmd )
   { DetIn->SetKW_Zdim(KW_ZdimCmd->GetNewDoubleValue(newValue));}

  if( command == KW_switchCmd )
   { DetIn->SetKW_switch(KW_switchCmd->GetNewIntValue(newValue));}

  if( command == KW_hCmd )
   { DetIn->SetKW_h(KW_hCmd->GetNewDoubleValue(newValue));}

  if( command == fLayerThickCmd )
   { DetIn->SetLayerThickness(fLayerThickCmd->GetNewDoubleValue(newValue));}

  if( command == fLayerGaCmd )
   { DetIn->SetLayerGap(fLayerGaCmd->GetNewDoubleValue(newValue));}

   
  // if( command == RepCmd )
  //  { DetIn->Report();}
}
