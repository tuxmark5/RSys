#ifndef RSYS_IMPORT_RXLS_TABLE_HH
#define RSYS_IMPORT_RXLS_TABLE_HH

/**********************************************************************************************/
#include <RSys/Import/RITable.hh>
/********************************************* RS *********************************************/
/*                                         RXLSTable                                          */
/**********************************************************************************************/

class RXLSTable: public RITable
{
  public:
    _V QVariant     cell(int x, int y) const;
    _V QString      title() const;
    _V int          height() const;
    _V int          width() const;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RXLS_TABLE_HH */
