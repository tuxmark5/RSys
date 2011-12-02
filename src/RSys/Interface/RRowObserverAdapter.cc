#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RModel2D.hh>
#include <RSys/Interface/RRowObserverAdapter.hh>

/********************************************* RS *********************************************/
/*                                     RRowObserverAdapter                                    */
/**********************************************************************************************/

Vacuum RRowObserverAdapter :: RRowObserverAdapter(RAbstractItemModel* model):
  m_model(model)
{
}

/**********************************************************************************************/

Vacuum RRowObserverAdapter :: ~RRowObserverAdapter()
{
}

/**********************************************************************************************/

bool RRowObserverAdapter :: insert0(int i0, int i1)
{
  i0 += m_model->editable();
  i1 += m_model->editable();
  m_model->beginInsertRows(QModelIndex(), i0, i1 - 1);
  return true;
}

/**********************************************************************************************/

void RRowObserverAdapter :: insert1(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
  m_model->endInsertRows();
}

/**********************************************************************************************/

void RRowObserverAdapter :: modify0(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
}

/**********************************************************************************************/

void RRowObserverAdapter :: modify1(int i0, int i1)
{
  Q_UNUSED(i1);

  /**/ if (RModel1D* model = qobject_cast<RModel1D*>(m_model))
    model->notifyRowChanged(i0);
  else if (RModel2D* model = qobject_cast<RModel2D*>(m_model))
    emit model->headerDataChanged(Qt::Vertical, i0, i1 - 1);
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
  Q_UNUSED(i0);
  Q_UNUSED(i1);
  m_model->endRemoveRows();
}

/**********************************************************************************************/

void RRowObserverAdapter :: resetObservable()
{
  m_model->reset();
}

/**********************************************************************************************/
