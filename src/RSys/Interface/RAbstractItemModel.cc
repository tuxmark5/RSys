#include <RSys/Interface/RAbstractItemModel.hh>

/********************************************* RS *********************************************/
/*                                     RAbstractItemModel                                     */
/**********************************************************************************************/

Vacuum RAbstractItemModel :: RAbstractItemModel(QObject* parent):
  QAbstractItemModel(parent),
  m_editable(true)
{
}

/**********************************************************************************************/

Vacuum RAbstractItemModel :: ~RAbstractItemModel()
{
}

/**********************************************************************************************/

void RAbstractItemModel :: setEditable(bool editable)
{
  emit layoutAboutToBeChanged();
  m_editable = editable;
  emit layoutChanged();
}

/**********************************************************************************************/
