#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;


class G4GenericMessenger; 


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

  private:
    G4LogicalVolume* fLogicCrystal;
    
    // Variabili per il comando distanza
    G4GenericMessenger* fMessenger; 
    G4double fDistance;             
};

#endif