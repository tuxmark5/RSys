#include <RSys/Tests/TestRParser.hh>


void TestRParser::testSomething()
{
  // Find captions row.
  // Input: Columns captions.
  RXLSDocument document(QString::fromUtf8("static/test3.xls"));

  RITable *table = document.tableAt(0);
  QCOMPARE(table->title(), R_S("Duomenys"));
  QCOMPARE(table->width(), 6);
  QCOMPARE(table->height(), 1246);

  QList<QStringList> captions;
  captions << (QStringList() << R_S("Priemone") << R_S("Priemonė"));
  captions << (QStringList() << R_S("Nuo"));
  captions << (QStringList() << R_S("Iki"));
  captions << (QStringList() << R_S("Kiekis"));

  for (int rowIndex = 0; rowIndex < table->height(); rowIndex++)
  {
    for (int colIndex = 0; colIndex < table->width() - captions.size() + 1; colIndex++)
    {
      bool found = true;
      int i = 0;
      for (auto variants : captions)
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
        qDebug() << "Rado:" << rowIndex << colIndex;
        return;
      }
    }
  }

}

void TestRParser::testNormalFile()
{
  RParser parser("static/test2.xls");
  QMap<int, RDataType> *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUKNOWN);
  QCOMPARE((*guesses)[7], RUKNOWN);
}
