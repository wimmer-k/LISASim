
#include "CrazyDiamond.hh"

CrazyDiamond::CrazyDiamond()
{

  DThickness = 0.51*mm;
  DDimX = 5.*mm;
  DDimY   = 5.*mm; 
  Name = "Muda" ; 



CrazyDiamondBox = new G4Box("DiamondBox",DDimX/2,DDimY/2,DThickness/2);

}

CrazyDiamond::~CrazyDiamond()
{;}
//-----------------------------------------------------------------------------
G4Box* CrazyDiamond::Build()
{

    
    CrazyDiamondBox = new G4Box(Name,DDimX/2,DDimY/2,DThickness/2);
  G4cout<<"Building CrazyDiamondBox with dimX:   "<<DDimX<<"  dimY:  "<<DDimY<<"  Thickness:  "<<DThickness<<G4endl;

  return CrazyDiamondBox;
}

//-----------------------------------------------------------------------------
void CrazyDiamond::setDThickness(G4double in)
{

    DThickness = in; 


  //  G4cout<<"---->  Diamond thickness set to "<<in<< G4endl;

}
//-----------------------------------------------------------------------------
void CrazyDiamond::setDDimX(G4double in)
{

    DDimX = in; 


  //  G4cout<<"---->  Diamond Xdim set to "<<in<< G4endl;

}
//-----------------------------------------------------------------------------
void CrazyDiamond::setDDimY(G4double in)
{

    DDimY = in; 


  //  G4cout<<"---->  Diamond Ydim set to "<<in<< G4endl;

}


void CrazyDiamond::setName(G4String in)
{

      Name = in; 

  //  G4cout<<"---->  Diamond Name set to "<<in<< G4endl;

}



//-----------------------------------------------------------------------------

//---------------------------------------------------------------------


