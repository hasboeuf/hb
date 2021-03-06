// Qt
#include <QtCore/QDebug>
#include <QtCore/QTime>
#include <QtWidgets/QFileDialog>
// Hb
#include <HbLogGuiNotifier.h>
#include <HbLogMessage.h>
#include <outputs/HbLogFileOutput.h>
// Local
#include <LogViewer.h>
#include <LogViewerConfigDialog.h>
#include <LogViewerTab.h>

using namespace hb::logviewer;
using namespace hb::log;

LogViewer::LogViewer(QWidget* parent) : QWidget(parent), Ui::LogViewer() {
    setupUi(this);

    mTabIds = 0;
    mLogNotifier = q_check_ptr(new HbLogGuiNotifier());

    mConfig.loadSettings();

    connect(mLogNotifier, &HbLogGuiNotifier::newLogMessage, this, &LogViewer::onNewLogMessage, Qt::UniqueConnection);
    connect(&mProcessTimer, &QTimer::timeout, this, &LogViewer::processLogMessage);
    connect(qpb_open, &QPushButton::clicked, this, &LogViewer::onOpenFileClicked);
    connect(qpb_configure, &QPushButton::clicked, this, &LogViewer::onConfigureClicked);
    connect(qtw_main, &QTabWidget::tabCloseRequested, this, &LogViewer::onTabCloseRequested);
    connect(
        qsb_refresh_time, (void (QSpinBox::*)(int)) & QSpinBox::valueChanged, this, &LogViewer::onRefreshTimeChanged);

    LogViewerTab* tab_general = q_check_ptr(new LogViewerTab(mTabIds++, mConfig));

    connect(tab_general, &LogViewerTab::newTabRequest, this, &LogViewer::onNewTabRequest);

    mTabs.insert(tab_general->id(), tab_general);
    qtw_main->insertTab(tab_general->id(), tab_general, QStringLiteral("General"));

    mProcessTimer.start(qsb_refresh_time->value());
}

void LogViewer::loadConfigPath(const QString& path) {
    Q_UNUSED(path);

    for (LogViewerTab* tab : mTabs) {
        if (tab)
            tab->updateView();
    }
}

void LogViewer::loadConfigSettings() {
    mConfig.loadSettings();

    for (LogViewerTab* tab : mTabs) {
        if (tab)
            tab->updateView();
    }
}

HbLogGuiNotifier* LogViewer::logNotifier() const {
    return mLogNotifier;
}

void LogViewer::onNewLogMessage(const HbLogMessagePtr& message) {
    HbLogMessage* log = q_check_ptr(new HbLogMessage(*message.data()));

    QMutexLocker locker(&mMutexBuffer);
    mTempBuffer.append(log);
}

void LogViewer::onOpenFileClicked() {
    QString file_path = QFileDialog::getOpenFileName(this, QStringLiteral("Save log"), QString(), QString());
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.close();
        return;
    }

    LogViewerTab* tab = q_check_ptr(new LogViewerTab(mTabIds++, mConfig, true));
    connect(tab, &LogViewerTab::newTabRequest, this, &LogViewer::onNewTabRequest);
    mTabs.insert(tab->id(), tab);
    qtw_main->insertTab(tab->id(), tab, file.fileName());
    qtw_main->setCurrentIndex(tab->id());

    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();

        const HbLogMessage* msg = HbLogMessage::fromRaw(line);
        if (!msg) {
            qDebug() << "Unreadable line";
            continue;
        }

        tab->addEntry(msg, true);
        delete msg;
    }

    file.close();
}

void LogViewer::onConfigureClicked() {
    LogViewerConfigDialog config_dialog(mConfig, this);
    if (config_dialog.exec() == QDialog::Accepted) {
        mConfig = config_dialog.config();
        mConfig.saveSettings();

        for (LogViewerTab* tab : mTabs) {
            tab->updateView();
        }
    }
}

void LogViewer::onRefreshTimeChanged(int refresh) {
    mProcessTimer.stop();
    mProcessTimer.start(refresh);
}

void LogViewer::onTabCloseRequested(int index) {
    if (index == 0) {
        return; // General tab does not close.
    }

    qtw_main->removeTab(index);
    if (mTabs.contains(index)) {
        delete mTabs.take(index);
    }
}

void LogViewer::processLogMessage() {
    QMutexLocker locker(&mMutexBuffer);

    while (!mTempBuffer.isEmpty()) {
        HbLogMessage* message = mTempBuffer.takeFirst();

        for (LogViewerTab* tab : mTabs) {
            tab->addEntry(message);
        }

        delete message;
    }
}

void LogViewer::onNewTabRequest(quint8 column, const QString& value) {
    ModelFilter* filter = q_check_ptr(new ModelFilter());
    filter->mValue = value;
    filter->mRole = Qt::DisplayRole;
    filter->mFlags = Qt::MatchExactly;

    LogViewerTab* tab =
        q_check_ptr(new LogViewerTab(mTabIds++, mConfig, false, filter, (LogViewerTab::ColumnId)column));
    connect(tab, &LogViewerTab::newTabRequest, this, &LogViewer::onNewTabRequest);
    mTabs.insert(tab->id(), tab);
    qtw_main->insertTab(tab->id(), tab, value);
    qtw_main->setCurrentIndex(tab->id());
}
