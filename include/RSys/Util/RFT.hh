#ifndef RSYS_UTIL_RFT_HH
#define RSYS_UTIL_RFT_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/**********************************************************************************************/
#define CALL(f, ...)    typename f<__VA_ARGS__>::x
#define LET(x, ...)     typedef __VA_ARGS__ x
#define LET_C(v, ...)   typedef typename __VA_ARGS__ ::x v
#define RET(...)        typedef __VA_ARGS__ x
#define RET_C(...)      typedef typename __VA_ARGS__ ::x x
#define Let(x, ...)     static const x = __VA_ARGS__
#define Let_C(v, ...)   static const v = __VA_ARGS__::x
/********************************************* RS *********************************************/
/*                                             FT                                             */
/**********************************************************************************************/

template <class... Args>
struct Id { };

/**********************************************************************************************/

namespace FT
{
  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <int N, class L>
  struct get;

  template <class X, class... Rest>
  struct get<0, Id<X, Rest...> >
  {
    RET(X);
  };

  template <int N, class X, class... Rest>
  struct get<N, Id<X, Rest...> >
  {
    RET_C(get<N - 1, Id<Rest...> >);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class, class>
  struct prepend;

  template <class X, class... L>
  struct prepend<X, Id<L...> >
  {
    RET(Id<X, L...>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class L0, class L1>
  struct add;

  template <class... L0, class... L1>
  struct add<Id<L0...>, Id<L1...> >
  {
    RET(Id<L0..., L1...>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class LL>
  struct concat;

  template <>
  struct concat<Id<> >
  {
    RET(Id<>);
  };

  template <class L, class... Rest>
  struct concat<Id<L, Rest...> >
  {
    LET_C(Rest1,  concat<Id<Rest...> >);
    LET_C(x,      add<L, Rest1>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <template <class> class, class>
  struct map;

  template <template <class> class F>
  struct map<F, Id<> >
  {
    RET(Id<>);
  };

  template <template <class> class F, class X, class... Rest>
  struct map<F, Id<X, Rest...> >
  {
    LET_C(X1,     F<X>);
    LET_C(REST1,  map<F, Id<Rest...> >);
    RET_C(prepend<X1, REST1>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <template <class> class P, class L>
  struct filter;

  template <template <class> class P>
  struct filter<P, Id<> >
  {
  };

  template <template <class> class P, class X, class... Rest>
  struct filter<P, Id<X, Rest...> >
  {
    template <bool, class d = void>
    struct helper;

    template <class d>
    struct helper<false, d>
    {
      LET_C(x,      filter<P, Id<Rest...> >);
    };

    template <class d>
    struct helper<true, d>
    {
      LET_C(Rest1,  filter<P, Id<Rest...> >);
      LET_C(x,      prepend<X, Rest1>);
    };

    Let_C(int r,  P<X>);
    LET_C(x,      helper<r>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class L>
  struct head;

  template <class X, class... Rest>
  struct head<Id<X, Rest...> >
  {
    RET(X);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class L>
  struct tail;

  template <class X, class... Rest>
  struct tail<Id<X, Rest...> >
  {
    RET(Id<Rest...>);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <class L>
  struct last;

  template <class X>
  struct last<Id<X> >
  {
    RET(X);
  };

  template <class X, class... Rest>
  struct last<Id<X, Rest...> >
  {
    RET_C(last<Id<Rest...> >);
  };

  /* * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * */

  template <int N, class L>
  struct take;

  template <class X, class... L>
  struct take<0, Id<X, L...> >
  {
    RET(Id<>);
  };

  template <int N>
  struct take<N, Id<> >
  {
    RET(Id<>);
  };

  template <int N, class X, class... Rest>
  struct take<N, Id<X, Rest...> >
  {
    LET_C(Rest1,  take<N - 1, Id<Rest...> >);
    LET_C(x,      prepend<X, Rest1>);
  };
}

/**********************************************************************************************/

#endif /* RSYS_UTIL_RFT_HH */
