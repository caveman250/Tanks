export module PlayerCameraSystem;

import System;

namespace app
{
    using namespace se;
    export class PlayerCameraSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();

        void OnUpdate(const ecs::QueryResults&) override;
    };
}
