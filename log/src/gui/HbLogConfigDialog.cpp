// Qt
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
// Hb
#include <HbLogService.h>
// Local
#include <gui/HbLogConfigDialog.h>

using namespace hb::log;


HbLogConfigDialog::HbLogConfigDialog(HbLogConfig& pConfig, QWidget *parent) :
QDialog(parent), mConfig(pConfig)
{
    setupUi(this);

    QMenu* save_menu = new QMenu(qtb_save);
    QAction* action_import = save_menu->addAction("Import...");
    QAction* action_export = save_menu->addAction("Export...");
    qtb_save->setMenu(save_menu);

    connect(qpb_cancel,    &QPushButton::clicked, this, &HbLogConfigDialog::reject);
    connect(qtb_save,      &QToolButton::clicked, this, &HbLogConfigDialog::onSaveClicked);
    connect(qpb_reset,     &QPushButton::clicked, this, &HbLogConfigDialog::onResetClicked);
    connect(qpb_font,      &QPushButton::clicked, this, &HbLogConfigDialog::onFontClicked);
    connect(qpb_bck_color, &QPushButton::clicked, this, &HbLogConfigDialog::onBackgroundColorClicked);
    connect(action_import, &QAction::triggered,   this, &HbLogConfigDialog::onImportClicked);
    connect(action_export, &QAction::triggered,   this, &HbLogConfigDialog::onExportClicked);
    connect(&qbg_colors,   (void (QButtonGroup::*)(int)) &QButtonGroup::buttonClicked, this, &HbLogConfigDialog::onColorClicked);

    
    // Level colors
    QMap<quint32, QColor>::const_iterator iC = mConfig.levelColor().constBegin();
    while (iC != mConfig.levelColor().constEnd())
    {
        QLabel*      label = q_check_ptr(new QLabel(QStringLiteral("Level %1").arg(iC.key())));
        QPushButton* button = q_check_ptr(new QPushButton(QStringLiteral("Choose...")));
        button->setFixedHeight(20);

        QHBoxLayout* h_layout = q_check_ptr(new QHBoxLayout());
        h_layout->addStretch();
        h_layout->addWidget(button);

        qfl_colors->addRow(label, h_layout);

        qbg_colors.addButton(button, iC.key());

        ++iC;
    }

    updateGui();

}

void HbLogConfigDialog::updateGui()
{
    // Max buffer
    qsb_buffer->setValue(mConfig.maxBuffer());

    // Colors
    foreach(QAbstractButton* vButton, qbg_colors.buttons())
    {
        QColor c = mConfig.colorByIdLevel(qbg_colors.id(vButton));

        QPixmap vPix(10, 10);
        vPix.fill(c);

        vButton->setIcon(QIcon(vPix));
    }

    QPixmap vPix(10, 10);
    vPix.fill(mConfig.backgroundColor());
    qpb_bck_color->setIcon(QIcon(vPix));
}

void HbLogConfigDialog::onFontClicked()
{
    bool ok = false;
    QFont vFont = QFontDialog::getFont(&ok, mConfig.font(), this, QStringLiteral("Select a font"));

    if (ok)
    {
        mConfig.setFont(vFont);
    }
}

void HbLogConfigDialog::onColorClicked(int pId)
{
    QColor vColor = QColorDialog::getColor(mConfig.colorByIdLevel(pId), this, QStringLiteral("Select a color"));
    mConfig.setColorById(pId, vColor);

    QPixmap vPix(10, 10);
    vPix.fill(vColor);
    qbg_colors.button(pId)->setIcon(QIcon(vPix));
}

void HbLogConfigDialog::onBackgroundColorClicked()
{
    QColor vColor = QColorDialog::getColor(mConfig.backgroundColor(), this, QStringLiteral("Select a color"));
    mConfig.setBackgroundColor(vColor);

    QPixmap vPix(10, 10);
    vPix.fill(vColor);
    qpb_bck_color->setIcon(QIcon(vPix));
}

void HbLogConfigDialog::onSaveClicked()
{
    saveConfig();

    accept();

}

void HbLogConfigDialog::saveConfig()
{
    // Save the GUI values in the local model.
    // NOTE: Colors are saved a little at a time in the local model.

    // Max buffer
    mConfig.setMaxBuffer(qsb_buffer->value());
}

void HbLogConfigDialog::onResetClicked()
{
    mConfig = HbLogConfig::importConfigXml(QString::fromLatin1(HbLogConfig::msDefaultConfigXml));
    accept();
}

void HbLogConfigDialog::onImportClicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, QStringLiteral("Import log configuration"), QStringLiteral(""), "Config file (*.hblog)");
    if (file_path.isEmpty())
    {
        return;
    }

    HbLogConfig config = HbLogConfig::importConfigXml(file_path);

    if (config.isValid())
    {
        mConfig = config;
        updateGui();
    }
}

void HbLogConfigDialog::onExportClicked()
{
    saveConfig();

    QString file_path = QFileDialog::getSaveFileName(this, QStringLiteral("Export log configuration"), QStringLiteral(""), "Config file (*.hblog)");
    if (file_path.isEmpty())
    {
        return;
    }

    if (!HbLogConfig::exportConfigXml(file_path, mConfig))
    {
        HbError("Exporting log config file failed.");
    }
}

const HbLogConfig & HbLogConfigDialog::config() const
{
    return mConfig;
}
