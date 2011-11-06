#ifndef RSYS_INTERFACE_RMODEL_1D_HH
#define RSYS_INTERFACE_RMODEL_1D_HH

/**********************************************************************************************/
#include <RSys/Util/RContainer.hh>
#include <QtCore/QAbstractItemModel>
/********************************************* RS *********************************************/
/*                                          RModel1D                                          */
/**********************************************************************************************/

class RModel1D: public QAbstractItemModel
{
  Q_OBJECT

  public:
    _M RContainer*    m_container;

  public:
    _M Vacuum         RModel1D(RContainer* container, QObject* parent = 0);
    _V Vacuum         ~RModel1D();
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V Qt::ItemFlags  flags(const QModelIndex& index) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       lastRowData(const QModelIndex& index, int role) const;
    _V QModelIndex    parent(const QModelIndex& index) const;
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
    _V bool           setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMODEL_1D_HH */
