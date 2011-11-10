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
#define _F friend
#define _M
#define _S static
#define _T typedef
#define _V virtual
/**********************************************************************************************/
#define FN(x)         decltype(x), x
#define R_GUARD(x, r) if (!(x)) return r
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
/**********************************************************************************************/
// Interface
class RAbstractItemModel;
class RMainWindow;
class RModel1D;
class RRowObserverAdapter;
class RTab;
/**********************************************************************************************/
// Util
class RContainer;
/**********************************************************************************************/
class QDateEdit;
class QLabel;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QSplitter;
class QTabWidget;
class QTableView;
/**********************************************************************************************/
typedef long long                 RID;
typedef enum {RDEBUG, RINFO, RWARNING, RERROR, RCRITICAL}
                                  RLEVEL;
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QMap<RSystem*, bool>      RSystemMap;
/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
/**********************************************************************************************/
typedef ROList<RDivision*>        RDivisionList;
typedef ROList<RMeasure*>         RMeasureList;
typedef ROList<RSubmission*>      RSubmissionList;
typedef ROList<RSystem*>          RSystemList;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
