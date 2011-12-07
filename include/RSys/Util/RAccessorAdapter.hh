#ifndef RSYS_UTIL_RACCESSOR_ADAPTER_HH
#define RSYS_UTIL_RACCESSOR_ADAPTER_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                      RAccessorAdapter                                      */
/**********************************************************************************************/

template <class _Entry>
class RAccessorAdapter
{
  public:
    _T _Entry                                 Entry;

  public:
    _V Vacuum         ~RAccessorAdapter() { }
    _V QVariant       get(const Entry& entry) const                         = 0;
    _V bool           less(const Entry& entry0, const Entry& entry1) const  = 0;
    _V void           set(Entry& entry, const QVariant& variant)            = 0;
};

/**********************************************************************************************/

template <class _Accessor>
class RAccessorAdapterI: public RAccessorAdapter<typename _Accessor::Entry>
{
  public:
    _T _Accessor                              Accessor;
    _T typename _Accessor::Entry              Entry;
    _T typename _Accessor::Value              Value;

  public:
    _M Accessor       m_accessor;

  public:
    template <class... _Args>
    _M Vacuum         RAccessorAdapterI(_Args... args):
      m_accessor(std::forward<_Args>(args)...) { }

    _V Vacuum         ~RAccessorAdapterI()
    { }

    _M QVariant       get(const Entry& entry) const
    { return QVariant::fromValue(m_accessor.get(entry)); }

    _V bool           less(const Entry& entry0, const Entry& entry1) const
    { return m_accessor.get(entry0) < m_accessor.get(entry1); }

    _M void           set(Entry& entry, const QVariant& variant)
    { m_accessor.set(entry, qvariant_cast<Value>(variant)); }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RACCESSOR_ADAPTER_HH */
