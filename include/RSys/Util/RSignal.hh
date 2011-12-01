#ifndef RSYS_UTIL_RSIGNAL_HH
#define RSYS_UTIL_RSIGNAL_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/**********************************************************************************************/
#define R_SIGNAL(ret, name, ...)  struct: Sig<ret (__VA_ARGS__)> { } name
#define _G(ret, name, ...)        static R_SIGNAL(ret, name, __VA_ARGS__)
/********************************************* RS *********************************************/
/*                                          RSignal                                           */
/**********************************************************************************************/

template <class Signature>
struct Sig;

template <class Result, class... Args>
struct Sig<Result (Args...)>
{
  typedef std::function<Result (Args...)>   Function;
  typedef Result                            (Signature)(Args...);
};

/**********************************************************************************************/

template <class Signature>
struct Invocation;

template <class Result, class... Args>
struct Invocation<Result (Args...)>
{
  _T Invocation<Result (Args...)>     Self;
  _T const std::type_info*            Key;
  _T std::function<void ()>           Slot0;
  _T std::function<Result (Args...)>  Slot;
  _T QMultiHash<Key, Slot0>           Connections0;
  _T QMultiHash<Key, Slot>            Connections;

  _M Connections&     m_connections;
  _M Key              m_signature;
  _M bool             m_block;

  _M Vacuum           Invocation(Connections0& connections, Key signature, bool block):
    m_connections(reinterpret_cast<Connections&>(connections)),
    m_signature(signature), m_block(block) { }

  _M void             operator ()(Args... args)
  {
    if (!m_block)
    {
      auto it = m_connections.find(m_signature);
      for (; it.key() == m_signature && it != m_connections.end(); ++it)
        (*it)(args...);
    }
  }

  _M Self&            operator <<(Slot&& slot)
  {
    m_connections.insert(m_signature, std::forward<Slot>(slot));
    return* this;
  }
};

/**********************************************************************************************/

struct RSignal
{
  public:
    _T const std::type_info*      Key;
    _T std::function<void ()>     Slot0;
    _T QMultiHash<Key, Slot0>     Connections;

  private:
    _M Connections    m_connections;
    _M bool           m_block;

  public:
    _M Vacuum         RSignal():
      m_block(false) { }

    _M void           disconnectAll()
    { m_connections.clear(); }

    template <class Signal>
    _M auto           operator[](Signal) -> Invocation<typename Signal::Signature>
    { return Invocation<typename Signal::Signature>(m_connections, &typeid(Signal), m_block); }

    template <class Lambda>
    _M void           withBlock(const Lambda& lambda)
    { m_block = true; lambda(); m_block = false; }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RSIGNAL_HH */
