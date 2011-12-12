#ifndef RSYS_CORE_RSUBMISSION_HH
#define RSYS_CORE_RSUBMISSION_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <RSys/Core/RElement.hh>
/**********************************************************************************************/

struct RPhantomMeasureDeleter
{
  static void f(RMeasure* measure);
};

/********************************************* RS *********************************************/
/*                                        RSubmission                                         */
/**********************************************************************************************/

class RSubmission: public RElement
{
  protected:
    _M RMeasurePtr      m_measure;
    _M QString          m_measureName;
    _M QDate            m_date0;
    _M QDate            m_date1;
    _M int              m_count;
    _M bool             m_planned: 1;

  public:
    _M Vacuum           RSubmission(RData* data, bool planned = false);
    _M Vacuum           RSubmission(RSubmission& other, RData* data);
    _V Vacuum           ~RSubmission();
    _M int              count() const { return m_count; }
    _M QDate            date0() const { return m_date0; }
    _M QDate            date1() const { return m_date1; }
    _M bool             isPlanned() const { return m_planned; }
    _M RMeasure*        measure() const { return m_measure.get(); }
    _M QString          measureFullName() const;
    _M RID              measureId() const;
    _M QString          measureName() const { return m_measureName; }
    _M void             remove();
    _M bool             setCount(int count);
    _M bool             setDate0(const QDate& date0);
    _M bool             setDate1(const QDate& date1);
    _M void             setMeasure(RMeasure* measure);
    _M void             setMeasureId(RID id);
    _M bool             setMeasureName(const QString& measureName);
    _M void             setMeasure1NameE(const QString& measureName);
    _M void             validate();

  public:
    _G(void,            countChange, RSubmission* submission, int newCount);
    _G(void,            date0Changed, RSubmission* submission, QDate oldDate0);
    _G(void,            date1Changed, RSubmission* submission, QDate oldDate1);
    _G(void,            measureChange, RSubmission* submission, RMeasure* measure);
    _G(void,            submissionRemoval, RSubmission* submission);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RSUBMISSION_HH */
