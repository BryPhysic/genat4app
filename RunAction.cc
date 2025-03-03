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
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
