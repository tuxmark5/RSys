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
    _T std::tuple<QString, Getter>    Field;
    _T QList<Field>                   FieldList;

  public:
    _M RResults*      m_results;
    _M Orientation    m_orientation;
    _M FieldList      m_fields;

  public:
    _M Vacuum         RResultsModel(RResults* results, QObject* parent = 0);
    _V Vacuum         ~RResultsModel();
    _V int            columnCount(const QModelIndex& parent = QModelIndex()) const;
    _V QVariant       data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    _V QVariant       headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    _V QModelIndex    index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    _V QModelIndex    parent(const QModelIndex& index) const;
    _V int            rowCount(const QModelIndex& parent = QModelIndex()) const;
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RRESULTS_MODEL_HH */
