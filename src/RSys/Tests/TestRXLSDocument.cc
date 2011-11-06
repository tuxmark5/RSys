#include <RSys/Tests/TestRXLSDocument.hh>


void TestRXLSDocument::testOpenningExampleFile()
{

  RXLSDocument document(QString::fromUtf8("../../RSys/static/test1.xls"));
  QCOMPARE(document.numTables(), 5);

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
  // FIXME: Kodėl lentelės title yra tuščias?
  //QCOMPARE(table->title(), QString::fromUtf8("Padaliniai"));
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
  // FIXME: Kodėl lentelės title yra tuščias?
  //QCOMPARE(table->title(), QString::fromUtf8("IS"));
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
  // FIXME: Kodėl lentelės title yra tuščias?
  //QCOMPARE(table->title(), QString::fromUtf8("IS"));
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
  // FIXME: Kodėl lentelės title yra tuščias?
  //QCOMPARE(table->title(), QString::fromUtf8("IS"));
  QCOMPARE(table->width(), 13);
  QCOMPARE(table->height(), 30);

  QCOMPARE(table->cell(0, 2).toString(),
           QString::fromUtf8("Priemonė/Padaliniai"));
  QCOMPARE(table->cell(1, 2).toString(),
           QString::fromUtf8("PA1"));
  QCOMPARE(table->cell(5, 2).toString(),
           QString::fromUtf8("PA5"));
  QCOMPARE(table->cell(0, 4).toString(),
           QString::fromUtf8("p1-2"));

  QCOMPARE(table->cell(2, 4).toString(),
           QString::fromUtf8("3"));
  QCOMPARE(table->cell(2, 4).toInt(), 3);
  QCOMPARE(table->cell(3, 4).toString(),
           QString::fromUtf8(""));
  QCOMPARE(table->cell(3, 4).toInt(), 0);
}
