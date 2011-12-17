#ifndef RSYS_CORE_RGROUP_HH
#define RSYS_CORE_RGROUP_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
/********************************************* RS *********************************************/
/*                                           RGroup                                           */
/**********************************************************************************************/

class RGroup: public RElement
{
  public:
    _M QString          m_name;

  public:
    _M Vacuum           RGroup(RData* data);
    _M Vacuum           RGroup(RGroup& group, RData* data);
    _V Vacuum           ~RGroup();
    _M RGroup*          buddy() { return static_cast<RGroup*>(m_buddy); }
    _M QString          name() const { return m_name; }
    _M bool             setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RGROUP_HH */
