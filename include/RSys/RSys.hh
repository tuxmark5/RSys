#ifndef RSYS_RSYS_HH
#define RSYS_RSYS_HH

/**********************************************************************************************/
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QDate>
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
#define R_S(x)        QString::fromUtf16((const ushort*) u##x)
/**********************************************************************************************/
#define Vacuum
/**********************************************************************************************/
// Core
class RAdminData;
class RData;
class RDivision;
class RElement;
class RMeasure;
class RSubmission;
class RSystem;
class RUnit;
class RUser;
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
class RUsageWidget;
/**********************************************************************************************/
// Logic
class RCalculator;
class RResults;
/**********************************************************************************************/
// Store
class RDatabase;
class REntity;
class REntity1D;
class REntity2D;
/**********************************************************************************************/
// Util
class RContainer;
/**********************************************************************************************/
// Qt
class QComboBox;
class QDate;
class QDateEdit;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLayoutItem;
class QLineEdit;
class QMenu;
class QPushButton;
class QRadioButton;
class QScrollArea;
class QSpinBox;
class QSplitter;
class QStackedLayout;
class QTabWidget;
class QTableView;
class QVBoxLayout;
/**********************************************************************************************/
typedef long long                 RID;
typedef std::tuple<QDate, QDate>  RInterval;
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QMap<RSystem*, double>    RSystemMap;
typedef QMap<RDivision*, double>  RDivisionMap;
/**********************************************************************************************/
enum RMessageLevel
{
  RDEBUG,
  RINFO,
  RWARNING,
  RERROR,
  RCRITICAL
};
enum RDataType
{
  RMEASURE,
  RDIVISION,
  RSYSTEM,
  RDIVISIONSYSTEMS,
  RDIVISIONMEASURES,
  RSUBMISSION,
  RUNKNOWN
};
/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
#include <RSys/Util/RSharedPtr.hh>
/**********************************************************************************************/
typedef RSharedPtr<RDivision>           RDivisionPtr;
typedef RSharedPtr<RMeasure>            RMeasurePtr;
typedef RSharedPtr<RSubmission>         RSubmissionPtr;
typedef RSharedPtr<RSystem>             RSystemPtr;
typedef RSharedPtr<RUnit>               RUnitPtr;

typedef ROList<RDivision*>              RDivisionList;
typedef ROList<RMeasure*>               RMeasureList;
typedef ROList<RSystem*>                RSubmissionList;
typedef ROList<RSystem*>                RSystemList;
typedef ROList<RUnit*>                  RUnitList;

typedef ROList<RDivisionPtr>            RDivisionPtrList;
typedef ROList<RMeasurePtr>             RMeasurePtrList;
typedef ROList<RSubmissionPtr>          RSubmissionPtrList;
typedef ROList<RSystemPtr>              RSystemPtrList;
typedef ROList<RUnitPtr>                RUnitPtrList;

typedef std::function<RInterval (int)>  RIntervalFun;
/**********************************************************************************************/
using namespace std::placeholders;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
