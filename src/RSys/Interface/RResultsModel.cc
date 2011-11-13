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
  m_lastKey(0)
{
  // l(1)
}

/**********************************************************************************************/

Vacuum RResultsModel :: ~RResultsModel()
{
  removeFields();
}

/**********************************************************************************************/

int RResultsModel :: addField(FieldType type, RUnit* unit)
{
  return insertField(m_fields.size(), type, unit);
}

/**********************************************************************************************/

void RResultsModel :: addGetter(int fieldId, int role, Getter&& getter)
{
  m_getters.insert((role << 8) | fieldId, std::forward<Getter>(getter));
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

  int     fieldKey  = m_fields.at(field);
  Getter  getter    = m_getters.value((role << 8) | fieldKey);
  return getter ? getter(record) : QVariant();
}

/**********************************************************************************************/

QVariant RResultsModel :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(role == Qt::DisplayRole, QVariant());

  if (m_orientation != orientation)
  {
    int     fieldKey  = m_fields.at(section);
    Getter  getter    = m_getters.value(0xFF00 | fieldKey);
    return  getter ? getter(0) : QVariant();
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

int RResultsModel :: insertField(int index, FieldType type, RUnit* unit)
{
  int fieldKey = m_lastKey++;

  m_units.insert(fieldKey, unit);
  m_results->registerField(unit, this, fieldKey);

  switch (type)
  {
    case Usage0:
      addGetter(fieldKey, Qt::DisplayRole, m_results->field(RResults::Usage0, unit));
      break;

    case Usage1:
      addGetter(fieldKey, Qt::DisplayRole, m_results->field(RResults::Usage1, unit));
      addGetter(fieldKey, 0xFF, m_results->field(RResults::Identifier, unit));
      break;
  }

  if (m_orientation == Qt::Horizontal)
  {
    beginInsertRows(QModelIndex(), index, index);
    m_fields.insert(index, fieldKey);
    endInsertRows();
  }
  else
  {
    beginInsertColumns(QModelIndex(), index, index);
    m_fields.insert(index, fieldKey);
    endInsertColumns();
  }

  return fieldKey;
}

/**********************************************************************************************/

QModelIndex RResultsModel :: parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

/**********************************************************************************************/

void RResultsModel :: removeDimension(int id, Qt::Orientation orientation, const Lambda& lambda)
{
  if (m_orientation == orientation)
  {
    beginRemoveRows(QModelIndex(), id, id);
    lambda();
    endRemoveRows();
  }
  else
  {
    beginRemoveColumns(QModelIndex(), id, id);
    lambda();
    endRemoveColumns();
  }
}

/**********************************************************************************************/

void RResultsModel :: removeField(int id)
{
  R_GUARD(id < m_fields.size(), Vacuum);

  int     fieldKey  = m_fields.at(id);
  RUnit*  unit      = m_units.value(fieldKey);

  removeDimension(id, Qt::Horizontal, [&]()
  {
    m_fields.removeAt(id);
    m_units.remove(fieldKey);
    m_results->unregisterField(unit, this, fieldKey);
  });

  for (auto it = m_getters.begin(); it != m_getters.end(); )
  {
    if ((it.key() & 0xFF) == fieldKey)
      it = m_getters.erase(it);
    else
      ++it;
  }
}

/**********************************************************************************************/

void RResultsModel :: removeFields()
{
  emit layoutAboutToBeChanged();

  for (auto it = m_fields.begin(); it != m_fields.end(); ++it)
  {
    RUnit* unit = m_units.value(*it);
    m_results->unregisterField(unit, this, *it);
  }

  m_getters.clear();
  m_fields.clear();
  m_units.clear();
  emit layoutChanged();
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

void RResultsModel :: setOrientation(Orientation orientation)
{
  m_orientation = orientation;
}

/**********************************************************************************************/

void RResultsModel :: updateField(int fieldKey)
{
  int           field = m_fields.indexOf(fieldKey);
  QModelIndex   first;
  QModelIndex   last;

  if (m_orientation == Qt::Horizontal)
  {
    first   = createIndex(0, field, 0);
    last    = createIndex(m_results->numRecords(), field, 0);
  }
  else
  {
    first   = createIndex(field, 0, 0);
    last    = createIndex(field, m_results->numRecords(), 0);
  }

  emit dataChanged(first, last);
}

/**********************************************************************************************/
