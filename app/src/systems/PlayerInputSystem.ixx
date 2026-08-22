export module PlayerInputSystem;

import System;

namespace app
{
    using namespace se;
    export class PlayerInputSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();

        void OnUpdate(const ecs::QueryResults&) override;
    };
}
