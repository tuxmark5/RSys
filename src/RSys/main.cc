#include <QtCore/QLocale>
#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Tests/RTests.hh>

#include <functional>
#include <tuple>

/*
#if 0

template <class Args1, class Args2>
struct Cat2;

template <class... Args1, class... Args2>
struct Cat2<Args1..., Args2...>
{
  template <template <class...> class Template>
  struct Apply
  {
    typedef Template<Args1..., Args2...> Type;
  };
};

template <class... Args>
struct Id
{
  template <template <class...> class Template>
  struct Apply
  {
    typedef Template<Args...> Type;
  };
};

#define CAT_PACKS(a, b)





template <class _List, class _Entry>
struct List1D
{
  _C int        DIMENSION = 1;
  _T int        Key;
  _T int        Value;
};

typedef List1D<int, int> L;


template <class... _Entities>
struct Cat;

template <class _Entity>
struct Cat<_Entity>
{
  _C int                    DIMENSION = _Entity::DIMENSION;
  _C _Entity::Index         Index;
};

template <class Head, class... Tail>
struct Cat<Head, Tail...>
{
  _C int                    DIMENSION = Head::DIMENSION + Cat<Tail>::DIMENSION;
  _C Cat2<_Entity::Index    Index;
};



// int get(i

//  V get(int, int, char);
//          List2   List1
//          E1       E2
//  V getter(E1, E2);


template <class... _Entities>
struct Cat:
{

};




template <class Value, class... Args>
struct AccessorGen
{
  Value get()
};


template <class... _Entities>
struct Entity;

template <class _Entity>
struct Cat<_Entity>
{
  _C int                    DIMENSION = _Entity::DIMENSION;
  _C _Entity::Index         Index;
};




          #include <tuple>

          template <typename... Args>
          struct variadic_typedef
          {
              // this single type represents a collection of types,
              // as the template arguments it took to define it
          };

          template <typename... Args>
          struct convert_in_tuple
          {
              // base case, nothing special,
              // just use the arguments directly
              // however they need to be used
              typedef std::tuple<Args...> type;
          };

          template <typename... Args>
          struct convert_in_tuple<variadic_typedef<Args...>>
          {
              // expand the variadic_typedef back into
              // its arguments, via specialization
              // (doesn't rely on functionality to be provided
              // by the variadic_typedef struct itself, generic)
              typedef typename convert_in_tuple<Args...>::type type;
          };

          typedef variadic_typedef<int, float> myTypes;
          typedef convert_in_tuple<myTypes>::type int_float_tuple;

          int main()
          {}





template <typename... _Types>
struct Id
{
  typedef _Types Type;
};

typedef Entity<L, L>    E2;
typedef Entity<E2, E2>  E4;



class <class T, int N>
struct Dup
{
  typedef Id<typename Dup<T, N - 1>::Type..., T>::Type Type;
};
#endif */

template <class... Args>
struct Id { };

typedef Id<int, int>          A1;
typedef Id<char*>             A2;
typedef Id<char, int, char>   A3;
typedef Id<int, int>          A4;



struct S1
{
  typedef Id<int, int>    Keys;
  typedef char            Value;
};

struct S2
{
  typedef Id<char*>       Keys;
  typedef char            Value;
};

struct S3
{
  typedef Id<char, int, char> Keys;
  typedef void*               Value;
};


struct S4
{
  typedef Id<void*, char>     Keys;
  typedef int*                Value;
};





#define CALL(f, ...)  typename f<__VA_ARGS__>::x
#define LET(x, ...)   typedef __VA_ARGS__ x
#define LET_C(v, ...) typedef typename __VA_ARGS__ ::x v
#define RET(...)      typedef __VA_ARGS__ x
#define RET_C(...)    typedef typename __VA_ARGS__ ::x x
#define Let(x, ...)   static const x = __VA_ARGS__
#define Let_C(v, ...) static const v = __VA_ARGS__::x

// RET_c, RET_C - const, type
// LET_c, LET_C

/*

  flatten :: [x, y, z] x ++ y ++ z

  */

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

  template <template <class> class F, class X>
  struct map<F, Id<X> >
  {
    RET_C(F<X>);
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

  template <int N, class L>
  class take;

  template <class... L>
  class take<0, Id<L...> >
  {
    RET(Id<>);
  };

  template <int N>
  class take<N, Id<> >
  {
    RET(Id<>);
  };

  template <int N, class X, class... Rest>
  class take<N, Id<X, Rest...> >
  {
    LET_C(Rest1,  take<N - 1, Id<Rest...> >);
    LET_C(x,      prepend<X, Rest1>);
  };
}



// Predicates!


template <class, class, class>
struct Fun;

template <class... A, class... B, class... C>
struct Fun< Id<A...>, Id<B...>, Id<C...>  >
{
  static void call(A... a, B... b, C... c)
  {
  }
};

struct Zimbabwe: Fun<A1, A2, A3>
{

};

template <class>
struct GEN;

template <class... L>
struct GEN<Id<L...> >
{
  static void call(L... l)
  {

  }
};

/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

typedef Id<int, int, char*, char*> Argz;
typedef Id<Argz, Argz, Argz>        Argz25;
typedef FT::concat<Argz25>::x   Argz2;
///typedef FT::take<4, Argz2>::x   Argz4;

int main(int argc, char** argv)
{
  run_all_tests(argc, argv);
  return 0;
//  GEN<Argz4 >::call(2, 2, 3, 3);


  //Zimbabwe::call(2, 2, 3);

//QLocale       locale(QLocale::Lithuanian, QLocale::Lithuania);
//QLocale::setDefault(locale);
//QApplication  app(argc, argv);
//RMainWindow   mainWnd;

//QApplication  app(argc, argv);
//RMainWindow   mainWnd;

//mainWnd.show();
//return app.exec();
}

/**********************************************************************************************/
