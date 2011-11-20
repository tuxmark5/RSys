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
    _E State
    {
      Insert = 0x00,
      Remove = 0x01,
      Update = 0x02,
      Select = 0x03
    };

  public:
    _V Vacuum             ~REntity() { }
    _V bool               commit(QSqlQuery& query)  = 0;
    _V void               init()                    = 0;
    _V void               rollback()                = 0;
    _V bool               select(QSqlQuery& query)  = 0;
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_HH */
