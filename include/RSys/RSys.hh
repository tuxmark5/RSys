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
#define _M
#define _S static
#define _T typedef
#define _V virtual
/**********************************************************************************************/
#define R_GUARD(x, r) if (!(x)) return r
/**********************************************************************************************/
#define Vacuum
/**********************************************************************************************/
class RData;
class RDivision;
class RElement;
class RMeasure;
class RSystem;
/**********************************************************************************************/
class QSplitter;
class QTabWidget;
/**********************************************************************************************/
typedef long long                 RID;
typedef QVector<RDivision*>       RDivisionVector;
typedef QList<RMeasure*>          RMeasureList;
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QVector<RSystem*>         RSystemVector;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
