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
//
/// \file DetectorConstruction.hh
/// \brief Definition of the B1::DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Material.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

//namespace B1
//{

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    void  CreateMaterials();
    void  SetMaterialProperties_Air();   //
    void  SetMaterialProperties_Bc408(); //
    void  SetMaterialProperties_LG();    // Lightguides (Ac)
    void  SetMaterialProperties_PMT();   //
    void  SetProperties_Scinti();
    void  SetProperties_LG();
    

    const G4VPhysicalVolume* GetWorldPV()     const;
    const G4VPhysicalVolume* GetScintiPV()     const;
    const G4VPhysicalVolume* GetLightGuide_RPV() const;
    const G4VPhysicalVolume* GetLightGuide_LPV() const;
    const G4VPhysicalVolume* GetPMT_RPV()        const;
    const G4VPhysicalVolume* GetPMT_LPV()        const;

    void     SetLightGuideLength(G4double d)     {LightGuideLength = d;}
    void     SetScintiType(char* type)           {scinti_type = (G4String)type;}
    G4double GetLightGuideLength()               {return LightGuideLength;}
    G4String GetScintType()                      {return scinti_type;} 

    G4String    scinti_type;
    G4double    LightGuideLength; 

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;

  private:
    G4VPhysicalVolume*   fphys_world;
    G4VPhysicalVolume*   fphys_lg_r;    
    G4VPhysicalVolume*   fphys_lg_l;         
    G4VPhysicalVolume*   fphys_pmt_r;      
    G4VPhysicalVolume*   fphys_pmt_l;
    G4VPhysicalVolume*   fphys_scinti;

    G4double scinti_X;
    G4double scinti_Y;
    G4double scinti_Z;
    G4double lg_X;
    G4double lg_Y1;
    G4double lg_Y2;
    G4double lg_Z1;
    G4double lg_Z2;

    G4Material* air_m;
    G4Material* scinti_m;
    G4Material* lg_m;
    G4Material* pmt_m;
    G4Material* vacuum;
};

//inline function
inline const G4VPhysicalVolume* DetectorConstruction::GetWorldPV() const {
  return fphys_world;
}
inline const G4VPhysicalVolume* DetectorConstruction::GetScintiPV() const {
  return fphys_scinti;
}
inline const G4VPhysicalVolume* DetectorConstruction::GetLightGuide_RPV() const {
  return fphys_lg_r;
}
inline const G4VPhysicalVolume* DetectorConstruction::GetLightGuide_LPV() const {
  return fphys_lg_l;
}
inline const G4VPhysicalVolume* DetectorConstruction::GetPMT_RPV() const {
  return fphys_pmt_r;
}
inline const G4VPhysicalVolume* DetectorConstruction::GetPMT_LPV() const {
  return fphys_pmt_l;
}

//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
