#ifndef TOOLSMAINWINDOW_H
#define TOOLSMAINWINDOW_H

// Qt
// Hb
// Local
#include <ui_ToolsMainWindow.h>

class QNetworkAccessManager;

namespace hb
{
    namespace toolsexample
    {

        class ToolsMainWindow : public QMainWindow, private Ui::ToolsMainWindow
        {
            Q_OBJECT

        public:
            explicit ToolsMainWindow( QWidget * parent = nullptr );
            virtual ~ToolsMainWindow();

        private:

        public slots:

        private slots:

        signals:

        };
    }
}

#endif // TOOLSMAINWINDOW_H
