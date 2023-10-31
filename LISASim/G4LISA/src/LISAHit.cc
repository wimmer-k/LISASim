#include "LISAHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<LISAHit>* LISAHitAllocator = nullptr;

G4bool LISAHit::operator==(const LISAHit& right) const{
  return ( this == &right ) ? true : false;
}

void LISAHit::Print(){
  G4cout
    << "Edep: "
    << "  energy deposit: " << G4BestUnit(fEdep,"Energy")
    << "  position: " << G4BestUnit(fpos,"Length") << G4endl;
}
