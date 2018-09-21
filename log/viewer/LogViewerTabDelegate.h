#ifndef LOGVIEWERTABDELEGATE_H
#define LOGVIEWERTABDELEGATE_H

// Qt
#include <QtWidgets/QStyledItemDelegate>

namespace hb {
namespace logviewer {

class LogViewerTabDelegate final : public QStyledItemDelegate {
    Q_OBJECT
    Q_DISABLE_COPY(LogViewerTabDelegate)

public:
    LogViewerTabDelegate(QObject* parent = nullptr);
    virtual ~LogViewerTabDelegate() = default;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setEditorData(QWidget* editor, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};
} // namespace logviewer
} // namespace hb

#endif
