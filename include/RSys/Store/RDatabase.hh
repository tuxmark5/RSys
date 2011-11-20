#ifndef RSYS_STORE_RDATABASE_HH
#define RSYS_STORE_RDATABASE_HH

/**********************************************************************************************/
#include <QtCore/QSet>
#include <QtSql/QSqlDatabase>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                         RDatabase                                          */
/**********************************************************************************************/

class RDatabase: public QObject
{
  Q_OBJECT

  public:
    _T QList<REntity*>  EntityList;

  private:
    _M RData*         m_data;
    _M QSqlDatabase   m_database;
    _M EntityList     m_entities;

  public:
    _M Vacuum         RDatabase(RData* data, QObject* parent = 0);
    _V Vacuum         ~RDatabase();
    _M RData*         data() const { return m_data; }
    _M bool           login(const QString& addr, const QString& db, const QString& user, const QString& pass);

  public slots:
    _M bool           commit();
    _M void           logout();
    _M bool           rollback();
    _M bool           select();

  private:
    _M void           initDb();

  signals:
    _M void           loggedIn();
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RDATABASE_HH */
