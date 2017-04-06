#include <Veritas/Orchestra/Interfacing/Replier.h>
#include <Veritas/Orchestra/Messaging/Messaging.h>
#include <Veritas/Orchestra/Module.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

String extract(const String& string) {
    String result("Reply");
    String::iterator it = string.begin();
    for (; it != string.end() && *it != '-'; it++);
    for (; it != string.end(); it++) result.append(*it);
    return result;
}

Replier::Replier(const Message &message)
    : requestID((Number) message.get("RequestID"))
    , origin(message.getOrigin())
    , sender((LocalModule*) message.getDestiny().getLocalAddress())
    , interface(extract(message.getInterface()))
{}

void Replier::reply(const Message &message) const {
    sender.send(interface, Module(origin), Message().set("RequestID", requestID).set("Content", message.getContent()));
}