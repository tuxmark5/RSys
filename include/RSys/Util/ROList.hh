#ifndef RSYS_UTIL_ROLIST_HH
#define RSYS_UTIL_ROLIST_HH

/**********************************************************************************************/
#include <functional>
#include <QtCore/QList>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                           ROList                                           */
/**********************************************************************************************/

class RIObserver
{
  public:
    _V bool     insert0(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); return true; }
    _V void     insert1(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); }
    _V void     modify0(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); }
    _V void     modify1(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); }
    _V bool     remove0(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); return true; }
    _V void     remove1(int i0, int i1) { Q_UNUSED(i0); Q_UNUSED(i1); }
};

/**********************************************************************************************/

class RODispatcher
{
  public:
    _M RIObserver*        m_observer;
    _M RODispatcher*      m_nextDispatcher;
};

/**********************************************************************************************/

template <class _Value>
class ROList
{
  public:
    _T Id<int>                        Key;
    _T _Value                         Value;
    _T QList<Value>                   Base;
    _T ROList<Value>                  Self;
    _T typename Base::ConstIterator   ConstIterator;

  private:
    _M RODispatcher*        m_dispatcher;
    _M QList<Value>         m_list;

  private:

/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

    template <typename Fun, typename... Args>
    void notify(Fun fun, Args... args)
    {
      for (RODispatcher* d = m_dispatcher; d; d = d->m_nextDispatcher)
        (d->m_observer->*fun)(args...);
    }

    template <typename Fun, typename... Args>
    bool notifyAnd(Fun fun, Args... args)
    {
      bool result = true;
      for (RODispatcher* d = m_dispatcher; d; d = d->m_nextDispatcher)
        result &= (d->m_observer->*fun)(args...);
      return result;
    }

    template <typename Lambda, typename Fun0, typename Fun1, typename... Args>
    auto guarded(Fun0 fun0, Fun1 fun1, Lambda lambda, Args... args) -> decltype(lambda())
    {
      typedef decltype(lambda()) Result;

      if (notifyAnd(fun0, args...))
      {
        Result r = lambda();
        notify(fun1, args...);
        return r;
      }
      return Result();
    }

    template <typename Lambda, typename Fun0, typename Fun1, typename... Args>
    auto surrounded(Fun0 fun0, Fun1 fun1, Lambda lambda, Args... args) -> decltype(lambda())
    {
      notify(fun0, args...);
      decltype(lambda()) r = lambda();
      notify(fun1, args...);
      return r;
    }

/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

  public:
    _M Vacuum             ROList():
      m_dispatcher(0) { }

    _M Vacuum             ~ROList()
    {
      // TODO: delete observers & dispatchers
    }

    _M void addObserver(RIObserver* observer)
    {
      RODispatcher* dispatcher = new RODispatcher();

      dispatcher->m_nextDispatcher  = m_dispatcher;
      dispatcher->m_observer        = observer;
      m_dispatcher                  = dispatcher;
    }

    _M void append(const Value& x)
    {
      int i0 = m_list.length();

      guarded(&RIObserver::insert0, &RIObserver::insert1, [=]() -> bool
      { return this->m_list.append(x), true; }, i0, i0 + 1);
    }

    _M void modify(int i)
    {
      notify(&RIObserver::modify0, i, i + 1);
      notify(&RIObserver::modify1, i, i + 1);
    }

    _M void remove(int i)
    {
      guarded(&RIObserver::remove0, &RIObserver::remove1, [=]() -> bool
      { return this->m_list.remove(i), true; }, i, i + 1);
    }

    _M void removeObserver(RIObserver* observer)
    {
      for (RODispatcher** self = &m_dispatcher; *self; self = &(*self)->m_nextDispatcher)
      {
        if ((*self)->m_observer == observer)
        {
          RODispatcher* dispatcher0 = *self;

          *self = (*self)->m_nextDispatcher;
          delete dispatcher0;
          return;
        }
      }
    }

    _M const Value&     at(int x) const     { return m_list.at(x);    }
    _M ConstIterator    begin()   const     { return m_list.begin();  }
    _M ConstIterator    end()     const     { return m_list.end();    }
    _M int              length()  const     { return m_list.length(); }
    _M int              size()    const     { return m_list.size();   }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_ROLIST_HH */
