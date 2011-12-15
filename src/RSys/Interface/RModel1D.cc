#include <QtGui/QFont>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RRowObserverAdapter.hh>

/**********************************************************************************************/
QFont g_lastRowFont;
/********************************************* RS *********************************************/
/*                                         RAdapter1D                                         */
/**********************************************************************************************/

Vacuum RAdapter1D :: RAdapter1D(RModel1D* model):
  m_model(model)
{
}

/**********************************************************************************************/

bool RAdapter1D :: insert0(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
  return true;
}

/**********************************************************************************************/

void RAdapter1D :: insert1(int i0, int i1)
{
  Q_UNUSED(i1);
  RNode1D&  root    = m_model->m_root;
  int       dstId   = root.m_children.size();
  auto      it      = root.m_children.end();

  m_model->beginInsertRows(QModelIndex(), dstId + 1, dstId + 1);
  root.m_children.insert(it, RNode1D(m_model, &root, m_model->m_container->pointer(i0)));
  m_model->endInsertRows();
}

/**********************************************************************************************/

void RAdapter1D :: modify0(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
}

/**********************************************************************************************/

void RAdapter1D :: modify1(int i0, int i1)
{
  Q_UNUSED(i1);
  void*             ptr   = m_model->m_container->pointer(i0);
  int               index = m_model->m_root.find(ptr);
  QModelIndex       left  = m_model->index(index, 0);
  QModelIndex       right = m_model->index(index, m_model->m_container->width());

  m_model->dataChanged(left, right);
}

/**********************************************************************************************/

bool RAdapter1D :: remove0(int i0, int i1)
{
  Q_UNUSED(i1);
  void*   ptr   = m_model->m_container->pointer(i0);
  int     index = m_model->m_root.find(ptr);

  m_model->beginRemoveRows(QModelIndex(), index, index);
  m_model->m_root.m_children.removeAt(index);
  m_model->endRemoveRows();
  return true;
}

/**********************************************************************************************/

void RAdapter1D :: remove1(int i0, int i1)
{
  Q_UNUSED(i0);
  Q_UNUSED(i1);
}

/**********************************************************************************************/

void RAdapter1D :: resetObservable0()
{
  m_model->resetBegin();
}

/**********************************************************************************************/

void RAdapter1D :: resetObservable()
{
  m_model->resetEnd();
}

/********************************************* RS *********************************************/
/*                                          RNode1D                                           */
/**********************************************************************************************/

Vacuum RNode1D :: RNode1D(RModel1D* model, RNode1D* parent, void* value):
  m_model(model), m_parent(parent), m_value(value)
{
}

/**********************************************************************************************/

Vacuum RNode1D :: ~RNode1D()
{
}

/**********************************************************************************************/

int RNode1D :: find(void* pointer)
{
  for (auto it = m_children.begin(); it != m_children.end(); ++it)
    if (it->m_value == pointer)
      return it - m_children.begin();
  return -1;
}

/********************************************* RS *********************************************/
/*                                          RModel1D                                          */
/**********************************************************************************************/

Vacuum RModel1D :: RModel1D(RContainerPtr container, QObject* parent):
  RAbstractItemModel(parent),
  m_container(container)
{
  if (!container->writable())
    m_editable = false;

  m_rowAdapter = new RAdapter1D(this);
  m_container->addObserver(m_rowAdapter);
  resetBegin();
  resetEnd();

  if (!g_lastRowFont.italic())
    g_lastRowFont.setItalic(true);
}

/**********************************************************************************************/

Vacuum RModel1D :: ~RModel1D()
{
  m_container->removeObserver(m_rowAdapter);
  delete m_rowAdapter;
}

/**********************************************************************************************/

void RModel1D :: addRow()
{
  int row = m_container->height();
  if (m_container->add())
    notifyRowChanged(row);
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

  if (m_editable && index.row() == height)
    return lastRowData(index, role);

  if (role == Qt::EditRole)
    role = Qt::DisplayRole;

  if (const RNode1D* node = this->node(index))
  {
    QVariant value = m_container->get(index.column(), node->m_value, role);
    if (!value.isValid())
      value = m_container->get(0xFE, node->m_value, role);
    return value;
  }
  return QVariant();
}

/**********************************************************************************************/

Qt::ItemFlags RModel1D :: flags(const QModelIndex& index) const
{
  R_GUARD(index.isValid(), 0);

  Qt::ItemFlags flags
      = Qt::ItemIsSelectable
      | Qt::ItemIsEnabled
      | Qt::ItemIsUserCheckable;

  if (m_editable)
    flags |= Qt::ItemIsEditable;

  return flags;
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
  if (const RNode1D* node = this->node(row, parent))
    return createIndex(row, column, (void*) node);
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

const RNode1D* RModel1D :: node(const QModelIndex& index) const
{
  return index.isValid() ? static_cast<const RNode1D*>(index.internalPointer()) : &m_root;
}

/**********************************************************************************************/

const RNode1D* RModel1D :: node(int row, const QModelIndex& parent) const
{
  const RNode1D* node = parent.isValid()
      ? static_cast<const RNode1D*>(parent.internalPointer()) : &m_root;
  if (row < node->m_children.size())
    return &node->m_children.at(row);
  return 0;
}

/**********************************************************************************************/

void RModel1D :: notifyAllRowsChanged()
{
  QModelIndex left  = createIndex(0, 0, 0);
  QModelIndex right = createIndex(m_container->height() - 1, m_container->width() - 1, 0);

  emit dataChanged(left, right);
}

/**********************************************************************************************/

void RModel1D :: notifyRowChanged(int row)
{
  QModelIndex left  = createIndex(row, 0, 0);
  QModelIndex right = createIndex(row, m_container->width() - 1, 0);

  emit dataChanged(left, right);
}

/**********************************************************************************************/

QModelIndex RModel1D :: parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

/**********************************************************************************************/

bool RModel1D :: removeRows(int row, int count, const QModelIndex& parent)
{
  Q_UNUSED(count);
  R_GUARD(editable(),                     false);
  R_GUARD(!parent.isValid(),              false);
  R_GUARD(row < m_container->height(),    false);

  if (RNode1D* node = const_cast<RNode1D*>(this->node(row, parent)))
  {
    int index = m_container->indexOf(node->m_value);
    m_container->remove(index);
    return true;
  }
  return false;
}

/**********************************************************************************************/

void RModel1D :: resetBegin()
{
  beginResetModel();
  m_root.m_children.clear();
}

/**********************************************************************************************/

void RModel1D :: resetEnd()
{
  int   height = m_container->height();
  auto  it     = m_root.m_children.end();

  for (int y = 0; y < height; y++)
  {
    it = m_root.m_children.insert(it, RNode1D(this, &m_root, m_container->pointer(y)));
    //m_nodes.insert(y, &*it);
    ++it;
  }

  endResetModel();
}

/**********************************************************************************************/

int RModel1D :: rowCount(const QModelIndex& parent) const
{
  if (const RNode1D* node = this->node(parent))
    return node->m_children.size() + int(m_editable);
  return 0;
}

/**********************************************************************************************/

void RModel1D :: setContainer(RContainer* container)
{
  beginResetModel();
  resetBegin();
  m_container->removeObserver(m_rowAdapter);
  m_container = container;
  m_container->addObserver(m_rowAdapter);
  resetEnd();
  endResetModel();
}

/**********************************************************************************************/

bool RModel1D :: setData(const QModelIndex& index, const QVariant& value, int role)
{
  R_GUARD(index.isValid(), false);

  if (role == Qt::EditRole)
    role = Qt::DisplayRole;

  RNode1D* node = const_cast<RNode1D*>(this->node(index));

  if (!node)
    node = const_cast<RNode1D*>(this->node(index.row(), QModelIndex()));

  if (node)
  {
    QVariant old = m_container->get(index.column(), node->m_value, role);
    if (old != value)
      m_container->set(index.column(), node->m_value, role, value);
  }

  return true;
}

/**********************************************************************************************/

void RModel1D :: sort(int column, Qt::SortOrder order)
{
  beginResetModel();
  qStableSort(m_root.m_children.begin(), m_root.m_children.end(), [=](const RNode1D& a, const RNode1D& b) -> bool
  {
    return m_container->less(column, a.m_value, b.m_value, Qt::DisplayRole)
            != (order == Qt::AscendingOrder);
  });
  endResetModel();
}

/**********************************************************************************************/
