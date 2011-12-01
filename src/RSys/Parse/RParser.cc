#include <RSys/Parse/RParser.hh>


bool RParser::open(const QString &filename)
{
  RXLSDocument *document = new RXLSDocument(filename);
  if (!document->isOpen())
  {
    log(RERROR, 20, R_S("Nepavyko atverti failo „%1“.").arg(filename));
    return false;
  }
  else
  {
    m_document = document;
    makeGuessing();
    return true;
  }
}

bool RParser::readMeasures(RData *data, RITable *table, int tableIndex)
{
  RMeasurePtrList *list = data->measures();
  int added = 0;
  bool errors = false;
  QPoint start = findCaptionRow(table, m_guessInfo[RMEASURE]);
  if (start.x() == -1)
  {
    this->log(
          RERROR, 21,
          R_S("Lakšte „%1“ nepavyko rasti eilutės su stulpelių antraštėmis.")
          .arg(table->title()));
    errors = true;
  }
  else
  {
    int codeColumn = start.x();
    int nameColumn = start.x() + 1;
    for (int rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(codeColumn, rowIndex).isNull())
      {
        // Kryptis.
        // FIXME: Kryptys (ir tuščios eilutės) yra ignoruojamos.
        continue;
      }
      else
      {
        RMeasurePtr measure = new RMeasure(data);
        if (table->cell(nameColumn, rowIndex).isNull())
        {
          errors = true;
          measure->setValid(false);
        }
        // Priemonė.
        // FIXME: Kryptys yra ignoruojamos.
        measure->setIdentifier(table->cell(codeColumn, rowIndex).toString().toUpper());
        measure->setName(table->cell(nameColumn, rowIndex).toString());
        list->append(measure);
        added++;
      }
    }
  }
  m_readRaport[tableIndex] = added;
  return !errors;
}

bool RParser::readDivisions(RData *data, RITable *table, int tableIndex)
{
  RDivisionPtrList *list = data->divisions();
  int added = 0;
  bool errors = false;
  QPoint start = findCaptionRow(table, m_guessInfo[RDIVISION]);
  if (start.x() == -1)
  {
    this->log(
          RERROR, 21,
          R_S("Lakšte „%1“ nepavyko rasti eilutės su stulpelių antraštėmis.")
          .arg(table->title()));
    errors = true;
  }
  else
  {
    int codeColumn = start.x();
    int nameColumn = start.x() + 1;
    for (int rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(codeColumn, rowIndex).isNull() &&
          table->cell(nameColumn, rowIndex).isNull())
      {
        // Tuščios eilutės yra ignoruojamos.
      }
      else
      {
        RDivisionPtr division = new RDivision(data);
        if (table->cell(codeColumn, rowIndex).isNull() ||
            table->cell(nameColumn, rowIndex).isNull())
        {
          errors = true;
          division->setValid(false);
        }
        // Padalinys.
        division->setIdentifier(table->cell(codeColumn, rowIndex).toString().toUpper());
        division->setName(table->cell(nameColumn, rowIndex).toString());
        list->append(division);
        added++;
      }
    }
  }
  m_readRaport[tableIndex] = added;
  return !errors;
}

bool RParser::readSystems(RData *data, RITable *table, int tableIndex)
{
  RSystemPtrList *list = data->systems();
  bool errors = false;
  int added = 0;
  QPoint start = findCaptionRow(table, m_guessInfo[RSYSTEM]);
  if (start.x() == -1)
  {
    this->log(
          RERROR, 21,
          R_S("Lakšte „%1“ nepavyko rasti eilutės su stulpelių antraštėmis.")
          .arg(table->title()));
    errors = true;
  }
  else
  {
    int codeColumn = start.x();
    int nameColumn = start.x() + 1;
    for (int rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(codeColumn, rowIndex).isNull() &&
          table->cell(nameColumn, rowIndex).isNull())
      {
        // Tuščios eilutės yra ignoruojamos.
      }
      else
      {
        RSystemPtr system = new RSystem(data);
        if (table->cell(codeColumn, rowIndex).isNull() ||
            table->cell(nameColumn, rowIndex).isNull())
        {
          errors = true;
          system->setValid(false);
        }
        // Sistema.
        system->setIdentifier(table->cell(codeColumn, rowIndex).toString().toUpper());
        system->setName(table->cell(nameColumn, rowIndex).toString());
        list->append(system);
        added++;
      }
    }
  }
  m_readRaport[tableIndex] = added;
  return !errors;
}

bool RParser::readSubmissions(RData *data, RITable *table, int tableIndex)
{
  RSubmissionPtrList *list = data->submissions();
  int added = 0;
  bool errors = false;
  QPoint start = findCaptionRow(table, m_guessInfo[RSUBMISSION]);
  if (start.x() == -1)
  {
    this->log(
          RERROR, 21,
          R_S("Lakšte „%1“ nepavyko rasti eilutės su stulpelių antraštėmis.")
          .arg(table->title()));
    errors = true;
  }
  else
  {
    int measureColumn = start.x();
    int dateFromColumn = start.x() + 1;
    int dateToColumn = start.x() + 2;
    int amountColumn = start.x() + 3;
    for (int rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(measureColumn, rowIndex).isNull() &&
          table->cell(dateFromColumn, rowIndex).isNull() &&
          table->cell(dateToColumn, rowIndex).isNull() &&
          table->cell(amountColumn, rowIndex).isNull())
      {
        // Tuščios eilutės yra ignoruojamos.
      }
      else
      {
        RSubmissionPtr submission = new RSubmission(data);
        if (table->cell(measureColumn, rowIndex).isNull() ||
            table->cell(dateFromColumn, rowIndex).isNull() ||
            table->cell(dateToColumn, rowIndex).isNull() ||
            table->cell(amountColumn, rowIndex).isNull())
        {
          errors = true;
          submission->setValid(false);
        }
        // Apkrova.
        submission->setMeasureName(
              table->cell(measureColumn,rowIndex).toString().toUpper());
        submission->setDate0(this->parseDate(table->cell(dateFromColumn,rowIndex)));
        submission->setDate1(this->parseDate(table->cell(dateToColumn,rowIndex)));
        submission->setCount(table->cell(amountColumn,rowIndex).toInt());
        if (submission->date0().isNull() ||
            submission->date1().isNull() ||
            submission->count() < 0)
        {
          errors = true;
          submission->setValid(false);
        }
        list->append(submission);
        added++;
      }
    }
  }
  m_readRaport[tableIndex] = added;
  return !errors;
}

bool RParser::readTable(RData *data, RDataType type, RITable *table, int tableIndex)
{
  switch (type)
  {
  case RMEASURE: return readMeasures(data, table, tableIndex);
  case RDIVISION: return readDivisions(data, table, tableIndex);
  case RSYSTEM: return readSystems(data, table, tableIndex);
  case RSUBMISSION: return readSubmissions(data, table, tableIndex);
  //case RUNKNOWN: return false;        TODO: Pritaikyti testus.
  }
  return true;                          // FIXME: Pakeisti, kai bus
                                        // realizuoti visi pasirinkimai.
}

bool RParser::read(RData *data, QList<std::tuple<QString, int, int> > guesses)
{
  bool allOk = true;
  for (auto it : guesses)
  {
    int type = std::get<1>(it);
    int index = std::get<2>(it);
    if (type & 0x100)
    {
      // Ignore.
    }
    else
    {
      allOk &= readTable(data, (RDataType) type, m_document->tableAt(index), index);
    }
  }
  return allOk;
}

QPoint RParser::findCaptionRow(
  RITable *table, RTableTypeGuessInfo info)
{
  if (table->width() >= info.columnsCaptions.size())
  {
    for (int rowIndex = 0; rowIndex < table->height(); rowIndex++)
    {
      for (int colIndex = 0;
           colIndex < table->width() - info.columnsCaptions.size() + 1;
           colIndex++)
      {
        bool found = true;
        int i = 0;
        for (auto variants : info.columnsCaptions)
        {
          bool match = false;
          for (auto variant : variants)
          {
            if (variant == table->cell(colIndex + i, rowIndex).toString())
            {
              match = true;
              break;
            }
          }
          if (!match)
          {
            found = false;
            break;
          }
          i++;
        }
        if (found)
        {
          return QPoint(colIndex, rowIndex);
        }
      }
    }
  }
  return QPoint(-1, -1);
}

QDate RParser::parseDate(QVariant cell)
{
  if (cell.isNull())
  {
    return QDate();
  }
  else if (cell.toDate().isValid())
  {
    return cell.toDate();
  }
  else
  {
    auto seconds = (cell.toLongLong() - 25569) * 86400000;
    if (seconds < 0)
    {
      return QDate();
    }
    else
    {
      return QDateTime::fromMSecsSinceEpoch(seconds).date();
    }
  }
}

RDataType RParser::guessTableTypeByName(RITable *table)
{
  for (auto info = m_guessInfo.begin(); info != m_guessInfo.end(); info++)
  {
    for (auto name : info.value().tableName)
    {
      if (table->title().toLower() == name.toLower())
      {
        return info.key();
      }
    }
  }
  return RUNKNOWN;
}

RDataType RParser::guessTableTypeByColumns(RITable *table)
{
  for (auto it = m_guessInfo.begin(); it != m_guessInfo.end(); it++)
  {
    const RTableTypeGuessInfo info = it.value();
    QPoint point = findCaptionRow(table, it.value());
    if (point.x() != -1)
    {
      return it.key();
    }
  }
  return RUNKNOWN;
}

RDataType RParser::guessTableType(RITable *table)
{
  RDataType guess = guessTableTypeByName(table);
  if (guess == RUNKNOWN)
  {
    guess = guessTableTypeByColumns(table);
  }
  return guess;
}

void RParser::makeGuessing()
{
  for (int i = 0; i < m_document->numTables(); i++)
  {
    m_guesses[i] = guessTableType(m_document->tableAt(i));
  }
}

RParser::RParser()
{
  m_document = NULL;
  m_guessInfo[RMEASURE] = RTableTypeGuessInfo(
        (QStringList() << R_S("Paramos priemones") << R_S("Paramos priemonės")),
        (QList<QStringList>()
         << (QStringList() << R_S("Kodas"))
         << (QStringList() << R_S("Paramos priemonė") << R_S("Paramos priemone"))
         )
        );
  m_guessInfo[RDIVISION] = RTableTypeGuessInfo(
        (QStringList() << R_S("Padaliniai")),
        (QList<QStringList>()
         << (QStringList() << R_S("Kodas"))
         << (QStringList() << R_S("Padalinys") << R_S("Padaliniai"))
         )
        );
  m_guessInfo[RSYSTEM] = RTableTypeGuessInfo(
        (QStringList()
         << R_S("IS")
         << R_S("Informacinės sistemos")
         << R_S("Informacines sistemos")),
        (QList<QStringList>()
         << (QStringList() << R_S("Kodas"))
         << (QStringList()
             << R_S("IS")
             << R_S("Informacinė sistema")
             << R_S("Informacine sistema")
             << R_S("Informacinės sistemos")
             << R_S("Informacines sistemos"))
         )
        );
  m_guessInfo[RDIVISIONSYSTEMS] = RTableTypeGuessInfo(
        (QStringList()
         << R_S("IS-Padaliniai")
         << R_S("Padaliniai-IS")),
        (QList<QStringList>()
         << (QStringList()
             << R_S("IS/Padalinys")
             << R_S("Informacinė sistema/Padalinys")
             << R_S("Informacinės sistemos/Padalinys")
             << R_S("Informacine sistema/Padalinys")
             << R_S("Informacines sistemos/Padalinys")
             << R_S("IS/Padaliniai")
             << R_S("Informacinė sistema/Padaliniai")
             << R_S("Informacinės sistemos/Padaliniai")
             << R_S("Informacine sistema/Padaliniai")
             << R_S("Informacines sistemos/Padaliniai")
             )
         )
        );
  m_guessInfo[RDIVISIONMEASURES] = RTableTypeGuessInfo(
        (QStringList()
         << R_S("Paramos administravimas")),
        (QList<QStringList>()
         << (QStringList()
             << R_S("Priemonė/Padaliniai")
             << R_S("Priemone/Padaliniai")
             << R_S("Priemonė/Padalinys")
             << R_S("Priemone/Padalinys")
             << R_S("Priemonės/Padaliniai")
             << R_S("Priemones/Padaliniai")
             << R_S("Priemonės/Padalinys")
             << R_S("Priemones/Padalinys"))
         )
        );
  m_guessInfo[RSUBMISSION] = RTableTypeGuessInfo(
        (QStringList()
         << R_S("Paramos kiekiai")),
        (QList<QStringList>()
         << (QStringList()
             << R_S("Priemonės")
             << R_S("Priemones")
             << R_S("Priemonė")
             << R_S("Priemone"))
         << (QStringList()
             << R_S("Nuo"))
         << (QStringList()
             << R_S("Iki"))
         << (QStringList()
             << R_S("Kiekis"))
         )
        );
}

RParser::RParser(QMap<RDataType, RTableTypeGuessInfo> guessInfo)
{
  m_document = NULL;
  m_guessInfo = guessInfo;
}

RParser::~RParser()
{
  delete m_document;
}

auto RParser::guesses() -> GuessMap*
{
  return &m_guesses;
}

auto RParser::guessesList() -> GuessList
{
  QList<std::tuple<QString, int, int> > list;
  for (auto it = m_guesses.begin(); it != m_guesses.end(); it++)
  {
    list << std::make_tuple(m_document->nameAt(it.key()), (int) it.value(), it.key());
  }
  return list;
}

auto RParser::readRaport() -> ReadRaport
{
  return m_readRaport;
}

RIDocument* RParser::document()
{
  return m_document;
}

QString RParser::nameAt(int index)
{
  return m_document->nameAt(index);
}

auto RParser::guessInfo() -> GuessInfoMap*
{
  return &m_guessInfo;
}
