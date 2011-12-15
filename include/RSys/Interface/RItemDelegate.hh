#ifndef RSYS_INTERFACE_RITEM_DELEGATE_HH
#define RSYS_INTERFACE_RITEM_DELEGATE_HH

/**********************************************************************************************/
#include <QtGui/QItemDelegate>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                       RItemDelegate                                        */
/**********************************************************************************************/

class RItemDelegate: public QItemDelegate
{
  Q_OBJECT

  public:
    _M Vacuum         RItemDelegate(QObject* parent = 0);
    _V Vacuum         ~RItemDelegate();

  public:
    _V QWidget*       createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const;
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RITEM_DELEGATE_HH */
