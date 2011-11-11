#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                       RResultsModel                                        */
/**********************************************************************************************/

Vacuum RResultsModel :: RResultsModel(RResults* results, QObject* parent):
  RAbstractItemModel(parent),
  m_results(results)
{
}

/**********************************************************************************************/

Vacuum RResultsModel :: ~RResultsModel()
{
}

/**********************************************************************************************/

int RResultsModel :: columnCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  if (m_orientation == Qt::Horizontal)
    return m_results->numRecords();
  else
    return m_fields.size();
}

/**********************************************************************************************/

QVariant RResultsModel :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(),          QVariant());
  R_GUARD(role == Qt::DisplayRole,  QVariant());

  int   field;
  int   record;

  if (m_orientation == Qt::Horizontal)
  {
    field     = index.row();
    record    = index.column();
  }
  else
  {
    field     = index.column();
    record    = index.row();
  }

  return std::get<1>(m_fields.at(field))(record);
}

/**********************************************************************************************/

QVariant RResultsModel :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(role == Qt::DisplayRole, QVariant());

  if (m_orientation == orientation)
  {
    return std::get<0>(m_fields.at(section));
  }
  else
  {
    //return QDate();
    return QVariant();
  }
}

/**********************************************************************************************/

QModelIndex RResultsModel :: index(int row, int column, const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), QModelIndex());

  return createIndex(row, column, 0);
}

/**********************************************************************************************/

QModelIndex RResultsModel :: parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

/**********************************************************************************************/

int RResultsModel :: rowCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  if (m_orientation == Qt::Vertical)
    return m_results->numRecords();
  else
    return m_fields.size();
}

/**********************************************************************************************/
