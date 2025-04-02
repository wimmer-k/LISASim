
#ifndef CrazyDiamond_H
#define CrazyDiamond_H 1



#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class CrazyDiamond 
{
public:



  CrazyDiamond();
  ~CrazyDiamond();
  
  G4Box *Build();

  void setDThickness(G4double);
  void setDDimX(G4double);
  void setName(G4String);
  void setDDimY(G4double);
  



//getters

  G4double GetDThickness() const {return DThickness;};
  G4double GetDDimX() const {return DDimX;};
  G4double GetDDimY() const {return DDimY;};
  G4String GetName() const {return Name;};

private:
  // dimensions
  G4double DThickness ;
  G4double DDimX ;
  G4double DDimY ;
  G4String Name ; 

G4Box* CrazyDiamondBox ;


  


};

#endif

