#ifndef RSYS_CORE_RELEMENT_HH
#define RSYS_CORE_RELEMENT_HH

/**********************************************************************************************/
#include <RSys/Util/RSharedData.hh>
/********************************************* RS *********************************************/
/*                                          RElement                                          */
/**********************************************************************************************/

class RElement: public RSharedData
{
  public:
    _M RData*           m_data;
    _M RElement*        m_buddy;
    _M RID              m_id;
    _M bool             m_valid: 1;
    _M bool             m_visible: 1;

  public:
    _M Vacuum           RElement(RData* data);
    _M Vacuum           RElement(RElement& element, RData* data);
    _V Vacuum           ~RElement();
    _M RData*           data() const { return m_data; }
    _M RID              id() const { return m_id; }
    _M bool             isValid() const { return m_valid; }
    _M bool             visible() const { return m_visible; }
    _M void             setId(RID id);
    _M void             setValid(bool valid);
    _M void             setVisible(bool visible);
    _M void             setVisibleRaw(bool visible);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RELEMENT_HH */
