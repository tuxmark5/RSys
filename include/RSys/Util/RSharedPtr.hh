#ifndef RSYS_UTIL_RSHARED_PTR_HH
#define RSYS_UTIL_RSHARED_PTR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                         RSharedPtr                                         */
/**********************************************************************************************/

template <class Value>
struct RStandardDeleter
{
  static void f(Value* value)
  {
    delete value;
  }
};

/**********************************************************************************************/

template <class _Value, class _Deleter = RStandardDeleter<_Value> >
class RSharedPtr
{
  public:
    _T _Value                       Value;
    _T _Deleter                     Deleter;
    _T RSharedPtr<Value, Deleter>   Self;

  private:
    _M Value*         m_value;

  public:
    _M Vacuum         RSharedPtr():
      m_value(0) { }

    _M Vacuum         RSharedPtr(Value* value):
      m_value(value) { retain(); }

    _M Vacuum         RSharedPtr(const Self& ptr):
      m_value(ptr.m_value) { retain(); }

    _M Vacuum         RSharedPtr(Self&& ptr):
      m_value(ptr.m_value) { ptr.m_value = 0; }

    _M Vacuum         ~RSharedPtr()
    { release(); }

    _M Value*         get() const
    { return m_value; }

    _M void           release()
    { if (m_value) if (m_value->release() <= 0) { Deleter::f(m_value); m_value = 0; } }

    _M void           retain() const
    { if (m_value) m_value->retain(); }

    _M Value*         operator -> () const
    { return m_value; }

    _M Value&         operator * () const
    { return *m_value; }

    _M Self&          operator = (Value* value)
    { if (value) value->retain(); release(); m_value = value; return *this; }

    _M Self&          operator = (const Self& ptr)
    { ptr.retain(); release(); m_value = ptr.m_value; return *this; }

    _M Vacuum         operator Value* ()
    { return m_value; }
};

/**********************************************************************************************/

namespace std
{
  template <class Value>
  struct remove_pointer<RSharedPtr<Value> >
  { typedef Value type; };
}

/**********************************************************************************************/

#endif /* RSYS_UTIL_RSHARED_PTR_HH */
