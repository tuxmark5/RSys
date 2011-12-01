#ifndef RSYS_INTERFACE_RMODEL_2D_HH
#define RSYS_INTERFACE_RMODEL_2D_HH

/**********************************************************************************************/
#include <RSys/Interface/RAbstractItemModel.hh>
#include <RSys/Util/RContainer.hh>
/********************************************* RS *********************************************/
/*                                          RModel2D                                          */
/**********************************************************************************************/

class RModel2D: public RAbstractItemModel
{
  Q_OBJECT

  public:
    _T std::function<QVariant (int, int)>               Getter;
    _T std::function<void (int, int, const QVariant&)>  Setter;

  public:
    _M RContainerPtr  m_containerX;
    _M RContainerPtr  m_containerY;
    _M RIObserver*    m_adapterX;
    _M RIObserver*    m_adapterY;
    _M Getter         m_getter;
    _M Setter         m_setter;

  public:
    _M Vacuum         RModel2D(RContainerPtr containerX, RContainerPtr containerY, QObject* parent = 0);
    _V Vacuum         ~RModel2D();
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V Qt::ItemFlags  flags(const QModelIndex& index) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _V QModelIndex    parent(const QModelIndex& index) const;
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
    _V bool           setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    _M void           setGetter(Getter&& m_getter);
    _M void           setSetter(Setter&& m_setter);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMODEL_2D_HH */
