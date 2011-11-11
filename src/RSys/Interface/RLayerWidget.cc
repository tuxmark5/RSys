#include <QtCore/QEvent>
#include <QtGui/QPushButton>
#include <QtGui/QStackedLayout>
#include <RSys/Interface/RLayerWidget.hh>

/********************************************* RS *********************************************/
/*                                        RLayerWidget                                        */
/**********************************************************************************************/

Vacuum RLayerWidget :: RLayerWidget(QWidget* parent):
  QWidget(parent)
{
  new QStackedLayout(this);
}

/**********************************************************************************************/

Vacuum RLayerWidget :: ~RLayerWidget()
{

}

/**********************************************************************************************/

void RLayerWidget :: enterEvent(QEvent* event)
{
  int baseY = 0; //(height() - 3 * 25) / 2;
  QPalette palette = this->palette();

  palette.setBrush(QPalette::Button, palette.highlightedText());
  palette.setBrush(QPalette::Window, palette.highlight());

  for (int i = 0; i < 3; i++)
  {
    QPushButton* button = new QPushButton(this);

    //button->setFlat(true);
    button->setPalette(palette);

    button->setGeometry(10, baseY + 24 * i, 20, 20);
    button->setText("XXXX");
    button->setVisible(true);
  }
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

QString RLayerWidget :: nameAt(int index) const
{
  return QString();
}

/**********************************************************************************************/

int RLayerWidget :: numWidgets() const
{
  return 0;
}

/**********************************************************************************************/

QWidget* RLayerWidget :: widgetAt(int index)
{
  return 0;
}

/**********************************************************************************************/
