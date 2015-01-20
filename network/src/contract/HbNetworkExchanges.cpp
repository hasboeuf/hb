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

HbNetworkExchanges & HbNetworkExchanges::operator=( const HbNetworkExchanges & source )
{
    if( &source != this )
    {
        foreach(const Contracts & contracts, source._contracts)
        {
            foreach(HbNetworkContract * contract, contracts)
            {
                add( contract->copy() );
            }
        }
    }
    return *this;
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

    Contracts & contracts = _contracts[ contract->service() ];
    HbNetworkContract * existing_contract = contracts.value( contract->code(), nullptr );

    delete contract;

    if ( existing_contract )
    {
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

bool HbNetworkExchanges::registered( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code ) const
{
    return _contracts.value( service ).contains( code );
}

HbNetworkContract * HbNetworkExchanges::contract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code) const
{
    HbNetworkContract * contract = nullptr;

    if( _contracts.contains( service ) )
    {
        Contracts contracts = _contracts.value( service );
        if( contracts.contains( code ) )
        {
            HbNetworkContract * reference = contracts.value( code, nullptr );
            q_assert_ptr( reference );
            contract = reference->copy();
        }
    }
    return contract;
//    return _contracts.value( service ).value( code, nullptr );
}
