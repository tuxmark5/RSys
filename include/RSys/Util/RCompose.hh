#ifndef RSYS_UTIL_RCOMPOSE_HH
#define RSYS_UTIL_RCOMPOSE_HH

/**********************************************************************************************/
#include <RSys/Util/RFT.hh>
#include <tuple>
/********************************************* RS *********************************************/
/*                                          RCompose                                          */
/**********************************************************************************************/

template
  < int Index
  , class Entities
  >
struct RCompose0;


/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

template
  < int Index
  , class... E0
  >
struct RCompose0
  < Index
  , Id<Id<E0...>, Id<>
  >
{
  template <class Value, class Keys>
  struct Gen;

  template <class Value, class... Keys>
  struct Gen<Value, Id<Keys...> >: Next::x
  {
    Value get(Keys... keys)
    {
      return Next::x::get(std::get<Index>(entities).get(keys...));
    }
  };

  RET(Gen<typename E1::Value, typename E1::Keys>);
};

/* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * */

template
  < int Index
  , class... E0, class E1, class... E2
  >
struct RCompose0
  < Index
  , Id<Id<E0...>, Id<E1, E2...>
  >
{
  LET(Next,   RCompose0
      < Index + 1
      , Id<Id<E0..., E1>, Id<E2...> >
      > );

  template <class Value, class Keys>
  struct Gen;

  template <class Value, class... Keys>
  struct Gen<Value, Id<Keys...> >: Next::x
  {
    Value get(Keys... keys)
    {
      return Next::x::get(std::get<Index>(entities).get(keys...));
    }
  };

  RET(Gen<typename E1::Value, typename E1::Keys>);
};

/**********************************************************************************************/

template <class... _Entities>
struct RCompose: RCompose0<0, Id<Id<>, Id<_Entities...> > >::x
{
  LET(Entities,     Id<_Entities...>);
  LET(Keys,         typename FT::head<Entities>::x::Keys);
  LET(Value,        typename FT::last<Entities>::x::Value);


  /*RCompose(_Entities&... entities):
    Base(EntityTuple(entities...)) { }*/
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RCOMPOSE_HH */
