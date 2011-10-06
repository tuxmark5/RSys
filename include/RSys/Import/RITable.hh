#ifndef RSYS_IMPORT_RITABLE_HH
#define RSYS_IMPORT_RITABLE_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RITable                                           */
/**********************************************************************************************/

class RITable
{
  public:
    _V QVariant     cell(int x, int y) const = 0;
    _V QString      title() const   = 0;
    _V int          height() const  = 0;
    _V int          width() const   = 0;
};

/**********************************************************************************************/

#endif /* RSYS_IMPORT_RITABLE_HH */
