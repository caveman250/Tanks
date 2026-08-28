#pragma once
#include "engine/ecs/System.h"

namespace app
{
    using namespace se;
    class PlayerInputSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();

        void OnUpdate(const ecs::QueryResults&) override;
    };
}
