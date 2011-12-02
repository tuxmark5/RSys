#include <RSys/Tests/RTests.hh>


void run_all_tests(int argc, char *argv[])
{
  TestRXLSDocument test1;
  QTest::qExec(&test1, argc, argv);

  TestRValidator test2;
  QTest::qExec(&test2, argc, argv);

//TestRParser test3;
//QTest::qExec(&test3, argc, argv);
}
