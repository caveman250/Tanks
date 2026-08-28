#include "PlayerCameraSystem.h"
#include "components/PlayerComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/ecs/components/TransformComponent.h"

namespace app
{
    ecs::SystemDeclaration PlayerCameraSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration()
            .WithComponent<const PlayerComponent>()
            .WithComponent<ecs::components::TransformComponent>()
            .WithSingletonComponent<camera::ActiveCameraComponent>();
    }

    void PlayerCameraSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::SingleThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            auto* app = Application::Get();
            const auto& entities = updateData.GetEntities();
            auto* transforms = updateData.GetComponentArray<ecs::components::TransformComponent>();
            auto* camera = updateData.GetSingletonComponent<camera::ActiveCameraComponent>();

            for (size_t i = 0; i < entities.size(); ++i)
            {
                auto& transform = transforms[i];

                camera->pos.x = transform.pos.x;
                camera->pos.y = 50.f;
                camera->pos.z = transform.pos.z;
                camera->rot.y = 90.f;
                camera->rot.x = 90.f;

                math::Vec3 forward(cos(math::Radians(camera->rot.x)) * sin(math::Radians(camera->rot.y)),
                             sin(math::Radians(camera->rot.x)),
                             cos(math::Radians(camera->rot.x)) * cos(math::Radians(camera->rot.y)));

                math::Vec3 right = math::Vec3(
                    sin(math::Radians(camera->rot.y) - 3.14f / 2.0f),
                    0,
                    cos(math::Radians(camera->rot.y) - 3.14f / 2.0f));

                math::Vec3 up = math::Cross(right, forward);
                camera->view = math::LookAt(
                        camera->pos,
                        camera->pos + math::Vec3(0.f, -1.f, 0.f),
                        up);

                auto gameViewport = app->GetGameViewportSize();
                camera->proj = math::Perspective(math::Radians(45.f), (float)gameViewport.x / (float)gameViewport.y,.1f, 100.f);
            }
        });
    }
}
