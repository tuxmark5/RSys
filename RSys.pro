
############################################## RS ##############################################
#                                             RSys                                             #
################################################################################################

CONFIG              += depend_includepath qtestlib
QT                  += core gui sql
TARGET               = RSys
TEMPLATE             = app

################################################################################################

DESTDIR              = bin
ORIGIN               = dist

debug {
  MOC_DIR            = "$$ORIGIN/moc-debug"
  OBJECTS_DIR        = "$$ORIGIN/obj-debug"
  RCC_DIR            = "$$ORIGIN/rcc-debug"
} else:debug {
  MOC_DIR            = "$$ORIGIN/moc-release"
  OBJECTS_DIR        = "$$ORIGIN/obj-release"
  RCC_DIR            = "$$ORIGIN/rcc-release"
}

################################################################################################

INCLUDEPATH         += include include/External include/External/ExcelFormat
QMAKE_CXXFLAGS      += -std=gnu++0x

LIBS                += -L$$PWD/lib -L$$PWD/lib/External -lkdchart
unix:QMAKE_LFLAGS   += -Wl,-rpath $$PWD/lib/External

################################################################################################

SOURCES             +=                              \
  src/External/ExcelFormat/BasicExcel.cpp           \
  src/External/ExcelFormat/ExcelFormat.cpp          \
  src/RSys/Core/RData.cc                            \
  src/RSys/Core/RDivision.cc                        \
  src/RSys/Core/RElement.cc                         \
  src/RSys/Core/RMeasure.cc                         \
  src/RSys/Core/RSubmission.cc                      \
  src/RSys/Core/RSystem.cc                          \
  src/RSys/Core/RUnit.cc                            \
  src/RSys/Import/RXLSDocument.cc                   \
  src/RSys/Import/RXLSTable.cc                      \
  src/RSys/Interface/RAbstractItemModel.cc          \
  src/RSys/Interface/RChart.cc                      \
  src/RSys/Interface/RColumnObserverAdapter.cc      \
  src/RSys/Interface/RDivisionTab.cc                \
  src/RSys/Interface/RIntervalToolBar.cc            \
  src/RSys/Interface/RLayerWidget.cc                \
  src/RSys/Interface/RLoginWidget.cc                \
  src/RSys/Interface/RMainMenuBar.cc                \
  src/RSys/Interface/RMainToolBar.cc                \
  src/RSys/Interface/RMainWindow.cc                 \
  src/RSys/Interface/RMeasureAdmTab.cc              \
  src/RSys/Interface/RMeasureTab.cc                 \
  src/RSys/Interface/RMessage.cc                    \
  src/RSys/Interface/RModel1D.cc                    \
  src/RSys/Interface/RModel2D.cc                    \
  src/RSys/Interface/RPaletteDock.cc                \
  src/RSys/Interface/RPlannedTab.cc                 \
  src/RSys/Interface/RResultsModel.cc               \
  src/RSys/Interface/RRowObserverAdapter.cc         \
  src/RSys/Interface/RSearchForm.cc                 \
  src/RSys/Interface/RStatusWidget.cc               \
  src/RSys/Interface/RTab.cc                        \
  src/RSys/Interface/RTableView.cc                  \
  src/RSys/Interface/RSubmissionTab.cc              \
  src/RSys/Interface/RSummaryTab.cc                 \
  src/RSys/Interface/RSummaryWidget.cc              \
  src/RSys/Interface/RSystemAdmTab.cc               \
  src/RSys/Interface/RSystemTab.cc                  \
  src/RSys/Interface/RUsageTab.cc                   \
  src/RSys/Interface/RUsageWidget.cc                \
  src/RSys/Logic/RCalculator.cc                     \
  src/RSys/Logic/RResults.cc                        \
  src/RSys/Store/RDatabase.cc                       \
  src/RSys/Store/REntity1D.cc                       \
  src/RSys/Tests/RTests.cc                          \
  src/RSys/Tests/TestRXLSDocument.cc                \
  src/RSys/Parse/RValidator.cc                      \
  src/RSys/Tests/TestRValidator.cc                  \
  src/RSys/main.cc

HEADERS             +=                              \
  include/External/ExcelFormat/ExcelFormat.h        \
  include/External/ExcelFormat/BasicExcel.hpp       \
  include/RSys/RSys.hh                              \
  include/RSys/Core/RData.hh                        \
  include/RSys/Core/RDivision.hh                    \
  include/RSys/Core/RElement.hh                     \
  include/RSys/Core/RMeasure.hh                     \
  include/RSys/Core/RSubmission.hh                  \
  include/RSys/Core/RSystem.hh                      \
  include/RSys/Core/RUnit.hh                        \
  include/RSys/Import/RITable.hh                    \
  include/RSys/Import/RIDocument.hh                 \
  include/RSys/Import/RXLSDocument.hh               \
  include/RSys/Import/RXLSTable.hh                  \
  include/RSys/Interface/RAbstractItemModel.hh      \
  include/RSys/Interface/RChart.hh                  \
  include/RSys/Interface/RColumnObserverAdapter.hh  \
  include/RSys/Interface/RDivisionTab.hh            \
  include/RSys/Interface/RIntervalToolBar.hh        \
  include/RSys/Interface/RLayerWidget.hh            \
  include/RSys/Interface/RLoginWidget.hh            \
  include/RSys/Interface/RMainMenuBar.hh            \
  include/RSys/Interface/RMainToolBar.hh            \
  include/RSys/Interface/RMainWindow.hh             \
  include/RSys/Interface/RMeasureAdmTab.hh          \
  include/RSys/Interface/RMeasureTab.hh             \
  include/RSys/Interface/RMessage.hh                \
  include/RSys/Interface/RModel1D.hh                \
  include/RSys/Interface/RModel2D.hh                \
  include/RSys/Interface/RPaletteDock.hh            \
  include/RSys/Interface/RPlannedTab.hh             \
  include/RSys/Interface/RResultsModel.hh           \
  include/RSys/Interface/RRowObserverAdapter.hh     \
  include/RSys/Interface/RSearchForm.hh             \
  include/RSys/Interface/RStatusWidget.hh           \
  include/RSys/Interface/RSubmissionTab.hh          \
  include/RSys/Interface/RSummaryTab.hh             \
  include/RSys/Interface/RSummaryWidget.hh          \
  include/RSys/Interface/RSystemAdmTab.hh           \
  include/RSys/Interface/RSystemTab.hh              \
  include/RSys/Interface/RTab.hh                    \
  include/RSys/Interface/RTableView.hh              \
  include/RSys/Interface/RUsageTab.hh               \
  include/RSys/Interface/RUsageWidget.hh            \
  include/RSys/Logic/RCalculator.hh                 \
  include/RSys/Logic/RResults.hh                    \
  include/RSys/Store/RDatabase.hh                   \
  include/RSys/Store/REntity1D.hh                   \
  include/RSys/Util/RAccessorAdapter.hh             \
  include/RSys/Util/RAlgorithm.hh                   \
  include/RSys/Util/RCompose.hh                     \
  include/RSys/Util/RContainer.hh                   \
  include/RSys/Util/RDynAccessor.hh                 \
  include/RSys/Util/REntity2D.hh                    \
  include/RSys/Util/RFunAccessor.hh                 \
  include/RSys/Util/RFunctional.hh                  \
  include/RSys/Util/RFT.hh                          \
  include/RSys/Util/RJoin.hh                        \
  include/RSys/Util/RMemAccessor.hh                 \
  include/RSys/Util/ROList.hh                       \
  include/RSys/Util/RSharedPtr.hh                   \
  include/RSys/Tests/RTests.hh                      \
  include/RSys/Tests/TestRXLSDocument.hh            \
  include/RSys/Parse/RValidator.hh                  \
  include/RSys/Tests/TestRValidator.hh

################################################################################################

RESOURCES +=                                        \
  res/RResources.qrc

################################################################################################
