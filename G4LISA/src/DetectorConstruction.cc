/**
 * @brief Detector construction class for LISA
 */

#include  <vector>
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


  fdetMessenger = new Detector_Messenger(this);
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
}

DetectorConstruction::~DetectorConstruction(){
}
void DetectorConstruction::SetNbOfLayers(G4int nl){
  //G4cout << "setting number of layers " << nl << G4endl;
  fNofLayers=nl;
}
void DetectorConstruction::SetXdim(G4int x){
  f_dim_x = x;
}
void DetectorConstruction::SetYdim(G4int y){
  f_dim_y = y;
}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  // Define materials
  DefineMaterials();

  // Define volumes
  return ConstructWorld();
}
void DetectorConstruction::ConstructLISA(){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  ConstructPCB();
  ConstructDetectors();
  ConstructSensitive();
}

void DetectorConstruction::DefineMaterials(){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
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

  G4Element*elSi =
    new G4Element("Silicon", symbol="Si", z=14., a = 28.0855*g/mole);

  G4Element*elAl =
    new G4Element("Aluminium", symbol="Al", z=13., a = 26.981*g/mole);

  G4Element*elB =
    new G4Element("Boron", symbol="B", z=5., a = 10.81*g/mole);

  G4Element*elMg =
    new G4Element("Magnesium", symbol="Mg", z=12., a = 24.305*g/mole);

  G4Element*elCa =
    new G4Element("Calcium", symbol="Ca", z=20., a = 40.078*g/mole);



  //G4NistManager* manager = G4NistManager::Instance();

  G4Material* Epoxy =
    new G4Material("Epoxy", density = 1.25*g/cm3, ncomp=4);
  Epoxy->AddElement(elH, natoms=25);
  Epoxy->AddElement(elO, natoms=5);
  Epoxy->AddElement(elCl, natoms=1);
  Epoxy->AddElement(elC, natoms=21);



  G4Material* SiO2 =
    new G4Material("SiO2", density = 2.65*g/cm3, ncomp=2);
  SiO2->AddElement(elSi, natoms=1);
  SiO2->AddElement(elO, natoms=2);

  G4Material* Al2O3 =
    new G4Material("Al2O3", density = 3.95*g/cm3, ncomp=2);
  Al2O3->AddElement(elAl, natoms=2);
  Al2O3->AddElement(elO, natoms=3);

  G4Material* B2O3 =
    new G4Material("B2O3", density = 2.46*g/cm3, ncomp=2);
  B2O3->AddElement(elB, natoms=2);
  B2O3->AddElement(elO, natoms=3);

  G4Material* MgO =
    new G4Material("MgO", density = 3.58*g/cm3, ncomp=2);
  MgO->AddElement(elMg, natoms=1);
  MgO->AddElement(elO, natoms=1);

  G4Material* CaO =
    new G4Material("CaO", density = 3.34*g/cm3, ncomp=2);
  CaO->AddElement(elCa, natoms=1);
  CaO->AddElement(elO, natoms=1);

  G4Material* Glass_Fiber =
    new G4Material("Glass_Fiber", density = 2.54*g/cm3, ncomp=5);
  Glass_Fiber->AddMaterial(SiO2, 0.559);
  Glass_Fiber->AddMaterial(Al2O3, 0.148);
  Glass_Fiber->AddMaterial(B2O3, 0.073);
  Glass_Fiber->AddMaterial(MgO, 0.033);
  Glass_Fiber->AddMaterial(CaO, 0.187);


  G4Material* FR4_PCB =
    new G4Material("FR4_PCB", density = 1.85*g/cm3, ncomp=2);
  FR4_PCB->AddMaterial(Epoxy, 0.60);
  FR4_PCB->AddMaterial(Glass_Fiber, 0.40);






  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  auto worldSizeX = 2* m;
  auto worldSizeY = 2* m;
  auto worldSizeZ = 2* m;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");

  if ( ! defaultMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
		"MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  auto world_solid = new G4Box("World", worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size

  fworld_logic  = new G4LogicalVolume(world_solid,      // its solid
					  defaultMaterial,  // its material
					  "World");         // its name
  
#ifdef G4VIS_USE
  fworld_logic->SetVisAttributes (G4VisAttributes::GetInvisible());
#endif
  auto world_place = new G4PVPlacement(0,                // no rotation
				       G4ThreeVector(),  // at (0,0,0)
				       fworld_logic,      // its logical volume
				       "World",          // its name
				       0,                // its mother  volume
				       false,            // no boolean operation
				       0,                // copy number
				       fCheckOverlaps);  // checking overlaps

  


  return world_place;
}
void DetectorConstruction::ConstructPCB(){
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  auto PCBMaterial = G4Material::GetMaterial("FR4_PCB");
  G4VisAttributes* PCB_vis_attributes = new G4VisAttributes();
  PCB_vis_attributes->SetColor(0.208,0.529,0.184,0.4);
  PCB_vis_attributes->SetForceAuxEdgeVisible (true) ;
  PCB_vis_attributes->SetForceWireframe (true);
  PCB_vis_attributes->SetForceSolid(true);

  G4Box* PCB_box_hole = new G4Box("PCB_box_hole",                //its name
				  DiamondSizeXY/2,DiamondSizeXY/2,PCB_thickness+1*mm);

  /*
  //////standard 2x2 PCB_construction///////
  
  G4Box* PCB_box = new G4Box("PCB_box",                //its name
		      25*mm,32.5*mm,PCB_thickness/2);
  G4ThreeVector TopRight = G4ThreeVector(3.*mm,10.5*mm,0.*mm);
  G4ThreeVector TopLeft = G4ThreeVector(-3.,10.5*mm,0.);
  G4ThreeVector BottomLeft = G4ThreeVector(-3.,4.5*mm,0.);
  G4ThreeVector BottomRight = G4ThreeVector(3.,4.5*mm,0.);

  G4VSolid* subtract = new G4SubtractionSolid("sub1", PCB_box, PCB_box_hole, 0 , BottomRight);
  G4VSolid* subtract2 = new G4SubtractionSolid("sub2", subtract, PCB_box_hole, 0 , BottomLeft);
  G4VSolid* subtract3 = new G4SubtractionSolid("sub3", subtract2, PCB_box_hole, 0 , TopRight);
  G4VSolid* subtract4 = new G4SubtractionSolid("sub4", subtract3, PCB_box_hole, 0 , TopLeft);
  G4LogicalVolume* PCB_board = new G4LogicalVolume(subtract4,PCBMaterial,"PCB_board") ;

  PCB_board->SetVisAttributes(PCB_vis_attributes);
  */
  
  
  //--------------------------- construction of general n x k PCB -------------------------------

  double tot_len = f_dim_x*DiamondSizeXY+(f_dim_x-1)*f_space_x+2*side_dist;
  double tot_high = f_dim_y*DiamondSizeXY+(f_dim_y-1)*f_space_y+bot_dist+top_dist;

  G4ThreeVector Bot_Left = G4ThreeVector(-tot_len/2+side_dist+DiamondSizeXY/2,-tot_high/2+bot_dist+DiamondSizeXY/2,0.);

  G4VSolid* box_general_2 = new G4Box("general_box",tot_len/2 ,tot_high/2 ,PCB_thickness/2);
  double x_cord = 0;
  double y_cord = 0;
  std::vector<double> xes;
  std::vector<double> yes;
  for(G4int x=0; x<f_dim_x; x++){  
    for(G4int y=0; y<f_dim_y; y++){  
      x_cord = Bot_Left.getX() + x*(f_space_x+DiamondSizeXY);
      y_cord = Bot_Left.getY() + y*(f_space_y+DiamondSizeXY);
      xes.push_back(x_cord);
      yes.push_back(y_cord);
      //G4cout<<x_cord<<"     "<<y_cord<<G4endl;
      G4ThreeVector temp = G4ThreeVector(x_cord,y_cord,0);
              
      G4VSolid* subtract_gen_3 = new G4SubtractionSolid("sub1", box_general_2, PCB_box_hole, 0 , temp);
      box_general_2 = subtract_gen_3 ; 
    }



  }


  xes_new = xes;
  yes_new = yes;
  
  for(G4int br=0; br<fNofLayers; br++){
    G4cout << "br " << br << G4endl;
    for(unsigned short zd=0; zd<xes.size(); zd++){  
      xes_new.push_back(xes[zd]);
      yes_new.push_back(yes[zd]);
    }
  }
  



  fPCB_general = new G4LogicalVolume(box_general_2,PCBMaterial,"plate_general") ;
  fPCB_general->SetVisAttributes(PCB_vis_attributes);
  //--------------------------- construction of general n x k PCB  END -------------------------------


  return;
}





void DetectorConstruction::ConstructDetectors(){
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  auto LISAMaterial = G4Material::GetMaterial("Diamond");
#ifdef G4VIS_USE
  double red[2] = { 51, 231};
  double gre[2] = { 66,  68};
  double blu[2] = {155,  56};
#endif
  
  char name[100];

  G4int mi = 0;
  G4double x = -0*cm; // front of first layer is at 0
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;
  for(G4int i=0; i<fNofLayers; i++){
    G4cout << "---> Constructing LISA layer " << i << " of " << fNofLayers;
    G4cout << ": thickness = " <<  fLayerThickness[i] << " mm, gap after = " << fLayerGap[i] << G4endl;

    x += +0.5*fLayerThickness[i];
    for(G4int j=0; j<f_dim_x; j++){  
      for(G4int k=0; k<f_dim_y; k++){  
	sprintf(name, "Diamond_%d%d%d", i,j,k);
 	G4cout << name << G4endl;
             
              
	fLayer_solid[mi] = new G4Box(name,                //its name
				     DiamondSizeXY/2,DiamondSizeXY/2,fLayerThickness[i]/2);
	fLayer_logic[mi] = new G4LogicalVolume(fLayer_solid[mi],    //its solid
					       LISAMaterial, //its material
					       name);
#ifdef G4VIS_USE
	double sred = red[0]+i*(red[1]-red[0])/(fNofLayers-1);
	double sgre = gre[0]+i*(gre[1]-gre[0])/(fNofLayers-1);
	double sblu = blu[0]+i*(blu[1]-blu[0])/(fNofLayers-1);

	G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(sred/256,sgre/256,sblu/256));
	fLayer_logic[mi]->SetVisAttributes(detectorVisAtt);
#endif
	//G4cout<<xes[j]<<"   "<<yes[k]<<"  "<<j<<G4endl;
	//G4cout<<xes_new[mi]<<"   "<<yes_new[mi] << "  " << mi << "  " << j << "  " << k << G4endl;
	fLayer_place[mi] = new G4PVPlacement(0,              
					     G4ThreeVector(xes_new[mi]*mm,yes_new[mi]*mm,x),
					     fLayer_logic[mi],               
					     name,
					     fworld_logic,                  
					     false,                      
					     i);                                //copy number
	mi+=1;
   
      }
    }

    new G4PVPlacement(0,G4ThreeVector(0.*mm,0.*mm,x*mm),fPCB_general,"plate_general",fworld_logic,false,0) ;
    x += fLayerThickness[i]/2;
    x += fLayerGap[i];
  }
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;

  
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSensitive()
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  char name[100];
  G4int counter =0;
  SensitiveDetector* sensitive_detector[MAXTARGETS];
  for(G4int i=0; i<fNofLayers; i++){
    for(G4int j=0; j<f_dim_x; j++){ 
      for(G4int k=0; k<f_dim_y; k++){ 
             
              
	//G4cout<<counter<<G4endl;
	sprintf(name, "layer_%d%d%d", i,k,j); //be careful, does not indicate layer but a detector
	//G4cout << name << G4endl;
	sensitive_detector[counter] = new SensitiveDetector(name);
	G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector[counter]);
	fLayer_logic[counter]->SetSensitiveDetector(sensitive_detector[counter]);
	counter+=1;

      }
    }
  }
}
