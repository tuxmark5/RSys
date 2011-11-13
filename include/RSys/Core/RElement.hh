#ifndef RSYS_CORE_RELEMENT_HH
#define RSYS_CORE_RELEMENT_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RElement                                          */
/**********************************************************************************************/

class RElement
{
  public:
    _M RData*           m_data;
    _M RID              m_id;
    _M bool             m_valid: 1;
    _M bool             m_visible: 1;

  public:
    _M Vacuum           RElement(RData* data);
    _V Vacuum           ~RElement();
    _M bool             isValid() const { return m_valid; }
    _M bool             visible() const { return m_visible; }
    _M void             setValid(bool valid);
    _M void             setVisible(bool visible);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RELEMENT_HH */
