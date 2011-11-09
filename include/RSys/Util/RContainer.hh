#ifndef RSYS_UTIL_RCONTAINER_HH
#define RSYS_UTIL_RCONTAINER_HH

/**********************************************************************************************/
#include <RSys/Util/RAccessorAdapter.hh>
#include <RSys/Util/RFunAccessor.hh>
#include <RSys/Util/RMemAccessor.hh>
/********************************************* RS *********************************************/
/*                                         RContainer                                         */
/**********************************************************************************************/

class RContainer
{
  public:
    _V Vacuum         ~RContainer() { }
    _V bool           add()                                                 = 0;
    _V void           addObserver(RIObserver* observer)                     = 0;
    _V QVariant       get(int x, int y, int role) const                     = 0;
    _V QString        header(int x) const                                   = 0;
    _V int            height() const                                        = 0;
    //_V void           remove(int x)                               = 0;
    _V void           removeObserver(RIObserver* observer)                  = 0;
    _V bool           set(int x, int y, int role, const QVariant& variant)  = 0;
    _V int            width() const                                         = 0;
    _V bool           writable() const                                      = 0;
};

/**********************************************************************************************/

template <class _List>
class RContainerI: public RContainer
{
  public:
    _T _List                                            List;
    _T typename _List::Value                            EntryPtr;
    _T typename std::remove_pointer<EntryPtr>::type     Entry;
    _T RAccessorAdapter<Entry>                          Accessor;
    _T std::function<Entry*()>                          Allocator;
    _T QHash<int, Accessor*>                            ColumnMap;
    _T QList<QString>                                   HeaderList;

  private:
    _M Allocator      m_allocator;
    _M List*          m_list;
    _M ColumnMap      m_columns;
    _M HeaderList     m_headers;

  public:
    _M Vacuum         RContainerI(List* list):
      m_list(list) { }

    _M Vacuum         ~RContainerI()
      { } // TODO: delete accessors

    _V bool           add()
    {
      if (m_allocator)
        return m_list->append(m_allocator()), true;
      return false;
    }

    _V void           addObserver(RIObserver* observer)
    { m_list->addObserver(observer); }

    template <class   Value,
              class   _Getter, _Getter Getter,
              class   _Setter, _Setter Setter>
    _M void           addAccessor(int column, int role)
    {
      Accessor* accessor = new RAccessorAdapterI<RMemAccessor<Entry, Value, _Getter, Getter, _Setter, Setter> >();
      m_columns.insert((column << 8) | role, accessor);
    }

    template <class   Value>
    _M RFunAccessor<Entry, Value>& addAccessor2(int column, int role)
    {
      auto accessor = new RAccessorAdapterI<RFunAccessor<Entry, Value> >();
      m_columns.insert((column << 8) | role, accessor);
      return accessor->m_accessor;
    }

    _M void           addColumn(const char* title)
    {
      m_headers.append(QString::fromUtf8(title));
    }

    _V QVariant       get(int x, int y, int role) const
    {
      if (Accessor* accessor  = m_columns.value(x << 8 | role))
        return accessor->get(*m_list->at(y));
      return QVariant();
    }

    _V QString        header(int x) const
    { return m_headers.at(x); }

    _V int            height() const
    { return m_list->length(); }

    _V void           removeObserver(RIObserver* observer)
    { m_list->removeObserver(observer); }

    _V bool           set(int x, int y, int role, const QVariant& variant)
    {
      if (Accessor* accessor = m_columns.value(x << 8 | role))
        accessor->set(*m_list->at(y), variant);
      return true;
    }

    _M void           setAlloc(Allocator allocator)
    { m_allocator = std::move(allocator); }

    _V int            width() const
    { return m_headers.length(); }

    _V bool           writable() const
    { return bool(m_allocator); }
};

/**********************************************************************************************/

template <class List>
RContainerI<List>* newContainer(List* list)
{ return new RContainerI<List>(list); }

/**********************************************************************************************/

#endif /* RSYS_UTIL_RCONTAINER_HH */
