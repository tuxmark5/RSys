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
    _M void             addUsage0Field(RResultModel* model, RElement* element);
    _M void             addUsage1Field(RResultModel* model, RElement* element);
    _M void             addDeltaUsageField(RResultModel* model, RElement* element);
    _M void             addDeltaPUsageField(RResultModel* model, RElement* element);
    _M int              numRecords() const { return 0; }
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RRESULTS_HH */
