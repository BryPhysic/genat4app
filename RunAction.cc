#include "RunAction.hh"
#include "G4RootAnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction() : G4UserRunAction() {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->CreateNtuple("Run", "Run Data");
    analysisManager->FinishNtuple();
}

// Implementación del destructor virtual
RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->OpenFile("output.root");
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
