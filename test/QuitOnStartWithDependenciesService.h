#pragma once

#include <ichor/Service.h>
#include "UselessService.h"

using namespace Ichor;

struct QuitOnStartWithDependenciesService final : public Service<QuitOnStartWithDependenciesService> {
    QuitOnStartWithDependenciesService(DependencyRegister &reg, IchorProperties props, DependencyManager *mng) : Service(std::move(props), mng) {
        reg.registerDependency<UselessService>(this, false);
    }
    ~QuitOnStartWithDependenciesService() final = default;
    bool start() final {
        getManager()->pushEvent<QuitEvent>(getServiceId());
        return true;
    }

    bool stop() final {
        return true;
    }

    void addDependencyInstance(UselessService *) {
    }

    void removeDependencyInstance(UselessService *) {
    }
};