#ifndef RSYS_UTIL_RFUN_ACCESSOR_HH
#define RSYS_UTIL_RFUN_ACCESSOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RFunAccessor                                        */
/**********************************************************************************************/

/*
 * Functional accessor
 */

template <class _Entry, class _Value>
class RFunAccessor
{
  public:
    _T _Entry                                     Entry;
    _T _Value                                     Value;
    _T std::function<Value (const Entry&)>        Getter;
    _T std::function<void (Entry&, const Value&)> Setter;
    _T RFunAccessor<Entry, Value>                 Self;

  private:
    _M Getter         m_getter;
    _M Setter         m_setter;

  public:
    _M Vacuum         RFunAccessor()
      { }

    _M Vacuum         RFunAccessor(Getter getter, Setter setter = Setter()):
      m_getter(std::move(getter)), m_setter(std::move(setter)) { }

    _M Value          get(const Entry& entry) const
    { return m_getter(entry); }

    _M void           set(Entry& entry, const Value& value)
    { if (m_setter) m_setter(entry, value); }

    _M Self&          operator >> (Getter getter)
    { m_getter = std::move(getter); return *this; }

    _M Self&          operator << (Setter setter)
    { m_setter = std::move(setter); return *this; }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RFUN_ACCESSOR_HH */
