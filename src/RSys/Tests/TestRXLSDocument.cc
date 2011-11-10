#include <RSys/Tests/TestRXLSDocument.hh>


void TestRXLSDocument::testOpenningExampleFile()
{

  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
//for (int i = 0; i < document.numTables(); i++)
//{
//  qDebug() << document.nameAt(i);
//}

  QCOMPARE(document.numTables(), 8);

  QCOMPARE(document.nameAt(0),
           QString::fromUtf8("Paramos priemonės"));
  this->checkMeasures(document.tableAt(0));

  QCOMPARE(document.nameAt(1), QString::fromUtf8("Padaliniai"));
  this->checkDivisions(document.tableAt(1));

  QCOMPARE(document.nameAt(2), QString::fromUtf8("IS"));
  this->checkSystems(document.tableAt(2));

  QCOMPARE(document.nameAt(3), QString::fromUtf8("IS-Padaliniai"));
  this->checkDivisionsSystems(document.tableAt(3));

  QCOMPARE(document.nameAt(4),
           QString::fromUtf8("Paramos administravimas"));
  this->checkMeasuresAdministration(document.tableAt(4));

  QCOMPARE(document.nameAt(5),
           QString::fromUtf8("Paramos kiekiai"));
  this->checkAmounts(document.tableAt(5));
  QCOMPARE(document.nameAt(6),
           QString::fromUtf8("Istoriniai duomenys"));
//RXLSTable *table = document.tableAt(6);
//qDebug() << table->height() << table->width();
  QCOMPARE(document.nameAt(7),
           QString::fromUtf8("Istorinė lentelė"));
//table = document.tableAt(7);
//qDebug() << table->height() << table->width();
}


void TestRXLSDocument::checkMeasures(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("Paramos priemonės"));
  QCOMPARE(table->width(), 2);
  QCOMPARE(table->height(), 32);

  QCOMPARE(table->cell(0, 0).toString(),
           QString::fromUtf8("Kodas"));
  QCOMPARE(table->cell(1, 0).toString(),
           QString::fromUtf8("Paramos priemonė"));
  QCOMPARE(table->cell(0, 1).toString(),
           QString::fromUtf8(""));
  QCOMPARE(table->cell(0, 1).isNull(), true);
  QCOMPARE(table->cell(1, 1).toString(),
           QString::fromUtf8(
               "1 KRYPTIS „Žemės, maisto ūkio ir "
               "miškininkystės sektoriaus konkurencingumo didinimas“"));
  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("p1-1"));
  QCOMPARE(table->cell(1, 2).toString(),
           QString::fromUtf8("1. Profesinio mokymo ir informavimo veikla"));
}

void TestRXLSDocument::checkDivisions(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("Padaliniai"));
  QCOMPARE(table->width(), 2);
  QCOMPARE(table->height(), 13);
  QCOMPARE(table->cell(0, 0).toString(), QString::fromUtf8("Kodas"));
  QCOMPARE(table->cell(1, 0).toString(), QString::fromUtf8("Padalinys"));
  QCOMPARE(table->cell(0, 1).toString(), QString::fromUtf8("PA1"));
  QCOMPARE(table->cell(1, 1).toString(), QString::fromUtf8("Padalinys 1"));
  QCOMPARE(table->cell(0, 2).toString(), QString::fromUtf8("PA2"));
  QCOMPARE(table->cell(1, 2).toString(), QString::fromUtf8("Padalinys 2"));
}

void TestRXLSDocument::checkSystems(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("IS"));
  QCOMPARE(table->width(), 2);
  QCOMPARE(table->height(), 11);
  QCOMPARE(table->cell(0, 0).toString(),
           QString::fromUtf8("Kodas"));
  QCOMPARE(table->cell(1, 0).toString(),
           QString::fromUtf8("Informacinės sistemos"));
  QCOMPARE(table->cell(0, 1).toString(),
           QString::fromUtf8("IS1"));
  QCOMPARE(table->cell(1, 1).toString(),
           QString::fromUtf8("Finansų apskaitos ir valdymo"));
  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("IS2"));
  QCOMPARE(table->cell(1, 2).toString(),
           QString::fromUtf8("Išmokų vykdymo"));
}

void TestRXLSDocument::checkDivisionsSystems(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("IS-Padaliniai"));
  QCOMPARE(table->width(), 14);
  QCOMPARE(table->height(), 14);

  for (int i = 0; i < table->width(); i++)
    QCOMPARE(table->cell(i, 1).toString(),
             QString::fromUtf8(""));

  QCOMPARE(table->cell(3, 0).toString(),
           QString::fromUtf8("Padalinių naudojamos informacinės sistemos"));

  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("IS/Padaliniai"));
  QCOMPARE(table->cell(8, 2).toString(),
           QString::fromUtf8("PA8"));
  QCOMPARE(table->cell(13, 2).toString(),
           QString::fromUtf8(""));

  QCOMPARE(table->cell(0, 9).toString(),
           QString::fromUtf8("IS7"));
  QCOMPARE(table->cell(0, 13).toString(),
           QString::fromUtf8(""));

  QCOMPARE(table->cell(1, 3).toString(),
           QString::fromUtf8("1"));
  QCOMPARE(table->cell(1, 3).toInt(), 1);
  QCOMPARE(table->cell(1, 5).toString(),
           QString::fromUtf8(""));
  QCOMPARE(table->cell(1, 5).toInt(), 0);

  for (int i = 0; i < table->width(); i++)
    QCOMPARE(table->cell(i, 13).toString(),
             QString::fromUtf8(""));
  for (int i = 0; i < table->width(); i++)
    QCOMPARE(table->cell(13, i).toString(),
             QString::fromUtf8(""));

}

void TestRXLSDocument::checkMeasuresAdministration(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("Paramos administravimas"));
  QCOMPARE(table->width(), 14);
  QCOMPARE(table->height(), 31);

  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("Priemonė/Padaliniai"));
  QCOMPARE(table->cell(1, 2).toString(),
           QString::fromUtf8("PA1"));
  QCOMPARE(table->cell(5, 2).toString(),
           QString::fromUtf8("PA5"));
  QCOMPARE(table->cell(12, 2).toString(),
           QString::fromUtf8("PA12"));
  QCOMPARE(table->cell(13, 2).toString(),
           QString::fromUtf8("Iš viso laiko"));
  QCOMPARE(table->cell(0, 4).toString(),
           QString::fromUtf8("p1-2"));
  QCOMPARE(table->cell(0, 30).toString(),
           QString::fromUtf8(""));

  QCOMPARE(table->cell(2, 4).toString(),
           QString::fromUtf8("0.5"));
  QCOMPARE(table->cell(2, 4).toInt(), 1);
  QCOMPARE(table->cell(2, 4).toDouble(), 0.5);

  QCOMPARE(table->cell(3, 4).toString(),
           QString::fromUtf8(""));
  QCOMPARE(table->cell(3, 4).toInt(), 0);
  QCOMPARE(table->cell(3, 4).toDouble(), 0.0);

  QCOMPARE(table->cell(2, 30).toString(),
           QString::fromUtf8(""));
  QCOMPARE(table->cell(13, 3).toString(),
           QString::fromUtf8(""));

}

void TestRXLSDocument::checkAmounts(RXLSTable *table)
{
  QCOMPARE(table->title(), QString::fromUtf8("Paramos kiekiai"));
  QCOMPARE(table->width(), 5);
  QCOMPARE(table->height(), 1243);

  QCOMPARE(table->cell(0, 0).toString(),
           QString::fromUtf8("Priemone"));
  QCOMPARE(table->cell(1, 0).toString(),
           QString::fromUtf8("Nuo"));
  QCOMPARE(table->cell(2, 0).toString(),
           QString::fromUtf8("Iki"));
  QCOMPARE(table->cell(3, 0).toString(),
           QString::fromUtf8("Kiekis"));

  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("p1-1"));
  QCOMPARE(table->cell(3, 2).toString(),
           QString::fromUtf8("27"));
  QCOMPARE(table->cell(3, 2).toInt(), 27);

  auto date = [&table](int x, int y)->QDate {
    return QDateTime::fromMSecsSinceEpoch(
        (table->cell(x, y).toLongLong() - 25569) * 86400000).date(); };

  QCOMPARE(date(1, 2).toString("yyyy-MM-dd"), QString("2008-02-01"));
  QCOMPARE(date(2, 2).toString("yyyy-MM-dd"), QString("2008-02-29"));
  QCOMPARE(date(1, 3).toString("yyyy-MM-dd"), QString("2008-03-01"));
  QCOMPARE(date(2, 3).toString("yyyy-MM-dd"), QString("2008-03-31"));
  QCOMPARE(date(1, 4).toString("yyyy-MM-dd"), QString("2008-04-01"));
  QCOMPARE(date(2, 4).toString("yyyy-MM-dd"), QString("2008-04-30"));

}
