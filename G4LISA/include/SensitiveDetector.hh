#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"

#include "LISAHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class SensitiveDetector : public G4VSensitiveDetector {
public:
  SensitiveDetector(const G4String& name);
  ~SensitiveDetector() override;

  // methods from base class
  void   Initialize(G4HCofThisEvent* hitCollection) override;
  G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  void   EndOfEvent(G4HCofThisEvent* hitCollection) override;

private:
  LISAHitsCollection* fhitsCollection = nullptr;
  G4String fname;
};

#endif

