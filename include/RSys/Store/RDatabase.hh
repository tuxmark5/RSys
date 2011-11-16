#ifndef RSYS_STORE_RDATABASE_HH
#define RSYS_STORE_RDATABASE_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                         RDatabase                                          */
/**********************************************************************************************/

class RDatabase: public QObject
{
  Q_OBJECT

  public:
    _M Vacuum         RDatabase(QObject* parent = 0);
    _V Vacuum         ~RDatabase();
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RDATABASE_HH */
