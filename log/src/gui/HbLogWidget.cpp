// Hb
#include <HbLogMessage.h>
// Local
#include <gui/HbLogWidget.h>

using namespace hb::log;

HbLogWidget::HbLogWidget(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(Qt::Tool);
    setWindowModality(Qt::NonModal);
	setWindowTitle("Log console");
	setVisible(true);

	mpLogNotifier = q_check_ptr(new HbLogGuiNotifier());

	mConfig.loadSettings(); // Init config from settings or default xml config file.

    foreach(QString level, HbLogger::MetaLevel::toString())
	{
		if (!level.contains(QLatin1String("_ALL")) && !level.contains(QLatin1String("_NONE")))
		{
			HbLogger::Level enum_level = HbLogger::MetaLevel::fromString(level, HbLogger::LEVEL_TRACE);

			qcb_level->addItem(level, enum_level);
		}
    }

	updateGui();

	connect(mpLogNotifier, &HbLogGuiNotifier::newLogMessage, this, &HbLogWidget::onNewLogMessage, Qt::UniqueConnection);
    connect(qpb_reset,      &QPushButton::clicked, this, &HbLogWidget::onResetClicked);
    connect(qpb_save_as,    &QPushButton::clicked, this, &HbLogWidget::onSaveAsClicked);
    connect(qpb_configure,  &QPushButton::clicked, this, &HbLogWidget::onConfigureClicked);
    connect(qcb_level,      (void (QComboBox::*)(int)) &QComboBox::currentIndexChanged,
            this,           &HbLogWidget::onLevelChanged);


}

HbLogWidget::~HbLogWidget()
{
}

HbLogGuiNotifier* HbLogWidget::logNotifier()
{
    return mpLogNotifier;
}

void HbLogWidget::onResetClicked()
{
    qte_log->clear();
    qDeleteAll(mLoggerMessages.begin(), mLoggerMessages.end());
}

void HbLogWidget::onConfigureClicked()
{
    HbLogConfigDialog config_dialog(mConfig, this);
    if(config_dialog.exec() == QDialog::Accepted)
    {
        mConfig = config_dialog.config();
        mConfig.saveSettings();
    }

    updateGui();
}

void HbLogWidget::onLevelChanged(int pLevel)
{
    if (pLevel < 0) return; // to avoid problems when we close the configure dialog (clear() sets the currentIndex to -1)

    qte_log->clear();

    foreach(HbLogMessage* msg, mLoggerMessages)
    {
        displayNewMessage(msg);
    }
}

void HbLogWidget::onSaveAsClicked()
{
    QString vFileName = QFileDialog::getSaveFileName(this, "Save log", QString(), "");

    QFile vFile(vFileName);
         if (!vFile.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

    QByteArray ba = qte_log->toPlainText().toLatin1();
    const char *data = ba.data();
    vFile.write(data);

    vFile.close();
}


void HbLogWidget::onNewLogMessage(const HbLogMessage& msg)
{
	HbLogMessage* local_msg = new HbLogMessage(msg);

    if(mLoggerMessages.size() == mConfig.maxBuffer())
    {
        delete mLoggerMessages.takeFirst();
    }
    mLoggerMessages.push_back(local_msg);
    displayNewMessage(local_msg);
}


void HbLogWidget::displayNewMessage(const HbLogMessage * msg)
{

    QString vMsg = "<pre style=\"color: " + mConfig.levelColor().value(msg->level()).name() + ";\">" +
            msg->toString() +
            "</pre>";

    qte_log->appendHtml(vMsg);

}

void HbLogWidget::updateGui()
{
	// Icons color
	for (qint32 index = 0; index < qcb_level->count(); ++index)
	{
		QColor color = mConfig.colorByIdLevel(qcb_level->itemData(index).toInt());
		QPixmap pix(10, 10);
		pix.fill(color);
		qcb_level->setItemIcon(index, QIcon(pix));
	}

	// Font
    qte_log->setFont(mConfig.font());

	// Background color
    qte_log->setStyleSheet("background-color: " + mConfig.backgroundColor().name());

	// Log entries colors
    qte_log->clear();
	foreach(HbLogMessage* msg, mLoggerMessages)
    {
        displayNewMessage(msg);
    }
}
