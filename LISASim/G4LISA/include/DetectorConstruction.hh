#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.h"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

  // set
  void SetNbOfLayers(G4int);
  void SetLayerThickness(G4int,G4double);
  void SetLayerGap(G4int,G4double);

  // get
  G4int GetNbOfLayers() const {return fNofLayers;}; 
  G4double GetLayerThickness(G4int i) const {return fLayerThickness[i];};
  G4double GetLayerGap(G4int i) const {return fLayerGap[i];};


  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;
  
private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

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

  G4Box* fLayer_solid[MAXTARGETS];
  G4LogicalVolume* fLayer_logic[MAXTARGETS];
  G4VPhysicalVolume* fLayer_place[MAXTARGETS];
  G4Box* PCB_box ;
  G4Box* PCB_box_hole;  
  G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
};

#endif

