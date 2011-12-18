#ifndef RSYS_INTERFACE_RTAB_HH
#define RSYS_INTERFACE_RTAB_HH

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

  protected:
    _M QLabel*      m_label;

  public:
    _M Vacuum       RTab(const QString& title, QWidget* parent = 0);
    _V Vacuum       ~RTab();
    _M RTableView*  addSubmissionTable(RResults* results, RContainer* container);
    _M RTableView*  makeTable1DTab(RContainer* container);
    _M RModel2D*    makeTable2DTab(RContainer* containerX, RContainer* containerY);
    _M void         makeTree1DTab(RContainer* container);
    _M void         setEditable(bool writable);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RTAB_HH */
