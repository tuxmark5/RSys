#include <RSys/Interface/RItemDelegate.hh>

/********************************************* RS *********************************************/
/*                                       RItemDelegate                                        */
/**********************************************************************************************/

Vacuum RItemDelegate :: RItemDelegate(QObject* parent):
  QItemDelegate(parent)
{
}

/**********************************************************************************************/

Vacuum RItemDelegate :: ~RItemDelegate()
{
}

/**********************************************************************************************/

QWidget* RItemDelegate :: createEditor(QWidget* parent, const QStyleOptionViewItem& option,
  const QModelIndex& index) const
{
  return QItemDelegate::createEditor(parent, option, index);
}

/**********************************************************************************************/
