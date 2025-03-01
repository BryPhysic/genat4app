#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

private:
    void DefineMaterials();
    G4VPhysicalVolume* ConstructWorld();
    void ConstructTissueLayers(G4LogicalVolume* worldLog);

    // **DECLARACIÓN DE VARIABLES GLOBALES DENTRO DE LA CLASE**
    G4Material* matWorld;
    G4Material* matPiel;
    G4Material* matHueso;
    G4Material* matMusculo;
    G4Material* matPulmon;

    G4LogicalVolume* logicWorld;
    G4LogicalVolume* logicPiel;
    G4LogicalVolume* logicHueso;
    G4LogicalVolume* logicMusculo;
    G4LogicalVolume* logicPulmon;

    G4double worldSizeX;
    G4double worldSizeY;
    G4double worldSizeZ;

    G4double d_piel;
    G4double d_hueso;
    G4double d_musculo;
    G4double d_pulmon;
};

#endif