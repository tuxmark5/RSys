#include <RSys/Tests/TestRValidator.hh>


void TestRValidator::testReadingMeasures()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(0),
           QString::fromUtf8("Paramos priemonės"));

  RValidator validator;
  RData data;
  RMeasureList *measures = data.measures();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);

  QCOMPARE(measures->size(), 27);
  QCOMPARE(
        measures->at(26)->identifier(),
        QString::fromUtf8("P4-3"));
  QCOMPARE(
        measures->at(26)->name(),
        QString::fromUtf8("3. Parama VVG veiklai, įgūdžiams "
                          "įgyti ir aktyviai pritaikyti"));

//for (auto it = measures->begin(); it != measures->end(); it++)
//{
//  qDebug() << "Priemonė: " << (*it)->identifier() << (*it)->name();
//}
}


void TestRValidator::testReadingSystems()
{

  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(2),
           QString::fromUtf8("IS"));

  RValidator validator;
  RData data;
  RSystemList *systems = data.systems();

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

  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(1),
           QString::fromUtf8("Padaliniai"));

  RValidator validator;
  RData data;
  RDivisionList *divisions = data.divisions();

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
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(3),
           QString::fromUtf8("IS-Padaliniai"));

  RValidator validator;
  RData data;
  RDivisionList *divisions = data.divisions();
  RSystemList *systems = data.systems();

  QCOMPARE(validator.validateDivisions(document.tableAt(1), &data), true);
  QCOMPARE(validator.validateSystems(document.tableAt(2), &data), true);
  QCOMPARE(validator.validateDivisionsSystems(document.tableAt(3), &data), true);

  RDivision *division = divisions->at(10);

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
  QCOMPARE(division->m_systemMap[systems->at(0)], true);
  QCOMPARE(division->m_systemMap[systems->at(1)], true);
  QCOMPARE(division->m_systemMap[systems->at(2)], false);
}


void TestRValidator::testReadingDivisionsMeasures()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(4),
           QString::fromUtf8("Paramos administravimas"));

  RValidator validator;
  RData data;
  RDivisionList *divisions = data.divisions();
  RMeasureList *measures = data.measures();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);
  QCOMPARE(validator.validateDivisions(document.tableAt(1), &data), true);
  QCOMPARE(validator.validateDivisionsMeasures(document.tableAt(4), &data), true);

  RDivision *division = divisions->at(6);

  QCOMPARE(
        division->identifier(),
        QString::fromUtf8("PA7"));
  QCOMPARE(
        measures->at(0)->identifier(),
        QString::fromUtf8("p1-1"));
  QCOMPARE(
        measures->at(1)->identifier(),
        QString::fromUtf8("p1-2"));
  QCOMPARE(
        measures->at(2)->identifier(),
        QString::fromUtf8("p1-3"));
  QCOMPARE(
        measures->at(3)->identifier(),
        QString::fromUtf8("p1-4"));
  QCOMPARE(division->m_measureMap[measures->at(0)], 1.0);
  QCOMPARE(division->m_measureMap[measures->at(1)], 0.5);
  QCOMPARE(division->m_measureMap[measures->at(2)], 1.0);
  QCOMPARE(division->m_measureMap[measures->at(3)], 0.0);
}


void TestRValidator::testTableTypeDetection()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
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

  // Neatpažintas
  QCOMPARE(validator.validate(document.tableAt(7), &data), false);
}


void TestRValidator::testImportingXLSFile()
{
  RValidator validator;
  RData data;

  QCOMPARE(validator.validate(
             QString::fromUtf8("../../RSys/static/test2.xls"), &data),
           false);
}
