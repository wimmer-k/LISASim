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
  void SetLayerThickness(G4double);
  void SetLayerGap(G4double);
  void Setdim_x(G4int);
  void Setdim_y(G4int);
  void SetDiamondSizeXY(G4double);
  void SetPCB_thickness(G4double);
  void Setspace_x(G4double); 
  void Setspace_y(G4double);
  void Setbot_dist(G4double);
  void Settop_dist(G4double);
  void Setsidedist(G4double);
  void SetKW_radius(G4double);
  void SetKW_thicc(G4double);
  void SetKW_Zdim(G4double);
  void SetKW_switch(G4bool);
  void SetKW_h(G4double);
  


  // get
  G4int GetNbOfLayers() const {return fNofLayers;}; 
  G4double GetLayerThickness(G4int i) const {return fLayerThickness[i];};
  G4double GetLayerGap(G4int i) const {return fLayerGap[i];};
  G4int Getdim_x() const {return f_dim_x;};
  G4int Getdim_y() const {return f_dim_y;};
  G4double GetDiamondSizeXY() const {return DiamondSizeXY;};
  G4double GetPCB_thickness() const {return PCB_thickness;};
  G4double Getspace_x() const {return f_space_x;};
  G4double Getspace_y() const {return f_space_y;};
  G4double Getbot_dist() const {return bot_dist;};
  G4double Gettop_dist() const {return top_dist;};
  G4double Getsidedist() const {return side_dist;};
  G4double GetKW_radius() const {return KW_radius;};
  G4double GetKW_thicc() const {return KW_thicc;};
  G4double GetKW_Zdim() const {return KW_Zdim;};
  G4bool GetKW_switch() const {return KW_switch;};
  G4double GetKW_h() const {return KW_h;};

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
  G4double KW_radius = -1 ;
  G4double KW_thicc = -1 ;
  G4double KW_Zdim = -2 ; 
  G4bool KW_switch = false ;
  G4double KW_h = -2 ;
  G4double fLayerThick = -1 ;
  G4double fLayerGa = -1 ;
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

