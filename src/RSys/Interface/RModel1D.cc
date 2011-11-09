#include <QtGui/QFont>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RRowObserverAdapter.hh>

/**********************************************************************************************/
QFont g_lastRowFont;
/********************************************* RS *********************************************/
/*                                          RModel1D                                          */
/**********************************************************************************************/

Vacuum RModel1D :: RModel1D(RContainer* container, QObject* parent):
  RAbstractItemModel(parent),
  m_container(container),
  m_writable(container->writable())
{
  container->addObserver(new RRowObserverAdapter(this));

  if (!g_lastRowFont.italic())
    g_lastRowFont.setItalic(true);
}

/**********************************************************************************************/

Vacuum RModel1D :: ~RModel1D()
{
  delete m_container;
}

/**********************************************************************************************/

int RModel1D :: columnCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_container->width();
}

/**********************************************************************************************/

QVariant RModel1D :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(), QVariant());

  int width   = m_container->width();
  int height  = m_container->height();

  R_GUARD(index.column() <  width,  QVariant());

  if (m_writable && index.row() == height)
    return lastRowData(index, role);

  R_GUARD(index.row()    <  height, QVariant());

  switch (role)
  {
    case Qt::CheckStateRole:
      return true;

    case Qt::EditRole:
    case Qt::DisplayRole:
      return m_container->get(index.column(), index.row());
  }

  return QVariant();
}

/**********************************************************************************************/

Qt::ItemFlags RModel1D :: flags(const QModelIndex& index) const
{
  R_GUARD(index.isValid(), 0);

  return Qt::ItemIsSelectable
       | Qt::ItemIsEditable
       | Qt::ItemIsEnabled
       | Qt::ItemIsUserCheckable // TODO: handle this more properly
      ;
}

/**********************************************************************************************/

QVariant RModel1D :: headerData(int section, Qt::Orientation orientation, int role) const
{
  R_GUARD(orientation == Qt::Horizontal,  QVariant());
  R_GUARD(role        == Qt::DisplayRole, QVariant());

  return m_container->header(section);
}

/**********************************************************************************************/

QModelIndex RModel1D :: index(int row, int column, const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), QModelIndex());

  return createIndex(row, column, 0);
}

/**********************************************************************************************/

QVariant RModel1D :: lastRowData(const QModelIndex& index, int role) const
{
  R_GUARD(index.column() == 0, QVariant());

  switch (role)
  {
    case Qt::EditRole:
    case Qt::DisplayRole:
      return QString::fromUtf8("Pridėti");

    case Qt::FontRole:
      return QVariant::fromValue(g_lastRowFont);
  }

  return QVariant();
}

/**********************************************************************************************/

QModelIndex RModel1D :: parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

/**********************************************************************************************/

int RModel1D :: rowCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_container->height() + int(m_writable);
}

/**********************************************************************************************/

void RModel1D :: setContainer(RContainer* container)
{
  beginResetModel();
  // TODO: RE-REGISTER observers
  m_container = container;
  endResetModel();
}

/**********************************************************************************************/

bool RModel1D ::setData(const QModelIndex& index, const QVariant& value, int role)
{
  R_GUARD(index.isValid(),      false);
  R_GUARD(role == Qt::EditRole, false);

  if (index.row() == m_container->height())
    if (!m_container->add())
      return false;

  m_container->set(index.column(), index.row(), value);
  return true;
}

/**********************************************************************************************/
