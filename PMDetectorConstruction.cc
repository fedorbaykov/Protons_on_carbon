#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // Материал мира — воздух
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

  // Объём мира 50 см куб
  G4Box* solidWorld = new G4Box("World", 25*cm, 25*cm, 25*cm);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "WorldLV");

  G4VPhysicalVolume* physWorld = new G4PVPlacement(
       0,                   // no rotation
       G4ThreeVector(),     // at (0,0,0)
       logicWorld,
       "WorldPV",
       0,
       false,
       0,
       true);

  // Материал мишени — углерод (чистый)
  G4Material* carbon = nist->FindOrBuildMaterial("G4_C");
  if (!carbon) {
    // если нет стандартного, создать вручную
    carbon = new G4Material("Carbon", 6, 12.01*g/mole, 2.267*g/cm3);
  }

  // Мишень – куб 2x2x2 см³
  G4Box* solidTarget = new G4Box("Target", 1*cm, 1*cm, 1*cm);

  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, carbon, "TargetLV");

  // Поместить мишень по Z=5 cm вперед от центра
  new G4PVPlacement(
       0,
       G4ThreeVector(0.,0.,5*cm),
       logicTarget,
       "TargetPV",
       logicWorld,
       false,
       0,
       true);

  return physWorld;
}
