// $Id$
//
// Class AGDDWriter
// ---------------------
// The implementation of the interface for the XML writer that
// writes VGM geometry objects to XML defined by AGDD.dtd
// (ATLAS Generic Detector Description)
//
// Author: I. Hrivnacova, 16.01.2004 

#ifndef XML_VGM_AGDD_WRITER_H
#define XML_VGM_AGDD_WRITER_H

#include <fstream>
#include <vector>
#include <string>

#include "VGM/solids/ISolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ITubs.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"

#include "XmlVGM/IWriter.h"
#include "XmlVGM/Maps.h"

class VGM::IMaterial;
class VGM::IElement;
class VGM::IVolume;
class VGM::IPlacement;

namespace XmlVGM {

  class AGDDWriter : public virtual IWriter
  {
    public:
      AGDDWriter(const std::string& version = "Undefined", 
	         const std::string& date = "Undefined", 
                 const std::string& author = "VGM AGGD Writer", 
	         const std::string dtdVersion = "v6");
      virtual ~AGDDWriter();

      // methods

      // XML elements 
      //
      virtual void OpenFile(std::string filePath);
      virtual void OpenDocument();
      virtual void OpenSection(const std::string& topVolume);
      virtual void OpenPositions() {} 
      virtual void OpenRotations() {}     
      virtual void OpenMaterials();
      virtual void OpenSolids() {} 
      virtual void OpenStructure() {} 
      virtual void OpenComposition(const std::string& name,
                                   const std::string& /*materialName*/);

      virtual void CloseFile();
      virtual void CloseDocument();
      virtual void CloseSection(const std::string& /*topVolume*/);
      virtual void ClosePositions() {}
      virtual void CloseRotations() {}
      virtual void CloseMaterials();
      virtual void CloseSolids() {}
      virtual void CloseStructure() {}
      virtual void CloseComposition();

      // Geometry elements
      //
      virtual void WriteElement(const VGM::IElement* /*element*/) {} 
    
      virtual void WriteMaterial(const VGM::IMaterial* material); 
    
      virtual void WriteSolid(std::string lvName, 
                            const VGM::ISolid* solid, 
                            std::string materialName); 
			    
      virtual void WritePosition(const std::string& /*name*/, 
                            const VGM::Transform& /*position*/) {} 
      virtual void WriteRotation(const std::string& /*name*/, 
                            const VGM::Transform& /*rotation*/) {} 

              void WritePlacement(const std::string& lvName, 
                            const ThreeVector& position); 
      virtual void WritePlacement(
                            const VGM::IPlacement& placement); 

      // Formatting utilities
      //
      virtual void WriteEmptyLine();
      virtual void IncreaseIndention();
      virtual void DecreaseIndention();
    
      // Units
      //
      virtual double LengthUnit() const;
      virtual double AngleUnit() const;
      virtual double AtomicWeightUnit() const;
      virtual double MassDensityUnit() const;

      // Set methods
      //
      virtual void SetNumWidth(int width);
      virtual void SetNumPrecision(int precision);

      // Get methods
      //
      virtual double GetNumWidth() const;
      virtual double GetNumPrecision() const;

    private:
      // Utility methods
      //
      void Append(std::string& string, int number) const;
      void CutName(std::string& name) const;
      void CutName(std::string& name, int size) const;
      void PutName(std::string& element, std::string name, 
                   std::string templ) const;
      std::ostream& SmartPut(std::ostream& out, int size, int precision,
		 double number, const std::string& separator) const;
      double  Round(double number) const;
      bool    IsIdentity(const ThreeVector& rotation) const;
   
      // Writing solids
      //
      void WriteBox (std::string lvName, 
                   double hx, double hy, double hz,  
                   std::string materialName); 
		   
      void WriteBox (std::string lvName, const VGM::IBox*  box,  
                     std::string materialName); 
		     
      void WriteTubs(std::string lvName, const VGM::ITubs* tubs, 
                   std::string materialName); 
		   
      void WriteCons(std::string lvName, const VGM::ICons* cons, 
                   std::string materialName); 
		   
      void WriteTrd (std::string lvName, const VGM::ITrd*  trd,  
                   std::string materialName); 
		   
      void WriteTrap(std::string lvName, const VGM::ITrap* trap, 
                    std::string materialName); 
		    
      void WritePara(std::string lvName, const VGM::IPara* para, 
                   std::string materialName); 
		   
      void WritePolycone(std::string lvName, const VGM::IPolycone* polycone, 
                   std::string materialName);
		    
      void WritePolyhedra(std::string lvName, const VGM::IPolyhedra* polyhedra, 
                   std::string materialName); 
		   
      void WriteNotSupportedSolid(std::string name, std::string materialName); 
  
      // Writing placements
      //
      virtual void WritePlacementWithRotation(
                            std::string lvName, 
			    const ThreeVector& position,
   			    const ThreeVector& rotation);
			    
      virtual void WritePlacementWithRotationAndReflection(
                            std::string lvName, 
			    const ThreeVector& position,
                            const ThreeVector& rotation); 
			    
      virtual void WriteMultiplePlacement(
                            const std::string& lvName,
                            VGM::Axis axis, int nofReplicas, 
			    double width, double offset);			       

      // static data members
      //
      static const int fgkMaxVolumeNameLength;  //maximal volume name length
      static const int fgkMaxMaterialNameLength;//maximal material name length
      static const int fgkDefaultNumWidth;      //default output numbers width
      static const int fgkDefaultNumPrecision;  //default output numbers precision 
      static const std::string fgkCompNameExtension; //name extension for composition

      // data members
      //
      std::ofstream      fOutFile;          //output file
      std::string        fVersion;          //geometry version
      std::string        fDate;             //date
      std::string        fAuthor;           //geometry author
      std::string        fDtdVersion;       //DTD version
      const std::string  fkBasicIndention;  //basic indention 
      std::string        fIndention;        //indention string
      int                fNW;               //output numbers width
      int                fNP;               //output numbers precision 
  };

}

// inline functions

inline double XmlVGM::AGDDWriter::LengthUnit() const
{ return 10.; }    // cm

inline double XmlVGM::AGDDWriter::AngleUnit() const
{ return  1.; }    // deg

inline double XmlVGM::AGDDWriter::AtomicWeightUnit() const
{ return  1.; }   // g/mole

inline double XmlVGM::AGDDWriter::MassDensityUnit() const
{ return  1.; }   // g/cm3
 
inline void XmlVGM::AGDDWriter::SetNumWidth(int width)
{ fNW = width; }

inline void XmlVGM::AGDDWriter::SetNumPrecision(int precision)
{ fNP = precision; }

inline double XmlVGM::AGDDWriter::GetNumWidth() const
{ return fNW; }

inline double XmlVGM::AGDDWriter::GetNumPrecision() const
{ return fNP; }

#endif //XML_VGM_AGDD_WRITER_H

