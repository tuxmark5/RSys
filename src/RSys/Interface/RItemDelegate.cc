#include <QtGui/QComboBox>
#include <RSys/Core/RData.hh>
#include <RSys/Interface/RItemDelegate.hh>
#include <RSys/Interface/RModel1D.hh>

/**********************************************************************************************/
Q_DECLARE_METATYPE(RMeasurePtr)
/********************************************* RS *********************************************/
/*                                       RItemDelegate                                        */
/**********************************************************************************************/

Vacuum RItemDelegate :: RItemDelegate(RModel1D* measureModel, RData* data, RContainer* container, QObject* parent):
  QItemDelegate(parent),
  m_data(data),
  m_measureModel(measureModel)
{
  m_groupModel = new RModel1D(container, this);
  m_groupModel->m_showAppenderRow = false;
}

/**********************************************************************************************/

Vacuum RItemDelegate :: ~RItemDelegate()
{
}

/**********************************************************************************************/

QWidget* RItemDelegate :: createEditor(QWidget* parent, const QStyleOptionViewItem& option,
  const QModelIndex& index) const
{
  R_GUARD(index.column() == 2, QItemDelegate::createEditor(parent, option, index));

  QComboBox*    comboBox  = new QComboBox(parent);
  int           row       = m_measureModel->translateRow(index.row());
  RMeasure*     measure   = row != -1 ? m_data->measures()->at(row) : 0;

  comboBox->setEditable(true);
  comboBox->setInsertPolicy(QComboBox::InsertAtBottom);
  comboBox->setModel(m_groupModel);
  comboBox->setCurrentIndex(m_groupModel->m_root.find((void*) measure->group()));

  return comboBox;
}

/**********************************************************************************************/

void RItemDelegate :: setEditorData(QWidget* editor, const QModelIndex& index) const
{
  R_GUARD(index.column() == 2, QItemDelegate::setEditorData(editor, index));

  QComboBox*  comboBox    = qobject_cast<QComboBox*>(editor);
  R_GUARD(comboBox, Vacuum);
  int         row         = m_measureModel->translateRow(index.row());
  RMeasure*   measure     = row != -1 ? m_data->measures()->at(row) : 0;
  R_GUARD(measure, Vacuum);
  int         newIndex    = comboBox->currentIndex();
  void*       groupPtr    = newIndex == -1 ? 0 : m_groupModel->m_root.m_children.at(newIndex).m_value;
  RGroup*     group       = static_cast<RGroup*>(groupPtr);
  measure->setGroup(group);
}

/**********************************************************************************************/
