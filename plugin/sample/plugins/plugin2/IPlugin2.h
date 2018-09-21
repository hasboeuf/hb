#ifndef IPLUGIN2_H
#define IPLUGIN2_H

namespace hb {
namespace pluginexample {
class IPlugin2 {
public:
    virtual bool doSomething() const = 0;
};
} // namespace pluginexample
} // namespace hb

#endif // IPLUGIN2_H
