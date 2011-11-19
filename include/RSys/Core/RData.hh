#ifndef RSYS_CORE_RDATA_HH
#define RSYS_CORE_RDATA_HH

/**********************************************************************************************/
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
/**********************************************************************************************/
typedef QMultiHash<QString, RUnit*> RUnitMultiHash;
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
    _M RDivisionPtrList       m_divisions;
    _M RMeasurePtrList        m_measures;
    _M RMeasureList           m_measures1;      // planned measures / phantom
    _M RSubmissionPtrList     m_submissions;
    _M RSubmissionPtrList     m_submissions1;   // planned submissions
    _M RSystemPtrList         m_systems;
    _M RUnitMultiHash         m_unitHash[3];
    _M bool                   m_purgeEnabled: 1;

  public:
    _M Vacuum                 RData();
    _M void                   clear();
    _M RDivision*             division(const QString& identifier) const;
    _M RDivisionPtrList*      divisions()     { return &m_divisions; }
    _M RMeasure*              measure(const QString& identifier) const;
    _M RMeasurePtrList*       measures()      { return &m_measures; }
    _M RMeasureList*          measures1()     { return &m_measures1; }
    _M void                   operator = (RData& data);
    _M void                   purgeDivision(RDivision* division);
    _M void                   purgeMeasure(RMeasure* measure);
    _M void                   purgeSystem(RSystem* system);
    _M RSubmissionPtrList*    submissions()   { return &m_submissions; }
    _M RSubmissionPtrList*    submissions1()  { return &m_submissions1; }
    _M RSystem*               system(const QString& identifier) const;
    _M RSystemPtrList*        systems()       { return &m_systems; }

  signals:
    _M void                   elementChanged(RElement* element, int changeType);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDATA_HH */
