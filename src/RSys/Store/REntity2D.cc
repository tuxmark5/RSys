#include <RSys/Store/REntity2D.hh>

/********************************************* RS *********************************************/
/*                                         REntity2D                                          */
/**********************************************************************************************/

Vacuum REntity2D :: REntity2D(const QString& name, const QString& key0Field,
                              const QString& key1Field, const QString& valueField)
{
  if (true)
  {
    m_exprs[Insert] = QString("INSERT INTO %1(%2,%3,%4) VALUES(?,?,?);")
      .arg(name, key0Field, key1Field, valueField);
    m_exprs[Remove] = QString("DELETE FROM %1 WHERE %2 = ? AND %3 = ?;")
      .arg(name, key0Field, key1Field);
    m_exprs[Select] = QString("SELECT %1,%2,%3 FROM %4;")
      .arg(key0Field, key1Field, valueField, name);
  }

  if (g_postgres)
  {
    m_exprs[Update] = QString("INSERT INTO %1(%2,%3,%4) VALUES(?,?,?);")
      .arg(name, key0Field, key1Field, valueField);
  }
  else
  {
    m_exprs[Update] = QString("REPLACE INTO %1(%2,%3,%4) VALUES(?,?,?);")
      .arg(name, key0Field, key1Field, valueField);
  }
}

/**********************************************************************************************/

Vacuum REntity2D :: ~REntity2D()
{
}

/**********************************************************************************************/
