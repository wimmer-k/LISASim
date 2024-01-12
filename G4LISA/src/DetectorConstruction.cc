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
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include  <vector>
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction_Messenger.hh"

/**
     * Create a new DetectorConstruction.
     * @brief Default constructor.
     */
DetectorConstruction::DetectorConstruction(){
  // Deafult geometry parameters, specify in the init_vis_mac file
  f_dim_x = 2;
  f_dim_y = 2;
  fNofLayers = 5;
  fLayerThick = 0.5*mm ;
  fLayerGa  = 2.0*mm ;
  DiamondSizeXY = 5*mm; 
  PCB_thickness = 1.*mm;
  f_space_x = 1.*mm ;
  f_space_y = 1.*mm ;
  bot_dist = 32*mm ;
  top_dist = 15*mm ;
  side_dist = 10*mm ;
  KW_radius = 10*mm ;
  KW_thicc = 0.0127*mm ;
  KW_Zdim = 10*mm ; 
  KW_switch = true ;
  KW_h = 8*mm ; //same as /BeamIn/Focus/Y



  for(G4int ab=0; ab<=10;ab++){
    fLayerThickness[ab] = fLayerThick;
    fLayerGap[ab] = fLayerGa;
    
  }
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
 G4int ncomp ; // number of components in a material
 G4String symbol; //symbol of a chemical element
 G4double density; //material density
  
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

G4Element*elN =
new G4Element("Nitrogen", symbol="N", z=7., a = 14.0067*g/mole);

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






//constructing materials for the PCB (epoxy + glass fiber)
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


//constructing "Kapton"  (Invented by the DuPont Corporation in the 1960s)

G4Material* Kapton =
new G4Material("Kapton", density = 1.42*g/cm3, ncomp=4);
Kapton->AddElement(elH, 0.0273);
Kapton->AddElement(elC, 0.7213);
Kapton->AddElement(elN, 0.0765);
Kapton->AddElement(elO, 0.1749);




  // Print materials
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  auto worldSizeX = 2* m;
  auto worldSizeY = 2* m;
  auto worldSizeZ = 2* m;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto LISAMaterial = G4Material::GetMaterial("Diamond");
  auto PCBMaterial = G4Material::GetMaterial("FR4_PCB");
  auto KaptonMaterial = G4Material::GetMaterial("Kapton");


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

  
  
  char name[100];




//////standard 2x2 PCB_construction///////
    PCB_box = new G4Box("PCB_box",                //its name
				25*mm,32.5*mm,PCB_thickness/2);
    PCB_box_hole = new G4Box("PCB_box_hole",                //its name
				DiamondSizeXY/2,DiamondSizeXY/2,PCB_thickness+1*mm);
    G4ThreeVector TopRight = G4ThreeVector(3.*mm,10.5*mm,0.*mm);
    G4ThreeVector TopLeft = G4ThreeVector(-3.,10.5*mm,0.);
    G4ThreeVector BottomLeft = G4ThreeVector(-3.,4.5*mm,0.);
    G4ThreeVector BottomRight = G4ThreeVector(3.,4.5*mm,0.);

    G4VSolid* subtract = new G4SubtractionSolid("sub1", PCB_box, PCB_box_hole, 0 , BottomRight);
    G4VSolid* subtract2 = new G4SubtractionSolid("sub2", subtract, PCB_box_hole, 0 , BottomLeft);
    G4VSolid* subtract3 = new G4SubtractionSolid("sub3", subtract2, PCB_box_hole, 0 , TopRight);
    G4VSolid* subtract4 = new G4SubtractionSolid("sub4", subtract3, PCB_box_hole, 0 , TopLeft);
  G4LogicalVolume* PCB_board = new G4LogicalVolume(subtract4,PCBMaterial,"PCB_board") ;

  G4VisAttributes* PCB_vis_attributes = new G4VisAttributes();
  PCB_vis_attributes->SetColor(0.208,0.529,0.184,0.4);
  PCB_vis_attributes->SetForceAuxEdgeVisible (true) ;
  PCB_vis_attributes->SetForceWireframe (true);
  PCB_vis_attributes->SetForceSolid(true);
  PCB_board->SetVisAttributes(PCB_vis_attributes);

  //new G4PVPlacement(0,G4ThreeVector(3.*mm,3.*mm,-10.*mm),PCB_board,"PCB_board",world_logic,false,0) ;





//--------------------------- construction of the general n x k PCB -------------------------------



double tot_len = f_dim_x*DiamondSizeXY+(f_dim_x-1)*f_space_x+2*side_dist;
double tot_high = f_dim_y*DiamondSizeXY+(f_dim_y-1)*f_space_y+bot_dist+top_dist;

//G4VSolid* box_general = new G4Box("general_box",tot_len/2 ,tot_high/2 ,PCB_thickness/2);
//G4VSolid* box_general_2 = new G4Box("general_box",tot_len/2 ,tot_high/2 ,PCB_thickness/2);

//G4LogicalVolume* plate_general = new G4LogicalVolume(box_general,PCBMaterial,"plate_general") ;


G4ThreeVector Bot_Left = G4ThreeVector(-tot_len/2+side_dist+DiamondSizeXY/2,-tot_high/2+bot_dist+DiamondSizeXY/2,0.);

//G4VSolid* subtract_gen = new G4SubtractionSolid("sub1", box_general, PCB_box_hole, 0 , Bot_Left);


//G4LogicalVolume* plate_sub = new G4LogicalVolume(subtract_gen,PCBMaterial,"plate_general") ;

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


std::vector<double> xes_new = xes;
std::vector<double> yes_new = yes;




for(G4int br=0; br<fNofLayers; br++){  
          for(G4int zd=0; zd<xes.size(); zd++){  
                xes_new.push_back(xes[zd]);
                yes_new.push_back(yes[zd]);

              


          }




}




G4LogicalVolume* PCB_general = new G4LogicalVolume(box_general_2,PCBMaterial,"plate_general") ;

PCB_general->SetVisAttributes(PCB_vis_attributes);

//new G4PVPlacement(0,G4ThreeVector(3.*mm,3.*mm,-10.*mm),PCB_general,"plate_general",world_logic,false,0) ;


//new G4PVPlacement(0,G4ThreeVector(3.*mm,3.*mm,-10.*mm),plate_sub,"plate_general",world_logic,false,0) ;



//--------------------------- construction of the general n x k PCB  END -------------------------------


//--------------------------- construction of the Kapton window ----------------------------------------

G4VSolid* KW_tube_solid = new G4Tubs("tube1",0 ,KW_radius ,KW_thicc/2,0,180);

G4LogicalVolume* KW_tube = new G4LogicalVolume(KW_tube_solid,KaptonMaterial, "kapton_win");

  G4VisAttributes* Kapton_vis_attributes = new G4VisAttributes();
  Kapton_vis_attributes->SetColor(0.529,0.357,0.016,0.4);
  Kapton_vis_attributes->SetForceAuxEdgeVisible (true) ;
  Kapton_vis_attributes->SetForceWireframe (true);
  Kapton_vis_attributes->SetForceSolid(true);

  KW_tube->SetVisAttributes(Kapton_vis_attributes);





//--------------------------- construction of the Kapton window END-----------------------------------


//--------------------------- Assembling the detector setup ----------------------------------------


  for(G4int ab=0; ab<=10;ab++){
    fLayerThickness[ab] = fLayerThick;
    fLayerGap[ab] = fLayerGa;
    
  }

  G4int mi = 0;
  G4double x = 0*cm; // front of first layer is at 0
  G4cout << G4endl << "------------------------------------------------------------" << G4endl;
  for(G4int i=0; i<fNofLayers; i++){
    G4cout << "---> Constructing LISA layer " << i << " of " << fNofLayers;
    G4cout << ": thickness = " <<  fLayerThickness[i] << " mm, gap after = " << fLayerGap[i] << G4endl;

    x += +0.5*fLayerThickness[i];
    for(G4int j=0; j<f_dim_x; j++){  
          for(G4int k=0; k<f_dim_y; k++){  
              sprintf(name, "Diamond_%d%d%d", i,j,k);
              
              
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
              if(fNofLayers==1) {detectorVisAtt->SetColor(0.,0.,0.9,0.5);}
            
              fLayer_logic[mi]->SetVisAttributes(detectorVisAtt);
          #endif
              //G4cout<<xes[j]<<"   "<<yes[k]<<"  "<<j<<G4endl;
              fLayer_place[mi] = new G4PVPlacement(0,              
                    G4ThreeVector(xes_new[mi]*mm,yes_new[mi]*mm,-x), //xes and yes are the vectors of the positions of holes in the PCB
                    fLayer_logic[mi],               
                    name,
                    world_logic,                  
                    false,                      
                    i);                                //copy number
              mi+=1;
   
  }
  }

    new G4PVPlacement(0,G4ThreeVector(0.*mm,0.*mm,-x*mm),PCB_general,"plate_general",world_logic,false,0) ;
    x += fLayerThickness[i]/2;
    x += fLayerGap[i];
  }


  if(KW_switch==true){
    new G4PVPlacement(0,G4ThreeVector(0.*mm,KW_h*mm,KW_Zdim*mm),KW_tube,"KW_tube",world_logic,false,0) ;
  }


  G4cout << G4endl << "------------------------------------------------------------" << G4endl;

  
  return world_place;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  char name[100];
  G4int counter =0;
  SensitiveDetector* sensitive_detector[MAXTARGETS];
  for(G4int i=0; i<fNofLayers; i++){
      for(G4int j=0; j<f_dim_x; j++){ 
          for(G4int k=0; k<f_dim_y; k++){ 
             
              
              //G4cout<<counter<<G4endl;
              sprintf(name, "layer_%d%d%d", i,k,j); //be careful, does not indicate the layer but the detector
              sensitive_detector[counter] = new SensitiveDetector(name);
              G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector[counter]);
              fLayer_logic[counter]->SetSensitiveDetector(sensitive_detector[counter]);
              counter+=1;

                                       }
 }
 }
}


void DetectorConstruction::SetNbOfLayers(G4int noLayersin)
{

  fNofLayers=noLayersin;
  //  G4cout<<"---->  no of layers set to "<<noLayersin<< G4endl;
  
}
//---------------------------------------------------------

void DetectorConstruction::SetLayerThickness(G4double in)
{

  fLayerThick=in;
  //  G4cout<<"---->  detector thickness set to "<<in<< G4endl;
  
}
//---------------------------------------------------------

void DetectorConstruction::SetLayerGap(G4double in)
{

  fLayerGa=in;
  //  G4cout<<"---->  gaps between layers set to "<<in<< G4endl;
  
}
//---------------------------------------------------------

void DetectorConstruction::Setdim_x(G4int in)
{

  f_dim_x=in;
  //  G4cout<<"---->  detector array dimension x set to "<<in<< G4endl;
  
}
//---------------------------------------------------------

void DetectorConstruction::Setdim_y(G4int in)
{

  f_dim_y=in;
  //  G4cout<<"---->  detector array dimension y set to "<<in<< G4endl;
  
}  
//---------------------------------------------------------

void DetectorConstruction::SetDiamondSizeXY(G4double in)
{

  DiamondSizeXY=in;
  //  G4cout<<"---->  size of the detecotr crystal set to "<<in<< G4endl;
  
}   

//---------------------------------------------------------

void DetectorConstruction::SetPCB_thickness(G4double in)
{

  PCB_thickness=in;
  //  G4cout<<"---->  thickness of the PCB board set to "<<in<< G4endl;
  
}  
//---------------------------------------------------------

void DetectorConstruction::Setspace_x(G4double in)
{

  f_space_x=in;
  //  G4cout<<"---->  distance between diamonds on the PCB board in x dimension set to "<<in<< G4endl;
  
} 
 
//---------------------------------------------------------

void DetectorConstruction::Setspace_y(G4double in)
{

  f_space_y=in;
  //  G4cout<<"---->  distance between diamonds on the PCB board in y dimension set to "<<in<< G4endl;
  
} 

//---------------------------------------------------------

void DetectorConstruction::Setbot_dist(G4double in)
{

  bot_dist=in;
  //  G4cout<<"---->  dimension of the PCB from the bottom to the bottom of the first detector set to "<<in<< G4endl;
  
} 

  //---------------------------------------------------------

void DetectorConstruction::Settop_dist(G4double in)
{

  top_dist=in;
  //  G4cout<<"---->  dimension of the PCB from the top to the top of the first detector set to "<<in<< G4endl;
  
} 

//---------------------------------------------------------

void DetectorConstruction::Setsidedist(G4double in)
{

  side_dist=in;
  //  G4cout<<"---->  dimension of the PCB from the edge to the side of the first detector set to "<<in<< G4endl;
  
}

//---------------------------------------------------------

void DetectorConstruction::SetKW_radius(G4double in)
{

  KW_radius=in;
  //  G4cout<<"---->  radius of the kapton window set to "<<in<< G4endl;
  
} 

//---------------------------------------------------------

void DetectorConstruction::SetKW_thicc(G4double in)
{

  KW_thicc=in;
  //  G4cout<<"---->  thickness of the kapton window set to "<<in<< G4endl;
  
} 

//---------------------------------------------------------

void DetectorConstruction::SetKW_Zdim(G4double in)
{

  KW_Zdim=in;
  //  G4cout<<"----> distance of the KW from the first layer set to "<<in<< G4endl;
  
}   
  
void DetectorConstruction::SetKW_switch(G4bool in)
{

  KW_switch=in;

  if(in==true){
  //  G4cout<<"----> kapton window is enabled" G4endl;
}
if(in==false){
  //  G4cout<<"----> kapton window is disabled" G4endl;
}

}   


void DetectorConstruction::SetKW_h(G4double in)
{

  KW_h=in;
  //  G4cout<<"----> height of the KW window set to "<<in<< G4endl;
  
} 
  
 
  // void SetKW_h(G4double);