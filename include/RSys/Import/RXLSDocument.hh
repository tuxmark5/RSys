#ifndef RSYS_IMPORT_RXLS_DOCUMENT_HH
#define RSYS_IMPORT_RXLS_DOCUMENT_HH

/**********************************************************************************************/
#include <External/ExcelFormat/BasicExcel.hpp>
#include <External/ExcelFormat/ExcelFormat.h>
#include <RSys/Import/RIDocument.hh>
#include <RSys/Import/RXLSTable.hh>
/**********************************************************************************************/
using namespace ExcelFormat;
/********************************************* RS *********************************************/
/*                                        RXLSDocument                                        */
/**********************************************************************************************/

class RXLSDocument: public RIDocument
{
  private:
    _M BasicExcel*    m_document;
    _M bool           m_opened: 1;

  public:
    _M Vacuum         RXLSDocument();
    _M Vacuum         RXLSDocument(const QString& name);
    _V Vacuum         ~RXLSDocument();
    _V bool           open(const QString& name);
    _V void           close();
    _M bool           isOpen() const { return m_opened; }
    _V QString        nameAt(int index) const;
    _V int            numTables() const;
    _V RXLSTable*     tableAt(int index) const;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RXLS_DOCUMENT_HH */
