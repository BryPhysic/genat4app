/* MySensitiveDetector.cc corregido */

#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh" // Nueva inclusión

// Constructor de MySensitiveDetector
MySensitiveDetector::MySensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name) {}

// Destructor virtual necesario para evitar problemas de vtable
MySensitiveDetector::~MySensitiveDetector() {}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // Obtener la energía depositada
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0) return false;  // Ignorar pasos sin depósito de energía

    // Obtener el volumen donde ocurre la interacción
    G4String volumeName = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

    // Imprimir la información en consola
    G4cout << "Energía depositada en " << volumeName << " = " << edep / keV << " keV" << G4endl;

    // Obtener el manejador de análisis correctamente
    auto analysisManager = G4RootAnalysisManager::Instance();

    if (!analysisManager || !analysisManager->IsOpenFile()) {
        G4cerr << "ERROR: G4RootAnalysisManager no está inicializado o el archivo de salida no está abierto." << G4endl;
        return false;
    }

    // Verificar que la ntuple existe antes de llenarla
    if (analysisManager->GetNtuple() == nullptr) {
        G4cerr << "ERROR: Ntuple no ha sido creada en RunAction." << G4endl;
        return false;
    }

    // Registrar los datos en la ntuple
    analysisManager->FillNtupleSColumn(0, volumeName);
    analysisManager->FillNtupleDColumn(1, edep / keV);
    analysisManager->AddNtupleRow();

    return true;
}
