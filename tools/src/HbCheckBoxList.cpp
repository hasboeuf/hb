// Qt
#include <QtWidgets/QApplication>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
// Hb
#include "HbCheckBoxList.h"

using namespace hb::tools;

// internal private delegate
class HbCheckBoxListDelegate : public QItemDelegate
{
private slots:

signals:

public:
    HbCheckBoxListDelegate(QObject *parent = 0) : QItemDelegate(parent)
    {

    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
    {
        QCheckBox *editor = new QCheckBox(parent);

        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {

        QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
        checkBox->setText(index.data(Qt::DisplayRole).toString());
        checkBox->setChecked(index.data(Qt::UserRole).toBool());

    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
        bool value = checkBox->isChecked();

        QMap<int,QVariant> data;
        data.insert(Qt::DisplayRole,checkBox->text());
        data.insert(Qt::UserRole,value);

        model->setItemData(index, data);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{

        //Get item data
        bool value = index.data(Qt::UserRole).toBool();
        QString text = index.data(Qt::DisplayRole).toString();

        // fill style options with item data
        const QStyle *style = QApplication::style();
        QStyleOptionButton opt;
        opt.state |= value ? QStyle::State_On : QStyle::State_Off;
        opt.state |= QStyle::State_Enabled;
        opt.text = text;
        opt.rect = option.rect;

        // draw item data as CheckBox
        style->drawControl(QStyle::CE_CheckBox,&opt,painter);

    }
   /*
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
       {
             //get the value from the editor (CheckBox)
             QCheckBox *myEditor = static_cast<QCheckBox*>(editor);
             bool value = myEditor->isChecked();

             //set model data
             QMap<int,QVariant> data;
             data.insert(Qt::DisplayRole,myEditor->text());
             data.insert(Qt::UserRole,value);
             model->setItemData(index,data);
       }
*/



    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
    {
        editor->setGeometry(option.rect);
    }
};
/*
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        //Get item data
        bool value = index.data(Qt::UserRole).toBool();
        QString text = index.data(Qt::DisplayRole).toString();

        // fill style options with item data
        const QStyle *style = QApplication::style();
        QStyleOptionButton opt;
        opt.state |= value ? QStyle::State_On : QStyle::State_Off;
        opt.state |= QStyle::State_Enabled;
        opt.text = text;
        opt.rect = option.rect;

        // draw item data as CheckBox
        style->drawControl(QStyle::CE_CheckBox,&opt,painter);
    }





    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        //get the value from the editor (CheckBox)
        QCheckBox *myEditor = static_cast<QCheckBox*>(editor);
        bool value = myEditor->isChecked();

        //set model data
        QMap<int,QVariant> data;
        data.insert(Qt::DisplayRole,myEditor->text());
        data.insert(Qt::UserRole,value);
        model->setItemData(index,data);
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        //set editor data
        QCheckBox *myEditor = static_cast<QCheckBox*>(editor);
        myEditor->setText(index.data(Qt::DisplayRole).toString());
        myEditor->setChecked(index.data(Qt::UserRole).toBool());
    }
*/




HbCheckBoxList::HbCheckBoxList(QWidget *parent) : QComboBox(parent)
{
    HbCheckBoxListDelegate* itemDelegate = new HbCheckBoxListDelegate(this);


    // set delegate items view
    view()->setItemDelegate(itemDelegate);

    // Enable editing on items view
    view()->setEditTriggers(QAbstractItemView::CurrentChanged);

    // set "HbCheckBoxList::eventFilter" as event filter for items view
    view()->viewport()->installEventFilter(this);



    // it just cool to have it as defualt ;)
    //view()->setAlternatingRowColors(true);

}

HbCheckBoxList::~HbCheckBoxList(){}

void HbCheckBoxList::onCheckStateChanged()
{


}


/*bool HbCheckBoxList::eventFilter(QObject *object, QEvent *event)
{
    // don't close items view after we release the mouse button
    // by simple eating MouseButtonRelease in viewport of items view
    if(event->type() == QEvent::MouseButtonRelease && object==view()->viewport())
    {
        return true;
    }
    return QComboBox::eventFilter(object,event);
}

*/
/*
void HbCheckBoxList::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));

    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox opt;
    initStyleOption(&opt);

    // if no display text been set , use "..." as default
    if(m_DisplayText.isNull())
            opt.currentText = "...";
        else
            opt.currentText = m_DisplayText;
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    // draw the icon and text
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}

void HbCheckBoxList::setDisplayText(QString text)
{
    m_DisplayText = text;
}

QString HbCheckBoxList::getDisplayText() const
{
    return m_DisplayText;
}*/

