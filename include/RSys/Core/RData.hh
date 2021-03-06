#ifndef RSYS_CORE_RDATA_HH
#define RSYS_CORE_RDATA_HH

/**********************************************************************************************/
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Util/RSignal.hh>
/**********************************************************************************************/
#define R_DATA_GUARD(exp, r, msg, ...) if (!(exp))                  \
  { (*m_data)[RData::errorMessage](R_S(msg) __VA_ARGS__); return r; }
/**********************************************************************************************/
typedef QMultiHash<QString, RUnit*> RUnitMultiHash;
/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

class RData: public QObject, public RSignal
{
  Q_OBJECT

  public:
    _F class RElement;
    _F class RMeasure;
    _F class RSubmission;
    _F class RUnit;

  public:
    _E ChangeType
    {
      TitleOrName   = 0,
      Visibility    = 1
    };

  private:
    _M RUnitMultiHash         m_unitHash[3];
    _M RDivisionPtrList       m_divisions;
    _M RGroupPtrList          m_groups;
    _M RMeasurePtrList        m_measures;
    _M RMeasurePtrList        m_measures1;      // planned measures / phantom
    _M RSubmissionPtrList     m_submissions;
    _M RSubmissionPtrList     m_submissions1;   // planned submissions
    _M RSystemPtrList         m_systems;
    _M RUserPtrList           m_users;
    _M QDate                  m_interval0;
    _M QDate                  m_interval1;
    _M bool                   m_modified: 1;
    _M bool                   m_purgeEnabled: 1;

  public:
    _M Vacuum                 RData();
    _M Vacuum                 ~RData();
    _M void                   calculateIntervals();
    _M void                   clear();
    _M RDivision*             division(RID id) const;
    _M RDivision*             division(const QString& identifier) const;
    _M RDivisionPtrList*      divisions()     { return &m_divisions; }
    _M void                   enableIntervalTracking();
    _M RGroup*                group(RID id) const;
    _M RGroup*                group(const QString& name) const;
    _M RGroupPtrList*         groups() { return &m_groups; }
    _M QDate                  interval0() const { return m_interval0; }
    _M QDate                  interval1() const { return m_interval1; }
    _M bool                   isModified() const { return m_modified; }
    _M RMeasure*              measure(RID id) const;
    _M RMeasure*              measure(const QString& identifier) const;
    _M RMeasurePtrList*       measures()      { return &m_measures; }
    _M RMeasurePtrList*       measures1()     { return &m_measures1; }
    _M void                   modify()        { m_modified = true; }
    _M void                   operator = (RData& data);
    _M void                   purgeDivision(RDivision* division);
    _M void                   purgeMeasure(RMeasure* measure);
    _M void                   purgeSystem(RSystem* system);
    _M void                   setModified(bool modified);
    _M RSubmissionPtrList*    submissions()   { return &m_submissions; }
    _M RSubmissionPtrList*    submissions1()  { return &m_submissions1; }
    _M RSystem*               system(RID id) const;
    _M RSystem*               system(const QString& identifier) const;
    _M RSystemPtrList*        systems()       { return &m_systems; }
    _M RUser*                 user(RID id) const;
    _M RUser*                 user(const QString& userName) const;
    _M RUserPtrList*          users() { return &m_users; }

  private:
    _M void                   calculateIntervals(RSubmissionPtrList* submissions);
    _M void                   onDate0Change(RSubmission* submission, QDate oldDate0);
    _M void                   onDate1Change(RSubmission* submission, QDate oldDate1);
    _M void                   onSubmissionRemoval(RSubmission* submission);
    _M void                   validateSubmissions1();

  signals:
    _M void                   elementChanged(RElement* element, int changeType);
    _M void                   globalIntervalChanged();
    _M void                   visibilityChanged(RUnit* element);

  public:
    _G(void,                  errorMessage, const QString& message);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDATA_HH */
