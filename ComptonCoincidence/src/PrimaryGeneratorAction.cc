#include "PrimaryGeneratorAction.hh"

#include "G4PhysicalConstants.hh" 
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Definizione del fotone gamma
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  
  // Energia di annichilazione del Na-22
  fParticleGun->SetParticleEnergy(511.*keV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Posizione della sorgente (origine del mondo)
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));

  // GENERAZIONE BACK-TO-BACK 
  
  // 1. Genero una direzione casuale nel 4pi per il primo fotone
  G4double cosTheta = 2.0*G4UniformRand() - 1.0;
  G4double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);
  
  G4double phi = CLHEP::twopi * G4UniformRand();
  
  G4ThreeVector dir1(sinTheta*std::cos(phi), sinTheta*std::sin(phi), cosTheta);
  
  // Sparo il primo fotone (verso il rivelatore)
  fParticleGun->SetParticleMomentumDirection(dir1);
  fParticleGun->GeneratePrimaryVertex(anEvent);

  // 2. Il secondo fotone va esattamente nella direzione opposta (180 gradi)
  G4ThreeVector dir2 = -dir1;
  fParticleGun->SetParticleMomentumDirection(dir2);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}