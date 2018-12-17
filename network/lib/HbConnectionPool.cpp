// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbConnectionPool.h>
#include <contract/general/HbKickContract.h>
#include <service/HbNetworkService.h>
#include <service/channel/HbChannelService.h>

using namespace hb::network;

HbConnectionPool::HbConnectionPool(const HbGeneralConfig& config, QObject* parent) : QObject(parent) {
    Q_UNUSED(config)

    mLeaving = false;

    qRegisterMetaType<HbNetworkProtocol::ServerStatus>("HbNetworkProtocol::ServerStatus");
    qRegisterMetaType<HbNetworkProtocol::ClientStatus>("HbNetworkProtocol::ClientStatus");
    qRegisterMetaType<HbNetworkProtocol::UserStatus>("HbNetworkProtocol::UserStatus");
    qRegisterMetaType<HbNetworkProtocol::KickCode>("HbNetworkProtocol::KickCode");
}

bool HbConnectionPool::plugChannel(HbNetworkChannel* channel, networkuid network_uid) {
    HbChannelService* channel_service = getService<HbChannelService>(HbNetworkProtocol::SERVICE_CHANNEL);
    Q_ASSERT(channel_service);

    return channel_service->plugChannel(channel, network_uid);
}

bool HbConnectionPool::unplugChannel(HbNetworkChannel* channel) {
    HbChannelService* channel_service = getService<HbChannelService>(HbNetworkProtocol::SERVICE_CHANNEL);
    Q_ASSERT(channel_service);

    return channel_service->unplugChannel(channel);
}

void HbConnectionPool::setExchanges(HbNetworkExchanges& exchanges) {
    exchanges.plug<HbKickContract>();

    for (HbNetworkService* service : mServices) {
        Q_ASSERT(service);
        service->plugContracts(exchanges);
    }
}

void HbConnectionPool::reset() {
    for (HbNetworkService* service : mServices) {
        Q_ASSERT(service);
        service->reset();
    }
}

HbNetworkService* HbConnectionPool::getService(serviceuid service_uid) {
    if (service_uid >= HbNetworkProtocol::SERVICE_USER) {
        // Service channel will redirect contract to right user channel.
        service_uid = HbNetworkProtocol::SERVICE_CHANNEL;
    }

    return mServices.value(service_uid, nullptr);
}
