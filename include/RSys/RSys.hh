#ifndef RSYS_RSYS_HH
#define RSYS_RSYS_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
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
#define R_Z(x)          if (!(x)) x
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
class RHelp;
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
class QProcess;
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
typedef QHash<RDivision*, double>       RDivisionHash;
typedef long long                       RID;
typedef std::tuple<QString, int, int>   RImportMode;
typedef QList<RImportMode>              RImportModes;
typedef std::tuple<QDate, QDate>        RInterval;
typedef QHash<RMeasure*, double>        RMeasureHash;
typedef QHash<RSystem*, double>         RSystemHash;
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
  RDEBUG      = 0x00,
  RINFO       = 0x01,
  RWARNING    = 0x02,
  RERROR      = 0x03,
  RCRITICAL   = 0x04
};

enum RMessageType
{
  RollbackSuccess,
  RollbackFailure,
  CommitSuccess,
  CommitFailure,
  ValidIntervalRequired,
  ImportBeginFailure,
  IntervalTooLong,
  IntervalTooShort,
  IntervalEndpointsInvalid,
  ParseOpenFileFailure,
  InvalidMeasureDiscarded,
  UnableToLocateMeasureHeaderRow,
  MeasuresParsed,
  InvalidDivisionDiscarded,
  UnableToLocateDivisionHeaderRow,
  DivisionsParsed,
  InvalidSystemDiscarded,
  UnableToLocateSystemHeaderRow,
  SystemsParsed,
  InternalParseError,
  UnableToLocateDivisionAdmHeaderRow,
  UnableToLocateSystemIdent,
  UnableToLocateDivisionIdent,
  DivisionAdmParsed,
  InvalidMeasureAdmEntryDiscarded,
  UnableToLocateMeasureAdmHeaderRow,
  FloatParseError,
  UnableToLocateMeasureIdent,
  UnableToLocateDivisionIdent2,
  MeasureAdmParsed,
  InvalidSubmissionDiscarded,
  UnableToLocateSubmissionsHeaderRow,
  IntegerParseError,
  SubmissionsParsed,
  InvalidSearchInterval
};

/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
#include <RSys/Util/RSharedPtr.hh>
/**********************************************************************************************/
typedef RSharedPtr<RContainer>          RContainerPtr;
typedef ROList<RDivision*>              RDivisionList;
typedef RSharedPtr<RDivision>           RDivisionPtr;
typedef ROList<RDivisionPtr>            RDivisionPtrList;
typedef std::function<RInterval (int)>  RIntervalFun;
typedef ROList<RMeasure*>               RMeasureList;
typedef RSharedPtr<RMeasure>            RMeasurePtr;
typedef ROList<RMeasurePtr>             RMeasurePtrList;
typedef ROList<RSystem*>                RSubmissionList;
typedef RSharedPtr<RSubmission>         RSubmissionPtr;
typedef ROList<RSubmissionPtr>          RSubmissionPtrList;
typedef ROList<RSystem*>                RSystemList;
typedef RSharedPtr<RSystem>             RSystemPtr;
typedef ROList<RSystemPtr>              RSystemPtrList;
typedef ROList<RUnit*>                  RUnitList;
typedef RSharedPtr<RUnit>               RUnitPtr;
typedef ROList<RUnitPtr>                RUnitPtrList;
typedef RSharedPtr<RUser>               RUserPtr;
typedef ROList<RUserPtr>                RUserPtrList;
/**********************************************************************************************/
using namespace std::placeholders;
/**********************************************************************************************/
extern QSettings* g_settings;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
