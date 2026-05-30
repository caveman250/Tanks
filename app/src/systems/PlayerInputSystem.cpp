#include "PlayerInputSystem.h"
#include "components/PlayerComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/input/InputComponent.h"
#include "engine/input/InputUtil.h"

namespace app
{
    ecs::SystemDeclaration PlayerInputSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
            .WithComponent<PlayerComponent>()
            .WithSingletonComponent<input::InputComponent>();
    }

    void PlayerInputSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            const auto& entities = updateData.GetEntities();
            auto* players = updateData.GetComponentArray<PlayerComponent>();
            auto* input = updateData.GetSingletonComponent<input::InputComponent>();

            for (size_t i = 0; i < entities.size(); ++i)
            {
                const auto& entity = entities[i];
                auto& player = players[i];

                input::InputUtil::ProcessKeyEvents(entity, input, [&player](const input::KeyEvent& ev)
                {
                    if (ev.state == input::KeyState::Down)
                    {
                        switch (ev.key)
                        {
                            case input::Key::W:
                                player.isMovingUp = true;
                                return true;
                            case input::Key::S:
                                player.isMovingDown = true;
                                return true;
                            case input::Key::A:
                                player.isMovingLeft = true;
                                return true;
                            case input::Key::D:
                                player.isMovingRight = true;
                                return true;
                            default:
                                break;
                        }
                    }

                    return false;
                });

                if (player.isMovingUp && !input::InputUtil::IsKeyDown(input, input::Key::W))
                {
                    player.isMovingUp = false;
                }
                if (player.isMovingDown && !input::InputUtil::IsKeyDown(input, input::Key::S))
                {
                    player.isMovingDown = false;
                }
                if (player.isMovingLeft && !input::InputUtil::IsKeyDown(input, input::Key::A))
                {
                    player.isMovingLeft = false;
                }
                if (player.isMovingRight && !input::InputUtil::IsKeyDown(input, input::Key::D))
                {
                    player.isMovingRight = false;
                }
            }
        });
    }
}
