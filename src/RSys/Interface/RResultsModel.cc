#include <QtCore/QDate>
#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                       RResultsModel                                        */
/**********************************************************************************************/

Vacuum RResultsModel :: RResultsModel(RResults* results, QObject* parent):
  RAbstractItemModel(parent),
  m_results(results),
  m_orientation(Qt::Horizontal),
  m_numFields(0)
{
  // l(1)
}

/**********************************************************************************************/

Vacuum RResultsModel :: ~RResultsModel()
{
}

/**********************************************************************************************/

int RResultsModel :: addField(Getter&& getter)
{
  m_fields.insert(0xFF00 | m_numFields, std::forward<Getter>(getter));
  return m_numFields++;
}

/**********************************************************************************************/

void RResultsModel ::addGetter(int field, int role, Getter&& getter)
{
  m_fields.insert((role << 8) | field, std::forward<Getter>(getter));
}

/**********************************************************************************************/

int RResultsModel :: columnCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  if (m_orientation == Qt::Horizontal)
    return m_results->numRecords();
  else
    return m_numFields;
}

/**********************************************************************************************/

QVariant RResultsModel :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(), QVariant());

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

  Getter getter = m_fields.value((role << 8) | field);
  return getter ? getter(record) : QVariant();
}

/**********************************************************************************************/

QVariant RResultsModel :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(role == Qt::DisplayRole, QVariant());

  if (m_orientation != orientation)
  {
    Getter getter = m_fields.value(0xFF00 | section);
    return getter ? getter(0) : QVariant();
  }
  else
  {
    QDate date(2000, 01, 01);

    return date.addMonths(section);
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

void RResultsModel :: removeFields()
{
  m_fields.clear();
  m_numFields = 0;
}

/**********************************************************************************************/

int RResultsModel :: rowCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  if (m_orientation == Qt::Vertical)
    return m_results->numRecords();
  else
    return m_numFields;
}

/**********************************************************************************************/

void RResultsModel :: setOrientation(Orientation orientation)
{
  m_orientation = orientation;
}

/**********************************************************************************************/
