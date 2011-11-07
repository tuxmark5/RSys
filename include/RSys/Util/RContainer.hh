#ifndef RSYS_UTIL_RCONTAINER_HH
#define RSYS_UTIL_RCONTAINER_HH

/**********************************************************************************************/
#include <RSys/Util/RAccessorAdapter.hh>
#include <RSys/Util/RMemAccessor.hh>
/********************************************* RS *********************************************/
/*                                         RContainer                                         */
/**********************************************************************************************/

class RContainer
{
  public:
    _V Vacuum         ~RContainer() { }
    _V bool           add()                                       = 0;
    _V void           addObserver(RIObserver* observer)           = 0;
    _V QVariant       get(int x, int y) const                     = 0;
    _V QString        header(int x) const                         = 0;
    _V int            height() const                              = 0;
    //_V void           remove(int x)                               = 0;
    _V bool           set(int x, int y, const QVariant& variant)  = 0;
    _V int            width() const                               = 0;
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
    _T std::pair<QString, Accessor*>                    Column;
    _T QList<Column>                                    ColumnList;
    _T std::function<Entry*()>                          Allocator;

  private:
    _M Allocator      m_allocator;
    _M List*          m_list;
    _M ColumnList     m_columns;

  public:
    _M Vacuum         RContainerI(List* list):
      m_list(list) { }

    _M Vacuum         ~RContainerI()
      { }

    _V bool           add()
    {
      m_list->append(m_allocator());
      return true;
    }

    _V void           addObserver(RIObserver* observer)
    { m_list->addObserver(observer); }

    template <class   Value,
              Value   (Entry::*Getter)() const,
              void    (Entry::*Setter)(const Value&)>
    _M void           addColumn(const QString& title)
    {
      Accessor* accessor = new RAccessorAdapterI<RMemAccessor<Entry, Value, Getter, Setter> >();
      m_columns.append(Column(title, accessor));
    }

    _V QVariant       get(int x, int y) const
    {
      Accessor*     accessor  = m_columns.at(x).second;
      const Entry*  entry     = m_list->at(y);

      return accessor->get(*entry);
    }

    _V QString        header(int x) const
    { return m_columns.at(x).first; }

    _V int            height() const
    { return m_list->length(); }

    _V bool           set(int x, int y, const QVariant& variant)
    {
      Accessor*     accessor  = m_columns.at(x).second;
      Entry*        entry     = m_list->at(y);

      accessor->set(*entry, variant);
      return true;
    }

    _M void           setAlloc(Allocator allocator)
    { m_allocator = std::move(allocator); }

    _V int            width() const
    { return m_columns.length(); }
};

/**********************************************************************************************/

template <class List>
RContainerI<List>* newContainer(List* list)
{ return new RContainerI<List>(list); }

/**********************************************************************************************/

#endif /* RSYS_UTIL_RCONTAINER_HH */
