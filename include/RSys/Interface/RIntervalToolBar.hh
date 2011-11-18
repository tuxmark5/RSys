#ifndef RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH
#define RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <QtGui/QToolBar>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

class RIntervalToolBar: public QToolBar
{
  Q_OBJECT

  private:
    _M QDateEdit*     m_interval0;
    _M QDateEdit*     m_interval1;
    _M QComboBox*     m_intervalLen;
    _M QPushButton*   m_applyButton;

  public:
    _M Vacuum         RIntervalToolBar(RMainWindow* parent = 0);
    _V Vacuum         ~RIntervalToolBar();
    _M QDate          date0() const;
    _M QDate          date1() const;
    _M void           setValid(bool valid);

  public slots:
    _M void           onApplyClicked();
    _M bool           validate(bool emitMessage = false);

  signals:
    _M void           intervalChanged(QDate date0, QDate date1);
    _M void           message(QString message, int timeout);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH */
