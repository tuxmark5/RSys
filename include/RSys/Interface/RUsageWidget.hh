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

  private:
    _M RUnit*           m_unit;
    _M RResults*        m_results;
    _M RResultsModel*   m_model;
    _M QString          m_title;
    _M QLabel*          m_header;
    _M RInterval        m_lowInterval;

  public:
    _M Vacuum           RUsageWidget(RUnit* unit, RResults* results, QWidget* parent = 0);
    _V Vacuum           ~RUsageWidget();
    _M RResultsModel*   model() const { return m_model; }
    _M void             updateHeader();

  protected:
    _V void             createButtons(const ButtonCallback& callback);
    _M void             setTitle(const char* title);

  public slots:
    _M void             setBarChartMode();
    _M void             setLineChartMode();
    _M void             setSearchInterval(bool search);
    _M void             setTableMode();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_WIDGET_HH */
