// Local
#include <contract/HbNetworkExchanges.h>

using namespace hb::network;

HbNetworkExchanges::~HbNetworkExchanges()
{
    foreach(const Contracts & contracts, mContracts)
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
        foreach(const Contracts & contracts, source.mContracts)
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

    Contracts & contracts = mContracts[ contract->header().service() ];
    HbNetworkContract * existing_contract = contracts.value( contract->header().code(), nullptr );

    if ( existing_contract )
    {
        delete contract;
    }
    else
    {
        contracts.insert( contract->header().code(), contract );
    }

    return true;
}

bool HbNetworkExchanges::remove( HbNetworkContract * contract )
{
    if( !contract )
    {
        return false;
    }

    Contracts & contracts = mContracts[ contract->header().service() ];
    HbNetworkContract * existing_contract = contracts.value( contract->header().code(), nullptr );

    delete contract;

    if ( existing_contract )
    {
        contracts.remove( existing_contract->header().code() );

        if ( contracts.isEmpty() )
        {
            mContracts.remove( existing_contract->header().service() );
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
    return mContracts.value( service ).contains( code );
}

HbNetworkContract * HbNetworkExchanges::contract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code) const
{
    HbNetworkContract * contract = nullptr;

    if( mContracts.contains( service ) )
    {
        Contracts contracts = mContracts.value( service );
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
