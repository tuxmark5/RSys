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
  protected:
    _M RDatabase*         m_database;
    _M QString            m_exprs[4];

  public:
    _M Vacuum             REntity2D(const QString& name, RDatabase* database, const QString& key0Field,
                                    const QString& key1Field, const QString& valueField);
    _V Vacuum             ~REntity2D();
};

/**********************************************************************************************/

template <class _Key0, class _Key1, class _Value>
class REntity2DI: public REntity2D
{
  public:
    _T _Key0                                      Key0;
    _T _Key1                                      Key1;
    //_T RSharedPtr<Key0>                           Key0Ptr;
    //_T RSharedPtr<Key1>                           Key1Ptr;
    _T _Value                                     Value;
    //_T QPair<Key0Ptr, Key1Ptr>                    JournalKey;
    _T QPair<Key0, Key1>                          JournalKey;
    _T QPair<Value, int>                          JournalValue;
    _T QHash<JournalKey, JournalValue>            Journal;
    _T std::function<QVariant (const Key0&)>      FromKey0;
    _T std::function<QVariant (const Key1&)>      FromKey1;
    _T std::function<Key0 (const QVariant&)>      ToKey0;
    _T std::function<Key1 (const QVariant&)>      ToKey1;
    _T std::function<void (Key0&, Key1&, Value)>  Setter;

  private:
    _M Journal            m_journal;
    _M FromKey0           m_fromKey0;
    _M FromKey1           m_fromKey1;
    _M ToKey0             m_toKey0;
    _M ToKey1             m_toKey1;
    _M Setter             m_setter;
    _M bool               m_allowInsert: 1;

  public:
    _M Vacuum             REntity2DI(const QString& name, RDatabase* database,
                                     const QString& key0Field, const QString& key1Field,
                                     const QString& valueField):
      REntity2D(name, database, key0Field, key1Field, valueField), m_allowInsert(true) { }

    _V bool               commit(QSqlQuery& query)
    {
      for (int state = 0; state < 3; state++)
      {
        query.prepare(m_exprs[state]);
        qDebug() << "DOIN" << m_exprs[state];

        for (auto it = m_journal.begin(); it != m_journal.end(); ++it)
        {
          const JournalKey&     key     = it.key();
          const JournalValue&   value   = it.value();

          if (value.second != state)
            continue;

          switch (state)
          {
            case Remove: syncRemove(query, key, value); break;
            case Update: syncUpdate(query, key, value); break;
          }
          query.exec();
        }
      }

      return m_journal.clear(), true;
    }

    _V void               init()
    { }

    _M void               onSet(const Key0& key0, const Key1& key1, Value value)
    {
      R_GUARD(m_allowInsert, Vacuum);
      m_journal.insert(JournalKey(key0, key1), JournalValue(value, Update));
    }

    _M void               onUnset(const Key0& key0, const Key1& key1)
    {
      m_journal.insert(JournalKey(key0, key1), JournalValue(Value(), Remove));
    }

    _V void               rollback()
    { m_journal.clear(); }

    _V bool               select(QSqlQuery& query)
    {
      query.exec(m_exprs[Select]);

      m_allowInsert = false;
      for (query.first(); query.isValid(); query.next())
      {
        Key0 key0 = m_toKey0(query.value(0));
        Key1 key1 = m_toKey1(query.value(1));
        m_setter(key0, key1, qvariant_cast<Value>(query.value(2)));
      }
      m_allowInsert = true;
      return true;
    }

    _M void               setKey0(FromKey0&& fromKey0, ToKey0&& toKey0)
    {
      m_fromKey0  = std::forward<FromKey0>(fromKey0);
      m_toKey0    = std::forward<ToKey0>(toKey0);
    }

    _M void               setKey1(FromKey1&& fromKey1, ToKey1&& toKey1)
    {
      m_fromKey1  = std::forward<FromKey1>(fromKey1);
      m_toKey1    = std::forward<ToKey1>(toKey1);
    }

    _M void               setSetter(Setter&& setter)
    {
      m_setter    = std::forward<Setter>(setter);
    }

  private:
    _M void               syncRemove(QSqlQuery& query, const JournalKey& key, const JournalValue& value)
    {
      Q_UNUSED(value);
      query.addBindValue(m_fromKey0(key.first));
      query.addBindValue(m_fromKey1(key.second));
    }

    _M void               syncUpdate(QSqlQuery& query, const JournalKey& key, const JournalValue& value)
    {
      query.addBindValue(m_fromKey0(key.first));
      query.addBindValue(m_fromKey1(key.second));
      query.addBindValue(value.first);
    }
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_2D_HH */
