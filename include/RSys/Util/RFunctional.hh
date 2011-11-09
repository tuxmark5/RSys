#ifndef RSYS_UTIL_RFUNCTIONAL_HH
#define RSYS_UTIL_RFUNCTIONAL_HH

/**********************************************************************************************/
#include <functional>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RFunComp                                          */
/**********************************************************************************************/

template <class F0, class F1>
struct RFunComp
{
  F0 f0;
  F1 f1;

  RFunComp(F0&& f0, F1&& f1):
    f0(std::forward<F0>(f0)), f1(std::forward<F1>(f1)) { }

  template <typename... Args>
  auto operator ()(Args... args) -> decltype(f0(f1(args...)))
  {
    return f0(f1(std::forward<Args>(args)...));
  }
};

/********************************************* RS *********************************************/
/*                                          RFunctor                                          */
/**********************************************************************************************/

template <class F>
struct RFunctor
{
  _M F f;
  _M RFunctor(F f): f(f) { }
     template <typename... Args>
  _M auto operator ()(Args... args) -> decltype(f(args...))
    { return f(args...); }
};

/********************************************* RS *********************************************/
/*                                         is_functor                                         */
/**********************************************************************************************/

template <class Class>
struct is_functor: std::false_type { };

/*template <class Class>
struct is_functor: std::is_function<typename Class::operator()>
{ };*/

template <class Signature>
struct is_functor<std::_Mem_fn<Signature> >: std::true_type { };

template <class InnerFunctor>
struct is_functor<RFunctor<InnerFunctor> >: std::true_type { };

template <class F0, class F1>
struct is_functor<RFunComp<F0, F1> >: std::true_type { };

/********************************************* RS *********************************************/
/*                                        composition                                         */
/**********************************************************************************************/

template <typename Functor>
inline RFunctor<Functor>
f(Functor&& f)
{
  return RFunctor<Functor>(std::forward<Functor>(f));
}

template <typename Result, typename Class>
inline std::_Mem_fn<Result Class::*>
f(Result Class::* member)
{
  return std::_Mem_fn<Result Class::*>(member);
}

template <class F0, class F1>
typename std::enable_if<is_functor<F0>::value, RFunComp<F0, F1> >::type
inline operator *(F0&& f0, F1&& f1)
{ return RFunComp<F0, F1>(std::forward<F0>(f0), std::forward<F1>(f1)); }

/**********************************************************************************************/

#endif /* RSYS_UTIL_RFUNCTIONAL_HH */
