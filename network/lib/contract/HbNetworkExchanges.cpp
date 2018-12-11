// Local
#include <contract/HbNetworkExchanges.h>

using namespace hb::network;

HbNetworkExchanges::~HbNetworkExchanges() {
    for (const Contracts& contracts : mContracts) {
        for (HbNetworkContract* contract : contracts) {
            delete contract;
        }
    }
}

HbNetworkExchanges& HbNetworkExchanges::operator=(const HbNetworkExchanges& source) {
    if (&source != this) {
        for (const Contracts& contracts : source.mContracts) {
            for (HbNetworkContract* contract : contracts) {
                add(contract->create());
            }
        }
    }
    return *this;
}

bool HbNetworkExchanges::add(HbNetworkContract* contract) {
    if (!contract) {
        return false;
    }

    Contracts& contracts = mContracts[contract->header().service()];
    HbNetworkContract* existing_contract = contracts.value(contract->header().code(), nullptr);

    if (existing_contract) {
        delete contract;
    } else {
        contracts.insert(contract->header().code(), contract);
    }

    return true;
}

bool HbNetworkExchanges::remove(HbNetworkContract* contract) {
    if (!contract) {
        return false;
    }

    Contracts& contracts = mContracts[contract->header().service()];
    HbNetworkContract* existing_contract = contracts.value(contract->header().code(), nullptr);

    delete contract;

    if (existing_contract) {
        contracts.remove(existing_contract->header().code());

        if (contracts.isEmpty()) {
            mContracts.remove(existing_contract->header().service());
        }

        delete existing_contract;
        return true;
    } else {
        return false;
    }
}

bool HbNetworkExchanges::registered(serviceuid service, codeuid code) const {
    return mContracts.value(service).contains(code);
}

HbNetworkContract* HbNetworkExchanges::contract(const HbNetworkHeader& header) const {
    HbNetworkContract* contract = nullptr;

    if (mContracts.contains(header.service())) {
        Contracts contracts = mContracts.value(header.service());
        if (contracts.contains(header.code())) {
            HbNetworkContract* reference = contracts.value(header.code(), nullptr);
            Q_ASSERT(reference);
            contract = reference->create();
            contract->setHeader(header);
        }
    }
    return contract;
}
