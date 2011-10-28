#ifndef RSYS_RSYS_HH
#define RSYS_RSYS_HH

/**********************************************************************************************/
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
typedef QMap<RMeasure*, double>   RMeasureMap;
typedef QVector<RSystem*>         RSystemVector;
/**********************************************************************************************/

#endif /* RSYS_RSYS_HH */
