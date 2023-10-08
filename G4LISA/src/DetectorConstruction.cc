//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "CalorimeterSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
  // Geometry parameters
  fNofLayers = 5;
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{

  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;

  new G4Material("Diamond", z=6, a = 12.01*g/mole, density= 3.515*g/cm3);
  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  auto worldSizeX = 1* m;
  auto worldSizeY = 1* m;
  auto worldSizeZ = 1* m;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto LISAMaterial = G4Material::GetMaterial("Diamond");

  if ( ! defaultMaterial || ! LISAMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }
#ifdef G4VIS_USE
  double r[2] = { 51, 231};
  double g[2] = { 66,  68};
  double b[2] = {155,  56};
#endif

  //
  // World
  //
  auto world_solid = new G4Box("World", worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size

  auto world_logic  = new G4LogicalVolume(world_solid,           // its solid
					  defaultMaterial,  // its material
					  "World");         // its name
  
  auto world_place = new G4PVPlacement(0,                // no rotation
				       G4ThreeVector(),  // at (0,0,0)
				       world_logic,          // its logical volume
				       "World",          // its name
				       0,                // its mother  volume
				       false,            // no boolean operation
				       0,                // copy number
				       fCheckOverlaps);  // checking overlaps

  
  auto DiamondSizeXY = 5*mm;
  char name[100];

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
    double sr = r[0]+i*(r[1]-r[0])/(fNofLayers-1);
    double sg = g[0]+i*(g[1]-g[0])/(fNofLayers-1);
    double sb = b[0]+i*(b[1]-b[0])/(fNofLayers-1);

    G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(sr/256,sg/256,sb/256));
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
  
  /*
  G4double absoThickness = 10.*mm;
  G4double gapThickness =  5.*mm;
  G4double calorSizeXY  = 10.*cm;

  auto layerThickness = absoThickness + gapThickness;
  auto calorThickness = fNofLayers * layerThickness;

  //
  // Calorimeter
  //
  auto calorimeterS
    = new G4Box("Calorimeter",     // its name
                 calorSizeXY/2, calorSizeXY/2, calorThickness/2); // its size

  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 defaultMaterial,  // its material
                 "Calorimeter");   // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 calorLV,          // its logical volume
                 "Calorimeter",    // its name
                 world_logic,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
  
  //
  // Layer
  //
  auto layerS
    = new G4Box("Layer",           // its name
                 calorSizeXY/2, calorSizeXY/2, layerThickness/2); //its size

  auto layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 defaultMaterial,  // its material
                 "Layer");         // its name

  new G4PVReplica(
                 "Layer",          // its name
                 layerLV,          // its logical volume
                 calorLV,          // its mother
                 kZAxis,           // axis of replication
                 fNofLayers,        // number of replica
                 layerThickness);  // witdth of replica

  //
  // Absorber
  //
  auto absorberS
    = new G4Box("Abso",            // its name
                 calorSizeXY/2, calorSizeXY/2, absoThickness/2); // its size

  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 LISAMaterial, // its material
                 "AbsoLV");        // its name

#ifdef G4VIS_USE
  G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(0.89,0.45,0.13));
  absorberLV->SetVisAttributes(detectorVisAtt);
#endif
   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -gapThickness/2), // its position
                 absorberLV,       // its logical volume
                 "Abso",           // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //
  // Gap
  //
  auto gapS
    = new G4Box("Gap",             // its name
                 calorSizeXY/2, calorSizeXY/2, gapThickness/2); // its size

  auto gapLV
    = new G4LogicalVolume(
                 gapS,             // its solid
                 defaultMaterial,      // its material
                 "GapLV");         // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2), // its position
                 gapLV,            // its logical volume
                 "Gap",            // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //
  // print parameters
  //
  G4cout
    << G4endl
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << fNofLayers << " layers of: [ "
    << absoThickness/mm << "mm of " << defaultMaterial->GetName()
    << " + "
    << gapThickness/mm << "mm of " << defaultMaterial->GetName() << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;
*/
  //
  // Visualization attributes
  //
  world_logic->SetVisAttributes (G4VisAttributes::GetInvisible());
  /*
  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  calorLV->SetVisAttributes(simpleBoxVisAtt);
  */
  //
  // Always return the physical World
  //
  //return worldPV;
  
  return world_place;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  //
  // Sensitive detectors
  //
  /*
  auto absoSD
    = new CalorimeterSD("AbsorberSD", "AbsorberHitsCollection", fNofLayers);
  G4SDManager::GetSDMpointer()->AddNewDetector(absoSD);
  SetSensitiveDetector("AbsoLV",absoSD);

  auto gapSD
    = new CalorimeterSD("GapSD", "GapHitsCollection", fNofLayers);
  G4SDManager::GetSDMpointer()->AddNewDetector(gapSD);
  SetSensitiveDetector("GapLV",gapSD);
*/
  char name[100];
  SensitiveDetector* sensitive_detector[MAXTARGETS];
  for(G4int i=0; i<fNofLayers; i++){
    sprintf(name, "layer_%d", i);
    sensitive_detector[i] = new SensitiveDetector(name);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector[i]);
    fLayer_logic[i]->SetSensitiveDetector(sensitive_detector[i]);


  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
