#include <RSys/Tests/TestRParser.hh>


void TestRParser::testNotExistingFile()
{
  RParser parser;
  QCOMPARE(parser.open("static/test_not_exist.xls"), false);
}

void TestRParser::testNormalFile()
{
  RParser parser;
  QCOMPARE(parser.open("static/test2.xls"), true);
  QMap<int, RDataType> *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUNKNOWN);
  QCOMPARE((*guesses)[7], RUNKNOWN);

  QList<std::tuple<QString, int, int> > list = parser.guessesList();
  QCOMPARE(list[0], std::make_tuple(R_S("Paramos priemonės"), (int) RMEASURE, 0));
  QCOMPARE(list[1], std::make_tuple(R_S("Padaliniai"), (int) RDIVISION, 1));
  QCOMPARE(list[2], std::make_tuple(R_S("IS"), (int) RSYSTEM, 2));
  QCOMPARE(list[3], std::make_tuple(R_S("IS-Padaliniai"), (int) RDIVISIONSYSTEMS, 3));
  QCOMPARE(list[4], std::make_tuple(R_S("Paramos administravimas"), (int) RDIVISIONMEASURES, 4));
  QCOMPARE(list[5], std::make_tuple(R_S("Paramos kiekiai"), (int) RSUBMISSION, 5));
  QCOMPARE(list[6], std::make_tuple(R_S("Istoriniai duomenys"), (int) RUNKNOWN, 6));
  QCOMPARE(list[7], std::make_tuple(R_S("Istorinė lentelė"), (int) RUNKNOWN, 7));

  RData data;
  QCOMPARE(parser.read(&data, list), true);
  //RIDocument *document = parser.document();
  QMap<int, int> raport = parser.readRaport();

  RMeasurePtrList *measures = data.measures();
  QCOMPARE(raport[0], 27);
  QCOMPARE(measures->at(26)->identifier(), R_S("P4-3"));
  QCOMPARE(measures->at(26)->name(),
           R_S("3. Parama VVG veiklai, įgūdžiams "
               "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(measures->at(1)->name(),
           R_S("2. Naudojimasis konsultavimo paslaugomis"));

}

void TestRParser::testDetectionByColumns()
{
  RParser parser;
  QCOMPARE(parser.open("static/test3.xls"), true);
  QMap<int, RDataType> *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUNKNOWN);
  QCOMPARE((*guesses)[7], RUNKNOWN);

  QList<std::tuple<QString, int, int> > list = parser.guessesList();
  QCOMPARE(list[0], std::make_tuple(R_S("AAAA"), (int) RMEASURE, 0));
  QCOMPARE(list[1], std::make_tuple(R_S("BBBB"), (int) RDIVISION, 1));
  QCOMPARE(list[2], std::make_tuple(R_S("CCCC"), (int) RSYSTEM, 2));
  QCOMPARE(list[3], std::make_tuple(R_S("DDDD"), (int) RDIVISIONSYSTEMS, 3));
  QCOMPARE(list[4], std::make_tuple(R_S("EEEE"), (int) RDIVISIONMEASURES, 4));
  QCOMPARE(list[5], std::make_tuple(R_S("FFFF"), (int) RSUBMISSION, 5));
  QCOMPARE(list[6], std::make_tuple(R_S("Istoriniai duomenys"), (int) RUNKNOWN, 6));
  QCOMPARE(list[7], std::make_tuple(R_S("Istorinė lentelė"), (int) RUNKNOWN, 7));
}
