#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
  // Registra la sorgente Na22
  SetUserAction(new PrimaryGeneratorAction());

  // Registra le azioni per gestire l'output CSV
  RunAction* runAction = new RunAction();
  SetUserAction(runAction);

  EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  // Registra lo SteppingAction per "leggere" i rilasci di energia nel NaI
  SetUserAction(new SteppingAction(eventAction));
}