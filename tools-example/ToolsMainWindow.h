#ifndef TOOLSMAINWINDOW_H
#define TOOLSMAINWINDOW_H

// Qt
// Hb
// Local
#include <ui_ToolsMainWindow.h>

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
            // core
            void testApplicationHelper();
            void testDictionnaryHelper();
            void testEnum();
            void testErrorCode();
            void testMultipleSortFilterProxyModel();
            void testNullable();
            void testSingleton();
            void testSteadyDateTime();
            void testUid();
            void testUidGenerator();
            void testSettings();

            // network
            void testHttpRequester();
            void testTimeoutNetworkReplies();

        public slots:

        private slots:

        signals:

        };
    }
}

#endif // TOOLSMAINWINDOW_H
