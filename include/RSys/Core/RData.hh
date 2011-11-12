#ifndef RSYS_CORE_RDATA_HH
#define RSYS_CORE_RDATA_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

class RData: public QObject
{
  Q_OBJECT

  public:
    _F class RElement;
    _F class RUnit;

  public:
    _E ChangeType
    {
      TitleOrName   = 0,
      Visibility    = 1
    };

  private:
    _M RDivisionList      m_divisions;
    _M RMeasureList       m_measures;
    _M RMeasureList       m_measures1;      // planned measures / phantom
    _M RSubmissionList    m_submissions;
    _M RSubmissionList    m_submissions1;   // planned submissions
    _M RSystemList        m_systems;

  public:
    _M Vacuum             RData();
    _M RDivisionList*     divisions()     { return &m_divisions; }
    _M RMeasureList*      measures()      { return &m_measures; }
    _M RMeasureList*      measures1()     { return &m_measures1; }
    _M RSubmissionList*   submissions()   { return &m_submissions; }
    _M RSubmissionList*   submissions1()  { return &m_submissions1; }
    _M RSystemList*       systems()       { return &m_systems; }

  signals:
    _M void               elementChanged(RElement* element, int changeType);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDATA_HH */
