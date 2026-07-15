#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4GenericMessenger.hh"


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), fLogicCrystal(nullptr), fDistance(10.0*cm)
{
    // Comando per impostare la distanza da macro
    fMessenger = new G4GenericMessenger(this, "/det/", "Detector control");
    fMessenger->DeclarePropertyWithUnit("setDistance", "cm", fDistance, "Set distance source-detector");
}

DetectorConstruction::~DetectorConstruction()
{
    delete fMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // --- MATERIALI ---
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* crystal_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4Material* alu_mat = nist->FindOrBuildMaterial("G4_Al");

    // MgO (Ossido di Magnesio) - Densità impaccata tipica ~0.6 g/cm3
    G4Element* elMg = nist->FindOrBuildElement("Mg");
    G4Element* elO  = nist->FindOrBuildElement("O");
    G4Material* matMgO = new G4Material("MgO_Powder", 0.6 * g/cm3, 2);
    matMgO->AddElement(elMg, 1);
    matMgO->AddElement(elO, 1);

    // --- DIMENSIONI ESATTE DA DATASHEET ---


    // 1. CRISTALLO NaI(Tl) (2" x 2")
    G4double crystalRad = 0.5 * 50.8 * mm;      
    G4double crystalThick = 50.8 * mm;        

    // 2. HOUSING IN ALLUMINIO (Ø 2.300")
    G4double housingDiameter = 58.42 * mm; 
    G4double aluRad = 0.5 * housingDiameter; 
    G4double aluWallThick = 0.508 * mm; // Dalla nota 1: .020" THK
    
    // 3. RIFLETTORE IN MgO
    // Lo spessore è lo spazio radiale rimanente tra alluminio e cristallo
    G4double mgoRad = aluRad - aluWallThick;
    G4double mgoThick = mgoRad - crystalRad; // Risulta ~3.3 mm
    
    // --- CALCOLO DELLE MEZZE LUNGHEZZE (Half-Z) ---
    // Struttura a Matrioska: ogni cilindro contiene il successivo.
    G4double crystalHalfZ = 0.5 * crystalThick;
    G4double mgoHalfZ = crystalHalfZ + mgoThick; 
    G4double aluHalfZ = mgoHalfZ + aluWallThick; 

    // --- DISTANZA SORGENTE-RIVELATORE ---
    G4double distanceSourceDet = fDistance;

    // --- MONDO ---
    G4double worldSize = 1.0 * m;
    G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // SORGENTE: BOTTONCINO DI PLASTICA

    G4Material* plastic_mat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
    
    // Dimensioni UFFICIALI Spectrum Techniques (Dischetto standard 1" in Plexiglass)
    // Diametro: 25.4 mm (Raggio = 12.7 mm)
    // Spessore totale: 0.125 pollici = 3.175 mm (HalfThick = 1.5875 mm)
    G4double buttonRad = 0.5 * 25.4 * mm;
    G4double buttonHalfThick = (0.125 * 25.4 * mm) / 2.0; 
    
    G4Tubs* solidButton = new G4Tubs("SourceButton", 0, buttonRad, buttonHalfThick, 0, 360*deg);
    G4LogicalVolume* logicButton = new G4LogicalVolume(solidButton, plastic_mat, "logicButton");
    
    // Lo posizioniamo esattamente nell'origine (0,0,0), dove nascono i fotoni
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicButton, "SourceButton", logicWorld, false, 0);

    
    // TOPOLOGIA A MATRIOSKA (Alluminio -> MgO -> Cristallo)
    
    // --- 1. HOUSING ALLUMINIO (Volume Madre del Rivelatore) ---
    G4Tubs* solidAlu = new G4Tubs("AluHousing", 0, aluRad, aluHalfZ, 0, 360*deg);
    G4LogicalVolume* logicAlu = new G4LogicalVolume(solidAlu, alu_mat, "logicAlu");
    
    // Posizioniamo l'alluminio nel Mondo. 
    // La faccia anteriore deve stare a Z = distanceSourceDet
    G4double zPosDet = distanceSourceDet + aluHalfZ;
    new G4PVPlacement(0, G4ThreeVector(0, 0, zPosDet), logicAlu, "AluHousing", logicWorld, false, 0);

    // --- 2. RIFLETTORE MgO (Figlio dell'Alluminio) ---
    G4Tubs* solidMgO = new G4Tubs("MgO", 0, mgoRad, mgoHalfZ, 0, 360*deg);
    G4LogicalVolume* logicMgO = new G4LogicalVolume(solidMgO, matMgO, "logicMgO");
    
    // Posizionato esattamente al centro dell'Alluminio (Z locale = 0)
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicMgO, "MgO", logicAlu, false, 0);

    // --- 3. CRISTALLO NaI (Figlio del MgO) ---
    G4Tubs* solidCrystal = new G4Tubs("Crystal", 0, crystalRad, crystalHalfZ, 0, 360*deg);
    fLogicCrystal = new G4LogicalVolume(solidCrystal, crystal_mat, "logicCrystal");
    
    // Posizionato esattamente al centro del MgO (Z locale = 0)
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), fLogicCrystal, "Crystal", logicMgO, false, 0);

// --- VISUALIZZAZIONE ---
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    // Bottoncino Plastica: Giallo semi-trasparente
    G4VisAttributes* buttonVis = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.7));
    buttonVis->SetForceSolid(true);
    logicButton->SetVisAttributes(buttonVis);

    // Alluminio: Grigio scuro semi-trasparente
    G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.3));
    aluVis->SetForceSolid(true);
    logicAlu->SetVisAttributes(aluVis);
    
    // MgO: Bianco semi-trasparente
    G4VisAttributes* mgoVis = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.4));
    mgoVis->SetForceSolid(true);
    logicMgO->SetVisAttributes(mgoVis);
    
    // Cristallo: Ciano solido
    G4VisAttributes* cryVis = new G4VisAttributes(G4Colour(0.0, 0.8, 1.0, 1.0));
    cryVis->SetForceSolid(true);
    fLogicCrystal->SetVisAttributes(cryVis);

    return physWorld;
}

