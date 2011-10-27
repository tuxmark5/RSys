#ifndef RSYS_IMPORT_RXLS_DOCUMENT_HH
#define RSYS_IMPORT_RXLS_DOCUMENT_HH

/**********************************************************************************************/
#include <RSys/Import/RIDocument.hh>
/********************************************* RS *********************************************/
/*                                        RXLSDocument                                        */
/**********************************************************************************************/

class RXLSDocument: public RIDocument
{
  public:
    _V QString      nameAt(int index) const;
    _V int          numTables() const;
    _V RITable*     tableAt(int index) const;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RXLS_DOCUMENT_HH */
