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
      DeltaUsage,
      DeltaPUsage,
      Identifier
    };

  private:
    _M RData*           m_data;
    _M FieldHash        m_fields;
    _M ModelSet         m_models;

    _M QDate            m_interval0;
    _M QDate            m_interval1;

    _M IntervalFun      m_intervalFun;
    _M int              m_numRecords;
    _M int              m_seasonalLengths[4];

  public:
    _M Vacuum           RResults(RData* data, QObject* parent = 0);
    _M Vacuum           ~RResults();
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

  public slots:
    _M void             setInterval(QDate date0, QDate date1);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
