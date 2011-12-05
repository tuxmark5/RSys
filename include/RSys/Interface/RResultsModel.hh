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
    _E FieldType
    {
      Usage0      = 0x0001,
      Usage1      = 0x0002,
      UsageD      = 0x0003,
      UsageDP     = 0x0004,

      Hours       = 0x0010,
      Counts      = 0x0020,
      Identifier  = 0x0040,
      Title       = 0x0000
    };

  public:
    _T std::function<QVariant (int)>  Getter;
    _T std::function<void()>          Lambda;
    _T Qt::Orientation                Orientation;
    _T QList<int>                     FieldList;
    _T QHash<int, Getter>             GetterHash;
    _T QHash<int, RUnit*>             UnitHash;

  public:
    _M RResults*      m_results;
    _M Orientation    m_orientation;
    _M FieldList      m_fields;
    _M GetterHash     m_getters;
    _M UnitHash       m_units;
    _M int            m_lastKey;

  public:
    _M Vacuum         RResultsModel(RResults* results, QObject* parent = 0);
    _V Vacuum         ~RResultsModel();
    _M int            addField(int type, RUnit* unit);
    _M void           addGetter(int field, int role, Getter&& getter);
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _M int            insertField(int index, int type, RUnit* unit);
    _S QString        longTitleForField(int type);
    _V QModelIndex    parent(const QModelIndex& index) const;
    _M void           removeDimension(int id, Qt::Orientation orientation, const Lambda& lambda);
    _M void           removeField(int id);
    _M void           removeFields();
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
    _M void           setOrientation(Orientation orientation);
    _S QString        titleForField(int type);
    _M void           updateField(int fieldId);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RRESULTS_MODEL_HH */
