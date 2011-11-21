#include <RSys/Interface/RColumnObserverAdapter.hh>
#include <RSys/Interface/RModel2D.hh>
#include <RSys/Interface/RRowObserverAdapter.hh>

/********************************************* RS *********************************************/
/*                                          RModel2D                                          */
/**********************************************************************************************/

Vacuum RModel2D :: RModel2D(RContainer* containerX, RContainer* containerY, QObject* parent):
  RAbstractItemModel(parent),
  m_containerX(containerX),
  m_containerY(containerY)
{
  m_containerX->addObserver(new RColumnObserverAdapter(this));
  m_containerY->addObserver(new RRowObserverAdapter(this));
}

/**********************************************************************************************/

Vacuum RModel2D :: ~RModel2D()
{
}

/**********************************************************************************************/

int RModel2D :: columnCount(const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), 0);

  return m_containerX->height();
}

/**********************************************************************************************/

QVariant RModel2D :: data(const QModelIndex& index, int role) const
{
  R_GUARD(index.isValid(), QVariant());

  int width   = m_containerX->height();
  int height  = m_containerY->height();

  R_GUARD(index.column()  < width,  QVariant());
  R_GUARD(index.row()     < height, QVariant());

  switch (role)
  {
    case Qt::EditRole:
    case Qt::DisplayRole:
      return m_getter(index.column(), index.row());
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
  switch (orientation)
  {
    case Qt::Horizontal:
      return m_containerX->get(0, section, role);

    case Qt::Vertical:
      return m_containerY->get(0, section, role);
  }

  return QVariant();
}

/**********************************************************************************************/

QModelIndex RModel2D :: index(int row, int column, const QModelIndex& parent) const
{
  R_GUARD(!parent.isValid(), QModelIndex());

  return createIndex(row, column, 0);
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

  return m_containerY->height();
}

/**********************************************************************************************/

bool RModel2D :: setData(const QModelIndex& index, const QVariant& value, int role)
{
  R_GUARD(index.isValid(),      false);
  R_GUARD(role == Qt::EditRole, false);

  if (m_setter)
    m_setter(index.column(), index.row(), value);
  return true;
}

/**********************************************************************************************/

void RModel2D :: setGetter(Getter&& getter)
{
  m_getter = std::forward<Getter>(getter);
}

/**********************************************************************************************/

void RModel2D :: setSetter(Setter&& setter)
{
  m_setter = std::forward<Setter>(setter);
}

/**********************************************************************************************/

