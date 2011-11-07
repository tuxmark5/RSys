#ifndef RSYS_INTERFACE_RCOLUMN_OBSERVER_ADAPTER_HH
#define RSYS_INTERFACE_RCOLUMN_OBSERVER_ADAPTER_HH

/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
/********************************************* RS *********************************************/
/*                                   RColumnObserverAdapter                                   */
/**********************************************************************************************/

class RColumnObserverAdapter: public RIObserver
{
  private:
    _M QAbstractItemModel*    m_model;

  public:
    _M Vacuum         RColumnObserverAdapter(QAbstractItemModel* model);
    _V Vacuum         ~RColumnObserverAdapter();
    _V bool           insert0(int i0, int i1);
    _V void           insert1(int i0, int i1);
    _V void           modify0(int i0, int i1);
    _V void           modify1(int i0, int i1);
    _V bool           remove0(int i0, int i1);
    _V void           remove1(int i0, int i1);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RCOLUMN_OBSERVER_ADAPTER_HH */
