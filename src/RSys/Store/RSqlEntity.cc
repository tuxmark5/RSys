#include <QtSql/QSqlQuery>
#include <RSys/Store/RSqlEntity.hh>

/********************************************* RS *********************************************/
/*                                         RSqlEntity                                         */
/**********************************************************************************************/

Vacuum RSqlEntity :: RSqlEntity()
{
}

/**********************************************************************************************/

Vacuum RSqlEntity :: ~RSqlEntity()
{
}

/**********************************************************************************************/

bool RSqlEntity :: commit(QSqlQuery& query)
{
  for (auto it = m_log.begin(); it != m_log.end(); ++it)
  {
    const QString& stmt = std::get<2>(*it);

    qDebug() << "EXECUTING" << stmt;
    if (!query.exec(stmt))
      qDebug() << "FAILED TO EXEC" << stmt;
  }

  m_log.clear();
  return true;
}

/**********************************************************************************************/

void RSqlEntity :: exec(void* source, int type, const QString& sql)
{
  if (source != 0)
  {
    for (auto it = m_log.begin(); it != m_log.end(); )
    {
      if ((std::get<0>(*it) == source) && (std::get<1>(*it) == type))
        it = m_log.erase(it);
      else
        ++it;
    }
  }

  m_log.append(Transaction(source, type, sql));
}

/**********************************************************************************************/

void RSqlEntity :: init()
{
}

/**********************************************************************************************/

void RSqlEntity :: rollback()
{
  m_log.clear();
}

/**********************************************************************************************/

bool RSqlEntity :: select(QSqlQuery& query)
{
  Q_UNUSED(query);
  return true;
}

/**********************************************************************************************/
