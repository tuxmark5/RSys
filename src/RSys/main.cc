#include <QtCore/QLocale>
#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>

#include <RSys/Util/RFT.hh>
#include <functional>
#include <tuple>



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







// RET_c, RET_C - const, type
// LET_c, LET_C



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




template <class>
struct GetterGen;

template <class... Pre, class... Curr, class... Post>
struct GetterGen<Id<Id<Pre...>, Id<Curr...>, Id<Post...> > >
{
  void get(Pre&&... pre, Cur&&... curr, Post&&... post)
  {

  }

  static void call(A... a, B... b, C... c)
  {
  }
};

template <int, class>
struct AccessorGen;

template <int I, class Entities>
struct AccessorGen
{
  LET_C(Pre)
};



template <class... Entities>
struct RCompose
{
  _T Id<Entities...>      Entities;
  //_T
};

/*

  break  2
  take 2

  drop 2



  split :: [x] -> Int -> [[x], [y], [z]]
  split l pivot = split





  */


/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

typedef Id<int, int, char*, char*> Argz;
typedef Id<Argz, Argz, Argz>        Argz25;
typedef FT::concat<Argz25>::x   Argz2;
typedef FT::take<4, Argz2>::x   Argz4;

int main(int argc, char** argv)
{
//  GEN<Argz4 >::call(2, 2, 3, 3);


  //Zimbabwe::call(2, 2, 3);

  QLocale       locale(QLocale::Lithuanian, QLocale::Lithuania);
  QLocale::setDefault(locale);
  QApplication  app(argc, argv);
  RMainWindow   mainWnd;

  mainWnd.show();
  return app.exec();
}

/**********************************************************************************************/
