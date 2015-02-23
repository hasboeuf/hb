#include <service/auth/HbClientAuthLoginObject.h>

using namespace hb::network;

HbClientAuthLoginObject::HbClientAuthLoginObject( authstgy strategy )
{
    mStrategy = strategy;
}

authstgy HbClientAuthLoginObject::strategy() const
{
    return mStrategy;
}
