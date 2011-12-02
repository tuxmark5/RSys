#ifndef RSYS_INTERFACE_RMODEL_1D_HH
#define RSYS_INTERFACE_RMODEL_1D_HH

/**********************************************************************************************/
#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Util/RContainer.hh>
/********************************************* RS *********************************************/
/*                                          RModel1D                                          */
/**********************************************************************************************/

class RModel1D: public RAbstractItemModel
{
  Q_OBJECT

  public:
    _F class RRowObserverAdapter;
    _T RRowObserverAdapter  RowAdapter;

  public:
    _M RContainerPtr  m_container;
    _M RowAdapter*    m_rowAdapter;

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
    _M bool           writable() const { return m_editable; }

  private:
    _M void           notifyRowChanged(int row);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMODEL_1D_HH */
