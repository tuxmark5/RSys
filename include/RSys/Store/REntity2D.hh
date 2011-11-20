#ifndef RSYS_STORE_RENTITY_2D_HH
#define RSYS_STORE_RENTITY_2D_HH

/**********************************************************************************************/
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/REntity.hh>
/********************************************* RS *********************************************/
/*                                         REntity2D                                          */
/**********************************************************************************************/

class REntity2D: public REntity
{
  /*public:
    _E State
    {
      Insert = 0x00,
      Remove = 0x01,
      Update = 0x02,
      Select = 0x03
    };

  protected:
    _M QString            m_entityName;
    _M RDatabase*         m_database;
    _M QString            m_exprs[4];

  public:
    _M Vacuum             REntity1D(const QString& entity, RDatabase* database);
    _V Vacuum             ~REntity1D();
    _V void               init();*/
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_2D_HH */
