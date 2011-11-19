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

void REntity1D :: buildExprs()
{
  int         numFields   = this->numFields();
  QString     wildcards;
  QString     field0      = fieldName(0);
  QString     fields;

  for (int i = 1; i < numFields; i++)
  {
    wildcards += "?";
    fields    += fieldName(i);

    if (i + 1 != numFields)
    {
      wildcards += ",";
      fields    += ",";
    }
  }

  m_exprs[Insert]  = QString("INSERT INTO %1(%2) VALUES(%3);")
    .arg(m_entityName).arg(fields).arg(wildcards);

  m_exprs[Remove]  = QString("DELETE FROM %1 WHERE %2 = ?;")
    .arg(m_entityName).arg(field0);

  //m_exprs[Update]  = m_exprs[Remove];
  m_exprs[Update]  = QString("REPLACE INTO %1(%2,%3) VALUES(?,%4);")
    .arg(m_entityName).arg(field0).arg(fields).arg(wildcards);

  m_exprs[Select]  = QString("SELECT %1,%2 FROM %3;")
    .arg(field0).arg(fields).arg(m_entityName);
}

/**********************************************************************************************/
