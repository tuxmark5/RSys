#include <RSys/Tests/RTests.hh>


void run_all_tests(int argc, char *argv[])
{
  TestRXLSDocument test1;
  QTest::qExec(&test1, argc, argv);
}
