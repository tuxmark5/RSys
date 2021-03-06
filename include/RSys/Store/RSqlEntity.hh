#ifndef RSYS_STORE_RSQL_ENTITY_HH
#define RSYS_STORE_RSQL_ENTITY_HH

/**********************************************************************************************/
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/REntity.hh>
/********************************************* RS *********************************************/
/*                                         RSqlEntity                                         */
/**********************************************************************************************/

class RSqlEntity: public REntity
{
  public:
    //_T std::function<bool (QSqlQuery&)>   QueryFun;
    _T std::tuple<void*, int, QString>    Transaction;
    _T QList<Transaction>                 Log;

  protected:
    _M Log                m_log;

  public:
    _M Vacuum             RSqlEntity();
    _V Vacuum             ~RSqlEntity();
    _V bool               commit(QSqlQuery& query);
    _M void               exec(void* source, int type, const QString& sql);
    _V void               init();
    _V void               rollback();
    _V bool               select(QSqlQuery& query);
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RSQL_ENTITY_HH */
