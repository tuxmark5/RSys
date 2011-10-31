#ifndef RSYS_IMPORT_RXLS_TABLE_HH
#define RSYS_IMPORT_RXLS_TABLE_HH

/**********************************************************************************************/
#include <External/ExcelFormat/BasicExcel.hpp>
#include <External/ExcelFormat/ExcelFormat.h>
#include <RSys/Import/RITable.hh>
/**********************************************************************************************/
using namespace ExcelFormat;
/********************************************* RS *********************************************/
/*                                         RXLSTable                                          */
/**********************************************************************************************/

class RXLSTable: public RITable
{
  private:
    _M BasicExcelWorksheet* m_table;

  public:
    _M                      RXLSTable(BasicExcelWorksheet* table);
    _V                      ~RXLSTable();
    _V QVariant             cell(int x, int y) const;
    _V QString              title() const;
    _V int                  height() const;
    _V int                  width() const;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RXLS_TABLE_HH */
