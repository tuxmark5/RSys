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

bool RParser::readMeasures(RData *data, RITable *table, QStringList &message)
{
  int rowIndex;
  int codeColumn;
  int nameColumn;
  RMeasurePtrList *list = data->measures();
  int added = 0;
  bool errors = false;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RWARNING, 23,
      R_S(
        "Priemonė, aprašyta lakšte „%1“, %2 eilutėje %3 stulpelyje, "
        "nebuvo pridėta. Priežastis: %4"
        ).arg(table->title())
        .arg(rowIndex + 1).arg(codeColumn + 1).arg(text));
  };
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
    codeColumn = start.x();
    nameColumn = start.x() + 1;
    for (rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
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
        bool correct = measure->setIdentifier(
              table->cell(codeColumn, rowIndex).toString());
        correct &= measure->setName(table->cell(nameColumn, rowIndex).toString());
        if (correct)
        {
          list->append(measure);
          added++;
        }
        else
        {
          errors = true;
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo sėkmingai pridėta informacija "
              "apie %2 naujas paramos priemones.")
          .arg(table->title()).arg(added));
  message << R_S("<li>„%1“ → +%2 paramos priemonės.</li>")
             .arg(table->title()).arg(added);
  conn.disconnect();
  return !errors;
}

bool RParser::readDivisions(RData *data, RITable *table, QStringList &message)
{
  int rowIndex;
  int codeColumn;
  int nameColumn;
  RDivisionPtrList *list = data->divisions();
  int added = 0;
  bool errors = false;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RWARNING, 24,
      R_S(
        "Padalinys, aprašytas lakšte „%1“, %2 eilutėje %3 stulpelyje, "
        "nebuvo pridėtas. Priežastis: %4"
        ).arg(table->title())
        .arg(rowIndex + 1).arg(codeColumn + 1).arg(text));
  };
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
    codeColumn = start.x();
    nameColumn = start.x() + 1;
    for (rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(codeColumn, rowIndex).isNull() &&
          table->cell(nameColumn, rowIndex).isNull())
      {
        // Tuščios eilutės yra ignoruojamos.
      }
      else
      {
        RDivisionPtr division = new RDivision(data);
        bool correct = division->setIdentifier(
              table->cell(codeColumn, rowIndex).toString().toUpper());
        correct &= division->setName(table->cell(nameColumn, rowIndex).toString());
        if (correct)
        {
          list->append(division);
          added++;
        }
        else
        {
          errors = true;
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo sėkmingai pridėta informacija "
              "apie %2 naujus padalinius.")
          .arg(table->title()).arg(added));
  message << R_S("<li>„%1“ → +%2 padaliniai.</li>")
             .arg(table->title()).arg(added);
  conn.disconnect();
  return !errors;
}

bool RParser::readSystems(RData *data, RITable *table, QStringList &message)
{
  int rowIndex;
  int codeColumn;
  int nameColumn;
  RSystemPtrList *list = data->systems();
  bool errors = false;
  int added = 0;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RWARNING, 24,
      R_S(
        "Sistema, aprašyta lakšte „%1“, %2 eilutėje %3 stulpelyje, "
        "nebuvo pridėta. Priežastis: %4"
        ).arg(table->title())
        .arg(rowIndex + 1).arg(codeColumn + 1).arg(text));
  };
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
    codeColumn = start.x();
    nameColumn = start.x() + 1;
    for (rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
    {
      if (table->cell(codeColumn, rowIndex).isNull() &&
          table->cell(nameColumn, rowIndex).isNull())
      {
        // Tuščios eilutės yra ignoruojamos.
      }
      else
      {
        RSystemPtr system = new RSystem(data);
        bool correct = system->setIdentifier(
              table->cell(codeColumn, rowIndex).toString().toUpper());
        correct &= system->setName(table->cell(nameColumn, rowIndex).toString());
        if (correct)
        {
          list->append(system);
          added++;
        }
        else
        {
          errors = true;
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo sėkmingai pridėta informacija "
              "apie %2 naujas sistemas.")
          .arg(table->title()).arg(added));
  message << R_S("<li>„%1“ → +%2 sistemos.</li>")
             .arg(table->title()).arg(added);
  conn.disconnect();
  return !errors;
}

bool RParser::readDivisionsSystems(RData *data, RITable *table, QStringList &message)
{
  bool errors = false;
  int existRelations = 0;
  int nonExistRelations = 0;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RCRITICAL, 28,
      R_S("Įvyko vidinė sistemos klaida: %1").arg(text));
  };
  QPoint start = findCaptionRow(table, m_guessInfo[RDIVISIONSYSTEMS]);
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
    for (int colIndex = start.x() + 1; colIndex < table->width(); colIndex++)
    {
      if (table->cell(colIndex, start.y()).isNull())
      {
        // Praleidžiame stulpelį nepriskirtą jokiam padaliniui.
      }
      else
      {
        QString divisionID = table->cell(
              colIndex, start.y()).toString().trimmed().toUpper();
        RDivisionPtr division = data->division(divisionID);
        if (division)
        {
          for (int rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
          {
            if (table->cell(start.x(), rowIndex).isNull())
            {
              // Praleidžiame eilutę nepriskirtą jokiai sistemai.
            }
            else
            {
              QString systemID = table->cell(
                    start.x(), rowIndex).toString().trimmed().toUpper();
              RSystemPtr system = data->system(systemID);
              if (system)
              {
                if (table->cell(colIndex, rowIndex).toBool())
                {
                  division->setSystem(system, 1.0);
                  existRelations++;
                }
                else
                {
                  division->setSystem(system, 0.0);
                  nonExistRelations++;
                }
              }
              else if (colIndex == start.x() + 1)
              {
                this->log(
                  RWARNING, 31,
                  R_S(
                        "Nepavyko rasti sistemos, kurios "
                        "identifikatorius yra „%1“ "
                        "(„%2“ lakšto %3 eilutės %4 stulpelis)."
                        ).arg(systemID).arg(table->title())
                        .arg(rowIndex + 1).arg(start.x()));
              }
            }
          }
        }
        else
        {
          this->log(
            RWARNING, 30,
            R_S(
                  "Nepavyko rasti padalinio, kurio identifikatorius yra „%1“ "
                  "(„%2“ lakšto %3 eilutės %4 stulpelis)."
                  ).arg(divisionID).arg(table->title())
                  .arg(start.y() + 1).arg(colIndex + 1));
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo atnaujinta informacija apie "
              "padalinių naudojamas informacines sistemas. "
              "(Buvo sukurti %2 naudojimo ir %3 nenaudojimo ryšiai.)")
          .arg(table->title()).arg(existRelations).arg(nonExistRelations));
  message << R_S("<li>„%1“ → %2 naudojimo ir %3 nenaudojimo ryšiai.</li>")
             .arg(table->title()).arg(existRelations).arg(nonExistRelations);
  conn.disconnect();
  return !errors;
}

bool RParser::readDivisionsMeasures(RData *data, RITable *table, QStringList &message)
{
  int rowIndex;
  int colIndex;
  bool errors = false;
  int updatedRelations = 0;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RWARNING, 24,
      R_S(
        "Duomuo, aprašytas lakšte „%1“, %2 eilutėje %3 stulpelyje, "
        "nebuvo pridėtas. Priežastis: %4"
        ).arg(table->title())
        .arg(rowIndex + 1).arg(colIndex + 1).arg(text));
  };
  QPoint start = findCaptionRow(table, m_guessInfo[RDIVISIONMEASURES]);
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
    for (colIndex = start.x() + 1; colIndex < table->width(); colIndex++)
    {
      if (table->cell(colIndex, start.y()).isNull())
      {
        // Praleidžiame stulpelį nepriskirtą jokiam padaliniui.
      }
      else
      {
        QString divisionID = table->cell(
              colIndex, start.y()).toString().trimmed().toUpper();
        RDivisionPtr division = data->division(divisionID);
        if (division)
        {
          for (rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
          {
            if (table->cell(start.x(), rowIndex).isNull())
            {
              // Praleidžiame eilutę nepriskirtą jokiai paramos priemonei.
            }
            else
            {
              QString measureID = table->cell(
                    start.x(), rowIndex).toString().trimmed().toUpper();
              RMeasurePtr measure = data->measure(measureID);
              if (measure)
              {
                bool loadOk;
                double load = table->cell(colIndex, rowIndex).toDouble(&loadOk);
                if (table->cell(colIndex, rowIndex).isNull())
                {
                  loadOk = true;
                  load = 0.0;
                }
                if (loadOk)
                {
                  updatedRelations++;
                  division->setMeasure(measure, load);
                }
                else
                {
                  this->log(
                    RWARNING, 31,
                    R_S(
                          "Nepavyko konvertuoti langelio reikšmės „%1“ "
                          "į slankaus kablelio skaičių."
                          "(„%2“ lakšto %3 eilutės %4 stulpelis)."
                          ).arg(table->cell(colIndex, rowIndex).toString())
                          .arg(table->title()).arg(rowIndex + 1).arg(colIndex + 1));
                }
              }
              else if (colIndex == start.x() + 1)
              {
                this->log(
                  RWARNING, 31,
                  R_S(
                        "Nepavyko rasti priemonės, kurios "
                        "identifikatorius yra „%1“ "
                        "(„%2“ lakšto %3 eilutės %4 stulpelis)."
                        ).arg(measureID).arg(table->title())
                        .arg(rowIndex + 1).arg(start.x()));
              }
            }
          }
        }
        else
        {
          this->log(
            RWARNING, 30,
            R_S(
                  "Nepavyko rasti padalinio, kurio identifikatorius yra „%1“ "
                  "(„%2“ lakšto %3 eilutės %4 stulpelis)."
                  ).arg(divisionID).arg(table->title())
                  .arg(start.y() + 1).arg(colIndex + 1));
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo atnaujinta informacija apie "
              "paramos administravimo sąnaudas. (Buvo atnaujinti "
              "%2 ryšiai.)")
             .arg(table->title()).arg(updatedRelations));
  message << R_S("<li>„%1“ → atnaujinti %2 ryšiai.</li>")
             .arg(table->title()).arg(updatedRelations);
  conn.disconnect();
  return !errors;
}

bool RParser::readSubmissions(RData *data, RITable *table, QStringList &message)
{
  int rowIndex;
  int measureColumn;
  int dateFromColumn;
  int dateToColumn;
  int amountColumn;
  RSubmissionPtrList *list = data->submissions();
  int added = 0;
  bool errors = false;
  RConnection conn = (*data)[RData::errorMessage] << [&](const QString& text)
  {
    this->log(
      RWARNING, 26,
      R_S(
        "Duomuo, aprašytas lakšte „%1“, %2 eilutėje %3 stulpelyje, "
        "nebuvo pridėtas. Priežastis: %4"
        ).arg(table->title())
        .arg(rowIndex + 1).arg(measureColumn + 1).arg(text));
  };
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
    measureColumn = start.x();
    dateFromColumn = start.x() + 1;
    dateToColumn = start.x() + 2;
    amountColumn = start.x() + 3;
    for (rowIndex = start.y() + 1; rowIndex < table->height(); rowIndex++)
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
        bool correct = submission->setMeasureName(
              table->cell(measureColumn,rowIndex).toString().toUpper());
        correct &= submission->setDate0(
              this->parseDate(table->cell(dateFromColumn,rowIndex)));
        correct &= submission->setDate1(
              this->parseDate(table->cell(dateToColumn,rowIndex)));
        bool countOk;
        correct &= submission->setCount(
              table->cell(amountColumn,rowIndex).toInt(&countOk));
        if (!countOk)
        {
          this->log(
            RWARNING, 27,
            R_S(
              "Duomuo, aprašytas lakšte „%1“, %2 eilutėje %3 stulpelyje, "
              "nebuvo pridėtas. Priežastis: kiekis nėra skaičius."
              ).arg(table->title()).arg(rowIndex + 1).arg(measureColumn + 1));
        }
        if (correct && countOk)
        {
          list->append(submission);
          added++;
        }
        else
        {
          errors = true;
        }
      }
    }
  }
  this->log(
          RINFO, 21,
          R_S("Iš lakšto „%1“ buvo sėkmingai pridėta %2 įrašai "
              "apie paramos priemonių administravimą.")
          .arg(table->title()).arg(added));
  message << R_S("<li>„%1“ → +%2 įrašai apie priemonių administravimą.</li>")
             .arg(table->title()).arg(added);
  conn.disconnect();
  return !errors;
}

bool RParser::readTable(RData *data, RDataType type, RITable *table, QStringList &message)
{
  switch (type)
  {
  case RMEASURE: return readMeasures(data, table, message);
  case RDIVISION: return readDivisions(data, table, message);
  case RSYSTEM: return readSystems(data, table, message);
  case RDIVISIONSYSTEMS: return readDivisionsSystems(data, table, message);
  case RDIVISIONMEASURES: return readDivisionsMeasures(data, table, message);
  case RSUBMISSION: return readSubmissions(data, table, message);
  case RUNKNOWN: return false;
  }
  return false;
}

bool RParser::read(RData *data, QList<std::tuple<QString, int, int> > guesses)
{
  bool allOk = true;
  QStringList message;
  message << R_S("<html>");
  message << R_S("<ul>");
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
      allOk &= readTable(
            data, (RDataType) type, m_document->tableAt(index), message);
    }
  }
  message << R_S("</ul>");
  message << R_S("</html>");
  if (!allOk)
    message.insert(1, R_S("<p>Importuojant buvo klaidų. "
                          "Jas galite peržiūrėti žurnale.</p>"));
  report(message.join(R_S("\n")));
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
