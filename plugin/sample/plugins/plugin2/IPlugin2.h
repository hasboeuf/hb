#ifndef IPLUGIN2_H
#define IPLUGIN2_H

namespace hb
{
    namespace pluginexample
    {
        class IPlugin2
        {
        public:
            virtual bool doSomething() const = 0;
        };
    }
}

#endif // IPLUGIN2_H