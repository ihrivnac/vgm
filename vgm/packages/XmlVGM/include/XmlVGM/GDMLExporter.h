// $Id$
//
// Author: I. Hrivnacova, 31.03.2004 
//
// Class GDMLExporter
// -------------------
// Class for generation of geometry data files in XML,
// in the GDML format.

#ifndef XML_VGM_GDML_EXPORTER_H
#define XML_VGM_GDML_EXPORTER_H

#include "XmlVGM/VExporter.h"

class VGM::IFactory;
class VGM::IVolume;

namespace XmlVGM {

  class GDMLExporter : public VExporter
  {
    public:
      GDMLExporter(const VGM::IFactory* factory);
      // --> protected
      // GDMLExporter(const GDMLExporter& right);
      virtual ~GDMLExporter();
 
    protected:
      GDMLExporter(const GDMLExporter& right);

      // operators
      GDMLExporter& operator=(const GDMLExporter& right);

      // methods 
      // (specific to XML definition)
      //
      virtual void GenerateGeometry(VGM::IVolume* volume);
      virtual void GenerateSection(VGM::IVolume* volume);
      virtual void ProcessVolume(VGM::IVolume* volume); 
  };

}

#endif //XML_VGM_GDML_EXPORTER_H
