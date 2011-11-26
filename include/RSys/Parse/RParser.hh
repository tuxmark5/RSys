#ifndef RPARSER_HH
#define RPARSER_HH

#include <QStringList>
#include <QPoint>

#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Import/RIDocument.hh>
#include <RSys/Import/RXLSDocument.hh>


/*
 * RParser is responsible for extracting RData from RIDocument.

 Workflow:

  1.  Read in Document.
  2.  For each table in document:

    1.  guessTableType:

      1.  try to guess by table name if success return;
      2.  find captions row if sucess return;
      3.  return error;

  3.  Return tables to guesses mapping.

 */

struct RTableTypeGuessInfo
{
  QStringList tableName;
  QList<QStringList> columnsCaptions;

  _M  Vacuum    RTableTypeGuessInfo();
  _M  Vacuum    RTableTypeGuessInfo(
                  QStringList name,
                  QList<QStringList> captions);
};


class RParser: public QObject
{
  Q_OBJECT

  private:

    _M  RIDocument            *m_document;
    _M  QMap<int, RDataType>  m_guesses;
    _M  QMap<RDataType, RTableTypeGuessInfo>
                              m_guessInfo;

    // Finds upper left corner of caption row in table. If fails, returns
    // Null point.
    _M  QPoint                findCaptionRow(
                                RITable *table, RTableTypeGuessInfo info);

    _M  RDataType             guessTableTypeByName(RITable *table);
    _M  RDataType             guessTableTypeByColumns(RITable *table);
    _M  RDataType             guessTableType(RITable *table);
    _M  void                  makeGuessing();

  public:

    // TODO: Handle file open failure.
    _M  Vacuum                RParser(const QString &filename);
    _M  Vacuum                RParser(const QString &filename,
                                      QMap<RDataType, RTableTypeGuessInfo> guessInfo);
    _M  Vacuum                ~RParser();

    _M  QMap<int, RDataType>* guesses();
    _M  RIDocument*           document();
    _M  QMap<RDataType, RTableTypeGuessInfo>*
                              guessInfo();
    _M  QString               nameAt(int index);

};

#endif // RPARSER_HH
