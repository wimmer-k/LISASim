#ifndef LISAHit_h
#define LISAHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

class LISAHit : public G4VHit
{
public:
  LISAHit(){};
  LISAHit(const LISAHit&) = default;
  ~LISAHit() override {};

  // operators
  LISAHit& operator=(const LISAHit&) = default;
  G4bool operator==(const LISAHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  void Draw()  override{}
  void Print() override;

  // set
  void SetLayerID(G4int layer_id){ flayerID = layer_id;};
  void SetXID(G4int x_id){ fxID = x_id;};
  void SetYID(G4int y_id){ fyID = y_id;};
  void SetEdep(G4double de){ fEdep = de; };
  void SetPos(G4ThreeVector xyz){ fpos = xyz; };
  // get methods
  G4int GetLayerID() const;
  G4int GetXID() const;
  G4int GetYID() const;
  G4double GetEdep() const;
  G4ThreeVector GetPosition() const;

private:
  G4int flayerID;
  G4int fxID;
  G4int fyID;
  G4double fEdep;       
  G4ThreeVector fpos;  
};


using LISAHitsCollection = G4THitsCollection<LISAHit>;

extern G4ThreadLocal G4Allocator<LISAHit>* LISAHitAllocator;

inline void* LISAHit::operator new(size_t){
  if (!LISAHitAllocator){
    LISAHitAllocator = new G4Allocator<LISAHit>;
  }
  void *hit;
  hit = (void *) LISAHitAllocator->MallocSingle();
  return hit;
}

inline void LISAHit::operator delete(void *hit){
  if (!LISAHitAllocator) {
    LISAHitAllocator = new G4Allocator<LISAHit>;
  }
  LISAHitAllocator->FreeSingle((LISAHit*) hit);
}

inline G4int LISAHit::GetLayerID() const {return flayerID;}

inline G4int LISAHit::GetXID() const {return fxID;}

inline G4int LISAHit::GetYID() const {return fyID;}

inline G4double LISAHit::GetEdep() const {return fEdep;}

inline G4ThreeVector LISAHit::GetPosition() const {return fpos;}

#endif
