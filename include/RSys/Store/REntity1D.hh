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
    _T typename FieldList::ConstIterator                FieldIterator;
    _T QHash<Value, int>                                Log;
    _T std::function<Entry*()>                          Allocator;
    _T std::function<bool (const Entry&)>               Filter;

  private:
    _M Log                m_log;
    _M FieldList          m_fields;
    _M List*              m_list;
    _M Allocator          m_allocator;
    _M Filter             m_filter;
    _M bool               m_allowInsert: 1;

  public:
    _M Vacuum             REntity1DI(const QString& entity, RDatabase* database, List* list, Allocator&& allocator):
      REntity1D(entity, database), m_list(list),
      m_allocator(std::forward<Allocator>(allocator)),
      m_allowInsert(true)
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

      for (int state = 0; state < 3; state++)
      {
        query.prepare(m_exprs[state]);

        for (auto it = m_log.begin(); it != m_log.end(); it++)
        {
          if (it.value() != state)
            continue;

          if (m_filter && !m_filter(*it.key()))
          {
            result = false;
            break;
          }

          switch (state)
          {
            case Insert: result = syncInsert(query, *it.key()); break;
            case Update: result = syncUpdate(query, *it.key()); break;
            case Remove: result = syncRemove(query, *it.key()); break;
          }
        }

        if (!result)
        {
          qDebug() << "ERR" << m_exprs[state] << query.lastError();
          return false;
        }
      }

      rollback();
      return true;
    }

    _V QString            fieldName(int i) const
    { return std::get<0>(m_fields.at(i)); }

    _V void               insert1(int i0, int i1)
    {
      Q_UNUSED(i1);
      R_GUARD(m_allowInsert, Vacuum);

      const Value& value = m_list->at(i0);
      m_log.insert(value, Insert); // (m_filter && !m_filter(*value)) ? Transient :
    }

    _V void               modify1(int i0, int i1)
    {
      Q_UNUSED(i1);
      Value   value = m_list->at(i0);

      switch (m_log.value(value, Invalid))
      {
        case Transient: m_log.insert(value, Insert); break;
        case Invalid:   m_log.insert(value, Update); break;
      }
    }

    _V int                numFields() const
    { return m_fields.size(); }

    _V bool               remove0(int i0, int i1)
    {
      Q_UNUSED(i1);
      Value   value = m_list->at(i0);
      int     state = m_log.value(m_list->at(i0), Update);

      switch (state)
      {
        case Update:    m_log.insert(value, Remove); break;
        case Insert:
        case Remove:
        case Transient: m_log.remove(value); break;
      }

      return true;
    }

    _V void               rollback()
    {
      m_log.clear();
      /*for (auto it = m_log.begin(); it != m_log.end(); )
      {
        if (it.value() < 3)
          it = m_log.erase(it);
        else
          ++it;
      }*/
    }

    _M bool               select(QSqlQuery& query)
    {
      if (!query.exec(m_exprs[Select]))
      {
        qDebug() << "Can't execute:" << m_exprs[Select];
        return false;
      }

      m_allowInsert = false;

      for (query.first(); query.isValid(); query.next())
      {
        Value record = m_allocator();
        for (int i = 0; i < m_fields.size(); i++)
          std::get<1>(m_fields[i])->set(*record, query.value(i));
        m_list->append(record);
      }

      m_allowInsert = true;

      return true;
    }

    _M void               setFilter(Filter filter)
    { m_filter = std::move(filter); }

  private:
    _M void               bindValues(QSqlQuery& query, Entry& entry, FieldIterator it0, FieldIterator it1)
    {
      for (; it0 != it1; ++it0)
        query.bindValue(":" + std::get<0>(*it0), std::get<1>(*it0)->get(entry));
    }

    _M bool               syncInsert(QSqlQuery& query, Entry& entry)
    {
      bindValues(query, entry, m_fields.begin() + 1, m_fields.end());

      if (query.exec())
      {
        QVariant lastId = m_database->isPostgres() ? query.first(), query.value(0) : query.lastInsertId();
        std::get<1>(m_fields.first())->set(entry, lastId);
        return true;
      }

      return false;
    }

    _M bool               syncRemove(QSqlQuery& query, Entry& entry)
    {
      bindValues(query, entry, m_fields.begin(), m_fields.begin() + 1);
      return query.exec();
    }

    _M bool               syncUpdate(QSqlQuery& query, Entry& entry)
    {
      bindValues(query, entry, m_fields.begin(), m_fields.end());
      return query.exec();
    }
};

/**********************************************************************************************/

template <class Value, class... Args>
REntity1DI<Value>* newEntity1D(const QString& entity, RDatabase* database, ROList<Value>* list, Args&&... args)
{ return new REntity1DI<Value>(entity, database, list, std::forward<Args>(args)...); }

/**********************************************************************************************/

#endif /* RSYS_STORE_RENTITY_1D_HH */
