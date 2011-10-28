#ifndef RSYS_IMPORT_RXLS_DOCUMENT_HH
#define RSYS_IMPORT_RXLS_DOCUMENT_HH

/**********************************************************************************************/
#include <External/ExcelFormat/BasicExcel.hpp>
#include <External/ExcelFormat/ExcelFormat.h>
#include <RSys/Import/RIDocument.hh>
#include <RSys/Import/RXLSTable.hh>

using namespace ExcelFormat;
/********************************************* RS *********************************************/
/*                                        RXLSDocument                                        */
/**********************************************************************************************/

class RXLSDocument: public RIDocument
{
  private:
    _M BasicExcel*  m_document;
  public:
    _M              RXLSDocument();
    _M              RXLSDocument(QString name);
    _V              ~RXLSDocument();
    _V void         open(QString name);
    _V void         close();
    _V QString      nameAt(int index) const;
    _V int          numTables() const;
    _V RXLSTable*   tableAt(int index) const;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RXLS_DOCUMENT_HH */
