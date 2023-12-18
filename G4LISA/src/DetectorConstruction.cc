/**
 * @brief Detector construction class for LISA
 */

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


/**
     * Create a new DetectorConstruction.
     * @brief Default constructor.
     */
DetectorConstruction::DetectorConstruction(){
  // Geometry parameters, to be passed by messenger or settings file
  f_dim_x = 2;
  f_dim_y = 2;
  fNofLayers = 5;
  DiamondSizeXY = 5*mm;
  PCB_thickness = 1.*mm;
  f_space_x = 1.*mm ;
  f_space_y = 1.*mm ;
  bot_dist = 32*mm ;
  top_dist = 15*mm ;
  side_dist = 15*mm ;

  fLayerThickness[0] = 0.5*mm;
  fLayerThickness[1] = 0.5*mm;
  fLayerThickness[2] = 0.5*mm;
  fLayerThickness[3] = 0.5*mm;
  fLayerThickness[4] = 0.5*mm;
  fLayerGap[0] = 1.0*mm;
  fLayerGap[1] = 1.0*mm;
  fLayerGap[2] = 1.0*mm;
  fLayerGap[3] = 1.0*mm;
  fLayerGap[4] = 1.0*mm;
}

DetectorConstruction::~DetectorConstruction(){
}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

void DetectorConstruction::DefineMaterials(){
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4int natoms;
  G4int ncomp ;
  G4String symbol;
  G4double density;
  
  new G4Material("Diamond", z=6, a = 12.01*g/mole, density= 3.515*g/cm3);
  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
		 kStateGas, 2.73*kelvin, 3.e-18*pascal);

  G4Element* elH =
    new G4Element("Hydrogen", symbol="H", z=1., a = 1.01*g/mole);

  G4Element* elO =
    new G4Element("Oxygen", symbol="O", z=8., a = 16.00*g/mole);

  G4Element*elC =
    new G4Element("Carbon", symbol="C", z=6., a = 12.011*g/mole);

  G4Element*elCl =
    new G4Element("Chlorine", symbol="Cl", z=17., a = 35.45*g/mole);



  G4Material* Epoxy = new G4Material("Epoxy", density = 1.25*g/cm3, ncomp=4);
  Epoxy->AddElement(elH, natoms=25);
  Epoxy->AddElement(elO, natoms=5);
  Epoxy->AddElement(elCl, natoms=1);
  Epoxy->AddElement(elC, natoms=21);
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  auto worldSizeX = 1* m;
  auto worldSizeY = 1* m;
  auto worldSizeZ = 1* m;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto LISAMaterial = G4Material::GetMaterial("Diamond");
  auto PCBMaterial = G4Material::GetMaterial("Epoxy");

  if ( ! defaultMaterial || ! LISAMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }
#ifdef G4VIS_USE
  double red[2] = { 51, 231};
  double gre[2] = { 66,  68};
  double blu[2] = {155,  56};
#endif

  //
  // World
  //
  auto world_solid = new G4Box("World", worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size

  auto world_logic  = new G4LogicalVolume(world_solid,      // its solid
					  defaultMaterial,  // its material
					  "World");         // its name
  
#ifdef G4VIS_USE
  world_logic->SetVisAttributes (G4VisAttributes::GetInvisible());
#endif
  auto world_place = new G4PVPlacement(0,                // no rotation
				       G4ThreeVector(),  // at (0,0,0)
				       world_logic,      // its logical volume
				       "World",          // its name
				       0,                // its mother  volume
				       false,            // no boolean operation
				       0,                // copy number
				       fCheckOverlaps);  // checking overlaps

  
  auto DiamondSizeXY = 5*mm;
  char name[100];


  auto PCB_thickness = 1.8*mm;
  //////PCB_construction///////
  PCB_box = new G4Box("PCB_box",                //its name
		      25*mm,32.5*mm,PCB_thickness/2);
  PCB_box_hole = new G4Box("PCB_box_hole",                //its name
			   DiamondSizeXY/2,DiamondSizeXY/2,PCB_thickness+1*mm);

  G4VSolid* subtract = new G4SubtractionSolid("sub1", PCB_box, PCB_box_hole, 0 , G4ThreeVector(22.*mm,22.*mm,0.));


  G4LogicalVolume* PCB_board = new G4LogicalVolume(subtract,PCBMaterial,"PCB_board") ;

  G4VisAttributes* PCB_vis_attributes = new G4VisAttributes(G4Colour::Green());
  PCB_vis_attributes->SetForceSolid(true);
  PCB_board->SetVisAttributes(PCB_vis_attributes);

  new G4PVPlacement(0,G4ThreeVector(3.*mm,3.*mm,-20.*mm),PCB_board,"PCB_board",world_logic,false,0) ;



  G4double x = -0*cm; // front of first layer is at 0
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;
  for(G4int i=0; i<fNofLayers; i++){
    G4cout << "---> Constructing LISA layer " << i << " of " << fNofLayers;
    G4cout << ": thickness = " <<  fLayerThickness[i] << " mm, gap after = " << fLayerGap[i] << G4endl;
    sprintf(name, "Diamond_%d", i);
    x += +0.5*fLayerThickness[i];
    fLayer_solid[i] = new G4Box(name,                //its name
				DiamondSizeXY/2,DiamondSizeXY/2,fLayerThickness[i]/2);
    fLayer_logic[i] = new G4LogicalVolume(fLayer_solid[i],    //its solid
					  LISAMaterial, //its material
					  name);
#ifdef G4VIS_USE
    double sred = red[0]+i*(red[1]-red[0])/(fNofLayers-1);
    double sgre = gre[0]+i*(gre[1]-gre[0])/(fNofLayers-1);
    double sblu = blu[0]+i*(blu[1]-blu[0])/(fNofLayers-1);

    G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(sred/256,sgre/256,sblu/256));
    fLayer_logic[i]->SetVisAttributes(detectorVisAtt);
#endif
    fLayer_place[i] = new G4PVPlacement(0,              
					G4ThreeVector(0.,0.,x),
					fLayer_logic[i],               
					name,
					world_logic,                  
					false,                      
					i);                                //copy number
    x += fLayerThickness[i]/2;
    x += fLayerGap[i];
   
  }
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;

  
  return world_place;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  char name[100];
  SensitiveDetector* sensitive_detector[MAXTARGETS];
  for(G4int i=0; i<fNofLayers; i++){
    sprintf(name, "layer_%d", i);
    sensitive_detector[i] = new SensitiveDetector(name);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector[i]);
    fLayer_logic[i]->SetSensitiveDetector(sensitive_detector[i]);


  }
}
