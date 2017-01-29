#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

InputInterface::InputInterface(const String &name, Callback callback) : Interface(name), callback([callback](const Message& message, LocalModule*) { callback(message); }) {}
InputInterface::InputInterface(const InputInterface &copy) : Interface(copy), callback(copy.callback) {}
InputInterface::InputInterface(InputInterface &&move) : Interface(std::move(move)), callback(std::move(move.callback)) {}
InputInterface::~InputInterface() {}

//void InputInterface::receive(const Message& message) const { if (callback) callback(message); }
void InputInterface::receive(const Message& message, LocalModule* from) const { if (callback) callback(message, from); }