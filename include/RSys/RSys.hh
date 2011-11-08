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
class RSystem;
/**********************************************************************************************/
// Interface
class RAbstractItemModel;
class RMainWindow;
class RModel1D;
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
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QMap<RSystem*, double>    RSystemMap;
/**********************************************************************************************/
#include <RSys/Util/ROList.hh>
/**********************************************************************************************/
typedef ROList<RDivision*>        RDivisionList;
typedef ROList<RMeasure*>         RMeasureList;
typedef ROList<RSystem*>          RSystemList;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
