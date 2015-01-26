/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGWIDGET_H
#define HBLOGWIDGET_H

// Qt
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QDebug>
#include <QtGui/QColor>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
// Hb
#include <HbLogGuiNotifier.h>
// Local
#include <ui_HbLogWidget.h>
#include <gui/HbLogConfigDialog.h>
#include <gui/HbLogConfig.h>


namespace hb
{

	namespace log
	{
		class HbLogMessage;

		class HB_LOG_DECL HbLogWidget : public QDialog, private Ui::HbLogWidget
		{

			Q_OBJECT

		public:
            explicit HbLogWidget(QWidget *parent = nullptr);
			~HbLogWidget();

			HbLogGuiNotifier* logNotifier();

		public slots:

		private slots :
			void onResetClicked();
			void onSaveAsClicked();
			void onConfigureClicked();
			void onLevelChanged(int);

			void onNewLogMessage(const HbLogMessage& msg);

		private:
			HbLogGuiNotifier* mpLogNotifier;

			QString mFileName;
			HbLogConfig mConfig;
			QList<HbLogMessage*> mLoggerMessages;

		private:
			void displayNewMessage(const HbLogMessage *msg);
			void updateGui();
		};
	}
}

#endif // HBLOGWIDGET_H
