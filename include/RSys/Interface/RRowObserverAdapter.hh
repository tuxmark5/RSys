#ifndef RSYS_INTERFACE_RROW_OBSERVER_ADAPTER_HH
#define RSYS_INTERFACE_RROW_OBSERVER_ADAPTER_HH

/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
/********************************************* RS *********************************************/
/*                                     RRowObserverAdapter                                    */
/**********************************************************************************************/

class RRowObserverAdapter: public RIObserver
{
  private:
    _M RAbstractItemModel*    m_model;
    _M int                    m_modifier;

  public:
    _M Vacuum         RRowObserverAdapter(RAbstractItemModel* model);
    _V Vacuum         ~RRowObserverAdapter();
    _V bool           insert0(int i0, int i1);
    _V void           insert1(int i0, int i1);
    _V void           modify0(int i0, int i1);
    _V void           modify1(int i0, int i1);
    _V bool           remove0(int i0, int i1);
    _V void           remove1(int i0, int i1);
    _V void           resetObservable();
    _M void           setModifier(int modifier);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RROW_OBSERVER_ADAPTER_HH */
