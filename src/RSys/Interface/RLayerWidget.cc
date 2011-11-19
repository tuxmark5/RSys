#include <QtCore/QEvent>
#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>
#include <RSys/Interface/RLayerWidget.hh>

/********************************************* RS *********************************************/
/*                                        RLayerWidget                                        */
/**********************************************************************************************/

Vacuum RLayerWidget :: RLayerWidget(QWidget* parent):
  QWidget(parent),
  m_widget(0)
{
  QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

  layout->setMargin(0);
  layout->setSpacing(0);
}

/**********************************************************************************************/

Vacuum RLayerWidget :: ~RLayerWidget()
{

}

/**********************************************************************************************/

void RLayerWidget :: createButtons(const ButtonCallback& callback)
{
  Q_UNUSED(callback);
}

/**********************************************************************************************/

void RLayerWidget :: enterEvent(QEvent* event)
{
  Q_UNUSED(event);

  int baseY = 20; //(height() - 3 * 25) / 2;
  int i = 0;
  QPalette palette = this->palette();

  palette.setBrush(QPalette::Button, palette.highlightedText());
  palette.setBrush(QPalette::Window, palette.highlight());

  createButtons([baseY, &i, this, &palette](QPushButton* button) -> void
  {
    button->setParent(this);
    button->setGeometry(10, baseY + 24 * i++, 80, 20);
    button->setPalette(palette);
    button->setVisible(true);
  });
}

/**********************************************************************************************/

bool RLayerWidget :: event(QEvent* event)
{
  if (event->type() == QEvent::Polish)
  {

  }

  return QWidget::event(event);
}

/**********************************************************************************************/

void RLayerWidget :: leaveEvent(QEvent* event)
{
  Q_UNUSED(event);

  QList<QPushButton*> buttons = findChildren<QPushButton*>();

  for (auto it = buttons.begin(); it != buttons.end(); ++it)
  {
    (*it)->deleteLater();
  }
}

/**********************************************************************************************/

void RLayerWidget :: setWidget(QWidget* widget)
{
  if (m_widget)
  {
    m_widget->setVisible(false);
    m_widget->deleteLater();
  }

  if ((m_widget = widget))
  {
    layout()->addWidget(m_widget);
    m_widget->lower();
  }
}

/**********************************************************************************************/
