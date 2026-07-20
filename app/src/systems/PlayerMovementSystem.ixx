module;
#include "engine/ecs/System.h"

export module PlayerMovementSystem;
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
