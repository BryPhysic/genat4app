#include "MyDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "MySensitiveDetector.hh"
#include "G4SDManager.hh"

MyDetectorConstruction::MyDetectorConstruction()
    : worldSizeX(20 * cm), worldSizeY(20 * cm), worldSizeZ(100 * cm),
      d_piel(2.0 * mm), d_hueso(10.0 * mm), d_musculo(30.0 * mm), d_pulmon(50.0 * mm),
      matWorld(nullptr), matPiel(nullptr), matHueso(nullptr), matMusculo(nullptr), matPulmon(nullptr),
      logicWorld(nullptr), logicPiel(nullptr), logicHueso(nullptr), logicMusculo(nullptr), logicPulmon(nullptr) {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    DefineMaterials();
    auto physWorld = ConstructWorld();
    ConstructSDandField(); // Asegurar que se asignen los Sensitive Detectors
    return physWorld;
}

void MyDetectorConstruction::DefineMaterials() {
    auto nist = G4NistManager::Instance();
    matWorld = nist->FindOrBuildMaterial("G4_AIR");
    matPiel = nist->FindOrBuildMaterial("G4_SKIN_ICRP");
    matHueso = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
    matMusculo = nist->FindOrBuildMaterial("G4_MUSCLE_SKELETAL_ICRP");
    matPulmon = nist->FindOrBuildMaterial("G4_LUNG_ICRP");
}

G4VPhysicalVolume* MyDetectorConstruction::ConstructWorld() {
    G4Box* solidWorld = new G4Box("World", worldSizeX/2, worldSizeY/2, worldSizeZ/2);
    logicWorld = new G4LogicalVolume(solidWorld, matWorld, "WorldLV");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr, G4ThreeVector(), logicWorld, "WorldPV", nullptr, false, 0);
    
    ConstructTissueLayers(logicWorld);
    return physWorld;
}

void MyDetectorConstruction::ConstructTissueLayers(G4LogicalVolume* worldLog) {
    G4double areaXY = 10 * cm;
    G4double totalThickness = d_piel + d_hueso + d_musculo + d_pulmon;
    G4double z0 = -totalThickness / 2;
    
    G4Box* solidPiel = new G4Box("SolidPiel", areaXY/2, areaXY/2, d_piel/2);
    G4Box* solidHueso = new G4Box("SolidHueso", areaXY/2, areaXY/2, d_hueso/2);
    G4Box* solidMusculo = new G4Box("SolidMusculo", areaXY/2, areaXY/2, d_musculo/2);
    G4Box* solidPulmon = new G4Box("SolidPulmon", areaXY/2, areaXY/2, d_pulmon/2);
    
    logicPiel = new G4LogicalVolume(solidPiel, matPiel, "PielLV");
    logicHueso = new G4LogicalVolume(solidHueso, matHueso, "HuesoLV");
    logicMusculo = new G4LogicalVolume(solidMusculo, matMusculo, "MusculoLV");
    logicPulmon = new G4LogicalVolume(solidPulmon, matPulmon, "PulmonLV");

    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, z0 + d_piel/2), logicPiel, "PielPV", worldLog, false, 0);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, z0 + d_piel + d_hueso/2), logicHueso, "HuesoPV", worldLog, false, 0);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, z0 + d_piel + d_hueso + d_musculo/2), logicMusculo, "MusculoPV", worldLog, false, 0);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, z0 + d_piel + d_hueso + d_musculo + d_pulmon/2), logicPulmon, "PulmonPV", worldLog, false, 0);
}

void MyDetectorConstruction::ConstructSDandField() {
    // Obtener el manejador de SD
    auto sdManager = G4SDManager::GetSDMpointer();

    MySensitiveDetector* sdPiel = new MySensitiveDetector("PielSD");
    MySensitiveDetector* sdHueso = new MySensitiveDetector("HuesoSD");
    MySensitiveDetector* sdMusculo = new MySensitiveDetector("MusculoSD");
    MySensitiveDetector* sdPulmon = new MySensitiveDetector("PulmonSD");

    sdManager->AddNewDetector(sdPiel);
    sdManager->AddNewDetector(sdHueso);
    sdManager->AddNewDetector(sdMusculo);
    sdManager->AddNewDetector(sdPulmon);

    // Verificar que los volúmenes lógicos existen antes de asignar el detector
    if (logicPiel) logicPiel->SetSensitiveDetector(sdPiel);
    if (logicHueso) logicHueso->SetSensitiveDetector(sdHueso);
    if (logicMusculo) logicMusculo->SetSensitiveDetector(sdMusculo);
    if (logicPulmon) logicPulmon->SetSensitiveDetector(sdPulmon);

    G4cout << "✅ Sensitive Detectors asignados correctamente." << G4endl;
}
