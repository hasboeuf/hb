#ifndef BASICNETWORKUSERMAINWINDOW_H
#define BASICNETWORKUSERMAINWINDOW_H

// Qt
// Hb
#include <com/tcp/HbTcpClient.h>
// Local
#include <ui_BasicUserMainWindow.h>

namespace hb {
namespace networkexample {

class BasicUserMainWindow : public QMainWindow, private Ui::BasicUserMainWindow {
    Q_OBJECT

public:
    explicit BasicUserMainWindow(QWidget* parent = nullptr);
    virtual ~BasicUserMainWindow() = default;

private:
    void onStartClicked();
    void onSendContractClicked();
    void onStopClicked();

    void onClientConnected(networkuid client_uid);
    void onClientDisconnected(networkuid client_uid);
    void onClientContractReceived(networkuid client_uid, const HbNetworkContract* contract);

    hb::network::HbTcpClient mTcpClient;
};
} // namespace networkexample
} // namespace hb

#endif // BASICNETWORKUSERMAINWINDOW_H
