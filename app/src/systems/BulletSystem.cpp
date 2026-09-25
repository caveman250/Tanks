#include "BulletSystem.h"

#include "components/BulletComponent.h"
#include "components/PlayerTurretComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/math/util/ViewportUtil.h"
#include "engine/input/InputUtil.h"

namespace app
{
    ecs::SystemDeclaration BulletSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
               .WithComponent<const BulletComponent>()
               .WithComponent<ecs::components::TransformComponent>();
    }

    void BulletSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            const auto& entities = updateData.GetEntities();
            const auto* bullets = updateData.GetComponentArray<const BulletComponent>();
            auto* transforms = updateData.GetComponentArray<ecs::components::TransformComponent>();

            for (size_t i = 0; i < entities.size(); ++i)
            {
                auto& transform = transforms[i];
                const auto& bullet = bullets[i];

                transform.pos += bullet.velocity * 0.1f;
            }
        });
    }
}
