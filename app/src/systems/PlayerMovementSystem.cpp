#include "PlayerMovementSystem.h"
#include "components/PlayerComponent.h"
#include "engine/ecs/components/TransformComponent.h"

namespace app
{
    ecs::SystemDeclaration PlayerMovementSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
            .WithComponent<const PlayerComponent>()
            .WithComponent<ecs::components::TransformComponent>();
    }

    void PlayerMovementSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            float dt = Application::Get()->GetDeltaTime();
            const auto& entities = updateData.GetEntities();
            const auto* players = updateData.GetComponentArray<const PlayerComponent>();
            auto* transforms = updateData.GetComponentArray<ecs::components::TransformComponent>();

            for (size_t i = 0; i < entities.size(); ++i)
            {
                const auto& entity = entities[i];
                const auto& player = players[i];
                auto& transform = transforms[i];

                std::vector<float> desiredRotations = {};

                if (player.isMovingUp)
                {
                    transform.pos.x -= player.moveSpeed * dt;
                    desiredRotations.push_back(180.f);
                }

                if (player.isMovingDown)
                {
                    transform.pos.x += player.moveSpeed * dt;
                    desiredRotations.push_back(0.f);
                }

                if (player.isMovingLeft)
                {
                    transform.pos.z += player.moveSpeed * dt;
                    desiredRotations.push_back(270.f);
                }

                if (player.isMovingRight)
                {
                    transform.pos.z -= player.moveSpeed * dt;
                    desiredRotations.push_back(90.f);
                }

                if (desiredRotations.size() > 0)
                {
                    transform.rot.y = std::accumulate(desiredRotations.begin(), desiredRotations.end(), float{}) / desiredRotations.size();

                    if (player.isMovingDown && player.isMovingLeft)
                    {
                        transform.rot.y += 180.f;
                    }
                }
            }
        });
    }
}
