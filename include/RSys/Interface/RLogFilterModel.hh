#ifndef RSYS_INTERFACE_RLOG_FILTER_MODEL_HH
#define RSYS_INTERFACE_RLOG_FILTER_MODEL_HH

/**********************************************************************************************/
#include <QtGui/QSortFilterProxyModel>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                       RLogFilterModel                                      */
/**********************************************************************************************/

class RLogFilterModel: public QSortFilterProxyModel
{
  Q_OBJECT

  private:
    _M int            m_minimumLevel;

  public:
    _M Vacuum         RLogFilterModel(QObject* parent = 0);
    _V Vacuum         ~RLogFilterModel();

  protected:
    _V bool           filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;

  public slots:
    _M void           setMinimumLevel(int level);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOG_FILTER_MODEL_HH */
