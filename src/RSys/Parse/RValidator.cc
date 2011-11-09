#include <RSys/Parse/RValidator.hh>


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
  else
  {
    return false;
  }
}


bool RValidator::validateMeasures(RITable *table, RData *data)
{
  RMeasureList *list = data->measures();
  int added = 0;
  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull())
    {
      // Kryptis.
      // FIXME: Kryptys yra ignoruojamos.
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
        continue;
      }
      // Priemonė.
      // FIXME: Kryptys yra ignoruojamos.
      RMeasure *measure = new RMeasure(data);
      measure->setIdentifier(table->cell(0, i).toString());
      measure->setName(table->cell(1, i).toString());
      list->append(measure);
      added++;
      // FIXME: Ar nėra kartais šioje vietoje „memory leak“?
    }
  }
  this->log(RINFO, 1,
            QString::fromUtf8(
              "Iš %1 buvo sėkmingai importuota informacija apie %2 paramos priemones."
              ).arg(table->title()).arg(added));

  return true;
}
