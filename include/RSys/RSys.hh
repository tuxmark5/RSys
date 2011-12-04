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
#define FN(x)           decltype(x), x
#define R_GUARD(x, r)   if (!(x)) return r
#define R_NZ(x)         if (x) (x)
#define R_S(x)          QString::fromUtf16((const ushort*) u##x)
#define R_DATE_TO_S(d)  d.toString(Qt::DefaultLocaleShortDate)
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
class RUser;
/**********************************************************************************************/
// Interface
class RAbstractItemModel;
class RIntervalToolBar;
class RLogDock;
class RMainToolBar;
class RMainMenuBar;
class RMainWindow;
class RMessage;
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
class RUserTab;
/**********************************************************************************************/
// Logic
class RCalculator;
class RResults;
/**********************************************************************************************/
// Parse
class RParser;
/**********************************************************************************************/
// Store
class RDatabase;
class REntity;
class REntity1D;
class REntity2D;
class RSignal;
class RSqlEntity;
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
class QItemSelection;
class QLabel;
class QLayoutItem;
class QLineEdit;
class QMenu;
class QModelIndex;
class QPushButton;
class QRadioButton;
class QScrollArea;
class QSettings;
class QSpinBox;
class QSplitter;
class QStackedLayout;
class QStandardItem;
class QStandardItemModel;
class QTabWidget;
class QTableView;
class QVBoxLayout;
/**********************************************************************************************/
typedef long long                       RID;
typedef std::tuple<QString, int, int>   RImportMode;
typedef QList<RImportMode>              RImportModes;
typedef std::tuple<QDate, QDate>        RInterval;
typedef QHash<RMeasure*, double>        RMeasureHash;
typedef QHash<RSystem*, double>         RSystemHash;
typedef QHash<RDivision*, double>       RDivisionHash;
typedef QPair<double, double>           RUsage;
/**********************************************************************************************/
enum RDataType
{
  RDIVISION           = 3,
  RDIVISIONMEASURES   = 4,
  RDIVISIONSYSTEMS    = 1,
  RMEASURE            = 5,
  RSYSTEM             = 0,
  RSUBMISSION         = 2,
  RUNKNOWN            = 10
};

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
#include <RSys/Util/RSharedPtr.hh>
/**********************************************************************************************/
typedef RSharedPtr<RDivision>           RDivisionPtr;
typedef RSharedPtr<RMeasure>            RMeasurePtr;
typedef RSharedPtr<RSubmission>         RSubmissionPtr;
typedef RSharedPtr<RSystem>             RSystemPtr;
typedef RSharedPtr<RUnit>               RUnitPtr;
typedef RSharedPtr<RUser>               RUserPtr;

typedef RSharedPtr<RContainer>          RContainerPtr;

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
typedef ROList<RUserPtr>                RUserPtrList;

typedef std::function<RInterval (int)>  RIntervalFun;
/**********************************************************************************************/
using namespace std::placeholders;
/**********************************************************************************************/
extern QSettings* g_settings;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
