#ifndef RSYS_IMPORT_RIDOCUMENT_HH
#define RSYS_IMPORT_RIDOCUMENT_HH

/**********************************************************************************************/
#include <RSys/Import/RITable.hh>
/********************************************* RS *********************************************/
/*                                         RIDocument                                         */
/**********************************************************************************************/

class RIDocument
{
  public:
    _V QString      nameAt(int index)   const = 0;
    _V int          numTables()         const = 0;
    _V RITable*     tableAt(int index)  const = 0;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RIDOCUMENT_HH */
