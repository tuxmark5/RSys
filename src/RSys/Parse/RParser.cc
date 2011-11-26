#include <RSys/Parse/RParser.hh>


RIDocument* RParser::open(const QString &filename)
{
  RXLSDocument *document = new RXLSDocument(filename);
  if (!document->isOpen())
  {
    log(RERROR, 20, R_S("Nepavyko atverti failo „%1“.").arg(filename));
  }
  return document;
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

RParser::RParser(const QString &filename)
{
  m_document = open(filename);

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
  makeGuessing();
}

RParser::RParser(
  const QString &filename,
  QMap<RDataType, RTableTypeGuessInfo> guessInfo)
{
  m_document = open(filename);
  m_guessInfo = guessInfo;
  makeGuessing();
}

RParser::~RParser()
{
  delete m_document;
}

QMap<int, RDataType>* RParser::guesses()
{
  return &m_guesses;
}

RIDocument* RParser::document()
{
  return m_document;
}

QString RParser::nameAt(int index)
{
  return m_document->nameAt(index);
}

QMap<RDataType, RTableTypeGuessInfo>* RParser::guessInfo()
{
  return &m_guessInfo;
}
