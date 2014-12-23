// Qt
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
// Hb
#include <HbLogService.h>
// Local
#include <LogViewerConfigDialog.h>

using namespace hb::logviewer;


LogViewerConfigDialog::LogViewerConfigDialog(LogViewerConfig& pConfig, QWidget *parent) :
    QDialog(parent), mConfig(pConfig)
{
    setupUi( this );

	QMenu* save_menu = new QMenu(qtb_save);
	QAction* action_import = save_menu->addAction("Import...");
	QAction* action_export = save_menu->addAction("Export...");
	qtb_save->setMenu(save_menu);

	connect(qpb_cancel,     &QPushButton::clicked, this, &LogViewerConfigDialog::reject);
	connect(qtb_save,       &QToolButton::clicked, this, &LogViewerConfigDialog::onSaveClicked);
    connect(qpb_reset,      &QPushButton::clicked, this, &LogViewerConfigDialog::onResetClicked);
	connect(qpb_font,       &QPushButton::clicked, this, &LogViewerConfigDialog::onFontClicked);
	connect(qpb_bck_color,	&QPushButton::clicked, this, &LogViewerConfigDialog::onBackgroundColorClicked);
	connect(qpb_add_editor,	&QPushButton::clicked, this, &LogViewerConfigDialog::onAddEditorClicked);
	connect(action_import,  &QAction::triggered,   this, &LogViewerConfigDialog::onImportClicked);
	connect(action_export,  &QAction::triggered,   this, &LogViewerConfigDialog::onExportClicked);
	connect(&qbg_colors,	(void (QButtonGroup::*)(int)) &QButtonGroup::buttonClicked,   this, &LogViewerConfigDialog::onColorClicked);

	// Level colors
	QMap<quint32, QColor>::const_iterator iC = mConfig.levelColor().constBegin();
	while(iC != mConfig.levelColor().constEnd())
	{
        QLabel*      label = q_check_ptr( new QLabel( QStringLiteral( "Level %1" ).arg( iC.key() ) ) );
        QPushButton* button = q_check_ptr( new QPushButton( QStringLiteral( "Choose..." ) ) );
		button->setFixedHeight(20);

		QHBoxLayout* h_layout = q_check_ptr( new QHBoxLayout() );
		h_layout->addStretch();
		h_layout->addWidget(button);

		qfl_colors->addRow(label, h_layout);

		qbg_colors.addButton(button, iC.key());

		++iC;
	}

    updateGui();

}

void LogViewerConfigDialog::updateGui()
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

	// Project folders
	qte_project_folders->clear();
	foreach(QString project_folder, mConfig.projectFolders())
	{
		qte_project_folders->append(project_folder);
	}

	// Editors
	qcb_default->clear();
	while (QLayoutItem *item = qfl_editors->takeAt(0))
	{
		delete item->widget();
		delete item;
	}

	QMap<QString, QString> editors = mConfig.editors();
	QString default_editor = mConfig.defaultEditor();
	QMap<QString, QString>::const_iterator it = editors.constBegin();
	while (it != editors.constEnd())
	{
		QString name = it.key();
		QString path = it.value();

		addEditorField(name, path);
		qcb_default->addItem(name);

		++it;
	}
	qcb_default->setCurrentIndex(qcb_default->findText(default_editor));
}

void LogViewerConfigDialog::addEditorField(QString name, QString cmd)
{
	QLineEdit* label = q_check_ptr( new QLineEdit(name) );
	QLineEdit* field = q_check_ptr( new QLineEdit(cmd) );

	connect(label, &QLineEdit::textEdited, this, &LogViewerConfigDialog::onEditorNameChanged);
	
	qfl_editor_fields.append(field); // Used when saving.

	qfl_editors->addRow(label, field);
}


void LogViewerConfigDialog::onFontClicked()
{
    bool ok = false;
    QFont vFont = QFontDialog::getFont( &ok, mConfig.font(), this, QStringLiteral( "Select a font" ) );

    if(ok)
    {
        mConfig.setFont(vFont);
    }
}

void LogViewerConfigDialog::onColorClicked(int pId)
{
    QColor vColor = QColorDialog::getColor( mConfig.colorByIdLevel( pId ), this, QStringLiteral( "Select a color" ) );
    mConfig.setColorById(pId, vColor);

    QPixmap vPix(10, 10);
    vPix.fill(vColor);
    qbg_colors.button(pId)->setIcon(QIcon(vPix));
}

void LogViewerConfigDialog::onBackgroundColorClicked()
{
    QColor vColor = QColorDialog::getColor( mConfig.backgroundColor(), this, QStringLiteral( "Select a color" ) );
    mConfig.setBackgroundColor(vColor);

    QPixmap vPix(10, 10);
    vPix.fill(vColor);
    qpb_bck_color->setIcon(QIcon(vPix));
}

void LogViewerConfigDialog::onAddEditorClicked()
{
    addEditorField( QString(), QString() );
}

void LogViewerConfigDialog::onEditorNameChanged()
{
	int current_index = qcb_default->currentIndex();

	qcb_default->clear();

	foreach(QLineEdit* field, qfl_editor_fields)
	{
		if (!field) continue;
		QLineEdit* label = qobject_cast<QLineEdit*>(qfl_editors->labelForField(field));
		if (!label) continue;

		QString editor_name = label->text();
		if (!editor_name.isEmpty())
		{
			qcb_default->addItem(editor_name);
		}
	}

	qcb_default->setCurrentIndex(current_index);
}

void LogViewerConfigDialog::onSaveClicked()
{
	saveConfig();

	accept();

}

void LogViewerConfigDialog::saveConfig()
{
	// Save the GUI values in the local model.
	// NOTE: Colors are saved a little at a time in the local model.

	// Max buffer
	mConfig.setMaxBuffer(qsb_buffer->value());

	// Project folders
	QStringList folders = qte_project_folders->toPlainText().split(QChar::LineFeed, QString::SkipEmptyParts);
	mConfig.resetProjectFolders();
	foreach(QString folder, folders)
	{
		mConfig.addProjectFolder(folder);
	}

	// Editors
	mConfig.setDefaultEditor(qcb_default->currentText());
	mConfig.resetEditors();

	foreach(QLineEdit* field, qfl_editor_fields)
	{
		if (!field) continue;
		QLineEdit* label = qobject_cast<QLineEdit*>(qfl_editors->labelForField(field));
		if (!label) continue;

		QString editor_name = label->text();
		QString editor_cmd = field->text();

		if (!(editor_name.isEmpty() || editor_cmd.isEmpty()))
		{
			mConfig.addEditor(editor_name, editor_cmd);
		}
	}
}


void LogViewerConfigDialog::onResetClicked()
{
	mConfig = LogViewerConfig::importConfigXml(QString::fromLatin1(LogViewerConfig::msDefaultConfigXml));
	accept();
}

void LogViewerConfigDialog::onImportClicked()
{
	QString file_path = QFileDialog::getOpenFileName(this, QStringLiteral("Import log configuration"), QStringLiteral(""), "Config file (*.hblog)");
	if (file_path.isEmpty())
	{
		return;
	}

	LogViewerConfig config = LogViewerConfig::importConfigXml(file_path);

	if (config.isValid())
	{
		mConfig = config;
		updateGui();
	}
}

void LogViewerConfigDialog::onExportClicked()
{
	saveConfig();

	QString file_path = QFileDialog::getSaveFileName(this, QStringLiteral("Export log configuration"), QStringLiteral(""), "Config file (*.hblog)");
	if (file_path.isEmpty())
	{
		return;
	}

	if (!LogViewerConfig::exportConfigXml(file_path, mConfig))
	{
		HbError("Exporting log config file failed.");
	}
}

const LogViewerConfig & LogViewerConfigDialog::config() const
{
    return mConfig;
}
