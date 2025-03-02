#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include "g4root.hh"  // Agregar esta línea para usar el gestor de análisis

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // Obtener la energía depositada
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0) return false;  // Ignorar pasos sin depósito de energía

    // Obtener el volumen donde ocurre la interacción
    G4String volumeName = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

    // Imprimir la información en consola
    G4cout << "Energía depositada en " << volumeName << " = " << edep / keV << " keV" << G4endl;

    // Obtener el manejador de análisis correctamente
    auto analysisManager = G4AnalysisManager::Instance();

    if (!analysisManager) {
        G4cerr << "ERROR: G4AnalysisManager no está inicializado correctamente." << G4endl;
        return false;
    }

    // Registrar los datos en la ntuple
    analysisManager->FillNtupleSColumn(0, volumeName);
    analysisManager->FillNtupleDColumn(1, edep / keV);
    analysisManager->AddNtupleRow();

    return true;
}