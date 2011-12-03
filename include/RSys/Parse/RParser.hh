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

  public:
    _T  QMap<int, RDataType>                    GuessMap;
    _T  QList<std::tuple<QString, int, int> >   GuessList;
    _T  QMap<RDataType, RTableTypeGuessInfo>    GuessInfoMap;

  private:

    _M  RIDocument *          m_document;
    _M  GuessMap              m_guesses;
    _M  GuessInfoMap          m_guessInfo;

    // Finds upper left corner of caption row in table. If fails, returns
    // (-1, -1).
    _M  QPoint                findCaptionRow(
                                RITable *table, RTableTypeGuessInfo info);
    _M  QDate                 parseDate(QVariant cell);

    _M  RDataType             guessTableTypeByName(RITable *table);
    _M  RDataType             guessTableTypeByColumns(RITable *table);
    _M  RDataType             guessTableType(RITable *table);
    _M  void                  makeGuessing();

  public:

    _M  Vacuum                RParser();
    _M  Vacuum                RParser(QMap<RDataType, RTableTypeGuessInfo> guessInfo);
    _M  Vacuum                ~RParser();

    _M  bool                  open(const QString &filename);
    _M  bool                  read(RData *data,
                                   QList<std::tuple<QString, int, int> > guesses);
    _M  bool                  readTable(RData *data, RDataType type, RITable *table, QStringList &message);
    _M  bool                  readMeasures(RData *data, RITable *table, QStringList &message);
    _M  bool                  readDivisions(RData *data, RITable *table, QStringList &message);
    _M  bool                  readSystems(RData *data, RITable *table, QStringList &message);
    _M  bool                  readDivisionsSystems(RData *data, RITable *table, QStringList &message);
    _M  bool                  readDivisionsMeasures(RData *data, RITable *table, QStringList &message);
    _M  bool                  readSubmissions(RData *data, RITable *table, QStringList &message);

    _M  GuessMap*             guesses();
    _M  GuessList             guessesList();
    _M  RIDocument*           document();
    _M  GuessInfoMap*         guessInfo();
    _M  QString               nameAt(int index);

  signals:
    _M  void          log(RMessageLevel level, RID id, QString message);
    _M  void          report(QString message);
    _M  void          parsed(double part);

};

#endif // RPARSER_HH
