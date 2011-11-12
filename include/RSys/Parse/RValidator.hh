#ifndef RSYS_PARSE_RVALIDATOR_HH
#define RSYS_PARSE_RVALIDATOR_HH

/**********************************************************************************************/
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Import/RIDocument.hh>
#include <RSys/Import/RXLSDocument.hh>
/********************************************* RS *********************************************/
/*                                         RValidator                                         */
/**********************************************************************************************/

class RValidator: public QObject
{
  Q_OBJECT

  public:
    _M  RDivision *   getDivision(RData *data, const QString &identifier);
    _M  RSystem *     getSystem(RData *data, const QString &identifier);
    _M  RMeasure *    getMeasure(RData *data, const QString &identifier);
    _M  QDate         parseDate(const QVariant &cell);

  public slots:
    _M  bool          validate(const QString &filename, RData *data);
    _M  bool          validate(RIDocument *document, RData *data);
    _M  bool          validate(RITable *table, RData *data);
    _M  bool          validateMeasures(RITable *table, RData *data);
    _M  bool          validateDivisions(RITable *table, RData *data);
    _M  bool          validateSystems(RITable *table, RData *data);
    _M  bool          validateDivisionsSystems(RITable *table, RData *data);
    _M  bool          validateDivisionsMeasures(RITable *table, RData *data);
    _M  bool          validateSubmissions(RITable *table, RData *data);

  signals:
    // FIXME: Kaip galima būtų realizuoti galimybę grupuoti žinutes?
    // Pavyzdžiui, jei turime 200 pranešimų apie to pačio tipo
    // klaidą. Taip pat, kaip užtikrinti ID unikalumą?
    _M  void          log(RMessageLevel level, RID id, QString message);
    _M  void          parsed(double part);
};

/**********************************************************************************************/

#endif /* RSYS_PARSE_RVALIDATOR_HH */
