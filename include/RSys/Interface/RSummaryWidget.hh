#ifndef RSYS_INTERFACE_RSUMMARY_WIDGET_HH
#define RSYS_INTERFACE_RSUMMARY_WIDGET_HH

/**********************************************************************************************/
#include <RSys/Interface/RLayerWidget.hh>
#include <RSys/Interface/RResultsModel.hh>
/********************************************* RS *********************************************/
/*                                       RSummaryWidget                                       */
/**********************************************************************************************/

class RSummaryWidget: public RLayerWidget, public RIObserver
{
  Q_OBJECT

  public:
    _T RResultsModel::FieldType     FieldType;

  private:
    _M RResults*        m_results;
    _M RResultsModel*   m_resultsModel;
    _M FieldType        m_fieldType;
    _M RUnitList*       m_units;

  public:
    _M Vacuum           RSummaryWidget(RResults* results, QWidget* parent = 0);
    _V Vacuum           ~RSummaryWidget();
    _M int              countVisible(int till);
    _V void             insert1(int i0, int i1);
    _M RResultsModel*   model() const { return m_resultsModel; }
    _V bool             remove0(int i0, int i1);
    _V void             resetObservable();
    _M void             setFieldType(FieldType type);

  public slots:
    _M void             setUnits(RUnitList* units);
    _M void             setUsage1BarMode();
    _M void             setUsage1TableMode();
    _M void             updateElement(RElement* unit, int updateType);

  protected:
    _V void             createButtons(const ButtonCallback& callback);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSUMMARY_WIDGET_HH */