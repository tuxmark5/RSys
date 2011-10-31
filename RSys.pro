############################################## RS ##############################################
#                                             RSys                                             #
################################################################################################

CONFIG              += depend_includepath
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

SOURCES             +=                          \
  src/External/ExcelFormat/BasicExcel.cpp       \
  src/External/ExcelFormat/Examples.cpp         \
  src/External/ExcelFormat/ExcelFormat.cpp      \
  src/RSys/Interface/RMeasureModel.cc           \
  src/RSys/Interface/RMainWindow.cc             \
  src/RSys/Interface/RModel1D.cc                \
  src/RSys/Interface/RModel2D.cc                \
  src/RSys/Interface/RUsageTab.cc               \
  src/RSys/main.cc

HEADERS             +=                          \
  include/RSys/RSys.hh                          \
  include/RSys/Core/RData.hh                    \
  include/RSys/Core/RDivision.hh                \
  include/RSys/Core/RElement.hh                 \
  include/RSys/Core/RMeasure.hh                 \
  include/RSys/Core/RSystem.hh                  \
  include/RSys/Import/RITable.hh                \
  include/RSys/Import/RIDocument.hh             \
  include/RSys/Interface/RMeasureModel.hh       \
  include/RSys/Interface/RMainWindow.hh         \
  include/RSys/Interface/RModel1D.hh            \
  include/RSys/Interface/RModel2D.hh            \
  include/RSys/Interface/RUsageTab.hh

################################################################################################
