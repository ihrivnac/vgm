// $Id$
//
// Class Tubs
// ---------------
// VGM implementation for Geant4 tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Tubs.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Tubs::Tubs(const std::string& name, 
                     double rin, double rout, double hz, 
		     double sphi, double dphi)
  : BaseVGM::VTubs(),
    fTubs(new G4Tubs(name, rin, rout, hz, sphi, dphi))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fTubs); 
}


//_____________________________________________________________________________
Geant4GM::Tubs::Tubs(G4Tubs* tubs, 
                     G4ReflectedSolid* reflTubs)
  : BaseVGM::VTubs(),
    fTubs(tubs)
{    
  if (reflTubs) 
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTubs);
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, tubs);
}

//_____________________________________________________________________________
Geant4GM::Tubs::~Tubs() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Tubs::Name() const
{
  return fTubs->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Tubs::InnerRadius() const
{
  return fTubs->GetInnerRadius();
}  

//_____________________________________________________________________________
double Geant4GM::Tubs::OuterRadius() const
{
  return fTubs->GetOuterRadius();
}  

//_____________________________________________________________________________
double Geant4GM::Tubs::ZHalfLength() const
{
  return fTubs->GetZHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Tubs::StartPhi() const
{
  return fTubs->GetStartPhiAngle();
}  

//_____________________________________________________________________________
double Geant4GM::Tubs::DeltaPhi() const
{
  return fTubs->GetDeltaPhiAngle();
}  