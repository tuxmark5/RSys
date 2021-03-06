#include <RSys/Tests/TestRValidator.hh>


void TestRValidator::testReadingMeasures()
{
  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(0),
           QString::fromUtf8("Paramos priemonės"));

  RValidator validator;
  RData data;
  RMeasurePtrList *measures = data.measures();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);

  QCOMPARE(measures->size(), 27);
  QCOMPARE(
        measures->at(26)->identifier(),
        QString::fromUtf8("P4-3"));
  QCOMPARE(
        measures->at(26)->name(),
        QString::fromUtf8("3. Parama VVG veiklai, įgūdžiams "
                          "įgyti ir aktyviai pritaikyti"));
  QCOMPARE(
        measures->at(1)->identifier(),
        QString::fromUtf8("P1-2"));
  QCOMPARE(
        measures->at(1)->name(),
        QString::fromUtf8("2. Naudojimasis konsultavimo paslaugomis"));

//for (auto it = measures->begin(); it != measures->end(); it++)
//{
//  qDebug() << "Priemonė: " << (*it)->identifier() << (*it)->name();
//}
}


void TestRValidator::testReadingSystems()
{

  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(2),
           QString::fromUtf8("IS"));

  RValidator validator;
  RData data;
  RSystemPtrList *systems = data.systems();

  QCOMPARE(validator.validateSystems(document.tableAt(2), &data), true);

  QCOMPARE(systems->size(), 10);
  QCOMPARE(
        systems->at(9)->identifier(),
        QString::fromUtf8("IS10"));
  QCOMPARE(
        systems->at(9)->name(),
        QString::fromUtf8("Vidaus audito sistema"));
}


void TestRValidator::testReadingDivisions()
{

  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(1),
           QString::fromUtf8("Padaliniai"));

  RValidator validator;
  RData data;
  RDivisionPtrList *divisions = data.divisions();

  QCOMPARE(validator.validateDivisions(document.tableAt(1), &data), true);

  QCOMPARE(divisions->size(), 12);
  QCOMPARE(
        divisions->at(11)->identifier(),
        QString::fromUtf8("PA12"));
  QCOMPARE(
        divisions->at(11)->name(),
        QString::fromUtf8("Padalinys 12"));
}


void TestRValidator::testReadingDivisionsSystems()
{
  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(3),
           QString::fromUtf8("IS-Padaliniai"));

  RValidator validator;
  RData data;
  RDivisionPtrList *divisions = data.divisions();
  RSystemPtrList *systems = data.systems();

  QCOMPARE(validator.validateDivisions(document.tableAt(1), &data), true);
  QCOMPARE(validator.validateSystems(document.tableAt(2), &data), true);
  QCOMPARE(validator.validateDivisionsSystems(document.tableAt(3), &data), true);

  RDivision *division = divisions->at(10).get();

  QCOMPARE(
        division->identifier(),
        QString::fromUtf8("PA11"));
  QCOMPARE(
        systems->at(0)->identifier(),
        QString::fromUtf8("IS1"));
  QCOMPARE(
        systems->at(1)->identifier(),
        QString::fromUtf8("IS2"));
  QCOMPARE(
        systems->at(2)->identifier(),
        QString::fromUtf8("IS3"));
  QCOMPARE(division->m_systemHash[systems->at(0).get()], 1.0);
  QCOMPARE(division->m_systemHash[systems->at(1).get()], 1.0);
  QCOMPARE(division->m_systemHash.contains(systems->at(2).get()), 0);
  QCOMPARE(division->m_systemHash.size(), 2);
}


void TestRValidator::testReadingDivisionsMeasures()
{
  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(4),
           QString::fromUtf8("Paramos administravimas"));

  RValidator validator;
  RData data;
  RDivisionPtrList *divisions = data.divisions();
  RMeasurePtrList *measures = data.measures();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);
  QCOMPARE(validator.validateDivisions(document.tableAt(1), &data), true);
  QCOMPARE(validator.validateDivisionsMeasures(document.tableAt(4), &data), true);

  RDivision *division = divisions->at(6).get();

  QCOMPARE(
        division->identifier(),
        QString::fromUtf8("PA7"));
  QCOMPARE(
        measures->at(0)->identifier(),
        QString::fromUtf8("P1-1"));
  QCOMPARE(
        measures->at(1)->identifier(),
        QString::fromUtf8("P1-2"));
  QCOMPARE(
        measures->at(2)->identifier(),
        QString::fromUtf8("P1-3"));
  QCOMPARE(
        measures->at(3)->identifier(),
        QString::fromUtf8("P1-4"));
  QCOMPARE(division->m_measureHash[measures->at(0).get()], 1.0);
  QCOMPARE(division->m_measureHash[measures->at(1).get()], 0.5);
  QCOMPARE(division->m_measureHash[measures->at(2).get()], 1.0);
  QCOMPARE(division->m_measureHash.contains(measures->at(3).get()), false);
  QCOMPARE(division->m_measureHash.size(), 6);
}


void TestRValidator::testReadingSubmissions()
{
  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  QCOMPARE(document.nameAt(5),
           QString::fromUtf8("Paramos kiekiai"));

  RValidator validator;
  RData data;
  RSubmissionPtrList *submissions = data.submissions();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);
  QCOMPARE(validator.validateSubmissions(document.tableAt(5), &data), true);

  RSubmission *submission = submissions->at(0).get();
  QCOMPARE(
        submission->measure()->identifier(),
        QString::fromUtf8("P1-1"));
  QCOMPARE(
        submission->date0().toString("yyyy-MM-dd"),
        QString::fromUtf8("2008-01-01"));
  QCOMPARE(
        submission->date1().toString("yyyy-MM-dd"),
        QString::fromUtf8("2008-01-31"));
  QCOMPARE(submission->count(), 15);

  QCOMPARE(submissions->size(), 1242);

  submission = submissions->at(1241).get();

  QCOMPARE(
        submission->measure()->identifier(),
        QString::fromUtf8("P4-3"));
  QCOMPARE(
        submission->date0().toString("yyyy-MM-dd"),
        QString::fromUtf8("2011-10-01"));
  QCOMPARE(
        submission->date1().toString("yyyy-MM-dd"),
        QString::fromUtf8("2011-10-31"));
  QCOMPARE(submission->count(), 35);
}

void TestRValidator::testTableTypeDetection()
{
  RXLSDocument document(QString::fromUtf8("static/test2.xls"));
  RValidator validator;
  RData data;

  // Paramos priemonės
  QCOMPARE(validator.validate(document.tableAt(0), &data), true);

  // Padaliniai
  QCOMPARE(validator.validate(document.tableAt(1), &data), true);

  // IS
  QCOMPARE(validator.validate(document.tableAt(2), &data), true);

  // IS-Padaliniai
  QCOMPARE(validator.validate(document.tableAt(3), &data), true);

  // Paramos administravimas
  QCOMPARE(validator.validate(document.tableAt(4), &data), true);

  // Paramos kiekiai
  QCOMPARE(validator.validate(document.tableAt(5), &data), true);

  // Neatpažintas
  QCOMPARE(validator.validate(document.tableAt(7), &data), false);
}


void TestRValidator::testImportingXLSFile()
{
  RValidator validator;
  RData data;

  QCOMPARE(validator.validate(
             QString::fromUtf8("static/test2.xls"), &data),
           false);
}
