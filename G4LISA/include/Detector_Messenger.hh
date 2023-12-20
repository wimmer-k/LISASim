#ifndef Detector_Messenger_h
#define Detector_Messenger_h 1

#include "globals.hh"
#include "DetectorConstruction.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class DetectorConstruction;

class Detector_Messenger: public G4UImessenger
{
public:
  Detector_Messenger(DetectorConstruction* det);
  ~Detector_Messenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  DetectorConstruction* fDetector;    
  G4UIdirectory*             DetectorDir;
  G4UIcmdWithoutParameter*   UpdateCmd;
  G4UIcmdWithAnInteger*      LayerCmd;
  G4UIcmdWithAnInteger*      XdimCmd;
  G4UIcmdWithAnInteger*      YdimCmd;
  

};


#endif
