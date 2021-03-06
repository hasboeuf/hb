#ifndef BASICNETWORKSERVERMAINWINDOW_H
#define BASICNETWORKSERVERMAINWINDOW_H

// Qt
// Hb
#include <com/tcp/HbTcpServer.h>
// Local
#include <ui_BasicServerMainWindow.h>

namespace hb {
namespace networkexample {

class BasicServerMainWindow : public QMainWindow, private Ui::BasicServerMainWindow {
    Q_OBJECT

public:
    explicit BasicServerMainWindow(QWidget* parent = nullptr);
    virtual ~BasicServerMainWindow() = default;

private:
    void onStartClicked();
    void onSendContractClicked();
    void onStopClicked();

    void onServerConnected(networkuid server_uid);
    void onServerDisconnected(networkuid server_uid);
    void onSocketConnected(networkuid server_uid, networkuid socket_uid);
    void onSocketDisconnected(networkuid server_uid, networkuid socket_uid);
    void onSocketContractReceived(networkuid server_uid, networkuid socket_uid, const HbNetworkContract* contract);

    hb::network::HbTcpServer mTcpServer;
};
} // namespace networkexample
} // namespace hb

#endif // BASICNETWORKSERVERMAINWINDOW_H
