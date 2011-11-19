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
    _V bool           remove(int x)                                         = 0;
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
    _T RContainerI<_List>                               Self;

  public:
    _M Allocator      m_allocator;
    _M List*          m_list;
    _M ColumnMap      m_columns;
    _M HeaderList     m_headers;

  public:
    _M Vacuum         RContainerI(List* list):
      m_list(list) { }

    template <class List2>
    _M Vacuum         RContainerI(List* list, const List2& other):
      m_allocator(other.m_allocator),
      m_list(list),
      m_columns(other.m_columns),
      m_headers(other.m_headers) { }

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
      int   index     = (column << 8) | role;
      auto  accessor  = static_cast<RAccessorAdapterI<RFunAccessor<Entry, Value> >* >
          (m_columns.value(index));

      if (!accessor)
      {
        accessor = new RAccessorAdapterI<RFunAccessor<Entry, Value> >();
        m_columns.insert(index, accessor);
      }
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

    _V bool           remove(int x)
    { return m_list->removeAt(x); }

    _V void           removeObserver(RIObserver* observer)
    { m_list->removeObserver(observer); }

    _V bool           set(int x, int y, int role, const QVariant& variant)
    {
      if (Accessor* accessor = m_columns.value(x << 8 | role))
      {
        accessor->set(*m_list->at(y), variant);
        m_list->modify(y);
      }
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

template <class List, class List2>
RContainerI<List>* newContainer(List* list, const RContainerI<List2>& other)
{ return new RContainerI<List>(list, other); }

/**********************************************************************************************/

#endif /* RSYS_UTIL_RCONTAINER_HH */
