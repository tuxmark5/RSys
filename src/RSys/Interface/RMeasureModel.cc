#include <QtCore/QSize>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Interface/RMeasureModel.hh>

/********************************************* RS *********************************************/
/*                                       RMeasureModel                                        */
/**********************************************************************************************/

Vacuum RMeasureModel :: RMeasureModel(QObject* parent):
  QAbstractItemModel(parent)
{
  //m_measures.append();
}

/**********************************************************************************************/

Vacuum RMeasureModel :: ~RMeasureModel()
{
}

/**********************************************************************************************/

int RMeasureModel :: columnCount(const QModelIndex& parent) const
{
  return 2;
}

/**********************************************************************************************/

QVariant RMeasureModel :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(),                  QVariant());
  R_GUARD(index.row() < m_measures.size(),  QVariant());

  switch (role)
  {
    case Qt::DisplayRole:   break;
    case Qt::EditRole:      break;
    default:                return QVariant();
  }

  if (RMeasure* measure = m_measures.at(index.row()))
  {
    switch (index.column())
    {
      case 0: return measure->identifier();
      case 1: return measure->name();
    }
  }

  return QVariant();
}

/**********************************************************************************************/

Qt::ItemFlags RMeasureModel :: flags(const QModelIndex& index) const
{
  R_GUARD(index.isValid(), 0);

  return Qt::ItemIsSelectable
       | Qt::ItemIsEditable
       | Qt::ItemIsEnabled;
}

/**********************************************************************************************/

QVariant RMeasureModel :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(orientation == Qt::Horizontal,    QVariant());
  R_GUARD(role        == Qt::DisplayRole,   QVariant());

  switch (section)
  {
    case 0: return QString::fromUtf8("Priemonė");
    case 1: return QString::fromUtf8("Aprašymas");
  }
  return QVariant();
}

/**********************************************************************************************/

QModelIndex RMeasureModel :: index(int row, int column, const QModelIndex& parent) const
{
  return createIndex(row, column, 0);
}

/**********************************************************************************************/

QModelIndex	RMeasureModel :: parent(const QModelIndex& index) const
{
  return QModelIndex();
}

/**********************************************************************************************/

int RMeasureModel :: rowCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_measures.size();
}

/**********************************************************************************************/

bool RMeasureModel :: setData(const QModelIndex& index, const QVariant& value, int role)
{
  return true;
}

/**********************************************************************************************/
