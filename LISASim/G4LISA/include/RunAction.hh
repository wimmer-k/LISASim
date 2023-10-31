#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "DataManager.hh"
class G4Run;

class RunAction : public G4UserRunAction {
public:
  RunAction(DataManager *data);
  ~RunAction() override;

  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

private:
  G4String ffilename;
  DataManager* fdata;
};

#endif

