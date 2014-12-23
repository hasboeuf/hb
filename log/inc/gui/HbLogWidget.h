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
			explicit HbLogWidget(QWidget *parent = 0);
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
