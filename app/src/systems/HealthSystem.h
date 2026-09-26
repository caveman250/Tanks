#pragma once

#include "editor/util/ViewportUtil.h"
#include "engine/ecs/System.h"
namespace app
{
    using namespace se;
    class HealthSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();
        void OnUpdate(const ecs::QueryResults& results) override;
    };
}
