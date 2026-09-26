#include "HealthSystem.h"

#include "components/BulletComponent.h"
#include "components/HealthComponent.h"
#include "components/PlayerTurretComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/math/util/ViewportUtil.h"
#include "engine/input/InputUtil.h"

namespace app
{
    ecs::SystemDeclaration HealthSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
               .WithComponent<const HealthComponent>();
    }

    void HealthSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            const auto& entities = updateData.GetEntities();
            const auto* healthComps = updateData.GetComponentArray<const HealthComponent>();

            for (size_t i = 0; i < entities.size(); ++i)
            {
                const auto& entity = entities[i];
                const auto& health = healthComps[i];

                if (health.health <= 0)
                {
                    Application::Get()->GetWorld()->DestroyEntity(entity);
                }
            }
        });
    }
}
