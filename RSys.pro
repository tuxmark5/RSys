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
  src/RSys/main.cc

HEADERS             +=                          \
  include/RSys/RSys.hh

################################################################################################
