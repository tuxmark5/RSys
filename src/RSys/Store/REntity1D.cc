#include <RSys/Store/REntity1D.hh>

/********************************************* RS *********************************************/
/*                                         REntity1D                                          */
/**********************************************************************************************/

Vacuum REntity1D :: REntity1D(const QString& entity, RDatabase* database):
  m_entityName(entity),
  m_database(database)
{
}

/**********************************************************************************************/

Vacuum REntity1D :: ~REntity1D()
{
}

/**********************************************************************************************/

void REntity1D :: init()
{
  int         numFields   = this->numFields();
  QString     wildcards;
  QString     field0      = fieldName(0);
  QString     fields;

  for (int i = 1; i < numFields; i++)
  {
    wildcards += ":" + fieldName(i);
    fields    +=       fieldName(i);

    if (i + 1 != numFields)
    {
      wildcards += ",";
      fields    += ",";
    }
  }

  m_exprs[Remove]  = QString("DELETE FROM %1 WHERE %2 = :%2;")
    .arg(m_entityName, field0);
  m_exprs[Select]  = QString("SELECT %1,%2 FROM %3 ORDER BY 2;")
    .arg(field0, fields, m_entityName);

  if (m_database->isPostgres())
  {
    m_exprs[Insert]  = QString("INSERT INTO %1(%2,%3) VALUES(DEFAULT,%4) returning %2;")
      .arg(m_entityName, field0, fields, wildcards);
    m_exprs[Update]  = QString("UPDATE %1 SET (%3) = (%4) WHERE %2 = :%2;") // update
      .arg(m_entityName, field0, fields, wildcards);
  }
  else
  {
    m_exprs[Insert]  = QString("INSERT INTO %1(%2) VALUES(%3);")
      .arg(m_entityName, fields, wildcards);
    m_exprs[Update]  = QString("REPLACE INTO %1(%2,%3) VALUES(:%2,%4);")
      .arg(m_entityName, field0, fields, wildcards);
  }
}

/**********************************************************************************************/
