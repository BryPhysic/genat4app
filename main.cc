#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"  
#include "MyDetectorConstruction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "RunAction.hh"

int main(int argc, char** argv) {
    // Inicializa la interfaz de usuario si es necesario
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    
    // Crear el Run Manager
    G4RunManager* runManager = new G4RunManager;
    
    // 🔹 Configurar la lista de física ANTES de MyPrimaryGeneratorAction
    G4VModularPhysicsList* physicsList = new QGSP_BERT;
    runManager->SetUserInitialization(physicsList);

    // Configurar la geometría del detector
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // Configurar la generación de partículas
    runManager->SetUserAction(new MyPrimaryGeneratorAction());

    // Configurar la acción de ejecución
    runManager->SetUserAction(new RunAction());
    
    // Inicializar la visualización
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    
    // Obtener el UI Manager para aplicar comandos
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    


  
    
    // Ejecutar la interfaz de usuario si está habilitada
    if (ui) {
        UImanager->ApplyCommand("/control/execute ../init.mac");
        ui->SessionStart();
        delete ui;
    }
    
    // Liberar memoria
    delete visManager;
    delete runManager;
    
    return 0;
}