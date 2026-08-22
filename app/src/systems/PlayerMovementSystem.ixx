export module PlayerMovementSystem;

import System;

namespace app
{
    using namespace se;
    export class PlayerMovementSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();

        void OnUpdate(const ecs::QueryResults&) override;
    };
}
