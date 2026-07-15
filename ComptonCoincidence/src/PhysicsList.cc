#include "PhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh" 
#include "G4DecayPhysics.hh"            
#include "G4RadioactiveDecayPhysics.hh" 
#include "G4SystemOfUnits.hh"           
#include "G4ProductionCutsTable.hh"     

PhysicsList::PhysicsList() 
: G4VModularPhysicsList()
{

  SetVerboseLevel(1);

  RegisterPhysics(new G4EmStandardPhysics_option4()); 


  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::SetCuts()
{

  G4VUserPhysicsList::SetCuts();


  SetDefaultCutValue(0.01 * mm);

  SetCutsWithDefault();

  if (verboseLevel > 0) DumpCutValuesTable();
}