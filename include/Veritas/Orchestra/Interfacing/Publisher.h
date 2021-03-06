#pragma once
#include <Veritas/Orchestra/Interfacing/Sender.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Publisher : protected Sender {
                public:
                    Publisher(const Computing::LocalModule& module);
                    Publisher(const Computing::LocalModule* module);

                    void publish(const Data::String& interface, const Messaging::Content &content = Messaging::Content()) const;
            };
        }
    }
}
