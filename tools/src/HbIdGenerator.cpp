// Hb
#include <HbIdGenerator.h>

using namespace hb::tools;

HbIdGenerator::HbIdGenerator(QObject *parent) :
    QObject(parent), mCurrent(0)
{

}

HbIdGenerator::~HbIdGenerator()
{
	
}

quint16 HbIdGenerator::getUniqueId()
{
    if(!mUnused.isEmpty())
    {
        return mUnused.dequeue();
    }
    else
    {
        return mCurrent++;
    }
    return 1;
}

quint16 HbIdGenerator::getRandomId()
{
	quint16 lowest = 1989;
	quint16 highest = 4000;
    return qrand() % ((highest + 1) - lowest) + lowest;
}

void HbIdGenerator::addUnusedId(quint16 unused_id)
{
    mUnused.enqueue(unused_id);
}
