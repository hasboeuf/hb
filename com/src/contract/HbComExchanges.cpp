// Local
#include <contract/HbComExchanges.h>

using namespace hb::com;

HbComExchanges::~HbComExchanges()
{
    foreach( const Contracts & contracts, mContracts )
    {
        foreach( HbComContract * contract, contracts )
        {
            delete contract;
        }
    }
}

HbComExchanges & HbComExchanges::operator=( const HbComExchanges & source )
{
    if( &source != this )
    {
        foreach( const Contracts & contracts, source.mContracts )
        {
            foreach( HbComContract * contract, contracts )
            {
                add( contract->create() );
            }
        }
    }
    return *this;
}


bool HbComExchanges::add( HbComContract * contract )
{
    if( !contract )
    {
        return false;
    }

    Contracts & contracts = mContracts[contract->header().service()];
    HbComContract * existing_contract = contracts.value( contract->header().code(), nullptr );

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

bool HbComExchanges::remove( HbComContract * contract )
{
    if( !contract )
    {
        return false;
    }

    Contracts & contracts = mContracts[contract->header().service()];
    HbComContract * existing_contract = contracts.value( contract->header().code(), nullptr );

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

bool HbComExchanges::registered( servuid service, codeuid code ) const
{
    return mContracts.value( service ).contains( code );
}

HbComContract * HbComExchanges::contract( const HbComHeader & header ) const
{
    HbComContract * contract = nullptr;

    if( mContracts.contains( header.service() ) )
    {
        Contracts contracts = mContracts.value( header.service() );
        if( contracts.contains( header.code() ) )
        {
            HbComContract * reference = contracts.value( header.code(), nullptr );
            q_assert_ptr( reference );
            contract = reference->create();
            contract->setHeader( header );
        }
    }
    return contract;
}
