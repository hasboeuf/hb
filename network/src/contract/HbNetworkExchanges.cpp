// Local
#include <contract/HbNetworkExchanges.h>

using namespace hb::network;

HbNetworkExchanges::~HbNetworkExchanges()
{
    foreach(const Contracts & contracts, _contracts)
    {
        foreach(HbNetworkContract * contract, contracts)
        {
            delete contract;
        }
    }
}


bool HbNetworkExchanges::add(HbNetworkContract * contract)
{
    if( !contract )
    {
        return false;
    }


    Contracts & contracts = _contracts[ contract->service() ];
    HbNetworkContract * existing_contract = contracts.value( contract->code(), nullptr );

    if ( existing_contract )
    {
        delete contract;
    }
    else
    {
        contracts.insert( contract->code(), contract );
    }

    return true;
}

bool HbNetworkExchanges::remove( HbNetworkContract * contract )
{
    if( !contract )
    {
        return false;
    }

    HbNetworkContract * existing_contract = _contracts.value( contract->service() ).value( contract->code(), nullptr );

    if ( contract != existing_contract)
    {
        delete contract;
    }

    if ( existing_contract )
    {
        Contracts & contracts = _contracts[ existing_contract->service() ];
        contracts.remove( existing_contract->code() );

        if (contracts.isEmpty() )
        {
            _contracts.remove( existing_contract->service() );
        }

        delete existing_contract;
        return true;
    }
    else
    {
        return false;
    }
}

bool HbNetworkExchanges::registered( HbNetworkContract::Service service, HbNetworkContract::Code code ) const
{
    return _contracts.value( service ).contains( code );
}

HbNetworkContract * HbNetworkExchanges::contract( HbNetworkContract::Service service, HbNetworkContract::Code code) const
{
    HbNetworkContract * result = nullptr;

    if( _contracts.contains( service ) )
    {
        Contracts contracts = _contracts.value( service );
        if( contracts.contains( code ) )
        {
            result = contracts.value( code, nullptr );
        }
    }
    return result;
//    return _contracts.value( service ).value( code, nullptr );
}
