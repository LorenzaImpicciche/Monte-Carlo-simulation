#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


#include "G4PhysListFactory.hh" 
#include "G4VModularPhysicsList.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    auto* runManager = 
      G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);


    runManager->SetUserInitialization(new DetectorConstruction());
    
    G4PhysListFactory factory;
    G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTFP_BERT_EMZ");
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);
    

    runManager->SetUserInitialization(new ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui ) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
    
    return 0;
}