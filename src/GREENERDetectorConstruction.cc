//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "GREENERDetectorConstruction.hh"

#include "G4RunManager.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <iostream>
#include <ostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
GREENERDetectorConstruction::GREENERDetectorConstruction()
  :G4VUserDetectorConstruction(),
   worldPhysical(0),
   fConstructed(false)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
GREENERDetectorConstruction::~GREENERDetectorConstruction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* GREENERDetectorConstruction::Construct()
{
  if(!fConstructed)
  { 
    fConstructed = true;
    DefineMaterials();
    SetupGeometry();
  }
  return worldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GREENERDetectorConstruction::DefineMaterials()
{ 
  //-------- NIST Materials -----------------------------------------------
  //  Material Information imported from NIST database. 
  G4NistManager* NISTman = G4NistManager::Instance();

  capsuleMaterial   = NISTman->FindOrBuildMaterial("G4_WATER");

  static constexpr double universe_mean_density = 1.e-25*g/cm3;
  Vacuum1 = new G4Material("VACUUM1",
                           1.,
                           1.01*g/mole,
                           universe_mean_density);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GREENERDetectorConstruction::SetupGeometry()
{
  //     
  // World
  //
  G4VSolid* worldSolid = new G4Box("World",6.*m,6.*m,6.*m);

  worldLogical = new G4LogicalVolume(worldSolid,
                                     Vacuum1,
                                     "World");
  worldPhysical = new G4PVPlacement(0,
                                    G4ThreeVector(),
                                    worldLogical,
                                    "World",
                                    0,
                                    false,
                                    0);

  // Construct a box with the given parameters
  G4Box* capsuleSolid;
  G4LogicalVolume* capsuleLogical;

  capsuleSolid = new G4Box("Capsule", //its name
                            0.0005*m, // x half side length
                            0.0005*m, // y half side length
                            0.0025*m); // z half side length
                                      // z is the axis of the source -> detector

  capsuleLogical = new G4LogicalVolume(capsuleSolid,       //its solid
                                        capsuleMaterial,    //its material
                                        "CapsuleLV");          //its name

  // rotation
  G4RotationMatrix* capsuleRotMat =  new G4RotationMatrix();
  capsuleRotMat->rotateZ(0);

  // calculate the position of this block
  G4ThreeVector boxPosition (0,
                             0,
                             0);

  new G4PVPlacement(capsuleRotMat,              //its rotation
                    boxPosition,       //its translation
                    capsuleLogical,      //its logical volume
                    "Capsule",              //its name
                    worldLogical,       //its mother volume
                    false,               //no boolean operation
                    0,                   //copy number
                    true);     //checking overlaps


  G4cout << "GREENER: Geometry done" << std::endl;

}
