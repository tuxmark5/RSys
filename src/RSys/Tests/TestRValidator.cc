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
