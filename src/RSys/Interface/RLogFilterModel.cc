#include <RSys/Interface/RLogFilterModel.hh>

/********************************************* RS *********************************************/
/*                                       RLogFilterModel                                      */
/**********************************************************************************************/

Vacuum RLogFilterModel :: RLogFilterModel(QObject* parent):
  QSortFilterProxyModel(parent),
  m_minimumLevel(0)
{
}

/**********************************************************************************************/

Vacuum RLogFilterModel :: ~RLogFilterModel()
{
}

/**********************************************************************************************/

bool RLogFilterModel :: filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
  auto        source    = sourceModel();
  QModelIndex cellIndex = source->index(sourceRow, 0, sourceParent);
  int         level     = source->data(cellIndex, Qt::UserRole).toInt();

  return level >= m_minimumLevel;
}

/**********************************************************************************************/

void RLogFilterModel :: setMinimumLevel(int level)
{
  m_minimumLevel = level;
  invalidateFilter();
}

/**********************************************************************************************/
