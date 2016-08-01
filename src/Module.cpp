#include <Veritas/Orchestra/Module.h>

using namespace Veritas;
using namespace Orchestra;

Module::Module() {}
Module::~Module() {}

bool Module::isConnectedTo(Module *module) {
    for (Modules::iterator it = connections.begin(); it != connections.end(); it++)
        if (*it == module) return true;
    return false;
}

bool Module::connect(Module *module) {
    if (!isConnectedTo(module)) {

        // This implementation is incomplete and probably broken.
        on("", [](const Message& m) {
            Module* source = any_cast<Module*>(m.getSource());
            Module* destiny = any_cast<Module*>(m.getDestiny());

            if (source == destiny) {
                Message message = m;
                message.dispatch(source, any_cast<Module*>(m.getCallbackData()));
            }
        }, module);

        connections.push_back(module);
        module->connect(this);
        return true;
    } else return false;

    return true;
}

bool Module::disconnect(Module *module) {
    if (isConnectedTo(module)) {
        // TO-DO: remove event listener

        connections.remove(module);
        return true;
    } else return false;
}

void Module::run() {}