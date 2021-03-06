#ifndef RSYS_UTIL_RDYN_ACCESSOR_HH
#define RSYS_UTIL_RDYN_ACCESSOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RDynAccessor                                        */
/**********************************************************************************************/

/*
 * Dynamic accessor
 */

class <
class RDynAccessor
{
  public:
    _M Vacuum         RDynAccessor();
    _V Vacuum         ~RDynAccessor();
    _M QVariant       get(const Entry& entry) const
};

/**********************************************************************************************/


template <class _Entry, class _Value>
class RFunAccessor
{
  public:
    _T _Entry                                 Entry;
    _T _Value                                 Value;
    _T std::function<Value(const Entry&)>     Getter;
    _T std::function<void(Entry&, Value)>     Setter;

  private:
    _M Getter         m_getter;
    _M Setter         m_setter;

  public:
    _M Vacuum         RAccessor(Getter getter, Setter setter = Setter()):
      m_getter(std::move(getter)), m_setter(std::move(setter)) { }

    _M Value          get(const Entry& entry) const
    { return m_getter(entry); }

    _M void           set(Entry& entry, const Value& value)
    { m_setter(entry, value); }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RDYN_ACCESSOR_HH */
