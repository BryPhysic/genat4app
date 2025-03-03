#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    MyPrimaryGeneratorAction() {
        G4int n_particle = 1;
        fParticleGun = new G4ParticleGun(n_particle);

        // Default particle kinematic
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4String particleName;
        G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
        fParticleGun->SetParticleEnergy(1.0*GeV);
        fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-1.0*m));
    }

    ~MyPrimaryGeneratorAction() {
        delete fParticleGun;
    }

    virtual void GeneratePrimaries(G4Event* anEvent) {
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

private:
    G4ParticleGun* fParticleGun;
};