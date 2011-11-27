#ifndef RPARSER_HH
#define RPARSER_HH

#include <QStringList>
#include <QPoint>
#include <tuple>

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

  // Call to constructor.
  1.  Create parser object.
  // Call to open.
  1.  Read in Document.
  2.  For each table in document:

    1.  guessTableType:

      1.  try to guess by table name if success return;
      2.  find captions row if sucess return;
      3.  return error;

  // Call to guesses.
  3.  Return tables std::tuple<
        QString tableName,
        int tableType, // 0x100 -- marker that disabled
        int tableIndex>

  // Call to read.
  4.  Read data into given RData.

 */

struct RTableTypeGuessInfo
{
  QStringList tableName;
  QList<QStringList> columnsCaptions;

  _M  Vacuum    RTableTypeGuessInfo() {}
  _M  Vacuum    RTableTypeGuessInfo(
                  QStringList name,
                  QList<QStringList> captions
                  ): tableName(name), columnsCaptions(captions) {}
};


class RParser: public QObject
{
  Q_OBJECT

  private:

    _M  RIDocument *          m_document;
    _M  QMap<int, RDataType>  m_guesses;
    _M  QMap<RDataType, RTableTypeGuessInfo>
                              m_guessInfo;
    _M  QMap<int, int>        m_readRaport;

    // Finds upper left corner of caption row in table. If fails, returns
    // (-1, -1).
    _M  QPoint                findCaptionRow(
                                RITable *table, RTableTypeGuessInfo info);

    _M  RDataType             guessTableTypeByName(RITable *table);
    _M  RDataType             guessTableTypeByColumns(RITable *table);
    _M  RDataType             guessTableType(RITable *table);
    _M  void                  makeGuessing();

  public:

    // TODO: Atskirti failo atidarymą ir Parser kūrimą, kad open galėtų gražinti false.
    _M  Vacuum                RParser();
    _M  Vacuum                RParser(QMap<RDataType, RTableTypeGuessInfo> guessInfo);
    _M  Vacuum                ~RParser();

    _M  bool                  open(const QString &filename);
    _M  bool                  read(RData *data,
                                   QList<std::tuple<QString, int, int> > guesses);
    _M  bool                  readTable(RData *data, RDataType type, RITable *table, int tableIndex);
    _M  bool                  readMeasures(RData *data, RITable *table, int tableIndex);

    _M  QMap<int, RDataType>* guesses();
    _M  QList<std::tuple<QString, int, int> >
                              guessesList();
    _M  QMap<int, int>        readRaport();
    _M  RIDocument*           document();
    _M  QMap<RDataType, RTableTypeGuessInfo>*
                              guessInfo();
    _M  QString               nameAt(int index);

  signals:
    _M  void          log(RMessageLevel level, RID id, QString message);
    _M  void          parsed(double part);

};

#endif // RPARSER_HH
