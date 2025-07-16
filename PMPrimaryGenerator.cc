#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Proton.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  // Один первичный частиц
  fParticleGun = new G4ParticleGun(1);

  // Инициализация источника: протон 12 ГэВ направленный вдоль Z
  G4ParticleDefinition* particle = G4Proton::ProtonDefinition();
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(12*GeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Позиция пучка в начале координат
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
