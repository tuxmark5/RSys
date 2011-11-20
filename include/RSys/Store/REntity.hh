#ifndef RSYS_STORE_RENTITY_HH
#define RSYS_STORE_RENTITY_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          REntity                                           */
/**********************************************************************************************/

class REntity
{
  public:
    _V Vacuum             ~REntity() { }
    _V void               init()                    = 0;
    _V bool               commit(QSqlQuery& query)  = 0;
    _V QString            fieldName(int i) const    = 0;
    _V int                numFields() const         = 0;
    _V void               rollback()                = 0;
    _V bool               select(QSqlQuery& query)  = 0;
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_HH */
