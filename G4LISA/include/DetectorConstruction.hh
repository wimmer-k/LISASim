#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.h"
#include "G4VUserDetectorConstruction.hh"
#include "Detector_Messenger.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class Detector_Messenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

  // set
  void SetNbOfLayers(G4int);
  void SetXdim(G4int);
  void SetYdim(G4int);
  void SetLayerThickness(G4int,G4double);
  void SetLayerGap(G4int,G4double);

  // get
  G4int GetNbOfLayers() const {return fNofLayers;}; 
  G4double GetLayerThickness(G4int i) const {return fLayerThickness[i];};
  G4double GetLayerGap(G4int i) const {return fLayerGap[i];};


  G4VPhysicalVolume* Construct() override;
  //void ConstructSDandField() override;
  void ConstructLISA();
  
private:
  void DefineMaterials();
  G4VPhysicalVolume* ConstructWorld();
  void ConstructPCB();
  void ConstructDetectors();
  void ConstructSensitive();
  

  Detector_Messenger *fdetMessenger;

  G4int fNofLayers = -1;     // number of layers
  G4int f_dim_x = -1;
  G4int f_dim_y = -1;
  
  G4double DiamondSizeXY = -1;
  G4double PCB_thickness =-1;
  G4double f_space_x = -1 ;
  G4double f_space_y = -1 ;
  G4double bot_dist = -1 ;
  G4double top_dist = -1 ;
  G4double side_dist = -1 ;
  G4double fLayerThickness[MAXTARGETS];
  G4double fLayerGap[MAXTARGETS];

  // Logical volumes
  G4LogicalVolume* fworld_logic;
  G4LogicalVolume* fPCB_general;
  
  G4Box* fLayer_solid[MAXTARGETS];
  G4LogicalVolume* fLayer_logic[MAXTARGETS];
  G4VPhysicalVolume* fLayer_place[MAXTARGETS];
  G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps


  std::vector<double> xes_new;
  std::vector<double> yes_new;



};

#endif

