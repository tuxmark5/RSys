#ifndef RSYS_INTERFACE_RMODEL_1D_HH
#define RSYS_INTERFACE_RMODEL_1D_HH

/**********************************************************************************************/
#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Util/RContainer.hh>
/********************************************* RS *********************************************/
/*                                          RModel1D                                          */
/**********************************************************************************************/

class RAdapter1D: public RIObserver
{
  public:
    _M RModel1D*      m_model;

  public:
    _M Vacuum         RAdapter1D(RModel1D* model);
    _V bool           insert0(int i0, int i1);
    _V void           insert1(int i0, int i1);
    _V void           modify0(int i0, int i1);
    _V void           modify1(int i0, int i1);
    _V bool           remove0(int i0, int i1);
    _V void           remove1(int i0, int i1);
    _V void           resetObservable0();
    _V void           resetObservable();
};

/**********************************************************************************************/

class RNode1D
{
  public:
    _T QList<RNode1D> Children;

  public:
    _M RModel1D*      m_model;
    _M RNode1D*       m_parent;
    _M void*          m_value;
    _M Children       m_children;

  public:
    _M Vacuum         RNode1D(RModel1D* model = 0, RNode1D* parent = 0, void* value = 0);
    _M Vacuum         ~RNode1D();
    _M int            find(void* pointer);
    _M bool           operator < (const RNode1D& other);
    _M int            size() const { return m_children.size(); }
};

/**********************************************************************************************/

class RModel1D: public RAbstractItemModel
{
  Q_OBJECT

  public:
    _F class RAdapter1D;
    _F class RNode1D;
    _F class RRowObserverAdapter;
    _T RRowObserverAdapter      RowAdapter;
    _T QHash<int, RNode1D*>     NodeHash;

  public:
    _M RContainerPtr  m_container;
    _M RAdapter1D*    m_rowAdapter;
    _M RNode1D        m_root;

  public:
    _M Vacuum         RModel1D(RContainerPtr container, QObject* parent = 0);
    _V Vacuum         ~RModel1D();
    _M void           addRow();
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V Qt::ItemFlags  flags(const QModelIndex& index) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       lastRowData(const QModelIndex& index, int role) const;
    _M void           notifyAllRowsChanged();
    _V QModelIndex    parent(const QModelIndex& index) const;
    _V bool           removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
    _M void           setContainer(RContainer* container);
    _V bool           setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    _V void           sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    _M bool           writable() const { return m_editable; }

  public:
    _M const RNode1D* node(const QModelIndex& index) const;
    _M const RNode1D* node(int row, const QModelIndex& parent) const;
    _M void           resetBegin();
    _M void           resetEnd();

  private:
    _M void           notifyRowChanged(int row);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMODEL_1D_HH */
