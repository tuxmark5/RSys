#ifndef RSYS_UTIL_ROLIST_HH
#define RSYS_UTIL_ROLIST_HH

/**********************************************************************************************/
#include <functional>
#include <type_traits>
#include <QtCore/QList>
#include <RSys/Util/RFT.hh>
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
    _V void     resetObservable0() { }
    _V void     resetObservable() { }
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

    template <typename Fun, typename... Args>
    void notifySafe(Fun fun, Args... args)
    {
      std::vector<RIObserver*> observers;
      for (RODispatcher* d = m_dispatcher; d; d = d->m_nextDispatcher)
        observers.push_back(d->m_observer);
      for (auto it = observers.begin(); it != observers.end(); ++it)
        ((*it)->*fun)(args...);
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

      guarded(&RIObserver::insert0, &RIObserver::insert1, [&]() -> bool
      { return this->m_list.append(x), true; }, i0, i0 + 1);
    }

    template <class Value2>
    ROList<Value2>* cast()
    {
      return reinterpret_cast<ROList<Value2>*>(this);
    }

    _M void clear()
    {
      notifySafe(&RIObserver::resetObservable0);
      m_list.clear();
      notifySafe(&RIObserver::resetObservable);
    }

    template <class List, class... Args>
    _M void clone(List& list, Args... args)
    {
      notifySafe(&RIObserver::resetObservable0);
      for (auto it = list.begin(); it != list.end(); ++it)
        m_list.append(new typename std::remove_pointer<Value>::type(**it, args...));
      notifySafe(&RIObserver::resetObservable);
    }

    _M void deleteAll()
    {
      notifySafe(&RIObserver::resetObservable0);
      for (auto it = begin(); it != end(); ++it)
        delete *it;
      m_list.clear();
      notifySafe(&RIObserver::resetObservable);
    }

    _M void modify(int i)
    {
      notify(&RIObserver::modify0, i, i + 1);
      notify(&RIObserver::modify1, i, i + 1);
    }

    _M bool removeAt(int i)
    {
      return guarded(&RIObserver::remove0, &RIObserver::remove1, [=]() -> bool
      { return this->m_list.removeAt(i), true; }, i, i + 1);
    }

    template <class Lambda>
    _M void removeIf(const Lambda& lambda)
    {
      for (auto it = m_list.begin(); it != m_list.end(); )
      {
        if (lambda(*it))
        {
          int i = it - m_list.begin();
          surrounded(&RIObserver::remove0, &RIObserver::remove1, [&]() -> bool
          { it = m_list.erase(it); return true; }, i, i + 1);
        }
        else
        {
          ++it;
        }
      }
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

    _M void removeOne(const Value& x)
    {
      int index = indexOf(x);
      if (index != -1)
        removeAt(index);
    }

    _M const Value&     at(int x)               const { return m_list.at(x);      }
    _M ConstIterator    begin()                 const { return m_list.begin();    }
    _M ConstIterator    end()                   const { return m_list.end();      }
    _M int              indexOf(const Value& x) const { return m_list.indexOf(x); }
    _M bool             isEmpty()               const { return m_list.empty();    }
    _M int              length()                const { return m_list.length();   }
    _M int              size()                  const { return m_list.size();     }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_ROLIST_HH */
