// Hb
#include <inputs/HbLogAbstractInput.h>

using namespace hb::log;

HbLogAbstractInput::HbLogAbstractInput( InputType type )
{
    mType = type;
}


HbLogAbstractInput::InputType HbLogAbstractInput::type() const
{
	return mType;
}
