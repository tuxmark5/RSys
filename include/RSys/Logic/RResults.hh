#ifndef RSYS_LOGIC_RRESULTS_HH
#define RSYS_LOGIC_RRESULTS_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <QtCore/QSet>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

class RResults: public QObject
{
  Q_OBJECT

  public:
    _T std::function<QVariant (int)>      Getter;
    _T std::tuple<RResultsModel*, int>    Field;
    _T QMultiHash<RUnit*, Field>          FieldHash;
    _T std::tuple<QDate, QDate>           Interval;
    _T std::function<Interval (int)>      IntervalFun;
    _T QSet<RResultsModel*>               ModelSet;

  public:   
    _E ResultType
    {
      Date,
      Usage0,
      Usage1,
      Usage1Tooltip,
      DeltaUsage,
      DeltaUsageTooltip,
      DeltaPUsage,
      Identifier,
      FullName
    };

  private:
    _M RCalculator*     m_calculator0;
    _M RCalculator*     m_calculator1;
    _M RData*           m_data0;
    _M RData*           m_data1;

    _M FieldHash        m_fields;
    _M ModelSet         m_models;

    _M QDate            m_interval0;
    _M QDate            m_interval1;

    _M IntervalFun      m_intervalFun;
    _M int              m_numRecords;
    _M int              m_seasonalLengths[4];

  public:
    _M Vacuum           RResults(RData* data0, RData* data1, QObject* parent = 0);
    _M Vacuum           ~RResults();
    _M RData*           data1() const { return m_data1; }
    _M Getter           field(ResultType type, RUnit* unit);
    _M RInterval        findLowUsageInterval(RUnit* unit);
    _M RInterval        interval(int x) const { return m_intervalFun(x); }
    _M IntervalFun      intervalFun();
    _M int              numRecords() const { return m_numRecords; }
    _M void             registerField(RUnit* unit, RResultsModel* model, int key);
    _M void             registerModel(RResultsModel* model) { m_models.insert(model); }
    _M int*             seasonalLengths() { return m_seasonalLengths; }
    _M void             unregisterField(RUnit* unit, RResultsModel* model, int key);
    _M void             unregisterModel(RResultsModel* model) { m_models.remove(model); }
    _M void             updateDelayed();

  public slots:
    _M void             reset();
    _M void             setInterval(QDate date0, QDate date1);
    _M void             setInterval(RIntervalFun fun, int num);
    _M void             update();

  private:
    _S double           fieldDeltaUsage(RUnit* unit, int x);
    _M QString          intervalStr(int x);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
