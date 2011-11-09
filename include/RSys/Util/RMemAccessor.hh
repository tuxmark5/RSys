#ifndef RSYS_UTIL_RMEM_ACCESSOR_HH
#define RSYS_UTIL_RMEM_ACCESSOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RMemAccessor                                        */
/**********************************************************************************************/

/*
 * Member static accessor
 */

template <class _Entry,
          class _Value,
          class _Getter, _Getter Getter,
          class _Setter, _Setter Setter>
class RMemAccessor
{
  public:
    _T _Entry                                 Entry;
    _T _Value                                 Value;

  public:
    _M Value          get(const Entry& entry) const
    { return ((&entry)->*Getter)(); }

    _M void           set(Entry& entry, const Value& value)
    { ((&entry)->*Setter)(value); }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RMEM_ACCESSOR_HH */
