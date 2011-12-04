#ifndef RSYS_UTIL_RSHARED_DATA_HH
#define RSYS_UTIL_RSHARED_DATA_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RSharedData                                         */
/**********************************************************************************************/

class RSharedData
{
  private:
    _M int            m_numRefs;

  public:
    _M Vacuum         RSharedData():
      m_numRefs(0) { }

    _M int            numRefs()
    { return m_numRefs; }

    _M int            release()
    { return --m_numRefs; }

    _M void           retain()
    { m_numRefs++; }
};

/**********************************************************************************************/

#endif /* RSYS_UTIL_RSHARED_DATA_HH */
