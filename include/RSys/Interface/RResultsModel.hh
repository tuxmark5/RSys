#ifndef RSYS_INTERFACE_RRESULTS_MODEL_HH
#define RSYS_INTERFACE_RRESULTS_MODEL_HH

/**********************************************************************************************/
#include <RSys/Interface/RAbstractItemModel.hh>
/********************************************* RS *********************************************/
/*                                       RResultsModel                                        */
/**********************************************************************************************/

class RResultsModel: public RAbstractItemModel
{
  Q_OBJECT

  public:
    _F class          RResults;

  public:
    _T std::function<QVariant (int)>  Getter;
    _T Qt::Orientation                Orientation;
    _T QHash<int, Getter>             FieldHash;

  public:
    _M RResults*      m_results;
    _M Orientation    m_orientation;
    _M FieldHash      m_fields;
    _M int            m_numFields;

  public:
    _M Vacuum         RResultsModel(RResults* results, QObject* parent = 0);
    _V Vacuum         ~RResultsModel();
    _M int            addField(Getter&& getter);
    _M void           addGetter(int field, int role, Getter&& getter);
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _V QModelIndex    parent(const QModelIndex& index) const;
    _M void           removeFields();
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
    _M void           setOrientation(Orientation orientation);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RRESULTS_MODEL_HH */
