#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList();
    virtual ~PhysicsList();

    // Questa funzione è fondamentale per definire la soglia di produzione
    virtual void SetCuts();
};

#endif