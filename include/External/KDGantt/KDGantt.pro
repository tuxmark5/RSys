TEMPLATE = subdirs
INSTALL_HEADERS.files = kdganttconstraintgraphicsitem.h \
KDGanttConstraintGraphicsItem \
kdganttglobal.h \
KDGanttGlobal \
kdganttsummaryhandlingproxymodel.h \
KDGanttSummaryHandlingProxyModel \
kdganttforwardingproxymodel.h \
KDGanttForwardingProxyModel \
kdgantttreeviewrowcontroller.h \
KDGanttTreeViewRowController \
kdganttdatetimegrid.h \
KDGanttDateTimeGrid \
kdganttgraphicsscene.h \
KDGanttGraphicsScene \
kdganttgraphicsview.h \
KDGanttGraphicsView \
kdganttproxymodel.h \
KDGanttProxyModel \
kdganttstyleoptionganttitem.h \
KDGanttStyleOptionGanttItem \
kdganttlegend.h \
KDGanttLegend \
kdganttabstractgrid.h \
KDGanttAbstractGrid \
kdganttabstractrowcontroller.h \
KDGanttAbstractRowController \
kdganttconstraintmodel.h \
KDGanttConstraintModel \
kdganttitemdelegate.h \
KDGanttItemDelegate \
kdganttconstraint.h \
KDGanttConstraint \
kdganttview.h \
KDGanttView \
kdganttlistviewrowcontroller.h \
KDGanttListViewRowController \

message( $$INSTALL_HEADERS.path )
INSTALL_HEADERS.path = $$INSTALL_PREFIX/include/KDGantt/
message( $$INSTALL_HEADERS.path )
INSTALLS += INSTALL_HEADERS
