#ifndef RSYS_RSYS_HH
#define RSYS_RSYS_HH

/**********************************************************************************************/
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QString>
/********************************************* RS *********************************************/
/*                                            RSys                                            */
/**********************************************************************************************/
#define _C static const
#define _E enum
#define _F friend
#define _M
#define _S static
#define _T typedef
#define _V virtual
/**********************************************************************************************/
#define FN(x)         decltype(x), x
#define R_GUARD(x, r) if (!(x)) return r
#define R_S(x)        QString::fromUtf8(x)
/**********************************************************************************************/
#define Vacuum
/**********************************************************************************************/
// Core
class RData;
class RDivision;
class RElement;
class RMeasure;
class RSubmission;
class RSystem;
class RUnit;
/**********************************************************************************************/
// Interface
class RAbstractItemModel;
class RIntervalToolBar;
class RMainToolBar;
class RMainMenuBar;
class RMainWindow;
class RModel1D;
class RModel2D;
class RResultsModel;
class RLoginWidget;
class RPaletteDock;
class RRowObserverAdapter;
class RSearchForm;
class RSummaryWidget;
class RTab;
class RTableView;
/**********************************************************************************************/
// Logic
class RResults;
/**********************************************************************************************/
// Store
class RDatabase;
/**********************************************************************************************/
// Util
class RContainer;
/**********************************************************************************************/
// Qt
class QDateEdit;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLayoutItem;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QSpinBox;
class QSplitter;
class QStackedLayout;
class QTabWidget;
class QTableView;
class QVBoxLayout;
/**********************************************************************************************/
typedef long long                 RID;
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QMap<RSystem*, bool>      RSystemMap;
/**********************************************************************************************/
enum RMessageLevel
{
  RDEBUG,
  RINFO,
  RWARNING,
  RERROR,
  RCRITICAL
};
/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
/**********************************************************************************************/
typedef ROList<RDivision*>        RDivisionList;
typedef ROList<RMeasure*>         RMeasureList;
typedef ROList<RSubmission*>      RSubmissionList;
typedef ROList<RSystem*>          RSystemList;
typedef ROList<RUnit*>            RUnitList;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
