#ifndef RSYS_STORE_RENTITY_1D_HH
#define RSYS_STORE_RENTITY_1D_HH

/**********************************************************************************************/
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/REntity.hh>
#include <RSys/Util/RAccessorAdapter.hh>
#include <RSys/Util/RFunAccessor.hh>
/********************************************* RS *********************************************/
/*                                         REntity1D                                          */
/**********************************************************************************************/

class REntity1D: public REntity
{
  protected:
    _M QString            m_entityName;
    _M RDatabase*         m_database;
    _M QString            m_exprs[4];

  public:
    _M Vacuum             REntity1D(const QString& entity, RDatabase* database);
    _V Vacuum             ~REntity1D();
    _V QString            fieldName(int i) const    = 0;
    _V void               init();
    _V int                numFields() const         = 0;
};

/**********************************************************************************************/

template <class _Value>
class REntity1DI: public REntity1D,
                  public RIObserver
{
  public:
    _T _Value                                           Value;
    _T REntity1DI<Value>                                Self;

    _T ROList<Value>                                    List;
    _T typename std::remove_pointer<Value>::type        Entry;
    _T RAccessorAdapter<Entry>                          Accessor;
    _T std::tuple<QString, Accessor*>                   Field;
    _T QList<Field>                                     FieldList;
    _T QHash<Value, int>                                Log;

  private:
    _M Log                m_log;
    _M FieldList          m_fields;
    _M List*              m_list;
    _M bool               m_allowInsert: 1;

  public:
    _M Vacuum             REntity1DI(const QString& entity, List* list, RDatabase* database):
      REntity1D(entity, database), m_list(list), m_allowInsert(true)
    {
      m_list->addObserver(this);
    }

    _V Vacuum             ~REntity1DI()
    {
      m_list->removeObserver(this);
    }

    template <class Type>
    _M RFunAccessor<Entry, Type>& addField(const QString& name)
    {
      auto accessor = new RAccessorAdapterI<RFunAccessor<Entry, Type> >();
      m_fields.append(Field(name, accessor));
      return accessor->m_accessor;
    }

    _M bool               commit(QSqlQuery& query)
    {
      bool result = true;

      for (auto it = m_log.begin(); it != m_log.end(); ++it)
      {
        qDebug() << "DOIN" << m_exprs[it.value()];

        query.prepare(m_exprs[it.value()]);

        switch (it.value())
        {
          case Insert: result = syncInsert(query, *it.key()); break;
          case Update: result = syncUpdate(query, *it.key()); break;
          case Remove: result = syncRemove(query, *it.key()); break;
        }

        if (!result)
          qDebug() << "ERR" << query.lastError();
      }

      m_log.clear();
      return true;
    }

    _V QString            fieldName(int i) const
    { return std::get<0>(m_fields.at(i)); }

    _V void               insert1(int i0, int i1)
    {
      Q_UNUSED(i1);
      R_GUARD(m_allowInsert, Vacuum);
      m_log.insert(m_list->at(i0), Insert);
    }

    _V void               modify1(int i0, int i1)
    {
      Q_UNUSED(i1);
      Value   value = m_list->at(i0);
      if (!m_log.contains(m_list->at(i0)))
        m_log.insert(value, Update);
    }

    _V int                numFields() const
    { return m_fields.size(); }

    _V bool               remove0(int i0, int i1)
    {
      Q_UNUSED(i1);
      Value   value = m_list->at(i0);
      int     state = m_log.value(m_list->at(i0), Update);
      if (state == Update)
        m_log.insert(value, Remove);
      else if (state == Remove)
        m_log.remove(value);
      return true;
    }

    _V void               rollback()
    {
      m_log.clear();
    }

    _M bool               select(QSqlQuery& query)
    {
      m_allowInsert = false;
      query.exec(m_exprs[Select]);

      for (query.first(); query.isValid(); query.next())
      {
        Value record = new Entry(m_database->data());
        for (int i = 0; i < m_fields.size(); i++)
          std::get<1>(m_fields[i])->set(*record, query.value(i));
        m_list->append(record);
      }

      m_allowInsert = true;

      return true;
    }

  private:
    _M bool               syncInsert(QSqlQuery& query, Entry& entry)
    {
      for (auto itf = m_fields.begin() + 1; itf != m_fields.end(); ++itf)
        query.addBindValue(std::get<1>(*itf)->get(entry));

      if (query.exec())
      {
        std::get<1>(m_fields.first())->set(entry, query.lastInsertId());
        return true;
      }

      return false;
    }

    _M bool               syncRemove(QSqlQuery& query, Entry& entry)
    {
      query.addBindValue(std::get<1>(m_fields.first())->get(entry));
      return query.exec();
    }

    _M bool               syncUpdate(QSqlQuery& query, Entry& entry)
    {
      //query.addBindValue(std::get<1>(m_fields.first())->get(entry));
      for (auto itf = m_fields.begin(); itf != m_fields.end(); ++itf)
        query.addBindValue(std::get<1>(*itf)->get(entry));
      return query.exec();
    }
};

/**********************************************************************************************/

template <class Value>
REntity1DI<Value>* newEntity1D(const QString& entity, ROList<Value>* list, RDatabase* database)
{ return new REntity1DI<Value>(entity, list, database); }

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_1D_HH */
