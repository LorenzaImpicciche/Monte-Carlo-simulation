#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction(), 
  fEdep(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  // Reset dell'energia all'inizio di ogni nuovo evento
  fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  auto analysisManager = G4AnalysisManager::Instance();

  // Salva l'evento solo se c'è stata deposizione di energia
  if (fEdep > 0.) {
    analysisManager->FillNtupleIColumn(0, event->GetEventID());
    analysisManager->FillNtupleDColumn(1, fEdep);
    analysisManager->AddNtupleRow();
  }
}