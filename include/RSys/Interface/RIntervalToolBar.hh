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

  public:
    _E IntervalLength
    {
      ByWeek    = 0,
      ByMonth   = 1,
      ByQuarter = 2,
      ByYear    = 3,
      By10      = 4,
      By12      = 5
    };

    _E IntervalError
    {
      Correct,
      TooLong,
      TooShort,
      InvalidOrder
    };

  private:
    _M RResults*      m_results;
    _M QDateEdit*     m_interval0;
    _M QDateEdit*     m_interval1;
    _M QComboBox*     m_intervalLen;
    _M QPushButton*   m_applyButton;
    _M bool           m_validInterval: 1;

  public:
    _M Vacuum         RIntervalToolBar(RMainWindow* parent = 0);
    _V Vacuum         ~RIntervalToolBar();
    _M QDate          date0() const;
    _M QDate          date1() const;
    _V bool           eventFilter(QObject* watched, QEvent* event);
    _M void           getInterval(QDate& date0, QDate& date1, RIntervalFun& fun, int& num);
    _M bool           isIntervalValid() const { return m_validInterval; }
    _M void           modifyDate(int deltaYear, int deltaMonth);
    _M void           setValid(bool valid);

  public slots:
    _M bool           applyInterval();
    _M void           decMonth();
    _M void           decYear();
    _M void           incMonth();
    _M void           incYear();
    _M bool           validate(bool emitMessage = false);

  private:
    _M bool           adjustInterval(QDate& date0, QDate& date1);
    _M void           emitErrorMessage(int error);

  signals:
    _M void           intervalChanged();
    _M void           message(QString message, int timeout);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH */
