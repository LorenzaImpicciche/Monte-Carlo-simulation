#include "PhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh" // <--- MODIFICA 1: Inclusione della Option 4
#include "G4DecayPhysics.hh"            // Decadimenti particelle
#include "G4RadioactiveDecayPhysics.hh" // Decadimenti radioattivi
#include "G4SystemOfUnits.hh"           // Per usare 'mm', 'cm', 'MeV'
#include "G4ProductionCutsTable.hh"     // Per gestire i tagli (Cuts)

PhysicsList::PhysicsList() 
: G4VModularPhysicsList()
{

  SetVerboseLevel(1);

  // Registra la Fisica Elettromagnetica
  RegisterPhysics(new G4EmStandardPhysics_option4()); 


  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::SetCuts()
{

  G4VUserPhysicsList::SetCuts();

  // Imposta il "Range Cut" 
  SetDefaultCutValue(0.01 * mm);

  SetCutsWithDefault();

  // Stampa la tabella dei tagli nel terminale per conferma
  if (verboseLevel > 0) DumpCutValuesTable();
}