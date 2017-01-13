#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Messaging;
using namespace Interfacing;

LocalModule::LocalModule() : Module(this), runInterval(0.0f), t0(Clock::now()) {
    //set(InputInterface("RequestConnection").setCallback(&LocalModule::RequestConnection, this));
    //set(InputInterface("NotifyConnection").setCallback(&LocalModule::NotifyConnection, this));
    //set(InputInterface("RequestDisconnection").setCallback(&LocalModule::RequestDisconnection, this));
    //set(InputInterface("NotifyDisconnection").setCallback(&LocalModule::NotifyDisconnection, this));
    //set(OutputInterface("RequestDisconnection"));

    ModuleManager *mm = ModuleManager::getLocalInstance();
    mm->add(this);
}

LocalModule::~LocalModule() {
    //outputInterfaces.at("RequestDisconnection").publish();

    ModuleManager *mm = ModuleManager::getLocalInstance();
    mm->remove(this);
}

void LocalModule::run() {}

void LocalModule::set(InputInterface *interface) { inputInterfaces[interface->getName()] = interface; }
void LocalModule::set(OutputInterface *interface) { outputInterfaces[interface->getName()] = interface; }
const LocalModule::OutputInterfaces& LocalModule::getOutputInterfaces() const { return outputInterfaces; }
const LocalModule::InputInterfaces& LocalModule::getInputInterfaces() const { return inputInterfaces; }

void LocalModule::receive(const Message &message) {
    String interfaceName = message.getInterface();
    try {
        inputInterfaces.at(interfaceName)->receive(message);
    } catch (...) {
        // infinite loop if the module doesn't has the NotifyReport InputInterface
        // send(message.getOrigin(), Message("NotifyReport").set("Report", "Interface not found."));
    }
}

void LocalModule::setRunInterval(float64 seconds) { runInterval = seconds; }
float64 LocalModule::getRunInterval() const { return runInterval; }

/*
void LocalModule::RequestConnection(const Message &message) {
    Module module(message.getOrigin());
    connections.push_back(std::move(module));
    outputInterfaces.at("NotifyConnection").send(module);
}
void LocalModule::NotifyConnection(const Message& message) {
    connections.push_back(Module(message.getOrigin()));
}

void LocalModule::RequestDisconnection(const Message &message) {
    Module module(message.getOrigin());
    outputInterfaces.at("NotifyDisconnection").send(module);
    connections.remove(module);
}

void LocalModule::NotifyDisconnection(const Message& message) {
    connections.remove(Module(message.getOrigin()));
}
*/
