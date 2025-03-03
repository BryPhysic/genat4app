#include "RunAction.hh"
#include "G4RootAnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction() : G4UserRunAction() {
    auto analysisManager = G4RootAnalysisManager::Instance();
    
    analysisManager->SetVerboseLevel(1);  // Para depurar
    analysisManager->CreateNtuple("Hits", "Hit Data");
    analysisManager->CreateNtupleSColumn("Volume");  // Columna de strings
    analysisManager->CreateNtupleDColumn("Energy");  // Columna de doubles
    analysisManager->FinishNtuple();
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->OpenFile("output.root");  // Abrir el archivo antes de escribir

    G4cout << "📂 Archivo de salida `output.root` abierto correctamente." << G4endl;
}
void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    
    if (analysisManager->IsOpenFile()) {
        analysisManager->Write();
        analysisManager->CloseFile();
        G4cout << "✅ Archivo `output.root` escrito y cerrado correctamente." << G4endl;
    } else {
        G4cerr << "⚠️ ERROR: No se pudo escribir `output.root`, archivo no estaba abierto." << G4endl;
    }
}