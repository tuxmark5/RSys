#ifndef RSYS_INTERFACE_RABSTRACT_ITEM_MODEL_HH
#define RSYS_INTERFACE_RABSTRACT_ITEM_MODEL_HH

/**********************************************************************************************/
#include <QtCore/QAbstractItemModel>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                     RAbstractItemModel                                     */
/**********************************************************************************************/

class RAbstractItemModel: public QAbstractItemModel
{
  Q_OBJECT

  public:
    _F class          RColumnObserverAdapter;
    _F class          RRowObserverAdapter;

  protected:
    _M bool           m_editable: 1;

  public:
    _M Vacuum         RAbstractItemModel(QObject* parent = 0);
    _V Vacuum         ~RAbstractItemModel();
    _M bool           editable() const { return m_editable; }
    _M void           setEditable(bool editable);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RABSTRACT_ITEM_MODEL_HH */
