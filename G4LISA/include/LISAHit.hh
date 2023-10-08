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
/// \file LISAHit.hh
/// \brief Definition of the LISAHit class

#ifndef LISAHit_h
#define LISAHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"


/// LISA hit class
///
/// It defines data members to store the energy deposit and position
/// of charged particles in a selected volume:
/// - fEdep, fpos

class LISAHit : public G4VHit
{
public:
  LISAHit();
  LISAHit(const LISAHit&) = default;
  ~LISAHit() override;

  // operators
  LISAHit& operator=(const LISAHit&) = default;
  G4bool operator==(const LISAHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  void Draw()  override{}
  void Print() override;

  // methods to handle data
  void Add(G4double de, G4double dl);

  // set
  void SetLayerID(G4int layer_id){ flayerID = layer_id;};
  void SetEdep(G4double de){ fEdep = de; };
  void SetPos(G4ThreeVector xyz){ fpos = xyz; };
  // get methods
  G4int GetLayerID() const;
  G4double GetEdep() const;
  G4ThreeVector GetPosition() const;

private:
  G4int flayerID;
  G4double fEdep;        ///< Energy deposit in the sensitive volume
  G4ThreeVector fpos;    ///< Position of the hit in the  sensitive volume
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using LISAHitsCollection = G4THitsCollection<LISAHit>;

extern G4ThreadLocal G4Allocator<LISAHit>* LISAHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* LISAHit::operator new(size_t)
{
  if (!LISAHitAllocator) {
    LISAHitAllocator = new G4Allocator<LISAHit>;
  }
  void *hit;
  hit = (void *) LISAHitAllocator->MallocSingle();
  return hit;
}

inline void LISAHit::operator delete(void *hit)
{
  if (!LISAHitAllocator) {
    LISAHitAllocator = new G4Allocator<LISAHit>;
  }
  LISAHitAllocator->FreeSingle((LISAHit*) hit);
}
/*
inline void LISAHit::Add(G4double de, G4double dl) {
  fEdep += de;
  //fTrackLength += dl;
}
*/
inline G4int LISAHit::GetLayerID() const {
  return flayerID;
}

inline G4double LISAHit::GetEdep() const {
  return fEdep;
}

inline G4ThreeVector LISAHit::GetPosition() const {
  return fpos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
