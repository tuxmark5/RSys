#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Interface/RColumnObserverAdapter.hh>

/********************************************* RS *********************************************/
/*                                   RColumnObserverAdapter                                   */
/**********************************************************************************************/

Vacuum RColumnObserverAdapter :: RColumnObserverAdapter(RAbstractItemModel* model):
  m_model(model)
{
}

/**********************************************************************************************/

Vacuum RColumnObserverAdapter :: ~RColumnObserverAdapter()
{
}

/**********************************************************************************************/

bool RColumnObserverAdapter :: insert0(int i0, int i1)
{
  m_model->beginInsertColumns(QModelIndex(), i0, i1 - 1);
  return true;
}

/**********************************************************************************************/

void RColumnObserverAdapter :: insert1(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
  m_model->endInsertColumns();
}

/**********************************************************************************************/

void RColumnObserverAdapter :: modify0(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
}

/**********************************************************************************************/

void RColumnObserverAdapter :: modify1(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
}

/**********************************************************************************************/

bool RColumnObserverAdapter :: remove0(int i0, int i1)
{
  m_model->beginRemoveColumns(QModelIndex(), i0, i1 - 1);
  return true;
}

/**********************************************************************************************/

void RColumnObserverAdapter :: remove1(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
  m_model->endRemoveColumns();
}

/**********************************************************************************************/

void RColumnObserverAdapter :: resetObservable()
{
  m_model->reset();
}

/**********************************************************************************************/
