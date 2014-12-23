// Qt
#include <QtGui/QPainter>
#include <QtWidgets/QTextEdit>
// Local
#include <LogViewerTabDelegate.h>
#include <LogViewerTab.h>

using namespace hb::logviewer;

LogViewerTabDelegate::LogViewerTabDelegate(QObject *parent) :
	QStyledItemDelegate(parent)
{
}


QWidget* LogViewerTabDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if(index.column() == LogViewerTab::COLUMN_TEXT) // Text
	{
		QTextEdit* editor = q_check_ptr( new QTextEdit(parent) );
		editor->setReadOnly(true);

		return editor;
	}
	else
	{
		return QStyledItemDelegate::createEditor(parent, option, index);
	}
}


void LogViewerTabDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	// It is the same procedure for all comboboxes having an integer type as item data.

	if(index.column() == LogViewerTab::COLUMN_TEXT) // Text
	{
		QTextEdit *textEdit = qobject_cast<QTextEdit *>(editor);
		if (textEdit)
		{
			const QString text = index.model()->data(index).toString();
			textEdit->setPlainText(text);
		}
	}
	else
	{
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void LogViewerTabDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	// It is the same procedure for all comboboxes having an integer type as item data.

	if(index.column() == LogViewerTab::COLUMN_TEXT) // Text
	{
		QTextEdit *textEdit = qobject_cast<QTextEdit *>(editor);
		if (textEdit)
		{
			model->setData(index, textEdit->toPlainText());
		}
	}
	else
	{
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void LogViewerTabDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	Q_UNUSED(index);
	editor->setGeometry(option.rect);
}

void LogViewerTabDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::paint(painter, option, index);
}
