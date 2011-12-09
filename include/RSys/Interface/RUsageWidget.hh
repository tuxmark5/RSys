#ifndef RSYS_INTERFACE_RUSAGE_WIDGET_HH
#define RSYS_INTERFACE_RUSAGE_WIDGET_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <RSys/Interface/RLayerWidget.hh>
/********************************************* RS *********************************************/
/*                                        RUsageWidget                                        */
/**********************************************************************************************/

class RUsageWidget: public RLayerWidget
{
  Q_OBJECT

  public:
    _E Mode
    {
      Usage0      = 0x0001,
      Usage1      = 0x0002,
      UsageD      = 0x0003,
      UsageDP     = 0x0004,

      Hours       = 0x0010,
      Counts      = 0x0020,

      Bar         = 0x1000,
      Line        = 0x2000,
      Table       = 0x3000,

      DataMask    = 0x000F,
      DataModMask = 0x00F0,
      ViewMask    = 0xF000
    };

  private:
    _M RUnit*           m_unit;
    _M RResults*        m_results;
    _M RResultsModel*   m_model;
    _M QString          m_title;
    _M QLabel*          m_header;
    _M RInterval        m_lowInterval;

  public:
    _M Vacuum           RUsageWidget(int mode, RUnit* unit, RResults* results, QWidget* parent = 0);
    _V Vacuum           ~RUsageWidget();
    _S QMenu*           createModeMenu(QObject* receiver, const char* slot, int initialMode);
    _M RResultsModel*   model() const { return m_model; }
    _M void             updateHeader();

  public slots:
    _M void             modifyMode();
    _M void             modifyMode(int modifier);
    _M void             setMode(int mode);
    _M void             setSearchInterval(bool search);
    _M void             updateGlobalInterval();

  protected:
    _V void             createButtons(const ButtonCallback& callback);
    _M void             setTitle(const QString& title);

  protected slots:
    _M void             onViewClicked(const QModelIndex& index);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_WIDGET_HH */
