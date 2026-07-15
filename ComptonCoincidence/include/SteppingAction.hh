#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();

    // Metodo chiamato a ogni passo di ogni particella
    virtual void UserSteppingAction(const G4Step*);

  private:
    EventAction* fEventAction;
    G4LogicalVolume* fScoringVolume; // Il volume del cristallo NaI
};

#endif