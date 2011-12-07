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

/********************************************* RS *********************************************/
/*                                        RConnection                                         */
/**********************************************************************************************/

class RConnection
{
  public:
    _F class          RSignal;

  private:
    _M RSignal*       m_signal;
    _M int            m_identifier;

  public:
    _M Vacuum         RConnection(RSignal* signal, int identifier);
    _M void           disconnect();
};

/********************************************* RS *********************************************/
/*                                          RSignal                                           */
/**********************************************************************************************/

struct RSignal
{
  public:
    _F class          RInvocation;

  public:
    _T const std::type_info*                      Key;
    _T std::tuple<int, std::function<void ()> >   Slot0;
    _T QMultiHash<Key, Slot0>                     Connections;

  private:
    _M Connections    m_connections;
    _M bool           m_block;

  public:
    _M Vacuum         RSignal():
      m_block(false) { }

    _M const Connections& connections()
    { return m_connections; }

    _M void           disconnect(int connId);
    _M void           disconnectAll();

    template <class Signal>
    _M auto           operator[](Signal) -> Invocation<typename Signal::Signature>
    { return Invocation<typename Signal::Signature>(this, &typeid(Signal), m_block); }

    template <class Lambda>
    _M void           withBlock(const Lambda& lambda)
    { m_block = true; lambda(); m_block = false; }
};

/**********************************************************************************************/

struct RInvocation
{
  protected: static auto connections(RSignal* signal) -> RSignal::Connections&
  { return signal->m_connections; }
};

/**********************************************************************************************/

template <class Result, class... Args>
struct Invocation<Result (Args...)>: public RInvocation
{
  _T Invocation<Result (Args...)>                   Self;
  _T const std::type_info*                          Key;
  _T std::function<Result (Args...)>                Handler;
  _T std::tuple<int, std::function<void ()> >       Slot0;
  _T std::tuple<int, Handler>                       Slot;
  _T QMultiHash<Key, Slot0>                         Connections0;
  _T QMultiHash<Key, Slot>                          Connections;

  _M RSignal*         m_signal;
  _M Key              m_signature;
  _M bool             m_block;

  _M Vacuum           Invocation(RSignal* signal, Key signature, bool block):
    m_signal(signal), m_signature(signature), m_block(block) { }

  _M Connections&     connections()
  { return reinterpret_cast<Connections&>(RInvocation::connections(m_signal)); }

  _M void             operator ()(Args... args)
  {
    if (!m_block)
    {
      auto it   = connections().find(m_signature);
      auto end  = connections().end();
      for (; it.key() == m_signature && it != end; ++it)
        std::get<1>(*it)(args...);
    }
  }

  _M RConnection      operator <<(Handler&& handler)
  {
    int index = rand();
    connections().insert(m_signature, Slot(index, std::forward<Handler>(handler)));
    return RConnection(m_signal, index);
  }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RSIGNAL_HH */
