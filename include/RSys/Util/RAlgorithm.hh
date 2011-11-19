#ifndef RSYS_UTIL_RALGORITHM_HH
#define RSYS_UTIL_RALGORITHM_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
/********************************************* RS *********************************************/
/*                                         RAlgorithm                                         */
/**********************************************************************************************/

template <class Value, bool>
struct RBuddy;

template <class Value>
struct RBuddy<Value, false>
{
  static Value f(const Value& x)
  { return x; }
};

template <class Value>
struct RBuddy<Value, true>
{
  static Value f(const Value& x)
  { return x->buddy(); }
};

/**********************************************************************************************/

template <class Value>
Value r_buddy(Value buddy)
{
  constexpr bool isUnit = std::is_base_of<RUnit, typename std::remove_pointer<Value>::type>::value;
  return RBuddy<Value, isUnit>::f(buddy);
}

/**********************************************************************************************/

template <class Map0, class Map1>
void r_cloneMap(Map0& map0, const Map1& map1)
{
  map0.clear();
  for (auto it = map1.begin(); it != map1.end(); ++it)
    map0.insert(r_buddy(it.key()), r_buddy(it.value()));
}

/**********************************************************************************************/

#endif /* RSYS_UTIL_RALGORITHM_HH */
