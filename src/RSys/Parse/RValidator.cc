#include <RSys/Parse/RValidator.hh>


RDivision *RValidator::getDivision(RData *data, const QString &identifier)
{
  for (auto it = data->divisions()->begin(); it != data->divisions()->end(); it++)
  {
    if ((*it)->identifier() == identifier)
    {
      return *it;
    }
  }
  return NULL;
}


RSystem *RValidator::getSystem(RData *data, const QString &identifier)
{
  for (auto it = data->systems()->begin(); it != data->systems()->end(); it++)
  {
    if ((*it)->identifier() == identifier)
    {
      return *it;
    }
  }
  return NULL;
}


RMeasure *RValidator::getMeasure(RData *data, const QString &identifier)
{
  for (auto it = data->measures()->begin(); it != data->measures()->end(); it++)
  {
    if ((*it)->identifier() == identifier)
    {
      return *it;
    }
  }
  return NULL;
}


QDate RValidator::parseDate(const QVariant &cell)
{
  return QDateTime::fromMSecsSinceEpoch(
        (cell.toLongLong() - 25569) * 86400000).date();
}


bool RValidator::validate(const QString &filename, RData *data)
{
  RXLSDocument document;
  // FIXME: Reiktų, kad document.open grąžintų true jei pavyko atverti
  // failą ir false priešingu atveju.
  // TODO: Patikrinti ar nenusminga, jei failo varde yra lietuviškų
  // raidžių.
  document.open(filename);
  return this->validate(&document, data);
}


bool RValidator::validate(RIDocument *document, RData *data)
{
  bool errors = false;                   // Jei buvo klaidų.
  for (int i = 0; i < document->numTables(); i++)
  {
    if (!this->validate(document->tableAt(i), data))
    {
      this->log(
            RWARNING, 2,
            QString::fromUtf8(
              "Nepavyko atpažinti kokio tipo duomenys pateikti %1 lakšte "
              "„%2“. Duomenys iš jo nebuvo importuoti."
              ).arg(i + 1).arg(document->nameAt(i)));
      errors = true;
    }
  }
  return !errors;
}


bool RValidator::validate(RITable *table, RData *data)
{
  // FIXME: Čia turi būti ne „įhardcodintos“ reikšmės, o nusiskaitomos.
  if (table->title() == QString::fromUtf8("Paramos priemonės"))
  {
    return this->validateMeasures(table, data);
  }
  else if (table->title() == QString::fromUtf8("Padaliniai"))
  {
    return this->validateDivisions(table, data);
  }
  else if (table->title() == QString::fromUtf8("IS"))
  {
    return this->validateSystems(table, data);
  }
  else if (table->title() == QString::fromUtf8("IS-Padaliniai"))
  {
    return this->validateDivisionsSystems(table, data);
  }
  else if (table->title() == QString::fromUtf8("Paramos administravimas"))
  {
    return this->validateDivisionsMeasures(table, data);
  }
  else if (table->title() == QString::fromUtf8("Paramos kiekiai"))
  {
    return this->validateSubmissions(table, data);
  }
  else
  {
    return false;
  }
}


bool RValidator::validateMeasures(RITable *table, RData *data)
{
  RMeasureList *list = data->measures();
  int added = 0;
  bool errors = false;
  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull())
    {
      // Kryptis.
      // FIXME: Kryptys (ir tuščios eilutės) yra ignoruojamos.
      continue;
    }
    else
    {
      if (table->cell(1, i).isNull())
      {
        this->log(
              RWARNING, 3,
              QString::fromUtf8(
                "Praleidžiama „%1“ lakšto %2 eilutė, "
                "nes joje nenurodytas priemonės pavadinimas. "
                "(Nurodytas kodas buvo: „%3“.)")
              .arg(table->title()).arg(i + 1).arg(table->cell(0, i).toString()));
        errors = true;
        continue;
      }
      // Priemonė.
      // FIXME: Kryptys yra ignoruojamos.
      RMeasure *measure = new RMeasure(data);
      measure->setIdentifier(table->cell(0, i).toString().toUpper());
      measure->setName(table->cell(1, i).toString());
      list->append(measure);
      added++;
    }
  }
  this->log(RINFO, 1,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuota informacija "
              "apie %2 paramos priemones."
              ).arg(table->title()).arg(added));

  return !errors;
}


bool RValidator::validateDivisions(RITable *table, RData *data)
{
  RDivisionList *list = data->divisions();
  bool errors = false;                  // Ar buvo klaidų.
  int added = 0;
  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull() && table->cell(1, i).isNull())
    {
      // Tuščios eilutės yra normalu.
      continue;
    }
    if (table->cell(0, i).isNull())
    {
      this->log(
            RWARNING, 4,
            QString::fromUtf8(
              "Praleidžiama „%1“ lakšto %2 eilutė, "
              "nes joje nenurodytas padalinio kodas."
              ).arg(table->title()).arg(i + 1));
      errors = true;
      continue;
    }
    if (table->cell(1, i).isNull())
    {
      this->log(
            RWARNING, 5,
            QString::fromUtf8(
              "Praleidžiama „%1“ lakšto %2 eilutė, "
              "nes joje nenurodytas padalinio pavadinimas."
              ).arg(table->title()).arg(i + 1));
      errors = true;
      continue;
    }
    RDivision *division = new RDivision(data);
    division->setIdentifier(table->cell(0, i).toString().toUpper());
    division->setName(table->cell(1, i).toString());
    list->append(division);
    added++;
  }
  this->log(RINFO, 6,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuota informacija "
              "apie %2 padalinius."
              ).arg(table->title()).arg(added));

  return !errors;
}


bool RValidator::validateSystems(RITable *table, RData *data)
{
  RSystemList *list = data->systems();
  bool errors = false;                  // Ar buvo klaidų.
  int added = 0;
  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull() && table->cell(1, i).isNull())
    {
      // Tuščios eilutės yra normalu.
      continue;
    }
    if (table->cell(0, i).isNull())
    {
      this->log(
            RWARNING, 4,
            QString::fromUtf8(
              "Praleidžiama „%1“ lakšto %2 eilutė, "
              "nes joje nenurodytas sistemos kodas."
              ).arg(table->title()).arg(i + 1));
      errors = true;
      continue;
    }
    if (table->cell(1, i).isNull())
    {
      this->log(
            RWARNING, 5,
            QString::fromUtf8(
              "Praleidžiama „%1“ lakšto %2 eilutė, "
              "nes joje nenurodytas sistemos pavadinimas."
              ).arg(table->title()).arg(i + 1));
      errors = true;
      continue;
    }
    RSystem *system = new RSystem(data);
    system->setIdentifier(table->cell(0, i).toString().toUpper());
    system->setName(table->cell(1, i).toString());
    list->append(system);
    added++;
  }
  this->log(RINFO, 6,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuota informacija "
              "apie %2 informacines sistemas."
              ).arg(table->title()).arg(added));

  return !errors;
}


bool RValidator::validateDivisionsSystems(RITable *table, RData *data)
{
  bool errors = false;
  int updatedRelations = 0;
  for (int i = 1; i < table->width(); i++)
  {
    // TODO: Pridėti visus tikrinimus.
    if (table->cell(i, 2).isNull())
      continue;
    RDivision *division = this->getDivision(
          data, table->cell(i, 2).toString().toUpper());
    if (!division)
    {
      // TODO: Pranešti, kad nebuvo rastas padalinys.
      qDebug() << "Nerastas padalinys: " << table->cell(i, 2).toString();
      errors = true;
    }
    else
    {
      for (int j = 3; j < table->height() - 1; j++)
      {
        if (table->cell(0, j).isNull()) {
          continue;
          }
        if (!table->cell(i, j).toBool()) {
          continue;
          }
        RSystem *system = this->getSystem(
              data, table->cell(0, j).toString().toUpper());
        if (!system)
        {
          // TODO: Pranešti, kad nebuvo rasta sistema.
          qDebug() << "Nerasta sistema." << table->title() << 0 << j << table->cell(0, j).toString();
          errors = true;
        }
        else
        {
          division->m_systemMap[system] = table->cell(i, j).toDouble();
          updatedRelations++;
        }
      }
    }
  }
  this->log(RINFO, 7,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuoti %2 padalinių – "
              "informacinių sistemų ryšiai."
              ).arg(table->title()).arg(updatedRelations));
  return !errors;
}


bool RValidator::validateDivisionsMeasures(RITable *table, RData *data)
{
  bool errors = false;
  int updatedRelations = 0;
  for (int i = 1; i < table->width(); i++)
  {
    // TODO: Pridėti visus tikrinimus.
    if (table->cell(i, 2).isNull())
      continue;
    if (table->cell(i, 2).toString() == QString::fromUtf8("Iš viso laiko"))
      continue;
    RDivision *division = this->getDivision(
          data, table->cell(i, 2).toString().toUpper());
    if (!division)
    {
      // TODO: Pranešti, kad nebuvo rastas padalinys.
      qDebug() << "Nerastas padalinys: " << table->cell(i, 2).toString();
      errors = true;
    }
    else
    {
      for (int j = 3; j < table->height() - 1; j++)
      {
        if (table->cell(0, j).isNull()) {
          continue;
          }
        if (table->cell(i, j).isNull()) {
          continue;
          }
        RMeasure *measure = this->getMeasure(
              data, table->cell(0, j).toString().toUpper());
        if (!measure)
        {
          // TODO: Pranešti, kad nebuvo rasta sistema.
          qDebug() << "Nerasta priemonė." << table->title() << 0 << j << table->cell(0, j).toString();
          errors = true;
        }
        else
        {
          division->m_measureMap[measure] = table->cell(i, j).toDouble();
          updatedRelations++;
        }
      }
    }
  }
  this->log(RINFO, 8,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuoti %2 padalinių – "
              "paramos priemonių ryšiai."
              ).arg(table->title()).arg(updatedRelations));
  return !errors;
}


bool RValidator:: validateSubmissions(RITable *table, RData *data)
{
  RSubmissionList *list = data->submissions();
  int added = 0;
  bool errors = false;

  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull() &&
        table->cell(1, i).isNull() &&
        table->cell(2, i).isNull() &&
        table->cell(3, i).isNull())
    {
      // Ignoruojame tuščias eilutes.
      continue;
    }
    if (table->cell(0, i).isNull() ||
        table->cell(1, i).isNull() ||
        table->cell(2, i).isNull() ||
        table->cell(3, i).isNull())
    {
      this->log(RWARNING, 10,
                QString::fromUtf8(
                  "Praleidžiama „%1“ lakšto %2 eilutė, "
                  "nes joje yra ne vis duomenys."
              ).arg(table->title()).arg(i));
      errors = true;
      continue;
    }
    RSubmission *submission = new RSubmission(data);
    RMeasure *measure = this->getMeasure(
          data, table->cell(0, i).toString().toUpper());
    if (!measure)
    {
      // FIXME: Pridėti pranešimą.
      errors = true;
      continue;
    }
    submission->setMeasure(measure);
    submission->setDate0(this->parseDate(table->cell(1, i)));
    submission->setDate1(this->parseDate(table->cell(2, i)));
    submission->setCount(table->cell(3, i).toInt());
    list->append(submission);
    added++;
  }

  this->log(RINFO, 9,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuoti %2 įrašai "
              "apie paramos priemonių suadministravimą."
              ).arg(table->title()).arg(added));

  return !errors;
}
