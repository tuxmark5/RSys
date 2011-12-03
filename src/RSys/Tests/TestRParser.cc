#include <RSys/Tests/TestRParser.hh>


void TestRParser::checkReadData(RParser *parser, RParser::GuessList list)
{
  RData data;
  QCOMPARE(parser->read(&data, list), true);

  RMeasurePtrList *measures = data.measures();
  QCOMPARE(27, measures->size());
  QCOMPARE(measures->at(26)->identifier(), R_S("P4-3"));
  QCOMPARE(measures->at(26)->name(),
           R_S("3. Parama VVG veiklai, įgūdžiams "
               "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(measures->at(1)->name(),
           R_S("2. Naudojimasis konsultavimo paslaugomis"));

  RDivisionPtrList *divisions = data.divisions();
  QCOMPARE(12, divisions->size());
  QCOMPARE(divisions->at(11)->identifier(), R_S("PA12"));
  QCOMPARE(divisions->at(11)->name(), R_S("Padalinys 12"));

  RSystemPtrList *systems = data.systems();
  QCOMPARE(10, systems->size());
  QCOMPARE(systems->at(9)->identifier(), R_S("IS10"));
  QCOMPARE(systems->at(9)->name(), R_S("Vidaus audito sistema"));

  //QCOMPARE(raport[3], 44);
  QCOMPARE(divisions->size(), 12);
  RSystemPtr system = systems->at(0);
  QCOMPARE(system->identifier(), R_S("IS1"));
  for (int i = 0; i < divisions->size(); i++)
    QCOMPARE(divisions->at(i)->system(system), 1.0);
  QCOMPARE(systems->at(4)->identifier(), R_S("IS5"));
  QCOMPARE(divisions->at(3)->system(systems->at(4)), 0.0);
  QCOMPARE(divisions->at(3)->system(systems->at(7)), 0.0);
  QCOMPARE(divisions->at(3)->system(systems->at(8)), 0.0);
  QCOMPARE(systems->at(8)->identifier(), R_S("IS9"));
  QCOMPARE(divisions->at(8)->system(systems->at(2)), 0.0);
  QCOMPARE(divisions->at(8)->system(systems->at(7)), 0.0);
  QCOMPARE(divisions->at(8)->system(systems->at(8)), 1.0);

  //QCOMPARE(raport[4], 324);
  QCOMPARE(divisions->size(), 12);
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(divisions->at(1)->measure(measures->at(1)), 0.5);
  QCOMPARE(divisions->at(1)->measure(measures->at(4)), 0.0);
  QCOMPARE(divisions->at(1)->measure(measures->at(8)), 0.0);
  QCOMPARE(divisions->at(1)->measure(measures->at(18)), 1.0);
  QCOMPARE(divisions->at(1)->measure(measures->at(26)), 1.0);
  QCOMPARE(divisions->at(8)->identifier(), R_S("PA9"));
  QCOMPARE(measures->at(9)->identifier(), R_S("P1-10"));
  QCOMPARE(divisions->at(8)->measure(measures->at(9)), 0.0);
  QCOMPARE(divisions->at(8)->measure(measures->at(10)), 0.5);
  QCOMPARE(divisions->at(8)->measure(measures->at(11)), 0.0);

  RSubmissionPtrList *submissions = data.submissions();
  QCOMPARE(1242, submissions->size());

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

  list[6] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);
  list[7] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);

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

  list[6] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);
  list[7] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);

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

  list[6] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);
  list[7] = std::make_tuple(R_S("Istoriniai duomenys"), 0x106, 6);

  RData data;
  QCOMPARE(parser.read(&data, list), false);

  RMeasurePtrList *measures = data.measures();
  QCOMPARE(25, measures->size());
  QCOMPARE(measures->at(24)->identifier(), R_S("P4-3"));
  QCOMPARE(measures->at(24)->name(),
           R_S("3. Parama VVG veiklai, įgūdžiams "
               "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(measures->at(24)->isValid(), true);
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(measures->at(1)->name(),
           R_S("2. Naudojimasis konsultavimo paslaugomis"));
  QCOMPARE(measures->at(1)->isValid(), true);
  QCOMPARE(measures->at(2)->identifier(), R_S("P1-4"));
  QCOMPARE(measures->at(2)->name(),
           R_S("4. Ankstyvas pasitraukimas iš prekinės žemės ūkio gamybos"));
  QCOMPARE(measures->at(2)->isValid(), true);
  QCOMPARE(measures->at(5)->identifier(), R_S("P1-7"));
  QCOMPARE(measures->at(5)->name(),
           R_S("7. Miškų ekonominės vertės didinimas"));
  QCOMPARE(measures->at(5)->isValid(), true);
  QCOMPARE(measures->at(6)->identifier(), R_S("P1-9"));
  QCOMPARE(measures->at(6)->name(),
           R_S("9. Žemės ūkio produktų perdirbimas ir "
               "pridėtinės vertės didinimas"));
  QCOMPARE(measures->at(6)->isValid(), true);

  RDivisionPtrList *divisions = data.divisions();
  QCOMPARE(10, divisions->size());
  QCOMPARE(divisions->at(9)->identifier(), R_S("PA12"));
  QCOMPARE(divisions->at(9)->name(), R_S("Padalinys 12"));
  QCOMPARE(divisions->at(9)->isValid(), true);
  QCOMPARE(divisions->at(3)->identifier(), R_S("PA4"));
  QCOMPARE(divisions->at(3)->name(), R_S("Padalinys 4"));
  QCOMPARE(divisions->at(3)->isValid(), true);
  QCOMPARE(divisions->at(4)->identifier(), R_S("PA7"));
  QCOMPARE(divisions->at(4)->name(), R_S("Padalinys 7"));
  QCOMPARE(divisions->at(4)->isValid(), true);

  RSystemPtrList *systems = data.systems();
  QCOMPARE(8, systems->size());
  QCOMPARE(systems->at(7)->identifier(), R_S("IS10"));
  QCOMPARE(systems->at(7)->name(), R_S("Vidaus audito sistema"));
  QCOMPARE(systems->at(7)->isValid(), true);
  QCOMPARE(systems->at(2)->identifier(), R_S("IS3"));
  QCOMPARE(systems->at(2)->name(), R_S("Kontrolės su registrais"));
  QCOMPARE(systems->at(2)->isValid(), true);
  QCOMPARE(systems->at(3)->identifier(), R_S("IS5"));
  QCOMPARE(systems->at(3)->name(), R_S("Duomenų analizės"));
  QCOMPARE(systems->at(3)->isValid(), true);
  QCOMPARE(systems->at(4)->identifier(), R_S("IS7"));
  QCOMPARE(systems->at(4)->name(), R_S("Vaizdų kaupimo ir analizės"));
  QCOMPARE(systems->at(4)->isValid(), true);

  //QCOMPARE(raport[3], 32);
  QCOMPARE(divisions->size(), 10);
  RSystemPtr system = systems->at(0);
  QCOMPARE(system->identifier(), R_S("IS1"));
  for (int i = 0; i < divisions->size(); i++)
    QCOMPARE(divisions->at(i)->system(system), 1.0);
  QCOMPARE(systems->at(4)->identifier(), R_S("IS7"));
  QCOMPARE(divisions->at(3)->system(systems->at(4)), 1.0);
  QCOMPARE(divisions->at(3)->system(systems->at(6)), 0.0);
  QCOMPARE(divisions->at(3)->system(systems->at(7)), 0.0);
  QCOMPARE(systems->at(7)->identifier(), R_S("IS10"));
  QCOMPARE(divisions->at(8)->system(systems->at(2)), 0.0);
  QCOMPARE(divisions->at(8)->system(systems->at(6)), 0.0);
  QCOMPARE(divisions->at(8)->system(systems->at(7)), 0.0);

  //QCOMPARE(raport[4], 250);
  QCOMPARE(divisions->size(), 10);
  QCOMPARE(measures->at(1)->identifier(), R_S("P1-2"));
  QCOMPARE(divisions->at(1)->measure(measures->at(1)), 0.5);
  QCOMPARE(divisions->at(1)->measure(measures->at(4)), 0.0);
  QCOMPARE(divisions->at(1)->measure(measures->at(8)), 0.0);
  QCOMPARE(measures->at(18)->identifier(), R_S("P3-2"));
  QCOMPARE(divisions->at(1)->measure(measures->at(18)), 0.0);
  QCOMPARE(divisions->at(1)->measure(measures->at(24)), 1.0);
  QCOMPARE(divisions->at(6)->identifier(), R_S("PA9"));
  QCOMPARE(measures->at(7)->identifier(), R_S("P1-10"));
  QCOMPARE(divisions->at(6)->measure(measures->at(7)), 0.0);
  QCOMPARE(divisions->at(6)->measure(measures->at(8)), 0.5);
  QCOMPARE(divisions->at(6)->measure(measures->at(9)), 0.0);

  RSubmissionPtrList *submissions = data.submissions();
  QCOMPARE(1145, submissions->size());

  RSubmission *submission = submissions->at(0).get();
  QCOMPARE(submission->measureName(), R_S("P1-1"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2008-01-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2008-01-31"));
  QCOMPARE(submission->count(), 15);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1144).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-10-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-10-31"));
  QCOMPARE(submission->count(), 35);
  QCOMPARE(submission->isValid(), true);

  submission = submissions->at(1137).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2010-10-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2010-10-31"));
  QCOMPARE(submission->count(), 17);

  submission = submissions->at(1138).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-03-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-03-31"));
  QCOMPARE(submission->count(), 43);

  submission = submissions->at(1139).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-04-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-04-30"));
  QCOMPARE(submission->count(), 54);

  submission = submissions->at(1140).get();
  QCOMPARE(submission->measureName(), R_S("P4-3"));
  QCOMPARE(submission->date0().toString("yyyy-MM-dd"),
           R_S("2011-06-01"));
  QCOMPARE(submission->date1().toString("yyyy-MM-dd"),
           R_S("2011-06-30"));
  QCOMPARE(submission->count(), 18);
}
