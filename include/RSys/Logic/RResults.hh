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
      Usage0      = 0x0001,
      Usage1      = 0x0002,
      UsageD      = 0x0003,
      UsageDP     = 0x0004,

      Date        = 0x0005,
      Identifier  = 0x0006,
      FullName    = 0x0007,
      Background  = 0x0008,

      Hours       = 0x0010,
      Counts      = 0x0020,
      Tooltip     = 0x0080
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
    _M int              m_highlightedInterval;

    _M bool             m_updatesEnabled: 1;
    _M bool             m_updatePending: 1;

  public:
    _M Vacuum           RResults(RData* data0, RData* data1, QObject* parent = 0);
    _M Vacuum           ~RResults();
    _M RCalculator*     calculator0() const { return m_calculator0; }
    _M RCalculator*     calculator1() const { return m_calculator1; }
    _M RData*           data1() const { return m_data1; }
    _M Getter           field(int type, RUnit* unit);
    _M void             findLowestUsageIntervals();
    _M RInterval        interval(int x) const { return m_intervalFun(x); }
    _M QDate            interval0() const { return m_interval0; }
    _M QDate            interval1() const { return m_interval1; }
    _M int              numRecords() const { return m_numRecords; }
    _M void             registerField(RUnit* unit, RResultsModel* model, int key);
    _M void             registerModel(RResultsModel* model) { m_models.insert(model); }
    _M void             resetBegin();
    _M void             resetData();
    _M void             resetEnd();
    _M int*             seasonalLengths() { return m_seasonalLengths; }
    _M void             unregisterField(RUnit* unit, RResultsModel* model, int key);
    _M void             unregisterModel(RResultsModel* model) { m_models.remove(model); }
    _M void             updateDelayed();

  public slots:
    _M void             reset();
    _M void             setInterval(QDate date0, QDate date1);
    _M void             setInterval(RIntervalFun fun, int num);
    _M void             setHighlightedInterval(int x);
    _M void             setUpdatesEnabled(bool enabled);
    _M void             update();

  private:
    _S double           fieldDeltaUsage(RUnit* unit, int x);
    _S double           fieldDeltaUsageCount(RUnit* unit, int x);
    _M QString          intervalStr(int x);

  signals:
    _M void             updated();
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
