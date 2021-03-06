#ifndef LOGVIEWERTAB_H
#define LOGVIEWERTAB_H

// Qt
#include <QtGui/QStandardItem>
// Local
#include <MultipleSortFilterProxyModel.h>
#include <ui_LogViewerTab.h>

class QPropertyAnimation;

namespace hb {
namespace log {
class HbLogMessage;
}

namespace logviewer {
class LogViewerConfig;

using hb::log::HbLogMessage;
using hb::tools::ModelFilter;
using hb::tools::MultipleSortFilterProxyModel;

class LogViewerTab : public QWidget, private hb::logviewer::Ui::LogViewerTab {
    Q_OBJECT
    Q_DISABLE_COPY(LogViewerTab)

    Q_PROPERTY(qreal _freezeAnimationValue READ freezeAnimationValue WRITE setFreezeAnimationValue)

public:
    enum ColumnId : quint8 {
        COLUMN_LEVEL = 0,
        COLUMN_TIME = 1,
        COLUMN_OWNER = 2,
        COLUMN_LINE = 3,
        COLUMN_WHERE = 4, // Convenient = file | func.
        COLUMN_TEXT = 5,
        COLUMN_FILE = 6, // Hidden;
        COLUMN_FUNC = 7, // Hidden.
    };

    LogViewerTab() = delete;
    LogViewerTab(qint32 id,
                 const LogViewerConfig& config,
                 bool rerun = false,
                 ModelFilter* filter = nullptr,
                 ColumnId = COLUMN_OWNER,
                 QWidget* parent = nullptr);
    virtual ~LogViewerTab();

    qint32 id() const;

    void updateView();

    void addEntry(const hb::log::HbLogMessage* msg, bool rerun = false);

public:
    // From GUI
    void onLevelChanged(int index);
    void onFilterTextChanged(const QString& filter);
    void onClearClicked();
    void onFreezeClicked(bool checked);
    void onAdjustToContent();
    void onSaveAsClicked();
    void onOpenNewTab();
    void onCopyCellContent();

    void onRowDoubleClicked(const QModelIndex& index);
    void onCustomContextMenuRequested(const QPoint& pos);

signals:
    void newTabRequest(quint8 column, const QString& value);

private:
    static QString labels(ColumnId col_id);
    static QSet<QString> findAbsoluteFilePath(const QString& file_path, const QString& root_path);

    bool isValidEntry(QList<QStandardItem*>& row);

    void checkMaxBuffer();

    void initTable();

    qreal freezeAnimationValue() const;
    void setFreezeAnimationValue(qreal value);

    quint32 mId;
    QStandardItemModel mModel;
    MultipleSortFilterProxyModel mProxy;
    QStringList mLabels;
    bool mFrozen;
    bool mRerun;
    const LogViewerConfig& mConfig;

    ModelFilter* mFilter;
    quint8 mFilterColumn;

    qreal mFreezeAnimationValue;
    QPropertyAnimation* mFreezeAnimation;
};
} // namespace logviewer
} // namespace hb

#endif
