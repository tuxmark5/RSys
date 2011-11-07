#ifndef RSYS_CORE_RDATA_HH
#define RSYS_CORE_RDATA_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

class RData
{
  private:
    _M RDivisionList  m_divisions;
    _M RMeasureList   m_measures;
    _M RSystemList    m_systems;

  public:
    _M Vacuum         RData();
    _M RDivisionList* divisions() { return &m_divisions; }
    _M RMeasureList*  measures()  { return &m_measures; }
    _M RSystemList*   systems()   { return &m_systems; }
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDATA_HH */
