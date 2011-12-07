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
    _M int              m_mode;
    _M RUnitPtrList*    m_units;

  public:
    _M Vacuum           RSummaryWidget(RResults* results, QWidget* parent = 0);
    _V Vacuum           ~RSummaryWidget();
    _M int              countVisible(int till);
    _M int              fieldType() const;
    _V void             insert1(int i0, int i1);
    _M RResultsModel*   model() const { return m_resultsModel; }
    _M QString          modeName() const;
    _V bool             remove0(int i0, int i1);
    _V void             resetObservable();
    _M void             setFieldType(FieldType type);

  public slots:
    _M void             modifyMode();
    _M void             resetBegin();
    _M void             resetEnd();
    _M void             setMode(int mode);
    _M void             setUnits(RUnitPtrList* units);
    _M void             updateUnit(RUnit* unit);

  protected:
    _V void             createButtons(const ButtonCallback& callback);

  signals:
    _M void             modeChanged();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSUMMARY_WIDGET_HH */
