#ifndef RSYS_INTERFACE_RUSAGE_TAB_HH
#define RSYS_INTERFACE_RUSAGE_TAB_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QWidget>
/********************************************* RS *********************************************/
/*                                            RTab                                            */
/**********************************************************************************************/

class RTab: public QWidget
{
  Q_OBJECT

  public:
    _T std::function<QVariant (int, int)>               Getter2;
    _T std::function<void (int, int, const QVariant&)>  Setter2;

  public:
    _M Vacuum       RTab(const QString& title, QWidget* parent = 0);
    _V Vacuum       ~RTab();
    _M void         makeTable1DTab(RContainer* container);
    _M RModel2D*    makeTable2DTab(RContainer* containerX, RContainer* containerY);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_TAB_HH */
