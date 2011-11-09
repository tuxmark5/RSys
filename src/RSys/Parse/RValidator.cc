#include <RSys/Parse/RValidator.hh>


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
              RWARNING,
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
      // FIXME: Ar nėra kartais šioje vietoje „memory leak“?
    }
  }

  return true;
}
