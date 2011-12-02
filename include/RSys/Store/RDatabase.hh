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
    _M RData*           m_data;
    _M RUserPtr         m_user;
    _M QSqlDatabase     m_database;
    _M EntityList       m_entities;
    _M RSqlEntity*      m_sqlEntity;
    _M bool             m_postgres: 1;

  public:
    _M Vacuum           RDatabase(RData* data, QObject* parent = 0);
    _V Vacuum           ~RDatabase();
    _M RData*           data() const { return m_data; }
    _M bool             login(const QString& dbFile);
    _M bool             login(const QString& addr, const QString& db, const QString& user, const QString& pass);
    _M RSqlEntity*      sqlEntity() const { return m_sqlEntity; }
    _M RUser*           user() const { return m_user; }

  public slots:
    _M bool             commit();
    _M void             logout();
    _M bool             rollback();
    _M bool             select();

  private:
    _M void             createAdminDataEntities();
    _M void             createDataEntities();
    _M void             emitPSQLError(const QSqlError& error);
    _M void             emitSQLiteError(const QSqlError& error);
    _M void             initDb();
    _M bool             load();

  signals:
    _M void             loggedIn();
    _M void             message(const QString& text);
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RDATABASE_HH */
