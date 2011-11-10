#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Interface/RRowObserverAdapter.hh>

/********************************************* RS *********************************************/
/*                                     RRowObserverAdapter                                    */
/**********************************************************************************************/

Vacuum RRowObserverAdapter :: RRowObserverAdapter(RAbstractItemModel* model):
  m_model(model), m_modifier(0)
{
}

/**********************************************************************************************/

Vacuum RRowObserverAdapter :: ~RRowObserverAdapter()
{
}

/**********************************************************************************************/

bool RRowObserverAdapter :: insert0(int i0, int i1)
{
  i0 += m_modifier;
  i1 += m_modifier;
  m_model->beginInsertRows(QModelIndex(), i0, i1 - 1);
  return true;
}

/**********************************************************************************************/

void RRowObserverAdapter :: insert1(int i0, int i1)
{
  m_model->endInsertRows();
}

/**********************************************************************************************/

void RRowObserverAdapter :: modify0(int i0, int i1)
{

}

/**********************************************************************************************/

void RRowObserverAdapter :: modify1(int i0, int i1)
{
}

/**********************************************************************************************/

bool RRowObserverAdapter :: remove0(int i0, int i1)
{
  m_model->beginRemoveRows(QModelIndex(), i0, i1 - 1);
  return true;
}

/**********************************************************************************************/

void RRowObserverAdapter :: remove1(int i0, int i1)
{
  m_model->endRemoveRows();
}

/**********************************************************************************************/

void RRowObserverAdapter :: setModifier(int modifier)
{
  m_modifier = modifier;
}

/**********************************************************************************************/
