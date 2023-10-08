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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.h"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
  /// Detector construction class to define materials and geometry.
  /// The calorimeter is a box made of a given number of layers. A layer consists
  /// of an absorber plate and of a detection gap. The layer is replicated.
  ///
  /// Four parameters define the geometry of the calorimeter :
  ///
  /// - the thickness of an absorber plate,
  /// - the thickness of a gap,
  /// - the number of layers,
  /// - the transverse size of the calorimeter (the input face is a square).
  ///
  /// In ConstructSDandField() sensitive detectors of CalorimeterSD type
  /// are created and associated with the Absorber and Gap volumes.
  /// In addition a transverse uniform magnetic field is defined
  /// via G4GlobalMagFieldMessenger class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

public:

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
  // methods
  //
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  G4int fNofLayers = -1;     // number of layers
  G4double fLayerThickness[MAXTARGETS];
  G4double fLayerGap[MAXTARGETS];

  G4Box* fLayer_solid[MAXTARGETS];
  G4LogicalVolume* fLayer_logic[MAXTARGETS];
  G4VPhysicalVolume* fLayer_place[MAXTARGETS];
    
  G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

