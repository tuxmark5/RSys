#ifndef RSYS_LOGIC_RRESULTS_HH
#define RSYS_LOGIC_RRESULTS_HH

/**********************************************************************************************/
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RSubmission.hh>
/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

class RResults
{
  private:
    _T QMap<RUnit*, double>               RUnitMap;
  public:
    _T std::function<QVariant (int)>      Getter;
    _T std::tuple<RResultsModel*, int>    Field;
    _T QMultiHash<RUnit*, Field>          FieldHash;

  public:
    _E ResultType
    {
      Usage0,
      Usage1,
      DeltaUsage,
      DeltaPUsage,
      Identifier
    };

  private:
    _M RData*           m_data;
    _M FieldHash        m_fields;

  private:
    _M void             updateMeasures(RDivision* division, RMeasureMap& measures);
    _M void             updateUsages(RSubmissionList* submissions);
    _M void             updateUsageChanges(RUnitMap* units, RSubmission* submission);
    _M void             updateUsages(RUnitList* units);

  public:
    _M Vacuum           RResults(RData* data);
    _M Vacuum           ~RResults();
    _M Getter           field(ResultType type, RUnit* unit);
    _M int              numRecords() const { return 20; }
    _M void             registerField(RUnit* unit, RResultsModel* model, int key);
    _M void             unregisterField(RUnit* unit, RResultsModel* model, int key);
    _M void             update();
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
