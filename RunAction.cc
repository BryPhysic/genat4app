#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction() {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateNtuple("Data", "Energía depositada");
    analysisManager->CreateNtupleSColumn("Volume");
    analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.root");
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
