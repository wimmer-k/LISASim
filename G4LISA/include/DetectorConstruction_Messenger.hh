#ifndef DetectorConstruction_Messenger_h
#define DetectorConstruction_Messenger_h 1

#include "DetectorConstruction.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class DetectorConstruction_Messenger: public G4UImessenger
{
public:
  DetectorConstruction_Messenger(DetectorConstruction*);
  ~DetectorConstruction_Messenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  DetectorConstruction* DetIn;

  G4UIdirectory*             DetInDir;


  G4UIcmdWithAnInteger* fNofLayersCmd;    
  G4UIcmdWithAnInteger* f_dim_xCmd;
  G4UIcmdWithAnInteger* f_dim_yCmd;
  G4UIcmdWithADoubleAndUnit* DiamondSizeXYCmd;
  G4UIcmdWithADoubleAndUnit* PCB_thicknessCmd;
  G4UIcmdWithADoubleAndUnit* f_space_xCmd;
  G4UIcmdWithADoubleAndUnit* f_space_yCmd ;
  G4UIcmdWithADoubleAndUnit* bot_distCmd;
  G4UIcmdWithADoubleAndUnit* top_distCmd ;
  G4UIcmdWithADoubleAndUnit* side_distCmd;
  G4UIcmdWithADoubleAndUnit* KW_radiusCmd;
  G4UIcmdWithADoubleAndUnit* KW_thiccCmd;
  G4UIcmdWithADoubleAndUnit* KW_ZdimCmd; 
  G4UIcmdWithAnInteger* KW_switchCmd;
  G4UIcmdWithADoubleAndUnit* KW_hCmd;
  G4UIcmdWithADoubleAndUnit* fLayerThickCmd;
  G4UIcmdWithADoubleAndUnit* fLayerGaCmd;



};


#endif
