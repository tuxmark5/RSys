#include <RSys/Tests/TestRParser.hh>


void TestRParser::checkReadData(RParser *parser, RParser::GuessList list)
{
  RData data;
  QCOMPARE(parser->read(&data, list), true);
  RParser::ReadRaport raport = parser->readRaport();

  RMeasurePtrList *measures = data.measures();
  QCOMPARE(raport[0], 27);
  QCOMPARE(raport[0], measures->size());
  QCOMPARE(measures->at(26)->identifier(), R_S("P4-3"));
  QCOMPARE(measures->at(26)->name(),
           R_S("3. Parama VVG veiklai, įgūdžiams "
               "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(measures->at(1)->name(),
           R_S("2. Naudojimasis konsultavimo paslaugomis"));

  RDivisionPtrList *divisions = data.divisions();
  QCOMPARE(raport[1], 12);
  QCOMPARE(raport[1], divisions->size());
  QCOMPARE(divisions->at(11)->identifier(), R_S("PA12"));
  QCOMPARE(divisions->at(11)->name(), R_S("Padalinys 12"));

  RSystemPtrList *systems = data.systems();
  QCOMPARE(raport[2], 10);
  QCOMPARE(raport[2], systems->size());
  QCOMPARE(systems->at(9)->identifier(), R_S("IS10"));
  QCOMPARE(systems->at(9)->name(), R_S("Vidaus audito sistema"));

  RParser::DivisionSystems *divisionsSystems = parser->divisionsSystems();
  QCOMPARE(raport[3], 44);
  QCOMPARE(divisionsSystems->size(), 12);
  QCOMPARE(divisionsSystems->operator [](R_S("PA1")).size(), 5);
  QCOMPARE(divisionsSystems->operator [](R_S("PA3")).size(), 4);
  QCOMPARE(divisionsSystems->operator [](R_S("PA9")).size(), 4);

//for (auto it = divisionsSystems->begin(); it != divisionsSystems->end(); it++)
//{
//  qDebug() << it.key() << it.value();
//}

  RSubmissionPtrList *submissions = data.submissions();
  QCOMPARE(raport[5], 1242);
  QCOMPARE(raport[5], submissions->size());

  RSubmission *submission = submissions->at(0).get();
  QCOMPARE(submission->measureName(), R_S("P1-1"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2008-01-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2008-01-31"));
  QCOMPARE(submission->count(), 15);

  submission = submissions->at(1241).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-10-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-10-31"));
  QCOMPARE(submission->count(), 35);

}

void TestRParser::testNotExistingFile()
{
  RParser parser;
  QCOMPARE(parser.open("static/test_not_exist.xls"), false);
}

void TestRParser::testNormalFile()
{
  RParser parser;
  QCOMPARE(parser.open("static/test2.xls"), true);
  //QMap<int, RDataType> *guesses = parser.guesses();
  RParser::GuessMap *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUNKNOWN);
  QCOMPARE((*guesses)[7], RUNKNOWN);

  RParser::GuessList list = parser.guessesList();
  QCOMPARE(list[0], std::make_tuple(R_S("Paramos priemonės"), (int) RMEASURE, 0));
  QCOMPARE(list[1], std::make_tuple(R_S("Padaliniai"), (int) RDIVISION, 1));
  QCOMPARE(list[2], std::make_tuple(R_S("IS"), (int) RSYSTEM, 2));
  QCOMPARE(list[3], std::make_tuple(R_S("IS-Padaliniai"), (int) RDIVISIONSYSTEMS, 3));
  QCOMPARE(list[4], std::make_tuple(R_S("Paramos administravimas"), (int) RDIVISIONMEASURES, 4));
  QCOMPARE(list[5], std::make_tuple(R_S("Paramos kiekiai"), (int) RSUBMISSION, 5));
  QCOMPARE(list[6], std::make_tuple(R_S("Istoriniai duomenys"), (int) RUNKNOWN, 6));
  QCOMPARE(list[7], std::make_tuple(R_S("Istorinė lentelė"), (int) RUNKNOWN, 7));

  checkReadData(&parser, list);

}

void TestRParser::testDetectionByColumns()
{
  RParser parser;
  QCOMPARE(parser.open("static/test3.xls"), true);
  RParser::GuessMap *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUNKNOWN);
  QCOMPARE((*guesses)[7], RUNKNOWN);

  RParser::GuessList list = parser.guessesList();
  QCOMPARE(list[0], std::make_tuple(R_S("AAAA"), (int) RMEASURE, 0));
  QCOMPARE(list[1], std::make_tuple(R_S("BBBB"), (int) RDIVISION, 1));
  QCOMPARE(list[2], std::make_tuple(R_S("CCCC"), (int) RSYSTEM, 2));
  QCOMPARE(list[3], std::make_tuple(R_S("DDDD"), (int) RDIVISIONSYSTEMS, 3));
  QCOMPARE(list[4], std::make_tuple(R_S("EEEE"), (int) RDIVISIONMEASURES, 4));
  QCOMPARE(list[5], std::make_tuple(R_S("FFFF"), (int) RSUBMISSION, 5));
  QCOMPARE(list[6], std::make_tuple(R_S("Istoriniai duomenys"), (int) RUNKNOWN, 6));
  QCOMPARE(list[7], std::make_tuple(R_S("Istorinė lentelė"), (int) RUNKNOWN, 7));

  checkReadData(&parser, list);
}

void TestRParser::testWithMissingData()
{
  RParser parser;
  QCOMPARE(parser.open("static/test4.xls"), true);
  RParser::GuessMap *guesses = parser.guesses();

  QCOMPARE((*guesses)[0], RMEASURE);
  QCOMPARE((*guesses)[1], RDIVISION);
  QCOMPARE((*guesses)[2], RSYSTEM);
  QCOMPARE((*guesses)[3], RDIVISIONSYSTEMS);
  QCOMPARE((*guesses)[4], RDIVISIONMEASURES);
  QCOMPARE((*guesses)[5], RSUBMISSION);
  QCOMPARE((*guesses)[6], RUNKNOWN);
  QCOMPARE((*guesses)[7], RUNKNOWN);

  RParser::GuessList list = parser.guessesList();
  QCOMPARE(list[0], std::make_tuple(R_S("AAAA"), (int) RMEASURE, 0));
  QCOMPARE(list[1], std::make_tuple(R_S("BBBB"), (int) RDIVISION, 1));
  QCOMPARE(list[2], std::make_tuple(R_S("CCCC"), (int) RSYSTEM, 2));
  QCOMPARE(list[3], std::make_tuple(R_S("DDDD"), (int) RDIVISIONSYSTEMS, 3));
  QCOMPARE(list[4], std::make_tuple(R_S("EEEE"), (int) RDIVISIONMEASURES, 4));
  QCOMPARE(list[5], std::make_tuple(R_S("FFFF"), (int) RSUBMISSION, 5));
  QCOMPARE(list[6], std::make_tuple(R_S("Istoriniai duomenys"), (int) RUNKNOWN, 6));
  QCOMPARE(list[7], std::make_tuple(R_S("Istorinė lentelė"), (int) RUNKNOWN, 7));

  RData data;
  QCOMPARE(parser.read(&data, list), false);
  RParser::ReadRaport raport = parser.readRaport();

  RMeasurePtrList *measures = data.measures();
  QCOMPARE(raport[0], 27);
  QCOMPARE(raport[0], measures->size());
  QCOMPARE(measures->at(26)->identifier(), R_S("P4-3"));
  QCOMPARE(measures->at(26)->name(),
           R_S("3. Parama VVG veiklai, įgūdžiams "
               "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(measures->at(26)->isValid(), true);
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(measures->at(1)->name(),
           R_S("2. Naudojimasis konsultavimo paslaugomis"));
  QCOMPARE(measures->at(1)->isValid(), true);
  QCOMPARE(measures->at(2)->identifier(), R_S("P1-3"));
  QCOMPARE(measures->at(2)->name().isNull(), true);
  QCOMPARE(measures->at(2)->isValid(), false);
  QCOMPARE(measures->at(7)->identifier(), R_S("P1-8"));
  QCOMPARE(measures->at(7)->name().isNull(), true);
  QCOMPARE(measures->at(7)->isValid(), false);

  RDivisionPtrList *divisions = data.divisions();
  QCOMPARE(raport[1], 12);
  QCOMPARE(raport[1], divisions->size());
  QCOMPARE(divisions->at(11)->identifier(), R_S("PA12"));
  QCOMPARE(divisions->at(11)->name(), R_S("Padalinys 12"));
  QCOMPARE(divisions->at(11)->isValid(), true);
  QCOMPARE(divisions->at(4)->identifier().isNull(), true);
  QCOMPARE(divisions->at(4)->name(), R_S("Padalinys 5"));
  QCOMPARE(divisions->at(4)->isValid(), false);
  QCOMPARE(divisions->at(5)->identifier(), R_S("PA6"));
  QCOMPARE(divisions->at(5)->name().isNull(), true);
  QCOMPARE(divisions->at(5)->isValid(), false);

  RSystemPtrList *systems = data.systems();
  QCOMPARE(systems->size(), 10);
  QCOMPARE(systems->at(9)->identifier(), R_S("IS10"));
  QCOMPARE(systems->at(9)->name(), R_S("Vidaus audito sistema"));
  QCOMPARE(systems->at(9)->isValid(), true);
  QCOMPARE(systems->at(3)->identifier(), R_S("IS4"));
  QCOMPARE(systems->at(3)->name().isNull(), true);
  QCOMPARE(systems->at(3)->isValid(), false);
  QCOMPARE(systems->at(5)->identifier().isNull(), true);
  QCOMPARE(systems->at(5)->name(), R_S("Dokumentų valdymo"));
  QCOMPARE(systems->at(5)->isValid(), false);

  RParser::DivisionSystems *divisionsSystems = parser.divisionsSystems();
  QCOMPARE(raport[3], 44);
  QCOMPARE(divisionsSystems->size(), 12);
  QCOMPARE(divisionsSystems->operator [](R_S("PA1")).size(), 5);
  QCOMPARE(divisionsSystems->operator [](R_S("PA3")).size(), 4);
  QCOMPARE(divisionsSystems->operator [](R_S("PA9")).size(), 4);

  RSubmissionPtrList *submissions = data.submissions();
  QCOMPARE(raport[5], 1242);
  QCOMPARE(raport[5], submissions->size());

  RSubmission *submission = submissions->at(0).get();
  QCOMPARE(submission->measureName(), R_S("P1-1"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2008-01-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2008-01-31"));
  QCOMPARE(submission->count(), 15);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1241).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-10-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-10-31"));
  QCOMPARE(submission->count(), 35);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1230).get();
  QCOMPARE(submission->measureName().isNull(), true);
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2010-11-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2010-11-30"));
  QCOMPARE(submission->count(), 15);
  QCOMPARE(submission->isValid(), false);

  submission = submissions->at(1231).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().isNull(), true);
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2010-12-31"));
  QCOMPARE(submission->count(), 13);
  QCOMPARE(submission->isValid(), false);

  submission = submissions->at(1232).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-01-01"));
  QCOMPARE(submission->date1().isNull(), true);
  QCOMPARE(submission->count(), 24);
  QCOMPARE(submission->isValid(), false);

  submission = submissions->at(1233).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-02-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-02-28"));
  QCOMPARE(submission->count(), 0);
  QCOMPARE(submission->isValid(), false);

  submission = submissions->at(1234).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-03-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-03-31"));
  QCOMPARE(submission->count(), 43);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1235).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-04-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-04-30"));
  QCOMPARE(submission->count(), 54);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1236).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().isNull(), true);
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-05-31"));
  QCOMPARE(submission->count(), 58);
  QCOMPARE(submission->isValid(), false);
}
