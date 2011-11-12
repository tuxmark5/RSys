#ifndef RSYS_LOGIC_RRESULTS_HH
#define RSYS_LOGIC_RRESULTS_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

class RResults
{
  private:
    _M RData*           m_data;

  public:
    _M Vacuum           RResults(RData* data);
    _M Vacuum           ~RResults();
    _M void             addUsage0Field(RResultsModel* model, RUnit* unit);
    _M void             addUsage1Field(RResultsModel* model, RUnit* unit);
    _M void             addDeltaUsageField(RResultsModel* model, RUnit* unit);
    _M void             addDeltaPUsageField(RResultsModel* model, RUnit* unit);
    _M int              numRecords() const { return 20; }
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
