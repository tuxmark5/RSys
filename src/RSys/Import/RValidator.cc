#include <RSys/Import/RValidator.hh>


bool RValidator::validateMeasures(
  RITable *table, RData *data, RMeasureList *list)
{
  qDebug() << "Veikia 1";
  for (int i = 1; i < table->height(); i++)
  {
    if (table->cell(0, i).isNull())
    {
      qDebug() << i << "Ignoruojame kryptį";
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
      qDebug() << i << "Pridedame priemonę";
      // Priemonė.
      // FIXME: Kryptys yra ignoruojamos.
      RMeasure *measure = new RMeasure(data);
      measure->setIdentifier(table->cell(0, i).toString());
      measure->setName(table->cell(1, i).toString());
      list->append(measure);
      qDebug() << i << "Priemonė prideta: " << list->size();
      // FIXME: Ar nėra kartais šioje vietoje „memory leak“?
    }
  }

  return true;
}
