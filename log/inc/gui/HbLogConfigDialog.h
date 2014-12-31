/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGCONFIGDIALOG_H
#define HBLOGCONFIGDIALOG_H

// Local
#include <HbLog.h>
#include <ui_HbLogConfigDialog.h>
#include <gui/HbLogConfig.h>

namespace hb
{
	namespace log
	{

		class HbLogConfigDialog : public QDialog, private Ui::HbLogConfigDialog
		{
			Q_OBJECT
			Q_DISABLE_COPY(HbLogConfigDialog)


		public:

			HbLogConfigDialog() = delete;
			HbLogConfigDialog(HbLogConfig & pConfig, QWidget *parent = 0);
			virtual ~HbLogConfigDialog() = default;

			const HbLogConfig & config() const;

		private:
			void saveConfig();
			void updateGui();

		private slots :

			void onFontClicked();
			void onColorClicked(int color_id);
			void onBackgroundColorClicked();
			void onSaveClicked();
			void onResetClicked();
			void onImportClicked();
			void onExportClicked();


		private:

			HbLogConfig mConfig;

			QButtonGroup qbg_colors;
			QList< QLineEdit * > qfl_editor_fields; // Use when saving.
		};
	}
}

#endif // HBLOGCONFIGDIALOG_H
