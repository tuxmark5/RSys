#ifndef RSYS_INTERFACE_RITEM_DELEGATE_HH
#define RSYS_INTERFACE_RITEM_DELEGATE_HH

/**********************************************************************************************/
#include <QtGui/QItemDelegate>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                       RItemDelegate                                        */
/**********************************************************************************************/

class RItemDelegate: public QItemDelegate
{
  Q_OBJECT

  private:
    _M RData*         m_data;
    _M RModel1D*      m_groupModel;
    _M RModel1D*      m_measureModel;

  public:
    _M Vacuum         RItemDelegate(RModel1D* measureModel, RData* data, RContainer* container, QObject* parent = 0);
    _V Vacuum         ~RItemDelegate();

  public:
    _V QWidget*       createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const;
    _V void           setEditorData(QWidget* editor, const QModelIndex& index) const;
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RITEM_DELEGATE_HH */
