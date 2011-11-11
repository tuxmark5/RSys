#ifndef RSYS_UTIL_RJOIN_HH
#define RSYS_UTIL_RJOIN_HH

/**********************************************************************************************/
#include <RSys/Util/RFT.hh>
#include <tuple>
/********************************************* RS *********************************************/
/*                                           RJoin                                            */
/**********************************************************************************************/

template <class Entity>
struct GetKeys
{
  RET(typename Entity::Keys);
};

template <class Entity>
struct GetValue
{
  RET(typename Entity::Value);
};

/**********************************************************************************************/

template
  < class Value, int Index
  , class Entities
  >
struct RJoin0;

/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

template
  < class Value, int Index
  , class... E0
  >
struct RJoin0
  < Value, Index
  , Id<Id<E0...>, Id<> >
  >
{
  template <class V0>
  struct Gen;

  template <class... V0>
  struct Gen<Id<V0...> >
  {
    LET(EntityTuple,  std::tuple<E0&...>);
    LET(Getter,       std::function<Value (V0...)>);
    LET(Setter,       std::function<void  (V0..., const Value&)>);

    EntityTuple       entities;
    Getter            getter;
    Setter            setter;

    Gen(EntityTuple&& entities):
      entities(std::forward<EntityTuple>(entities)) { }

    Value get(V0&&... v0)
    {
      return getter(std::forward<V0>(v0)...);
    }

    void set(V0&&... v0, const Value& value)
    {
      setter(std::forward<V0>(v0)..., value);
    }
  };

  LET_C(_V0, FT::map<GetValue, Id<E0...> >);
  RET(Gen<_V0>);
};

/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

template
  < class _Value, int Index
  , class... E0, class E1, class... E2
  >
struct RJoin0
  < _Value, Index
  , Id<Id<E0...>, Id<E1, E2...> >
  >
{
  LET(Value,  _Value);
  LET(Next,   RJoin0
      < Value, Index + 1
      , Id<Id<E0..., E1>, Id<E2...> >
      > );

  template <class V0, class K1, class K2>
  struct Gen;

  template <class... V0, class... K1, class... K2>
  struct Gen<Id<V0...>, Id<K1...>, Id<K2...> >: Next::x
  {
    LET(EntityTuple, typename Next::x::EntityTuple);

    Gen(EntityTuple&& entities):
      Next::x(std::forward<EntityTuple>(entities)) { }

    Value get(V0&&... v0, K1&&... k1, K2&&... k2)
    {
      return Next::x::get
        ( std::forward<V0>(v0)...
        , std::get<Index>(Next::x::entities).get(std::forward<K1>(k1)...)
        , std::forward<K2>(k2)...
        );
    }

    void set(V0&&... v0, K1&&... k1, K2&&... k2, const Value& value)
    {
      Next::x::set
        ( std::forward<V0>(v0)...
        , std::get<Index>(Next::x::entities).get(std::forward<K1>(k1)...)
        , std::forward<K2>(k2)...
        , value
        );
    }
  };

  LET_C(_V0,  FT::map<GetValue, Id<E0...> >);
  LET_C(_K1,  GetKeys<E1>);
  LET_C(K2L,  FT::map<GetKeys, Id<E2...> >);
  LET_C(_K2,  FT::concat<K2L>);
  RET(Gen<_V0, _K1, _K2>);
};

/**********************************************************************************************/

template <class _Value, class... _Entities>
struct RJoin: RJoin0<_Value, 0, Id<Id<>, Id<_Entities...> > >::x
{
  LET(Value,        _Value);
  LET(Entities,     Id<_Entities...>);
  LET_C(Base,       RJoin0<_Value, 0, Id<Id<>, Entities > >);
  LET(Self,         RJoin<_Value, _Entities...>);

  LET_C(KeysL,      FT::map<GetKeys, Entities>);
  LET_C(Keys,       FT::concat<KeysL>);

  LET(EntityTuple,  decltype(Base::entities));
  LET(Getter,       decltype(Base::getter));
  LET(Setter,       decltype(Base::setter));

  RJoin(_Entities&... entities):
    Base(EntityTuple(entities...)) { }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RJOIN_HH */
