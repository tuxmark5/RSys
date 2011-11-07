#include <RSys/Interface/RModel2D.hh>

/********************************************* RS *********************************************/
/*                                          RModel2D                                          */
/**********************************************************************************************/

Vacuum RModel2D :: RModel2D(RContainer* container, QObject* parent):
  RAbstractItemModel(parent),
  m_container(container)
{
}

/**********************************************************************************************/

Vacuum RModel2D :: ~RModel2D()
{
  delete m_container;
}

/**********************************************************************************************/

int RModel2D :: columnCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_container->width();
}

/**********************************************************************************************/

QVariant RModel2D :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(), QVariant());

  int width   = m_container->width();
  int height  = m_container->height();

  R_GUARD(index.column() <  width,  QVariant());
  R_GUARD(index.row()    != height, lastRowData(index, role));
  R_GUARD(index.row()    <  height, QVariant());

  switch (role)
  {
    case Qt::EditRole:
    case Qt::DisplayRole:
      return m_container->get(index.column(), index.row());
  }

  return QVariant();
}

/**********************************************************************************************/

Qt::ItemFlags RModel2D :: flags(const QModelIndex& index) const
{
  R_GUARD(index.isValid(), 0);

  return Qt::ItemIsSelectable
       | Qt::ItemIsEditable
       | Qt::ItemIsEnabled;
}

/**********************************************************************************************/

QVariant RModel2D :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(orientation == Qt::Horizontal,  QVariant());
  R_GUARD(role        == Qt::DisplayRole, QVariant());

  return m_container->header(section);
}

/**********************************************************************************************/

QModelIndex RModel2D :: index(int row, int column, const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), QModelIndex());

  return createIndex(row, column, 0);
}

/**********************************************************************************************/

QVariant RModel2D :: lastRowData(const QModelIndex& index, int role) const
{
  return QVariant();
}

/**********************************************************************************************/

QModelIndex RModel2D :: parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

/**********************************************************************************************/

int RModel2D :: rowCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_container->height() + 1;
}

/**********************************************************************************************/

bool RModel2D ::setData(const QModelIndex& index, const QVariant& value, int role)
{
  R_GUARD(index.isValid(),      false);
  R_GUARD(role == Qt::EditRole, false);

  m_container->set(index.column(), index.row(), value);
  return true;
}

/**********************************************************************************************/

